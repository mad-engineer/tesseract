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

#pragma once
#ifndef TESSERACT_TESSERACT_SIMPLEEDITOR_H
#define TESSERACT_TESSERACT_SIMPLEEDITOR_H

#include <QCompleter>
#include <QPlainTextEdit>
#include <QStringListModel>

#include "syntax.h"

class SimpleEditor:public QPlainTextEdit
{
	Q_OBJECT
	QString fileName;
	QTextCharFormat charFormat;
	QCompleter *completer;
	QStringListModel *completerModel;
	Syntax *syntax;
	QStringList comands_completion_list;
	
	bool auto_indent, automatic_indention_statement_ok;
	
	//QTextDocument which contains document
	//It's defined to control when QTextDocument is deleted in views cloned
	//QTextDocument *_document;
	
	public:
	bool firtsTimeUsedOk;
	
	SimpleEditor(QWidget * parent = 0);
	~SimpleEditor();
	
	/**Makes document the new document of the text editor. The parent QObject of the provided document remains the owner of the object. If the current document is a child of the text editor, then it is deleted.The document must have a document layout that inherits QPlainTextDocumentLayout (see QTextDocument::setDocumentLayout()). See also document().<br>
	 * It's reimplemented to control _document deleted.
	 */
	void setDocument ( QTextDocument * document );
	
	
	/**Load a file.
	 * @param file file name to load
	 */
	bool load(const QString &file);
	bool save();
	QString getFileName();
	void setFile(const QString &file);
	
	/**Loads XML file with syntax description.
	 */
	void loadSyntaxXMLDescription();
	
	void setCharFormat( const QTextCharFormat &charFormat );
	
	
	/**List of y top left positions of bounding rects of each visible block of text.
	 * @param list List of top left positions.
	 * @param first_line First visible block in TextEdit.
	 */
	void publicBlockBoundingRectList(QVector<qreal>  &list, int &first_line);
	
	public slots:
	
	void activated( const QString & text );
	void cursorPositionChangedCallBack();
	void autoComplete(int size=3);
	void autoComplete(int position, int charsRemoved, int charsAdded);
	
	protected:
	virtual void keyPressEvent(QKeyEvent * e);
	//virtual void focusInEvent(QFocusEvent  * event);
	

	signals:
	/**Dinamic help required.*/
	void dynamic_help_required(const QString &text);
	
	///**Text modified.*/
	//void text_modified(bool ok);
	
	//void toggleBreakpoint(int lineno);
	
	//void focusChanged(QWidget *);
}
;
#endif

