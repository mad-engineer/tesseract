#pragma once
#ifndef TESSERACT_BASE_GENERATE_MENU_HPP
#define TESSERACT_BASE_GENERATE_MENU_HPP

#include <QProcess>
#include <QGroupBox>
#include <QComboBox>
#include <QScrollArea>
#include <QTextBrowser>

#ifdef TESSERACT_USE_VLD
#	include <vld.h>
#endif

#include "operations.hpp"
#include "mainwindow.hpp"
#include "octave_connection.hpp"

#define MENU_TRANSLATE(s) QCoreApplication::translate("", s.toLocal8Bit().data()).toLocal8Bit().data()

class MenuExtCallBack;

/**This class generates new menus from dirs.
 */
class GenerateMenu:public QObject
{
	Q_OBJECT
	public:
	GenerateMenu(MainWindow *mainwindow, Operations *operations);
	/** Set path to read menus entries.
	 * @param path path to menus.
	 */
	void setPath(const QString &path);
	/** Load menus. Menus are read from path.
	 */
	void load_menu();
	private:
	void load_menu(const QString &dir_name, QMenu *parent_menu);
		
	//Directorio en el que se encuentran los mens
	QString path;
	Operations *operations;
	MainWindow *mainwindow;
	/**Parse files with .menu extension.*/
	bool process_menu_file(const QString &file,  QStringList &  input_labels,  QStringList &  input_parameters, QStringList & output_labels, QStringList & output_parameters, QString & command, QString & menu_name, QString & help, bool & accept_blank_parameters, bool auto_exec);
	
	MenuExtCallBack *process_menu_file(QString _file);
	
	/**Removes path from file_path.*/
	QString menu_path(QString file_path);
	/**Finds icon for given menu.*/
	QString find_icon(const QString &file_path, const QString &menu);
};

/**Simple Callback for menus genetates using GenerateMenu. This callback is used when menu file is executable. When menu item is selected, menu file is executed and result is sent to OctaveConnection.*/
class MenuCallBack:public QObject
{
	Q_OBJECT

	QString output;
	QProcess process;
	QString menu_name;
	OctaveConnection *octave_connection;


	public:

		MenuCallBack( const QString &menu_name , OctaveConnection *oc );


	public slots:

		void actions_callback();
		void readyReadStandardOutput();
		void finished( int exitCode , QProcess::ExitStatus exitStatus );
};

/**Callback for ".menu" files. See QtOctave doc for ".menu" files.*/
class MenuFileCallBack: public QObject
{
	Q_OBJECT
	public:
		MenuFileCallBack(const QString &menu_name, OctaveConnection *oc, Operations *operations, QStringList &  input_labels,  QStringList &  input_parameters, QStringList & output_labels, QStringList & output_parameters, QString & command, QString & help, bool accept_blank_parameters);
	private:
		Operations *operations;
		QString menu_name;
		OctaveConnection *oc;
		QStringList input_parameters, output_parameters, output_labels, input_labels;
		QString command, help;
		bool accept_blank_parameters;
	public slots:
		void actions_callback();
	
};

/**Base class for input widgets in menus.*/
class InputWidget:public QWidget
{
	Q_OBJECT


	public:

		InputWidget(QWidget *parent=0);
		virtual QString parameter()=0;
};

/**Simple line edit for menus.*/
class LineEdit:public InputWidget
{
	Q_OBJECT


	public:

		LineEdit(const QString &label, QWidget *parent=0);
		QLabel *label;
		QLineEdit *lineedit;
		QString parameter();
		void setParameter( const QString &param );
};

/**Simple line edit and select file dialog for menus.*/
class FileEdit:public InputWidget
{
	Q_OBJECT


	public:

		FileEdit(const QString &label, QWidget *parent=0);
		QLabel *label;
		QLineEdit *lineedit;
		QPushButton *file_button;
		QString parameter();
		void setParameter( const QString &param );


	public slots:

		void file_button_callback();
};

/**Simple combobox for menus.*/
class ComboBox:public InputWidget
{
	Q_OBJECT


	public:

		ComboBox(const QString &label, QWidget *parent=0);
		QLabel *label;
		QComboBox *combobox;
		QString parameter();
		void setParameter( const QString &param );
};


/**Callback for ".menu" files. See QtOctave doc for ".menu" files.*/
class MenuExtCallBack: public QWidget
{
	Q_OBJECT

	OctaveConnection *oc;
	QList<InputWidget*>  input, output;
	QString command, help;
	QGroupBox *input_box, *output_box;
	QWidget *input_area, *output_area;
	//QTextBrowser *help_widget;
	bool accept_blank_parameters;
	QPushButton *ok_button, *copy_clipboard_button, *help_button, *cancel_button;
	bool auto_exec_ok;

	QString generate_command();


	public:

		MenuExtCallBack(QWidget *parent=0);
		void setOctaveConnection(OctaveConnection *oc);
		void addInput(InputWidget *input);
		void addOutput(InputWidget *output);
		void addHelp(const QString &help );
		void addCommand( const QString &command );
		void setAcceptBlankParameters(bool accept_blank_parameters);
		void setAutoExec(bool auto_exec_ok);


	public slots:

		void ok_button_callback();
		void copy_clipboard_button_callback();
		void cancel_button_callback();
		void help_button_callback();
		void actions_callback();
};

#endif
