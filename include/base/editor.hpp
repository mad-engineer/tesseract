/* Copyright (C) 2006, 2007, 2008 P.L. Lucas
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
#ifndef TESSERACT_BASE_EDITOR_HPP
#define TESSERACT_BASE_EDITOR_HPP

#include <QAction>
#include <QToolBar>
#include <QTabWidget>
#include <QDropEvent>
#include <QDockWidget>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QAbstractListModel>

#ifdef TESSERACT_USE_VLD
#	include <vld.h>
#endif

#include "syntax.hpp"
#include "projects.hpp"
#include "basewidget.hpp"
#include "simpleeditor.hpp"
#include "search_dialog.hpp"
#include "numberedtextview.hpp"
#include "octave_connection.hpp"

class ClipboardListView;

// Syntax highlighter editor. Supports several editors and auto completion code.
class Editor: public BaseWidget
{
	Q_OBJECT

	// Editors Toolbar
	QToolBar *toolBar;

	// Context Menu inside the editor
	QMenu *contextMenu;

	//Project opened in this editor.
	QString project_name;

	// Tabbed editor for multiple Documents
	QTabWidget *tabWidget;

	// Pointer to octave
	OctaveConnection *octave_connection;

	// Searching things
	SearchDialog *search_dialog;

	// Small File Explorer
	QListView *list_files;
	QDockWidget *list_files_dock;

	// Clipboard for Copy/Paste Operations
	QDockWidget list_clipboard_dock;
	ClipboardListView *list_clipboard;

	// Pointer to Numberbar left from the editor
	NumberedTextView *currentNtv;

	// Actions
	QAction *actionNew, *actionOpen, *actionSave, *actionSaveAs, *actionPrint, *actionClose, *actionClone;
	QAction *actionUndo, *actionRedo,*actionCut, *actionCopy, *actionPaste;
	QAction *actionSearch, *actionRun, *actionDebug, *actionStep, *actionSendToOctave;
	QAction *actionIndent, *actionUnindent, *actionComment, *actionUncomment, *actionSimpleRCS;
	QAction *actionToggleBreakPoint, *actionCloseAll;

	QMenu *menuFile, *menuEdit, *menuRun, *menuConfig, *menuDocks, *menuTools;

	void saveProject();

	/**Defines a new label for the page at position index's tab and updates list_files*/
	void setTabText(int index, const QString & label);
	/**Updates list_files*/
	void updateFileList();

	/**Add new empty tab to editor*/
	void newEditorTab();

	// Creates actions for the Objects
	void createActions();
	void createActionsMenu();
	void createActionsMenuRun();
	void createActionsMenuFile();
	void createActionsMenuEdit();
	void createActionsToolBarMain();

	// Connects the signals with their objects
	void createConnections();
	void createConnectionsMenuFile();
	void createConnectionsMenuEdit();

	// Create and add additional actions to the context menu
	void createContextMenu();

	void createToolBars();
	void createToolBarMain();

	void createMenus();
	void createMenuRun();
	void createMenuEdit();
	void createMenuFile();
	void createMenuDocks();
	void createMenuConfig();


	protected:

		//   void dropEvent ( QDropEvent * event );
		//   void dragEnterEvent(QDragEnterEvent *event);
		void closeEvent ( QCloseEvent * event );
		void resizeEvent( QResizeEvent * event );


	public slots:

		/**Execute actions as copy, paste, save, run, ...*/
		void toolbar_action(QAction*);

		/**Search word inserted in dialog in code.*/
		void search();

		/**Replace word inserted in dialog in code.*/
		void replace();

		/**Put/Quit break point to debug Octave code.*/
		void toggleBreakpoint(int lineno);

		/**Another document is selected to edit.*/
		void tabChanged(int index);

		/**Sets actual document modify flag true or false.*/
		void textModified();

		/**Starts debug of Octave code.*/
		void debug(int lineno, int colno);

		/**Ends of debug of Octave code.*/
		void endDebug();

		/**File selected in list file*/
		void file_selected(const QModelIndex & index);

		/**Open file.*/
		void openFile( const QString &file=QString() );

		/**Emits dynamic_help_required*/
		void emit_dynamic_help_required( const QString &text );

		/**Sets active project name.*/
		void setProject( const QString &name );

		/**Indent text.*/
		void indent_callback();

		/**Indent text.*/
		void unindent_callback();

		/**Indent text.*/
		void comment_callback();

		/**Indent text.*/
		void uncomment_callback();

		/**Shows simple_rcs tool for actual file*/
		void simple_rcs_callback();

		/**Sets/unsets breakpoint for debug*/
		void toggleBreakPoint_callback();

		/**Close window*/
		void close_editor();

		/**Print file*/
		void print_callback();

		/**Shows edit menu*/
		void show_edit_menu();

		/**Clone editor tab. Clone actual editor tab.*/
		void clone_callback();

		/**Text in clipboard has been selected double clicked, insert in text.*/
		void clipboard_double_clicked(const QModelIndex &);

		// Open the customized editor context menu
		void customContextMenuPopUp( const QPoint & /*pos*/);

	public:

		Editor(QWidget *parent);
		~Editor();

		/**Set conection with Octave.*/
		void setOctaveConnection(OctaveConnection *octave_connection);

		/**Gets active project name.*/
		QString getProject();

		/**Load a list of files.*/
		void loadFiles(const QStringList &files);

		/**Close one tab. If close_all_tabs== true close all tabs. It's usefull for load projects.*/
		void closeTabs(bool close_all_tabs);

		void setSession(Session *session);
		BaseWidget *copyBaseWidget( QWidget * parent = 0 );
};


class ListModel: public QAbstractListModel
{
	Q_OBJECT

	Editor *editor;

	struct ListItem
	{
		QString name;
		int position;
	};

	QList <ListItem> list;


	public:

		ListModel(QObject *parent = 0, Editor *editor = 0 );

		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		QVariant data(const QModelIndex &index, int role) const;

		/**Clear data*/
		void clear();
		void append( const QString &name , int position );
		void update();
		int position(const QModelIndex &index);
		QModelIndex position_index(int position);

		Qt::DropActions supportedDropActions() const;

		bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

		Qt::ItemFlags flags(const QModelIndex &index) const;

		QStringList mimeTypes() const;
};

class ClipboardListView : public QListView
{
	Q_OBJECT

	QMenu *popup;
	QAction *stopAction;
	QStringListModel *_stringModel;


	protected:

		void contextMenuEvent ( QContextMenuEvent * event );


	public:

		ClipboardListView(QWidget *parent = 0);
		~ClipboardListView();
		QStringListModel *stringModel();

		/**Saves state of ClipboardListView in xml.
		 * @param partOk if true, xml is part of other xml file*/
		void saveStateXML(QXmlStreamWriter &out, bool partOk = false);
		void loadStateXML(QXmlStreamReader &in, bool partOk = false);


	public slots:

		void edit_callback();
		void remove_callback();
		void remove_all_callback();
		void sort_ascending_callback();
		void sort_descending_callback();
		void up_callback();
		void down_callback();
		void top_callback();
		void bottom_callback();

		/**Text in clipboard has been selected.*/
		void clipboard_selected(const QModelIndex &);

		/**New clipboard data*/
		void clipboard_new_data_callback();
};

#endif
