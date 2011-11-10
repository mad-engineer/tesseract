/* Copyright (C) 2010 P.L. Lucas
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
#include <QFileInfo>
#include <QTextBlock>
#include <QTextStream>

#include "config.hpp"
#include "projects.hpp"
#include "simpleeditor.hpp"

extern QString syntaxPath();

SimpleEditor::SimpleEditor(QWidget *parent) : 
QPlainTextEdit(parent),
syntax(NULL),
firtsTimeUsedOk(true),
completer(new QStringListModel(this)),
syntaxCompleterModel(new QCompleter( completer , this ))
{
	// TODO: Set via Option

	{
		QTextDocument *tmpdoc=new QTextDocument();
		tmpdoc->setProperty("DocumentReferences", QVariant(0));
		
		QPlainTextDocumentLayout *layout=new QPlainTextDocumentLayout(tmpdoc);
		tmpdoc->setDocumentLayout(layout);

		setDocument(tmpdoc);
	}

	syntaxCompleterModel->setCompletionMode(QCompleter::PopupCompletion);
	syntaxCompleterModel->setWidget(this);

	connect(syntaxCompleterModel, SIGNAL(activated ( const QString &)), this, SLOT(activated ( const QString &)));
	
	if( get_config("bracketsMatch") != "false" )
	{
		connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(cursorPositionChangedCallBack()));
	}
	
	if( get_config("autoCompletion")!="false" )
	{
		connect(document(), SIGNAL(contentsChange(int, int, int)), this, SLOT(autoComplete(int, int, int)));
	}
	
	auto_indent=( "false"!=get_config("autoindent") );
	automatic_indention_statement_ok = (get_config("autoindent_statements")=="true");
	
	//Set editor's font
		
	QFont text_edit_font;
  	QString font_name=get_config("textEditFont");
	QString font_size=get_config("textEditFontSize");
	
	if( font_name.isEmpty() )
	{
		font_name="Courier New";
	}
	
	if( font_size.isEmpty() )
	{
		font_size=QString::number( text_edit_font.pointSize() );
	}
	
	text_edit_font.setFamily(font_name);
	text_edit_font.setPointSize(font_size.toInt());
	
	setFont(text_edit_font);

	//TODO: find a better way to avoid double code
	{
		QFile file( QApplication::applicationDirPath()+"/styles/default/editor.css" );

		if( file.open( QFile::ReadOnly ) )
		{
			setStyleSheet( QLatin1String( file.readAll() ) ) ;
		}
	}
}

void SimpleEditor::loadSyntaxXMLDescription()
{
	printf("[SimpleEditor::loadSyntaxXMLDescription] Loading syntax\n");

	QString installPath = syntaxPath();
	QFileInfo file(fileName);
	QString suffix=file.suffix();
	
	if(comands_completion_list.isEmpty())
	{
		QFile file(syntaxPath()+"commands.txt");

		if (file.open(QFile::ReadOnly))
		{
			char buf[1024];

			while(file.readLine(buf, sizeof(buf))>=0)
			{
				comands_completion_list.append(QString(buf).trimmed());
			}

			file.close();
		}
	}

	QFileInfo xml(installPath+suffix+".xml");

	if( xml.exists() )
	{
		printf("[SimpleEditor::loadSyntaxXMLDescription] Loading syntax\n");

		if( syntax==NULL )
		{
			syntax=new Syntax( document() );
			syntax->load(xml.absoluteFilePath());
			syntax->setDocument(document());
		}
		else
		{
			syntax->load(xml.absoluteFilePath());
		}
	}
}

bool SimpleEditor::load(const QString &file)
{
	if(file.isEmpty())
	{
		setPlainText("");
		fileName=file;
		return true;
	}
	
	FILE *input=fopen(file.toLocal8Bit().data(),"r");
	if(input==NULL) return false;
	fclose(input);
	QFile in(file);
	if (!in.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;
	QByteArray data=in.readAll();
	
	setPlainText( QString::fromLocal8Bit(data) );
	fileName=file;
	
	firtsTimeUsedOk=false;
	
	loadSyntaxXMLDescription();
	
	return true;
}

bool SimpleEditor::save()
{
	QFile::remove(fileName+"~");
	QFile::copy(fileName, fileName+"~");
	FILE *out=fopen(fileName.toLocal8Bit().data(),"w");
	if(out==NULL) return false;
	fprintf( out, "%s", toPlainText().toLocal8Bit().data() );
	fclose(out);
	document()->setModified(false);
	return true;
}

void SimpleEditor::keyPressEvent(QKeyEvent * e)
{
	//printf("%d %s\n",e->key(), e->text().toLocal8Bit().data());
	
	//In all cases completer popup must been hided.
	if(e->key()!=Qt::Key_Return && e->key()!=Qt::Key_Enter )
	{
		QAbstractItemView *view=syntaxCompleterModel->popup();
		if(view->isVisible()) view->hide();
		//completer->setWidget(NULL);
	}
	
	if(e->key()==Qt::Key_Return || e->key()==Qt::Key_Enter )
	{
		QAbstractItemView *view=syntaxCompleterModel->popup();
		if(view->isVisible())
		{
			QString word=view->currentIndex().data().toString();
			if( word.isEmpty() ) word=syntaxCompleterModel->currentCompletion();
			activated( word );
			return;
		}
		else if(auto_indent)
		{
			QTextCursor cursor=textCursor();
			QString line=cursor.block().text();
			QString line2=line;
			for(int i=0;i<line.length();i++)
			{
				if(line[i]!=' ' && line[i]!='\t') { line.resize(i); break;}
			}
			cursor.insertText('\n'+line);
			if( automatic_indention_statement_ok )
			{
				
				printf("[SimpleEditor::keyPressEvent] automatic_indention_statement_ok=%s\n", line2.toLocal8Bit().data() );
				
				QRegExp re("^while .*|^if .*|^for .*|^switch .*|^do$|^try|^function .*|^else$|^elseif .*");
				
				if(re.exactMatch( line2.trimmed() ) )
				{
					cursor.insertText("\t");
				}
			}
			setTextCursor(cursor);
		}
		else
			QPlainTextEdit::keyPressEvent(e);
	}
	//else if( e->key()==(Qt::Key_B) && Qt::ControlModifier==e->modifiers() )
	//{
	//	autoComplete();
	//	return;
	//}
	else if(e->key()==Qt::Key_Tab)
	{
		QTextCursor cursor=textCursor();
		int start=cursor.selectionStart();
		int end=cursor.selectionEnd();

		if( start == end )
		{
			QPlainTextEdit::keyPressEvent(e);
			return;
		}

		cursor.beginEditBlock();
		cursor.setPosition(end);
		end=cursor.blockNumber();
		cursor.setPosition(start);
		cursor.movePosition(QTextCursor::StartOfBlock);

		while(true)
		{
			cursor.insertText("\t");

			if(cursor.blockNumber() >= end )
			{
				break;
			}
			cursor.movePosition(QTextCursor::NextBlock);
		}

		cursor.endEditBlock();
	}
	else if(e->key()==Qt::Key_Backtab )
	{
		QTextCursor cursor=textCursor();
		int start=cursor.selectionStart();
		int end=cursor.selectionEnd();
		if(start==end)
		{
			QPlainTextEdit::keyPressEvent(e);
			return;
		}
		cursor.beginEditBlock();
		cursor.setPosition(end);
		end=cursor.blockNumber();
		cursor.setPosition(start);
		cursor.movePosition(QTextCursor::StartOfBlock);
		while( true )
		{
			QString line=cursor.block().text();
			if(line.length()>0 && (line[0]==' ' || line[0]
				=='\t') )
			{
				cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
				cursor.removeSelectedText();
			}
			if(cursor.blockNumber()>=end) break;
			cursor.movePosition(QTextCursor::NextBlock);
			cursor.movePosition(QTextCursor::StartOfBlock);
		}
		cursor.endEditBlock();
	}
	else
	{
		if( e->key()==(Qt::Key_B) && Qt::ControlModifier==e->modifiers() )
		{
			autoComplete(0);
			return;
		}
		
		QPlainTextEdit::keyPressEvent(e);
		
	}
	
	
}

void SimpleEditor::setCharFormat( const QTextCharFormat &charFormat )
{
	this->charFormat=charFormat;
	QTextCursor cursor=textCursor();

	cursor.movePosition(QTextCursor::Start);
	cursor.setCharFormat(charFormat);
	cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);

	setFont(charFormat.font());
	
	QFontMetrics fm(charFormat.font());

	setTabStopWidth( fm.width("    ") );
}

void SimpleEditor::activated( const QString & text )
{
	QAbstractItemView *view=syntaxCompleterModel->popup();
	QTextCursor cursor=textCursor();
	cursor.movePosition( 
		QTextCursor::PreviousWord, QTextCursor::KeepAnchor);
	cursor.insertText(text);
	view->hide();
}

void SimpleEditor::autoComplete( int /* ATM unused */ , int /* ATM unused */ , int charsAdded )
{
	if( charsAdded == 1 )
	{
		autoComplete( );
	}
}

void SimpleEditor::autoComplete(int size)
{
	QTextCursor cursor=textCursor();
	
	cursor.movePosition(QTextCursor::PreviousWord, QTextCursor::KeepAnchor);
	
	//printf("[SimpleEditor::autoComplete] >%s<\n", cursor.selectedText().toLocal8Bit().data());
	
	if( cursor.selectedText().endsWith(' ') || cursor.selectedText().trimmed().length()<size ) return;
	
	QStringList list=toPlainText().split(QRegExp("\\W+"));
	
	list.removeDuplicates();
	list.removeOne(cursor.selectedText());
	list.sort();
	
	list.append(comands_completion_list);
	
	completer->setStringList( list );
	
	syntaxCompleterModel->setCompletionPrefix(cursor.selectedText());
	
	//printf("[SimpleEditor::autoComplete] >%d<\n", completer->completionCount());
	
	if (syntaxCompleterModel->completionCount()>0 )
	{
		//completer->setWidget(this);
		QRect r=cursorRect(cursor);
		r.setWidth(200);
		syntaxCompleterModel->complete(r);
	}
}


QString SimpleEditor::getFileName()
{
	return fileName;
}


void SimpleEditor::setFile(const QString &file)
{
	fileName=file;
	loadSyntaxXMLDescription();
}


void SimpleEditor::cursorPositionChangedCallBack()
{
	//Hightlight brackets
	if(syntax!=NULL)
		syntax->setFormatPairBrackets(this);
}

void SimpleEditor::publicBlockBoundingRectList(QVector<qreal> &list, int &first_line)
{
	qreal pageBottom = /*viewport()->*/height();
	QPointF offset=contentOffset();
	QTextBlock block=firstVisibleBlock();
	first_line=block.blockNumber()+1;
	qreal first_position=blockBoundingGeometry(block).topLeft().y();
	
	for ( ; block.isValid(); block = block.next() )
	{
		QRectF position=blockBoundingGeometry(block);
		qreal y=position.topLeft().y()+offset.y()-first_position;
		
		if(y>pageBottom) break;
		
		list.append(y);
	}
}


/**Checks if document has references. If not document is deleted.
 */
static void unreferenceDocument(QTextDocument * document)
{
	printf("[SimpleEditor::unreferenceDocument] Entered\n");
	QVariant n_refs = document->property("DocumentReferences");
	if(n_refs.isValid())
	{
		int n=n_refs.toInt()-1;
		printf("[unreferenceDocument] References: %d\n", n);
		if(n<=0)
			delete document;
		else
			document->setProperty("DocumentReferences", QVariant(n));
	}
}

void SimpleEditor::setDocument ( QTextDocument * document )
{
	printf("[SimpleEditor::setDocument] Entered\n");

	if( document )
	{
		QVariant n_refs = document->property("DocumentReferences");
		if(n_refs.isValid())
		{
			document->setProperty("DocumentReferences", QVariant(n_refs.toInt()+1));
			int n=n_refs.toInt()+1;
			printf("[SimpleEditor::setDocument] References: %d\n", n);
		}
	}
	
	QTextDocument * oldDocument=this->document();
	QVariant n_refs = oldDocument->property("DocumentReferences");
		
	//if(document!=NULL)
	QPlainTextEdit::setDocument(document);

	QFontMetrics fm(charFormat.font());
	setTabStopWidth(fm.width("1234"));
		
	if( n_refs.isValid() )
	{
		unreferenceDocument(oldDocument);
	}
}

SimpleEditor::~SimpleEditor()
{
	printf("[SimpleEditor::~SimpleEditor] Entered\n");
	QTextDocument * oldDocument=this->document();
	unreferenceDocument(oldDocument);
}

