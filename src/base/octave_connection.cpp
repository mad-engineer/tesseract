/* Copyright (C) 2011 Tesseract Project
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <QDir>
#include <QFile>
#include <QThread>
#include <QMessageBox>
#include <QTextCursor>

#include "config.hpp"
#include "projects.hpp"
#include "octave_connection.hpp"

extern QString configPath();
extern QString projectsPath();

using std::unique_ptr;

void Sleep::micro_sleep( unsigned long u_seconds )
{
	usleep( u_seconds );
}

OctaveConnection::OctaveConnection( QObject * parent )
: QProcess( parent )
{
	octave_path.clear();

	init_regular_expresions();

	error_buffer.open( QBuffer::ReadOnly );

	QObject::connect( this , SIGNAL( readyReadStandardOutput()), this, SLOT(octaveOutputSlot()));
	QObject::connect( this , SIGNAL( readyReadStandardError()), this, SLOT(octaveErrorOutputSlot()));
	QObject::connect( this , SIGNAL( finished(int, QProcess::ExitStatus)), this, SLOT(octaveFinished(int, QProcess::ExitStatus)) );
}

void OctaveConnection::init_regular_expresions()
{
	//Used in octaveOutputSlot
	regexp_octave_prompt.setPattern("octave:[0-9]+>");
	regexp_octave_prompt2.setPattern("octave:[0-9]+\\+>");
	regexp_actual_debug_line_column.setPattern("^([a-zA-Z_]\\w*:)+ line ([0-9]+), column ([0-9]+)$");
}

void OctaveConnection::setOctavePath( const QString &path )
{
	octave_path = path;
}

QString OctaveConnection::getOctavePath()
{
	return octave_path;
}

void OctaveConnection::startOctave( bool quiet )
{
	QString extra_args = getConfig("octave_arguments");

	instructions_left_no = 0;
	debugging = false;

	bool ok;

	QString version = tr( "Not found" );

	{
		QProcess in(this);
		printf("[OctaveConnection::startOctave] Octave path: %s\n", octave_path.toLocal8Bit().data() );
		in.start("\"" + octave_path+"\" --version" , QIODevice::ReadOnly );
		
		if( in.waitForStarted() && in.waitForFinished() )
		{
			const QByteArray buf=in.readAll();
			const QRegExp rx("GNU Octave, version ([0-9]*)\\.([0-9]*)\\.([0-9]*)");

			if( rx.indexIn(buf) >= 0 )
			{
				version=rx.cap(1)+"."+rx.cap(2)+"."+rx.cap(3);
				
				const int ver0 = rx.cap(1).toInt();
				const int ver1 = rx.cap(2).toInt();
				const int ver2 = rx.cap(3).toInt();
				
				printf("[OctaveConnection::startOctave] Octave version: %s (%d.%d.%d)\n", version.toLocal8Bit().data(), ver0, ver1, ver2 );
				
				ok = (ver0==3 && ver1>=2) || (ver0>3);;
			}

			in.close();
		}
	}

	if( ! ok )
	{
		printf( "Exit code %d\n" , ok );

		unique_ptr<QMessageBox> msgBox( new QMessageBox() );
		msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
		msgBox->setStandardButtons( QMessageBox::Ok );
		msgBox->setWindowTitle( tr("Warning") );
		
		msgBox->setText
		( 
			tr
			(
				"QtOctave requires Octave version 3.2.0 or better.\nYou can select your Octave executable in Config/General Configuration/Octave/Octave Path.\n\nYour version is: "
			) +version
		);

		msgBox->setIcon(QMessageBox::Warning);
		msgBox->setModal( true ); // if you want it non-modal
		msgBox->open( this, SLOT(msgBoxClosed(QAbstractButton*)) );

		//... do something else, without blocking

		return;
	}

	if( quiet )
	{
		start("\""+octave_path+"\" --eval \"PS1(\'\');PS2(\'\');\" --persist --no-history -q -i "+extra_args);
	}
	else
	{
		QString command("\""+octave_path+"\"  --eval \"PS1(\'octave:\\#>\');PS2(\'octave:\\#+>\');addpath('" + scriptsPath() + "')\"  --persist --no-history -i "+extra_args);
		start(command);
	}

	if( ! waitForStarted() )
	{
		QMessageBox::critical (NULL, tr("Warning"), tr("QtOctave in:\n")+octave_path+tr("\nCouldn't be opened."));
	}

	if( getConfig( "easy_plot_active" ) == "true" )
	{
		QString path = getConfig( "easy_plot_path" );

		if( path.isEmpty() )
		{
			command_enter( "gnuplot_binary(\"easy_plot\")" );
		}
		else
		{
			command_enter( "gnuplot_binary(\"" + path + "\")" );
		}
	}

	loadScripts();
}

void OctaveConnection::loadScripts()
{
	const QStringList filters( "*.m" );

	const QFileInfoList list = QDir(scriptsPath()).entryInfoList( filters );
	
	QString _command( "__qtoctave_ps2=PS2();PS2('');__qtoctave_ps1=PS1();PS1('');\n" );

	for ( int i = 0 ; i < list.size() ; ++i ) 
	{
		const QFileInfo fileInfo = list.at( i );
		QFile file( fileInfo.absoluteFilePath() );
		
		if ( ! file.open( QIODevice::ReadOnly | QIODevice::Text ) )
		{
			continue;
		}
		
		while ( ! file.atEnd() ) 
		{
			_command += file.readLine();
		}
	}

	write( _command.toLocal8Bit() + "PS2(__qtoctave_ps2); clear __qtoctave_ps2;PS1(__qtoctave_ps1); clear __qtoctave_ps1;\n" );
}


void OctaveConnection::command_enter( const QString &command , bool show )
{
	if( command.isEmpty() )
	{
		return;
	}

	QString _command;
	
	if( command.at( command.size() - 1 ) != '\n' )
	{
		_command = command + '\n';
	}
	
	if( show )
	{
		//Count number of instructions
		if( ! debugging )
		{
			if( instructions_left_no < 0 )
			{
				instructions_left_no = _command.count( '\n' );
			}
			else
			{
				instructions_left_no += _command.count( '\n' );
			}
		}

		//printf("instructions_left_no=%d añadida\n",instructions_left_no);

		emit command_ready( ' ' + _command );
	}
	else
	{
		emit ide_command_ready( ' ' + _command );
	}

	write( _command.toLocal8Bit() );
}

/*
	The main problem is that the '\t' symbol is not portable.
	As i found no option to set a specific tab size this hack
	iterates through the output and replaces all '\t' characters
	with 'tabsize' empty spaces.

	TODO: Find away to avoid this ugly hack
*/
QString &OctaveConnection::tabHack( QString &buffer , QStringList &lines )
{
	const std::size_t tabsize = 4;

	for( QStringList::iterator i = lines.begin() ; i != lines.end() ; i++ )
	{
		// Not every line has '\t' characters.
		// This should avoid unnecessary copies.
		bool changedSomething = false;

		QString tmpstr( *i );

		// Find the first index of the '\t' character
		std::size_t found = tmpstr.indexOf( '\t' );

		/*
			If at least one '\t' character is found.
			Find and replace all '\t' characters in
			this line with 'tabsize' empty spaces.
		*/
		while( found != std::string::npos )
		{
			const std::size_t left = tabsize - found % tabsize;

			tmpstr.replace( found , 1 , QString( left ? left : tabsize , ' ' ) );

			changedSomething = true;
			found = tmpstr.indexOf( '\t' );
		}

		if( changedSomething )
		{
			(*i) = tmpstr;
		}
	}

	buffer.clear();

	for(QStringList::const_iterator i = lines.begin() ; i != lines.end() ; i++ )
	{
		buffer.append( *i + '\n' );
	}

	return buffer;
}

void OctaveConnection::octaveOutputSlot()
{
	//QRegExp regexp_octave_prompt("octave:[0-9]+>");
	//QRegExp regexp_octave_prompt2("octave:[0-9]+\\+>");
	//QRegExp regexp_actual_debug_line_column("^([a-zA-Z_]\\w*:)+ line ([0-9]+), column ([0-9]+)$");

	QString buffer = QString::fromLocal8Bit( readAllStandardOutput().data() );	
	QStringList lines = buffer.split('\n');

	emit output_ready( tabHack( buffer , lines ) );

	Sleep::micro_sleep( 200 );

	if( lines.empty() )
	{
		lines.push_back("");
	}

	// Al primer elemento se le debe concatenar el buffer de línea
	lines.first() = line_buffer + lines.first();
	line_buffer.clear();

	// En caso de que line_buffer sea debug> u octave:X>, no guardarlo
	if(line_buffer == "debug> ")
	{
		lines.push_back(line_buffer);
	}

	// Procesar las líneas
	for( QStringList::iterator i = lines.begin() ; i != lines.end(); i++)
	{
	  // Debug
	  if(i->startsWith("debug> "))
	  {
	    i->remove(0, 7);
	    debugging = true;
	    emit debug(lineno, colno);
	  }

	  //printf("line >%s<\n", i->toLocal8Bit().data());

	  // PS1 = octave:X>
	  if( regexp_octave_prompt.indexIn( *i ) > -1 )
	  {

	    instructions_left_no -= i->count( regexp_octave_prompt );

	    //i->remove(0, regexp_octave_prompt.matchedLength());
	    i->remove( regexp_octave_prompt );

	    //printf("instructions_left_no=%d eliminada\n",instructions_left_no);
	    //printf("line eliminada >%s<\n", i->toLocal8Bit().data());

	    if( debugging )
	    {
	      debugging = false;
	      emit endDebug();
	    }
	    else if( instructions_left_no == 0 )
	    {
	    	//printf("Comando terminado\n");
	    	instructions_left_no = 0;
	    	emit command_finished();
	    }
	  }

	  // PS2 = octave:X+>
	  if( regexp_octave_prompt2.indexIn( *i ) > -1 )
	  {

	    instructions_left_no-=i->count( regexp_octave_prompt2 );

	    //i->remove(0, regexp_octave_prompt.matchedLength());
	    i->remove( regexp_octave_prompt2 );

	    //printf("instructions_left_no=%d eliminada PS2\n",instructions_left_no);
	    //printf("line eliminada PS2 >%s<\n", i->toLocal8Bit().data());
	  }

	  // Línea y columna cuando va a parar
	  if( regexp_actual_debug_line_column.exactMatch( *i ) )
	  {
	     int start;

		//QStringList list = regexp_actual_debug_line_column.capturedTexts();
		//foreach(QString item, list)
		//{
		//	printf("Captura %s %d\n", item.toLocal8Bit().data(), regexp_actual_debug_line_column.numCaptures()-2 );
		//}

	    // Extraer la línea
	    start = regexp_actual_debug_line_column.numCaptures()-1;
	    
		if(!regexp_actual_debug_line_column.cap( start ).isEmpty())
		{
			lineno=regexp_actual_debug_line_column.cap( start ).toInt();
		}

	    // Extraer la columna
	    start = regexp_actual_debug_line_column.numCaptures();
	    
		if(!regexp_actual_debug_line_column.cap( start ).isEmpty())
		{
			colno=regexp_actual_debug_line_column.cap( start ).toInt();
		}

	  }
		// Code of clc (clean screen)
		if( *i == QString( "\033[H\033[2J" ) )
		{
			emit clearScreen();
		}
	}

	// Meter en el buffer de línea el último elemento si la cadena
	// no terminaba en \n
	if( ! buffer.endsWith( '\n' ) )
	{
		line_buffer = lines.last();
	}
}

void OctaveConnection::octaveErrorOutputSlot()
{	
	QString buffer=error_buffer.data();
	error_buffer.close();
	error_buffer.setData( buffer.toUtf8()+readAllStandardError());
	error_buffer.open(QBuffer::ReadOnly);
	Sleep::micro_sleep(200);

	QString line, error("");

	do
	{
		line=error_buffer.readLine();

		if(line.endsWith('\n') )
		{
			if(line.startsWith("~~"))
			{
				// Code of clc (clean screen)
				if(line=="~~ClearScreen\n")
				{
					emit clearScreen();
				}
				else
				{
					emit line_ready(line);
				}
			}
			else if(line.startsWith("warning"),false)
			{
				
			}
			else
			{
				error+=line;
			}
			
			if( regexp_actual_debug_line_column.exactMatch(line.trimmed()) )
			 {
			     int start;
			     
				//printf("[OctaveConnection::octaveErrorOutputSlot]\n");
				//QStringList list = regexp_actual_debug_line_column.capturedTexts();
				//foreach(QString item, list)
				//{
				//	printf("Captura %s %d\n", item.toLocal8Bit().data(), regexp_actual_debug_line_column.numCaptures()-2 );
				//}
		
			    // Extraer la línea
			    start=regexp_actual_debug_line_column.numCaptures()-1;
			    if(!regexp_actual_debug_line_column.cap(start).isEmpty())
			    	lineno=regexp_actual_debug_line_column.cap(start).toInt();
		
			    // Extraer la columna
			    start=regexp_actual_debug_line_column.numCaptures();
			    if(!regexp_actual_debug_line_column.cap(start).isEmpty())
			    	colno=regexp_actual_debug_line_column.cap(start).toInt();
		
			    emit debug(lineno, colno);
			  }

			continue;
		}
		else
		{
			line=line+error_buffer.readAll();
			error_buffer.close();
			error_buffer.setData(line.toUtf8());
			error_buffer.open(QBuffer::ReadOnly);
			break;
		}
		emit line_ready(line);
	}
	while(error_buffer.bytesAvailable());

	emit error_ready(error);

	if( ! error_buffer.bytesAvailable() )
	{
		error_buffer.close();
		error_buffer.setData(QString("").toUtf8());
		error_buffer.open(QBuffer::ReadOnly);
	}

	//Se procesa el buffer para buscar las líneas diponibles
	//QStringList lines=buffer.split('\n');
	//QStringList::const_iterator i;
	//for (i = lines.constBegin(); i != lines.constEnd();)
	//{
	//	QString line=*i;
	//	++i;
	//	if(i==lines.constEnd() && !buffer.endsWith('\n'))
	//		emit error_ready(line);
	//	else
	//		emit error_ready(line+'\n');
	//	emit line_ready(line);
	//}
}

void OctaveConnection::octaveFinished(int /*exitCode*/, QProcess::ExitStatus exitStatus)
{
	if(exitStatus == QProcess::CrashExit)
	{
		QMessageBox::critical(NULL,tr("Octave crashed"), tr("Octave has crashed. Restarting..."));
	}
	else
	{
		QMessageBox::critical(NULL,tr("Octave finished"), tr("Octave has finished. Restarting..."));
	}

	//Relanzar
	startOctave();
}
