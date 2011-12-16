/* Copyright (C) 2006 P.L. Lucas
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

#pragma once
#ifndef TESSERACT_BASE_TERMINAL_HPP
#define TESSERACT_BASE_TERMINAL_HPP

#include <QFile>
#include <QMdiArea>
#include <QTextEdit>
#include <QPushButton>
#include <QCloseEvent>

#ifdef TESSERACT_USE_VLD
#	include <vld.h>
#endif

#include "basewidget.hpp"
#include "dynamic_help.hpp"
#include "autocomplete.hpp"
#include "command_list.hpp"
#include "octave_connection.hpp"

/** Builds windows with QtextEdit and QLineEdit. QTextEdit shows OctaveConnection output.
 * QLineEdit is used to write commands.
 * 
 */

class Terminal : public BaseWidget
{
	Q_OBJECT

	QTextEdit *text;
	Autocomplete *combo_box;
	QPushButton *show_commands_button;
	OctaveConnection *octave_connection;

	//Formats of entries
	QTextCharFormat normal_format, error_format,
		command_format, ide_command_format;

	bool diary_ok; //Controls diary output
	QFile diary_file; //File to save diary

	bool show_ide_commands_ok;

	int lines_in_terminal;
	int cols_in_terminal;
	void remove_lines( QTextCursor &cursor );

	void closeEvent( QCloseEvent * );

	/**Regular expressions:*/
	QRegExp re; //Used in line_ready
	QRegExp regexp_octave_prompt; //Used in remove_lines

	/**Init most used regular expressions */
	void init_regular_expresions();


	protected:

		//Drag and drop
		void dropEvent ( QDropEvent * event );
		void dragEnterEvent( QDragEnterEvent *event );

	signals:

		void sendConfiguration
		( 
			string const &node, 
			shared_ptr<map<string,string>> const &defaults, 
			shared_ptr<map<string,string>> const &limitmin,
			shared_ptr<map<string,string>> const &limitmax
		);
	
	public:

		Terminal( QWidget * parent = 0 );
		~Terminal();

		void initConfig();
		QTextEdit *getTextEdit();

		OctaveConnection *getOctaveConnection();
		void command_enter( const QString &text );
		void setOctaveConnection( OctaveConnection *octave_connection );

		void setSession( Session *session );
		BaseWidget *copyBaseWidget( QWidget * parent = 0 );
	
		/**Use 'save' octave commend to save variables.*/
		void saveVariables();
		Autocomplete *getAutocomplete();
	
		QMdiArea *work_space;


	public slots:

		void clear_callback();
		void return_pressed();
		void stop_process_callback();
		void line_ready( QString line );
		void write_error( QString error );
		void completion_matches_callback();
		void write_output( QString output );
		void clear_command_line_first_time();
		CommandList *show_commands_callback();
		void write_command( QString command );
		void textChanged( const QString &text );
		void write_ide_command( QString command );
		void setProject( QString project = QString() );
};

#endif
