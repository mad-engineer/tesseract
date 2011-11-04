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
#ifndef TESSERACT_TESSERACT_OCTAVE_CONNECTION_H
#define TESSERACT_TESSERACT_OCTAVE_CONNECTION_H

#include <QBuffer>
#include <QThread>
#include <QProcess>
#include <QTextEdit>

#include "config.h"


/** This class build QProcess and exec Octave. Octave input and output are controlled by this class.
*/
class OctaveConnection : public QProcess
{
	Q_OBJECT
	public:
	OctaveConnection(QObject * parent = 0);
	/** Sets octave path.
	 * @param path path to Octave.
	 */
	void setOctavePath(const QString &path);
	QString getOctavePath();
	void startOctave(bool quiet=false);
	//void setTextEdit(QTextEdit *text);
	/** Sends command to Octave.
	 * @param text Command to send.
	 * @param show Shows command in Terminal or not.
	 */
	void command_enter(const QString &text, bool show=true);
	/**Reset number of instrucions left to send signal command_finished.
	 */
	void reset_instrutions_left() {instructions_left_no=0;};
	private:
	int lineno, colno;
	/**Number of instructions left to end actual octave command.*/
	int instructions_left_no;
	bool debugging;
	QString octave_path;
	QString line_buffer;
	QBuffer error_buffer;
	/**Load scripts from qtoctave/scripts.*/
	void loadScripts();
	
	/**Regular expresions:*/
	
	QRegExp regexp_octave_prompt; //Used in octaveOutputSlot
	QRegExp regexp_octave_prompt2; //Used in octaveOutputSlot
	QRegExp regexp_actual_debug_line_column; //Used in octaveOutputSlot
	
	/**Init most used regular expresions*/
	void init_regular_expresions();
	
	public slots:
	void octaveOutputSlot();
	void octaveErrorOutputSlot();
	void octaveFinished(int, QProcess::ExitStatus);
	
	signals:
	/**Emits this signal when line is available from stderr of Octave.*/
	void line_ready(const QString &line);
	void output_ready(const QString &output);
	void error_ready(const QString &error);
	void command_ready(const QString &command);
	void ide_command_ready(const QString &command);

	void debug(int lineno, int colno);
	void endDebug();
	
	void clearScreen();
	
	void command_finished();
};

/**This class is for usleep doesn't depend on OS*/
class Sleep:QThread
{
	Q_OBJECT
	public:
	static void micro_sleep(unsigned long u_seconds);
};

#endif

