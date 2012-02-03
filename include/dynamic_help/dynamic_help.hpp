#pragma once
#ifndef TESSERACT_DYNAMIC_HELP_DYNAMIC_HELP_HPP
#define TESSERACT_DYNAMIC_HELP_DYNAMIC_HELP_HPP

#include <QTime>
#include <QTimer>

#ifdef TESSERACT_USE_VLD
#	include <vld.h>
#endif

#include "basewidget.hpp"

class QTextEdit;
class QCheckBox;
class QLineEdit;
class OctaveConnection;

/**
 * If you write a command in Terminal's command line, DynamicHelp shows help of commands.
 */
class DynamicHelp : public BaseWidget
{
	Q_OBJECT

	QTime time;
	QTimer timer;
	QTextEdit *textEdit;
	QCheckBox *stop_help;
	QString input_text, octave_path;
	std::unique_ptr<OctaveConnection> octave;

	/**Listen opened session tools.*/
	void listen_tools( WidgetType type );

	/** Sets QLineEdit from keyboard signals are listen. **/
	void setLineEdit( QLineEdit *lineedit );

	BaseWidget *copyBaseWidget( QWidget * parent = NULL );


	public:

		DynamicHelp( const QString &octave_path , QWidget *parent = NULL );
		~DynamicHelp();

		/**Sets session.*/
		void setSession( Session *session );
	

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