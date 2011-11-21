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
#ifndef TESSERACT_BASE_NAVIGATOR_HPP
#define TESSERACT_BASE_NAVIGATOR_HPP

#include <memory>
using std::tr1::shared_ptr;

#include <QWidget>
#include <QVector>
#include <QModelIndex>
#include <QMenu>
#include <QThread>
#include <QFileInfo>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QMouseEvent>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTextEdit>
#include <QProgressBar>

#ifdef TESSERACT_USE_VLD
#	include <vld.h>
#endif

#include "projects.hpp"
#include "basewidget.hpp"
#include "octave_connection.hpp"

#define QFileSystemNewModel QFileSystemModel

class QToolBar;
class QAction;
class QVBoxLayout;
class QLineEdit;
class QDirModel;
class QListView;

class Navigator : public BaseWidget
{
	Q_OBJECT

	private:
		//Project opened in this editor.
		QString project_name; 
	
		QVBoxLayout *layout;
		QToolBar *toolbar;
		//QMenuBar *menubar;
		//QStatusBar *statusbar;
		
		QMenu *context_menu;
		
		QPushButton *go;
		QComboBox *url, *filter_comboBox;
		
		//QDirModel *treemodel;
		shared_ptr<QFileSystemNewModel> listmodel;
		//QTreeView *treeview;
		QTreeView *listview;
		
		QVector<QString> backHistory;
		QVector<QString> forwardHistory;
		
		OctaveConnection *octave_connection;
		
		//List of files to copy
		QList<QFileInfo> file_list;
		QFileInfo file_list_parent_path;
		bool copy_ok, cut_ok;

		// Actions
		QAction *cut;
		QAction *copy;
		QAction *paste;
		QAction *newFolder;
		QAction *exit;
		QAction *back;
		QAction *forward;
		QAction *up;
		QAction *remove;
		QAction *rename;

		void createActions();
		//void createMenuBar();
		void createToolBar();
		void createLayout();
		void createContextMenu();
		void createConnections();
		void setUrl(const QModelIndex &index);
		void setUpActionState(const QModelIndex &index);

	public:
		// Public Constructor
		Navigator(QWidget *parent = 0);
		~Navigator();
		
		
		void setSession(Session *session);
		BaseWidget *copyBaseWidget( QWidget * parent = 0 );
		
		// Public Methods
		void setOctaveConnection(OctaveConnection *oc);
		
		QString getNavigatorCurrentPath() const;
		bool setNavigatorCurrentPath(const QString &path );

	public slots:
		void expanded(const QModelIndex &index);
		void goBack(bool checked);
		void goForward(bool checked);
		void goUp(bool checked);
		void urlButtonPressed(const QString &s=QString());
		void urlButtonPressed(bool checked);
		void mkdir();
		void contextMenu_cb( const QPoint & pos);
		void copy_cb();
		void cut_cb();
		void paste_cb();
		void remove_cb();
		void rename_cb();
		void process_end(QThread *object);
		void filter_cb(const QString &s);
		void change_cursor_cb(const QModelIndex &index);
		/**Sets active project name.*/
		void setProject( const QString &name );
};


/**ListView for Drag & Drop */
class DragDropQTreeView:public QTreeView
{
	Q_OBJECT
	public:
		DragDropQTreeView(QWidget *parent=0);
	protected:
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		QPoint dragStartPosition;
};

/**Shows window with information about copy/move/remove process.
*/
class FileActions:public QThread
{
	Q_OBJECT
	//Flags.
	bool copy_ok, move_ok, remove_ok, stop_ok;
	
	//Window widgets
	QWidget *window;
	QPushButton *cancel_button, *ok_button;
	QTextEdit *textEdit;
	QProgressBar *progressBar;
	
	//File list
	QList<QFileInfo> list;
	QString path;
	QFileInfo parent;
	
	//Copy file
	void copy(QFileInfo file, QString path);
	void cut(QFileInfo file, QString path);
	void remove(QFileInfo file);
	/** Find all files in file.
	 *  If file is not a directory, it will return file.
	 */
	QList<QFileInfo> find(QFileInfo file);
	QList<QFileInfo> find(QList<QFileInfo> files);
	
	public:
	
	FileActions(QObject *parent);
	~FileActions();
	
	/**Copy files.*/
	void copy(QFileInfo parent, QList<QFileInfo> list, QString path);
	
	void cut(QFileInfo parent, QList<QFileInfo> list, QString path);
	
	void remove(QList<QFileInfo> list);
	
	void run();
	
	public slots:
	void set_label_text(QString text);
	void stop();
	void ok_button_callback();
	
	signals:
	void process_value(int value);
	void process_end(QThread *object);
};

#endif // NAVIGATOR_H
