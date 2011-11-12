/* This file is part of the KDE libraries
    Copyright (C) 2005, 2006 KJSEmbed Authors
    See included AUTHORS file.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#pragma once
#ifndef TESSERACT_BASE_NUMBEREDTEXTVIEW_HPP
#define TESSERACT_BASE_NUMBEREDTEXTVIEW_HPP

#include <QMenu>
#include <QLabel>
#include <QFrame>
#include <QPixmap>
#include <QTextCursor>
#include <QVBoxLayout>
#include <QHBoxLayout>

#ifdef TESSERACT_USE_VLD
#	include <vld.h>
#endif

#include "simpleeditor.hpp"

class CodeEdit;
class QHBoxLayout;

/**
 * @internal Used to display the numbers.
 */
class NumberBar : public QWidget
{
    Q_OBJECT

	SimpleEditor *edit;
	QPixmap stopMarker;
	QPixmap currentMarker;
	QPixmap bugMarker;
	QList<int> breakpoints;
	int currentLine;
	int bugLine;
	QRect stopRect;
	QRect currentRect;
	QRect bugRect;


	protected:

		bool event( QEvent *ev );


	public:

		NumberBar( QWidget *parent );
		~NumberBar();

		void setCurrentLine( int lineno );
		void setBugLine( int lineno );
		void toggleBreakpoint( int lineno );
		QList<int> *getBreakpoints();

		void setTextEdit( SimpleEditor *edit );
		void paintEvent( QPaintEvent *ev );
};

/**
 * Displays a CodeEdit with line numbers.
 */
class NumberedTextView : public QFrame
{
    Q_OBJECT
	QMenu *contextMenu;
	QString filePath;
	QLabel *line_column_label;
	SimpleEditor *view;
	NumberBar *numbers;
	QHBoxLayout *hbox;
	QVBoxLayout *vbox;
	int currentLine;
	QTextCursor highlight;
	bool textModifiedOk;

	void createConnections();
	void createContextMenu();

	protected:

		void contextMenuEvent ( QContextMenuEvent * event );

	public:

		NumberedTextView( QWidget *parent = 0 , SimpleEditor *textEdit=new SimpleEditor() );
		~NumberedTextView();

		QList<int> *getBreakpoints();

		void open( const QString &path );
	    
		/**Saves file to path. @return true if all is OK.*/
		bool save( QString path = QString());

		const QString &path();
		void setPath( const QString &path );
	    
		bool modified();
		void setModified(bool modify);

		/** Returns the CodeEdit of the main view. */
		SimpleEditor *textEdit() const { return view; }

		/**
		 * Sets the line that should have the current line indicator.
		 * A value of -1 indicates no line should show the indicator.
		 */
		void setCurrentLine( int lineno );

		/**
		 * Toggle breakpoint
		 */
		void toggleBreakpoint( int lineno );

		/**
		 * Sets the line that should have the bug line indicator.
		 * A value of -1 indicates no line should show the indicator.
		 */
		void setBugLine( int lineno );

		/** @internal Used to get tooltip events from the view for the hover signal. */
		bool eventFilter( QObject *obj, QEvent *event );
	    
		/**Indent selected text.*/
		void indent();
	    
		/**UnIndent selected text.*/
		void unindent();
	    
		/**Comment selected text.*/
		void comment();
	    
		/**UnComment selected text.*/
		void uncomment();


	signals:
		/**
		 * Emitted when the mouse is hovered over the text edit component.
		 * @param word The word under the mouse pointer
		 */
		void mouseHover( const QString &word );

		/**
		 * Emitted when the mouse is hovered over the text edit component.
		 * @param pos The position of the mouse pointer.
		 * @param word The word under the mouse pointer
		 */
		void mouseHover( const QPoint &pos, const QString &word );
	    
		/**
		 * Emitted when file is changed.
		 */
		void textModified();


	protected slots:

		/** @internal Used to update the highlight on the current line. */
		void textChanged( int pos, int added, int removed );


	public slots:

		void cursor_moved_cb();
		void contextMenuPopUp( const QPoint & pos );
};

#endif
