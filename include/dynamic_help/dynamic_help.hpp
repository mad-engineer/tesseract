#pragma once
#ifndef TESSERACT_DYNAMIC_HELP_DYNAMIC_HELP_HPP
#define TESSERACT_DYNAMIC_HELP_DYNAMIC_HELP_HPP

#include <QTime>
#include <QTimer>
#include <QCheckBox>
#include <QTextEdit>
#include <QLineEdit>

#ifdef TESSERACT_USE_VLD
#	include <vld.h>
#endif

// qtoctave project
#include "basewidget.hpp"
#include "octave_connection.hpp"

/**
 * If you write a command in Terminal's command line, DynamicHelp shows help of commands.
 */
class DynamicHelp :public BaseWidget
{
	Q_OBJECT
	public:
	DynamicHelp(QString octave_path, QWidget *parent=0);
	~DynamicHelp();

	/**Sets session.*/
	void setSession( Session *session );
	private:
	QTextEdit *textEdit;
	QCheckBox *stop_help;
	OctaveConnection *octave;
	QTime time;
	QTimer timer;
	QString input_text, octave_path;
	
	/**Listen opened session tools.*/
	void listen_tools(WidgetType type);

	/** Sets QLineEdit from keyboard signals are listen. **/
	void setLineEdit( QLineEdit *lineedit );
	

	BaseWidget *copyBaseWidget( QWidget * parent = 0 );
	

	public slots:
	
		/** Updates shown help when QLineEdit changes happened. */
		void update( );

		/**
		* Shows help when of text.
		 * @param text Text from QLineEdit.
		*/
		void textChanged ( const QString & text );
		
		/** Reads and shows Octave output.
		 */
		void readyReadStandardOutput ( const QString &line );
		
		/**New tool to listen.*/
		void newTool( WidgetType type , QObject *tool );
};

#endif