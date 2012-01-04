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
#include <QMap>
#include <QIcon>
#include <QLabel>
#include <QRegExp>
#include <QFileInfo>
#include <QDateTime>
#include <QLineEdit>
#include <QTextBlock>
#include <QTextStream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextCursor>

#include <signal.h>
#include <sys/types.h>

#include "config.hpp"
#include "projects.hpp"
#include "pkg_bind.hpp"
#include "terminal.hpp"

QString projectsPath();

Terminal::Terminal( QWidget * parent ) : 
BaseWidget( parent ),
octave_connection( NULL ),
diary_ok( false ),
text( new QTextEdit( this ) ),
combo_box( new Autocomplete( this ) )
{
	widget_type = TERMINAL;
	
	init_regular_expresions();
	
	menuBar()->hide();
	
	// TODO: Translate this comment: Se crea la ventana del terminal
	setWindowTitle( tr( "Octave Terminal" ) );
	setWindowIcon( QIcon(QApplication::applicationDirPath() + "/styles/default/images/console.png" ) );
	
	if( getConfig( "lines_in_terminal" ).isEmpty() )
	{
		QMap<QString,QString> c;
		c[ "lines_in_terminal" ] = "1000";
		setConfig( c );
	}

	if( getConfig( "cols_in_terminal" ).isEmpty() )
	{
		QMap<QString,QString> c;
		c["cols_in_terminal"] = "80";
		setConfig( c );
	}

	cols_in_terminal = getConfig( "cols_in_terminal" ).toInt();

	// Limit input to positive numbers and a width limit of 1000
	if( ( ! cols_in_terminal ) || cols_in_terminal > 1000 )
	{
		cols_in_terminal = 1000;
	}
	
	lines_in_terminal = getConfig( "lines_in_terminal" ).toInt();

	// Same as above
	if( ( ! lines_in_terminal ) || lines_in_terminal > 10000 )
	{
		lines_in_terminal = 10000;
	}

	text->setReadOnly( true );
	text->setLineWrapMode( QTextEdit::NoWrap );
	//text->setLineWrapColumnOrWidth ( cols_in_terminal );

	if( getConfig( "show_ide_commands" ).isEmpty() )
	{
		show_ide_commands_ok = false;

		QMap<QString,QString> c;

		c[ "show_ide_commands" ] = "false";
		setConfig( c );
	}
	else
	{ 
		show_ide_commands_ok = getConfig( "show_ide_commands" ) == "true" ;
	}

	if( getConfig( "terminal_font" ).isEmpty() )
	{
		QMap<QString,QString> c;

		c[ "terminal_font" ] = "Courier New";

		setConfig( c );
	}

	if( getConfig( "terminal_font_size" ).isEmpty() )
	{
		QMap<QString,QString> c;

		c[ "terminal_font_size" ] = "10";

		setConfig( c );
	}

	if( getConfig( "terminal_foreground_color" ).isEmpty() )
	{
		QMap<QString,QString> c;

		c[ "terminal_foreground_color" ] = "Black";
		setConfig( c );
	}
	
	if( getConfig( "terminal_background_color" ).isEmpty() )
	{
		QMap<QString,QString> c;

		c[ "terminal_background_color" ] = "White";
		setConfig( c );
	}
	
	if( getConfig( "terminal_error_color" ).isEmpty() )
	{
		QMap<QString,QString> c;

		c[ "terminal_error_color" ] = "Red";
		setConfig( c );
	}

	if( getConfig( "terminal_warning_color" ).isEmpty() )
	{
		QMap<QString,QString> c;

		c[ "terminal_warning_color" ] = "#FF6400";
		setConfig( c );
	}
	
	if( getConfig( "ide_command_color" ).isEmpty() )
	{
		QMap<QString,QString> c;

		c[ "ide_command_color" ] = "lightGray";
		setConfig( c );
	}
	
	//text->setTextColor(get_config("terminal_foreground_color"));
	{
		QPalette p = text->viewport ()->palette();
		p.setColor( QPalette::Base , QColor( getConfig( "terminal_background_color" ) ) );
		text->viewport()->setPalette( p );
	}

	QFont font( getConfig( "terminal_font" ) );
	font.setPointSize( getConfig( "terminal_font_size").toInt() );
	
	normal_format.setFont( font );
	normal_format.setFontWeight( QFont::Normal );
	normal_format.setFontPointSize( font.pointSize() );

	ide_command_format = normal_format;
	ide_command_format.setForeground( QColor( getConfig( "ide_command_color" ) ) );

	normal_format.setForeground( QColor( getConfig( "terminal_foreground_color" ) ) );
	
	command_format = normal_format;
	command_format.setFontWeight( QFont::Bold );

	error_format = normal_format;
	error_format.setFontWeight( QFont::Bold );
	error_format.setForeground( QColor( getConfig( "terminal_error_color" ) ) );

	warning_format = normal_format;
	warning_format.setFontWeight( QFont::Bold );
	warning_format.setForeground( QColor( getConfig( "terminal_warning_color" ) ) );

	text->show();

	combo_box->setSizePolicy( QSizePolicy::Expanding , QSizePolicy::Minimum );
	combo_box->show();
	
	//Se captura el "intro" para pasar comandos al octave
	QLineEdit *line_edit = combo_box/*->lineEdit()*/;

	connect( line_edit, SIGNAL(returnPressed() ) , this , SLOT( return_pressed() ) );
	connect( line_edit, SIGNAL( textChanged ( const QString &) ) , this, SLOT( textChanged ( const QString &) ) );
	
	line_edit->setText( tr( "Insert your commands here..." ) );
	line_edit->selectAll();
	line_edit->setToolTip( tr( "Insert your commands here. Use arrows and tab key to commands navigation." ) );
	
	connect( combo_box , SIGNAL(selectionChanged ()) , this , SLOT(clear_command_line_first_time() ) );
	
	QVBoxLayout *layout = new QVBoxLayout();
	QHBoxLayout *line_layout = new QHBoxLayout();

	layout->addWidget(text);
	layout->addLayout(line_layout);
	
	line_layout->addWidget( new QLabel( "<b>" + tr( "<Command line" ) + "&gt;&gt;</b>" , this ) );
	line_layout->addWidget( combo_box );
	
	centralWidget()->setLayout( layout );
	
	setAcceptDrops( true );

	//TODO: find a better way to avoid double code
	{
		QFile file( QApplication::applicationDirPath()+"/styles/default/mainwindow/widgets/terminal.css" );

		if( file.open( QFile::ReadOnly ) )
		{
			setStyleSheet( QLatin1String( file.readAll() ) ) ;
		}
	}
}

void Terminal::initConfig()
{
	shared_ptr<map<string,string>> limitmin( new map<string,string>() );
	shared_ptr<map<string,string>> limitmax( new map<string,string>() );
	shared_ptr<map<string,string>> defaults( new map<string,string>() );

	defaults->insert( std::pair<string,string>( "lines_in_terminal"			, "1000"		) );
	defaults->insert( std::pair<string,string>( "cols_in_terminal"			, "80"			) );
	defaults->insert( std::pair<string,string>( "show_ide_commands"			, "false"		) );
	defaults->insert( std::pair<string,string>( "terminal_font"				, "Courier New"	) );
	defaults->insert( std::pair<string,string>( "terminal_foreground_color"	, "Black"		) );
	defaults->insert( std::pair<string,string>( "terminal_background_color"	, "White"		) );
	defaults->insert( std::pair<string,string>( "terminal_error_color"		, "Red"			) );
	defaults->insert( std::pair<string,string>( "ide_command_color"			, "lightGray"	) );

	limitmax->insert( std::pair<string,string>( "lines_in_terminal" , "10000" ) );
	limitmax->insert( std::pair<string,string>( "cols_in_terminal"  , "800"   ) );

	limitmin->insert( std::pair<string,string>( "lines_in_terminal" , "100"   ) );
	limitmin->insert( std::pair<string,string>( "cols_in_terminal"  , "80"    ) );

	emit sendConfiguration( "terminal" , "int" , "0" , "100" ); 
}

void Terminal::init_regular_expresions()
{
	//Used in remove_lines
	regexp_octave_prompt.setPattern("(((octave:[0-9]+>)|(octave:[0-9]+\\+>))|>>>)+"); //PS1 or PS2
	
	//Used in line_ready
	re.setPattern("~~Diary: (.*) '(.*)'\n");
}

void Terminal::dragEnterEvent( QDragEnterEvent *event )
{
	if( event->mimeData()->hasFormat( "text/plain" ) )
	{
		event->acceptProposedAction();
	}
}

void Terminal::dropEvent ( QDropEvent * event )
{
	QString path = event->mimeData()->text();
	
	QFileInfo fileInfo( path );
	octave_connection->command_enter( QString("cd \"") + fileInfo.dir().absolutePath() +"\"" );
	octave_connection->command_enter( fileInfo.baseName() );

	event->acceptProposedAction();
}

void Terminal::return_pressed()
{
	QLineEdit *line_edit=combo_box/*->lineEdit()*/;
	QString command(line_edit->text());
	command_enter(command);
}

QTextEdit *Terminal::getTextEdit()
{
	return text;
}

Autocomplete *Terminal::getAutocomplete()
{
	return combo_box;
}

void Terminal::setOctaveConnection( OctaveConnection *oc )
{
	this->octave_connection = oc;
	
	connect( oc , SIGNAL(error_ready(QString)), this, SLOT(write_error(QString)));
	connect( oc , SIGNAL(output_ready(QString)), this, SLOT(write_output(QString)));
	connect( oc , SIGNAL(command_ready(QString)), this, SLOT(write_command(QString)));
	connect( oc , SIGNAL(ide_command_ready(QString)), this, SLOT(write_ide_command(QString)));
	connect( oc , SIGNAL(line_ready(QString)), this, SLOT(line_ready(QString)));
	combo_box->set_octave_connection( oc );
	//setProject(); //This line loads variables
}

OctaveConnection *Terminal::getOctaveConnection()
{
	return octave_connection;
}

void Terminal::command_enter( const QString &command )
{
	if( command.compare( "clc" , Qt::CaseInsensitive ) == 0  )
	{
		clear_callback();
	}
	else
	{
		octave_connection->command_enter( command );
		combo_box->setText( "" );
	}
}

void Terminal::remove_lines( QTextCursor &cursor )
{
	//Se cortan las líneas que sean demasiado largas
	cursor.movePosition(QTextCursor::Start);
	int lines=0;

	while(true)
	{
		QTextBlock block=cursor.block();

		if(block.length()>cols_in_terminal)
		{
			cursor.movePosition(QTextCursor::StartOfBlock);
			cursor.movePosition(QTextCursor::Right,QTextCursor::MoveAnchor,cols_in_terminal-1);
			cursor.insertText( "\n" );
		}
		else
		{
			cursor.movePosition(QTextCursor::EndOfBlock);
			cursor.movePosition(QTextCursor::Right);
		}

		cursor.movePosition(QTextCursor::EndOfBlock);
		lines++;

		if( cursor.atEnd() )
		{
			QTextBlock block=cursor.block();
			
			if( block.length() < cols_in_terminal )
			{
				break;
			}
		}
	}
	
	//Se borran las líneas iniciales si hay más de lines_in_terminal líneas
	//printf("lines=%d %d\n",lines,lines_in_terminal);
	lines=text->toPlainText().count('\n');

	while( lines > lines_in_terminal )
	{
		cursor.movePosition( QTextCursor::Start );
		cursor.movePosition( QTextCursor::EndOfBlock , QTextCursor::KeepAnchor );
		//printf("line %d: %s\n",lines, cursor.selectedText().toLocal8Bit().data());
		
		if(cursor.hasSelection())
		{
			cursor.removeSelectedText();
		}
		else
		{
			cursor.deleteChar();
		}

		cursor.deleteChar();
		lines--;
	}
	//printf("lines=%d %d\n",lines,lines_in_terminal);
	
	//Merge all octave:X> in only one
	//QRegExp regexp_octave_prompt("((octave:[0-9]+>)|(octave:[0-9]+\\+>))"); //PS1 or PS2
	
	cursor.movePosition( QTextCursor::Start );

	if( !text->isVisible() )
	{
		return;
	}

	cursor = text->document()->find( regexp_octave_prompt , cursor );

	while( cursor.position() >= 0 )
	{
		QTextCharFormat format=cursor.charFormat();

		if(format.fontWeight()!=QFont::Bold)
		{
			format.setFontWeight(QFont::Bold);
			//cursor.setCharFormat(format);
			cursor.insertText(">>", format);
		}
		cursor = text->document()->find(regexp_octave_prompt,cursor);
	}
	
	cursor=text->textCursor();
	
	return;
	
	/*
	//cursor.movePosition(QTextCursor::Start);
	//while(!cursor.atEnd())
	//{
	//	int prompt_no=0;
	//	
	//	cursor.movePosition(QTextCursor::Right);
	//	cursor.movePosition(QTextCursor::StartOfBlock);
	//	cursor.movePosition( QTextCursor::EndOfBlock,QTextCursor::KeepAnchor);
	//	
	//	QString line=cursor.selectedText();
	//	QString last_prompt;
	//	int pos = 0;

	//	while ((pos = regexp_octave_prompt.indexIn(line, pos)) != -1)
	//	{
	//		last_prompt=regexp_octave_prompt.cap(1);
	//		pos += regexp_octave_prompt.matchedLength();
	//		prompt_no++;
	//	}
		
	//	if(prompt_no>=1)
	//	{
	//		line.remove(regexp_octave_prompt);
	//		QTextCharFormat format=text->currentCharFormat();
	//		format.setFontWeight(QFont::Bold);
	//		cursor.insertText(last_prompt,format);
	//		format.setFontWeight(QFont::Normal);
	//		cursor.insertText(line,format);
	//	}
		
	//	cursor.movePosition(QTextCursor::EndOfBlock);
	//}
	*/
}

void Terminal::write_output( QString output )
{
	if( output.isEmpty() )
	{
		return;
	}

	QTextCursor cursor = text->textCursor();

	cursor.beginEditBlock();
	cursor.movePosition( QTextCursor::End );
	cursor.insertText( output , normal_format );

	remove_lines( cursor );

	cursor.movePosition( QTextCursor::End );
	cursor.endEditBlock();

	text->setTextCursor( cursor );

	if( diary_ok )
	{
		diary_file.write( output.toLocal8Bit() );
	}
}

void Terminal::write_warning( const QString &warn )
{
	if( warn.isEmpty() )
	{
		return;
	}

	QTextCursor cursor = text->textCursor();

	cursor.beginEditBlock();
	cursor.movePosition( QTextCursor::End );
	cursor.insertText( warn , warning_format );

	remove_lines( cursor );
	cursor.movePosition( QTextCursor::End );
	cursor.endEditBlock();

	text->setTextCursor( cursor );

	if( diary_ok )
	{
		diary_file.write( warn.toLocal8Bit() );
	}
}

void Terminal::write_error( QString error )
{
	if( error.isEmpty() )
	{
		return;
	}
	else if( error.toStdString().substr(0,8).compare("warning:") == 0 )
	{
		write_warning( error );
		return;
	}

	QTextCursor cursor = text->textCursor();

	cursor.beginEditBlock();
	cursor.movePosition( QTextCursor::End );
	cursor.insertText( error , error_format );

	remove_lines(cursor);

	cursor.movePosition(QTextCursor::End);
	cursor.endEditBlock();

	text->setTextCursor( cursor );

#ifdef PKG_ENABLED
	// Symbol not defined. ¿Quizá en un paquete?
	QRegExp undefinedSymbol("error: `(\\w+)' undefined near line \\d+ column \\d+");
	if(undefinedSymbol.indexIn(error) > -1)
	{
	  QString symbol(undefinedSymbol.capturedTexts()[1]);
	  if(PkgBind::getInstance()->checkSymbol(symbol))
	    PkgBind::getInstance()->invokePackageManager(symbol);
	}
#endif
}

void Terminal::write_command( QString command )
{
	if( command.isEmpty() )
	{
		return;
	}

	QTextCursor cursor = text->textCursor();
	
	cursor.beginEditBlock();
	cursor.movePosition( QTextCursor::End );
	cursor.insertText( command , command_format );

	remove_lines( cursor );
	
	cursor.movePosition( QTextCursor::End );
	cursor.endEditBlock();

	text->setTextCursor( cursor );
	
	if(diary_ok)
	{
		diary_file.write( command.toLocal8Bit() );
	}
}

void Terminal::write_ide_command( QString command )
{
	if( ! show_ide_commands_ok )
	{
		return;
	}
	else if( command.isEmpty() )
	{
		return;
	}

	QTextCursor cursor = text->textCursor();
	
	cursor.beginEditBlock();
	cursor.movePosition( QTextCursor::End );
	cursor.movePosition( QTextCursor::StartOfBlock , QTextCursor::KeepAnchor );
	cursor.setCharFormat( ide_command_format );
	cursor.movePosition( QTextCursor::End );
	cursor.insertText( command , ide_command_format );

	remove_lines( cursor );

	cursor.movePosition( QTextCursor::End );
	cursor.endEditBlock();

	text->setTextCursor( cursor );
}

void Terminal::closeEvent(QCloseEvent *event)
{
	if( session->getTools( TERMINAL ).size() < 2 )
	{
		//Ignorar este evento
		event->ignore();
	}
}

void Terminal::completion_matches_callback()
{
	QString command;
	QTextStream( &command ) << "completion_matches(\"" << combo_box/*->lineEdit()*/->text() << "\")";
	
	octave_connection->command_enter( command , false );
}

void Terminal::stop_process_callback()
{
	#if defined Q_OS_WIN32
		//system(QString("sh kill -s SIGINT "+QString("%d").arg(octave_connection->pid()) ).toLocal8Bit().data() );
		octave_connection->terminate();
	#else
		kill(octave_connection->pid(),SIGINT);
	#endif
}

void Terminal::clear_callback()
{
	text->clear();
	octave_connection->command_enter("",false);
}

void Terminal::clear_command_line_first_time()
{
	combo_box->setText("");
	disconnect(combo_box, SIGNAL(selectionChanged ()), this, SLOT(clear_command_line_first_time()));
}

CommandList * Terminal::show_commands_callback()
{
	CommandList *command_list=new CommandList(work_space);
	connect(combo_box, SIGNAL(new_command_entered(QStringList)), command_list, SLOT(set_list(QStringList)) );
	command_list->setSession(session);
	command_list->setLineEdit(combo_box);
	command_list->set_list(combo_box->commands());
	if(work_space!=NULL) work_space->addSubWindow(command_list);
	command_list->show();
	return command_list;
}

void Terminal::textChanged( const QString & text)
{
	emit dynamic_help_required(text);
}

void Terminal::setSession(Session *session)
{
	BaseWidget::setSession(session);
	connect(session, SIGNAL(projectChanged(QString)), this, SLOT(setProject(QString)));
}

void Terminal::setProject(QString /*project*/)
{
	if(octave_connection!=NULL)
	{
		//Load variables
		QString file_name=Projects::variablesListPath(session->getProjectName());

		if(file_name.isEmpty()) 
		{
			return;
		}

		octave_connection->command_enter("load(\"-text\",\""+file_name+"\"); cd(qtoctave_pwd); clear qtoctave_pwd;", false);

		combo_box->setProject(session->getProjectName());
	}
}

Terminal::~Terminal()
{
	//saveVariables();
}

void Terminal::saveVariables()
{
	if(octave_connection!=NULL)
	{
		//Save variables
		QDateTime date=QDateTime::currentDateTime();
		QString file_name=QString::number( date.toTime_t() );
		
		file_name=projectsPath()+file_name+".variables";
		
		QString command("qtoctave_pwd=pwd; save(\"-text\",\""+file_name+"\");");
		octave_connection->command_enter(command);
		octave_connection->command_enter("disp(\"\\n\\nAll data has been saved.\");",false);
		
		//Octave has 1 seconds to save data
		Sleep::micro_sleep(1000000);
		
		Projects::saveVariablesListPath(session->getProjectName(), file_name);
	}
}

BaseWidget *Terminal::copyBaseWidget(QWidget * parent )
{
	Terminal *bw=new Terminal(parent);
	bw->setSession(session);
	bw->setProject();
	bw->setOctaveConnection(octave_connection);
	bw->text->setHtml(text->toHtml());
	QTextCursor cursor=bw->text->textCursor();
	cursor.movePosition(QTextCursor::End);
	bw->text->setTextCursor( cursor );
	
	return bw;
}

void Terminal::line_ready(QString line)
{
	//QRegExp re("~~Diary: (.*) '(.*)'\n");
	
	if( re.exactMatch(line) )
	{
		QString command=re.cap(1);
		QString file_name=re.cap(2);
		
		if( command=="change" )
			diary_ok=!diary_ok;
		else if( command=="on" )
			diary_ok=true;
		else if( command=="off" )
			diary_ok=false;
		else if( command=="file" )
		{
			diary_ok=true;
			if(diary_file.isOpen()) diary_file.close();
			diary_file.setFileName(file_name);
			if (!diary_file.open(QIODevice::Append | QIODevice::Text)) return;
		}
		
		if(diary_ok)
		{
			if(!diary_file.isOpen())
			{
				if(diary_file.fileName().isEmpty())
					diary_file.setFileName(file_name+"/diary");
				diary_file.open(QIODevice::Append | QIODevice::Text);
			}
		}
		else
			diary_file.close();
	}
}



