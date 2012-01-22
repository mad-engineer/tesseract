#include <QIcon>
#include <QFile>
#include <QCheckBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTextStream>
#include <QTextCursor>
#include <QApplication>

#include "dynamic_help.hpp"
#include "octave_connection.hpp"

DynamicHelp::DynamicHelp( const QString &octave_path , QWidget *parent) : 
BaseWidget( parent ),
stop_help( new QCheckBox( tr( "Stop dynamic help" ) , this ) ),
octave( std::unique_ptr<OctaveConnection>( new OctaveConnection( this ) ) )
{
	widget_type = DYNAMIC_HELP;
	this->octave_path = octave_path;
	
	setWindowIcon( QIcon( QApplication::applicationDirPath() + "/styles/default/images/help_index.png" ) );
	setWindowTitle( tr( "Dynamic Help" ) );
	
	textEdit = new QTextEdit(this);
	textEdit->show();
	textEdit->setReadOnly(true);
	textEdit->setPlainText("Dynamic help...");
	textEdit->setLineWrapMode (QTextEdit::NoWrap);
	
	QVBoxLayout *layout = new QVBoxLayout;
	
	layout->addWidget( textEdit );
	layout->addWidget( stop_help );
	centralWidget()->setLayout( layout );
	

	octave->setOctavePath( octave_path );
	octave->startOctave( true );

	/*
	QString command;
	QTextStream(&command)
			<< "function ayuda(s)\n"
			<< "a=[completion_matches(s)];\n"
			<< "len=columns(s);\n"
			<< "s=strcat(s,blanks(columns(a)-columns(s)));\n"
			<< "ok=0;\n"
			<< "if (rows(a)==1)\n"
			<< "	help(s(1,1:len))\n"
			<< "end\n"
			<< "for i=1:rows(a)-1\n"
			<< "			for j=1:columns(a)\n"
			<< "				if(a(i,j)==0)\n"
			<< "				a(i,j)=32;\n"
			<< "				end\n"
			<< "			end\n"
			<< "		if(1==strcmp(a(i,:),s))\n"
			<< "			help(s(1,1:len))\n"
			<< "			ok=1;\n"
			<< "		end\n"
			<< "end\n"
			<< "if(ok==0)\n"
			<< "	completion_matches(s);\n"
			<< "end\n"
			<< "end\n";
	octave->write(command.toLocal8Bit());
	*/
	QString command;
	QTextStream(&command)
			<< "function ayuda(s)\n"
			<< "	printf(\"Completion matches:\\n\");\n"
			<< "	completion_matches(s)\n"
			<< "	printf(\"\\n\");\n"
			<< "	help(s);\n"
			<< "end\n";

	octave->command_enter( command.toLocal8Bit() );
	//textEdit->setPlainText(command);
	
	connect(octave.get(),SIGNAL(output_ready (QString )),this,SLOT(readyReadStandardOutput (QString)));
	
	time.start();
	timer.setSingleShot(true);
	connect(&timer,SIGNAL( timeout ()),this, SLOT(update()) );
	
	setAttribute(Qt::WA_DeleteOnClose);
	textEdit->clear();

	QFile file( QApplication::applicationDirPath() + "/styles/default/mainwindow/widgets/dynamic_help.css" );

	if( file.open( QFile::ReadOnly ) )
	{
		setStyleSheet( QLatin1String( file.readAll() ) ) ;
	}
}

void DynamicHelp::setLineEdit(QLineEdit *lineedit)
{
	connect( lineedit, SIGNAL( textChanged ( const QString &) ) , this, SLOT( textChanged ( const QString &) ) );
}

void DynamicHelp::update()
{
	textChanged(input_text);
}

void DynamicHelp::textChanged ( const QString & text )
{
	if(text.length()<2 || stop_help->checkState()==Qt::Checked) return;
	if( time.elapsed()< 1000)
	{
		input_text=text;
		timer.start(1000);
		return;
	}
	time.start();
	
	int separator,pos=-1;
	input_text=text.trimmed();
	separator=input_text.indexOf(' ');
	if(separator>-1 && separator<pos || pos<0) pos=separator;
	separator=input_text.indexOf('\t');
	if(separator>-1 && separator<pos || pos<0) pos=separator;
	separator=input_text.indexOf('\n');
	if(separator>-1 && separator<pos || pos<0) pos=separator;
	separator=input_text.indexOf("(");
	if(separator>-1 && separator<pos || pos<0) pos=separator;
	
	if(pos>0)input_text.truncate(pos);
	
	QString command;
	QTextStream(&command) << "ayuda(\"" << input_text << "\")\n";
	octave->command_enter(command.toLocal8Bit());
	
	textEdit->clear();
	textEdit->insertHtml("<b>Results for "+input_text+":</b><br>\n");
}

void DynamicHelp::readyReadStandardOutput ( const QString &out )
{
	QTextCursor cursor=textEdit->textCursor();

	cursor.movePosition(QTextCursor::End);

	textEdit->setTextCursor( cursor );
	textEdit->insertPlainText(out);

	cursor.movePosition(QTextCursor::Start);

	textEdit->setTextCursor( cursor );
}

DynamicHelp::~DynamicHelp()
{
	octave->command_enter(QString("quit\n").toLocal8Bit());
	octave->kill();
	//while( octave->state()!=QProcess::NotRunning ) ;
	delete stop_help;
	delete textEdit;
}

void DynamicHelp::setSession(Session *session)
{
	BaseWidget::setSession(session);
	
	connect(session, SIGNAL(newTool(WidgetType, QObject *)), this, SLOT(newTool(WidgetType, QObject *)));
	
	//Listen tools
	
	listen_tools(TERMINAL);
	listen_tools(HELP);
	listen_tools(EDITOR);
}

void DynamicHelp::listen_tools(WidgetType type)
{
	QVector<QObject*> tools=session->getTools(type);
	for(int i=0;i<tools.size();i++)
	{
		newTool(type, tools[i]);
	}
}

void DynamicHelp::newTool(WidgetType type, QObject *tool)
{
	if(tool!=NULL && (type==TERMINAL||type==HELP||type==EDITOR) )
	{
		BaseWidget *btool=(BaseWidget*)tool;
		connect(btool, SIGNAL(dynamic_help_required( const QString &)), this, SLOT(textChanged ( const QString &) ) );
	}
}

BaseWidget *DynamicHelp::copyBaseWidget(QWidget * parent )
{
	DynamicHelp *bw=new DynamicHelp(octave_path,parent);
	bw->setSession(session);
	bw->textEdit->setHtml(textEdit->toHtml());
	
	return bw;
}




