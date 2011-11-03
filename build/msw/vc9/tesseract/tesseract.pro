TEMPLATE = app

CODECFORTR   = UTF-8
CODECFORSRC  = UTF-8

VCPROJ_KEYWORD  = Qt4VSv1.0
QMAKE_COMPILER_DEFINES  += _MSC_VER=1500 WIN32

PROJECT_NAME = tesseract

PROJECT_LANG_PATH = ../../../../lang/$$PROJECT_NAME
TRANSLATIONS += $$PROJECT_LANG_PATH/tesseract_es.ts \
				$$PROJECT_LANG_PATH/tesseract_de.ts 

DEFINES += COMPILE_PORTABLE

PROJECT_SOURCE_PATH = ../../../../src/$$PROJECT_NAME
PROJECT_FORMS_PATH = ../../../../forms/$$PROJECT_NAME
PROJECT_INCLUDE_PATH = ../../../../include/$$PROJECT_NAME

# Other Projects
PROJECT_INCLUDE_PROJECTS = ../../../../include/projects
PROJECT_INCLUDE_SVGCANVAS = ../../../../include/svgcanvas
PROJECT_INCLUDE_OPERATIONS = ../../../../include/operations
PROJECT_INCLUDE_DYNAMIC_HELP = ../../../../include/dynamic_help

# Input Release Libs
PROJECT_LIB_PROJECTS = ../../../../lib/msw/vc9/x86/projects
PROJECT_LIB_SVGCANVAS = ../../../../lib/msw/vc9/x86/svgcanvas
PROJECT_LIB_OPERATIONS = ../../../../lib/msw/vc9/x86/operations
PROJECT_LIB_DYNAMIC_HELP = ../../../../lib/msw/vc9/x86/dynamic_help

# Input Debug Libs
PROJECT_LIB_PROJECTS_D = ../../../../lib/mswd/vc9/x86/projects
PROJECT_LIB_SVGCANVAS_D = ../../../../lib/mswd/vc9/x86/svgcanvas
PROJECT_LIB_OPERATIONS_D = ../../../../lib/mswd/vc9/x86/operations
PROJECT_LIB_DYNAMIC_HELP_D = ../../../../lib/mswd/vc9/x86/dynamic_help

INCLUDEPATH = 	$$PROJECT_INCLUDE_PATH \
				$$PROJECT_INCLUDE_PROJECTS \
				$$PROJECT_INCLUDE_DYNAMIC_HELP \
				$$PROJECT_INCLUDE_OPERATIONS \
				$$PROJECT_INCLUDE_SVGCANVAS \
				$(QTDIR2008)/include/QtXml \
				$(QTDIR2008)/include/QtSvg \
				$(BOOST)/

# Input
HEADERS = $$PROJECT_INCLUDE_PATH/autocomplete.h \
           $$PROJECT_INCLUDE_PATH/basewidget.h \
           $$PROJECT_INCLUDE_PATH/command_list.h \
           $$PROJECT_INCLUDE_PATH/config.h \
           $$PROJECT_INCLUDE_PATH/editor.h \
           $$PROJECT_INCLUDE_PATH/generate_menu.h \
           $$PROJECT_INCLUDE_PATH/help.h \
           $$PROJECT_INCLUDE_PATH/main.h \
           $$PROJECT_INCLUDE_PATH/mainwindow.h \
           $$PROJECT_INCLUDE_PATH/navigator.h \
           $$PROJECT_INCLUDE_PATH/numberedtextview.h \
           $$PROJECT_INCLUDE_PATH/octave_connection.h \
           $$PROJECT_INCLUDE_PATH/operations.h \
		   $$PROJECT_INCLUDE_PATH/pkg_bind.h \
           $$PROJECT_INCLUDE_PATH/search_dialog.h \
           $$PROJECT_INCLUDE_PATH/session.h \
		   $$PROJECT_INCLUDE_PATH/simpleeditor.h \
		   $$PROJECT_INCLUDE_PATH/splash.h \
           $$PROJECT_INCLUDE_PATH/syntax.h \
           $$PROJECT_INCLUDE_PATH/table.h \
           $$PROJECT_INCLUDE_PATH/terminal.h \
           $$PROJECT_INCLUDE_PATH/variables_list.h \
           $$PROJECT_INCLUDE_PATH/window_list.h

FORMS  = 	$$PROJECT_FORMS_PATH/table_ui.ui

SOURCES  = $$PROJECT_SOURCE_PATH/autocomplete.cpp \
		   $$PROJECT_SOURCE_PATH/splash.cpp \
           $$PROJECT_SOURCE_PATH/basewidget.cpp \
           $$PROJECT_SOURCE_PATH/command_list.cpp \
           $$PROJECT_SOURCE_PATH/config.cpp \
           $$PROJECT_SOURCE_PATH/editor.cpp \
           $$PROJECT_SOURCE_PATH/generate_menu.cpp \
           $$PROJECT_SOURCE_PATH/help.cpp \
           $$PROJECT_SOURCE_PATH/main.cpp \
           $$PROJECT_SOURCE_PATH/mainwindow.cpp \
           $$PROJECT_SOURCE_PATH/navigator.cpp \
           $$PROJECT_SOURCE_PATH/numberedtextview.cpp \
           $$PROJECT_SOURCE_PATH/octave_connection.cpp \
		   $$PROJECT_SOURCE_PATH/pkg_bind.cpp \
           $$PROJECT_SOURCE_PATH/search_dialog.cpp \
		   $$PROJECT_SOURCE_PATH/simpleeditor.cpp \
		   $$PROJECT_SOURCE_PATH/splash.cpp \
           $$PROJECT_SOURCE_PATH/session.cpp \
           $$PROJECT_SOURCE_PATH/syntax.cpp \
           $$PROJECT_SOURCE_PATH/table.cpp \
           $$PROJECT_SOURCE_PATH/terminal.cpp \
           $$PROJECT_SOURCE_PATH/variables_list.cpp \
           $$PROJECT_SOURCE_PATH/window_list.cpp

# Output

QMAKE_CXXFLAGS += /Fd$(IntDir)\$(ProjectName).pdb

win32 {

	CONFIG(Debug):DEFINES += DEBUG
	CONFIG(Release):DEFINES += NDEBUG

	CONFIG(Debug):QMAKE_POST_LINK = ../../../../scripts/mswd/vc9/x86/$$PROJECT_NAME/copy_images.bat
	CONFIG(Release):QMAKE_POST_LINK = ../../../../scripts/msw/vc9/x86/$$PROJECT_NAME/copy_images.bat

	CONFIG(Debug):DESTDIR = ../../../../bin/mswd/vc9/x86/
	CONFIG(Release):DESTDIR = ../../../../bin/msw/vc9/x86/

	CONFIG(Debug):OBJECTS_DIR = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAME	
	CONFIG(Release):OBJECTS_DIR = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAME		

	CONFIG(Debug):OUTBASE = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAME	
	CONFIG(Release):OUTBASE = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAME	

    CONFIG(Debug):MOC_DIR = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAME	
	CONFIG(Release):MOC_DIR = ../../../../tmp/msw/vc9/x86/$$PROJECT_NAME

	CONFIG(Debug):UI_DIR = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAME	
	CONFIG(Release):UI_DIR = ../../../../tmp/msw/vc9/x86/$$PROJECT_NAME

	CONFIG(Debug):LIBS = 	-lQtSvgd4 -lQtXmld4 -lsvgcanvasd -loperationsd -lprojectsd -ldynamic_helpd \
							-L$$PROJECT_LIB_PROJECTS_D \
							-L$$PROJECT_LIB_DYNAMIC_HELP_D \
							-L$$PROJECT_LIB_OPERATIONS_D \
							-L$$PROJECT_LIB_SVGCANVAS_D 

	CONFIG(Release):LIBS = -lQtSvg4 -lQtXml4 -lsvgcanvas -loperations -lprojects -ldynamic_help \
							-L$$PROJECT_LIB_PROJECTS \
							-L$$PROJECT_LIB_DYNAMIC_HELP \
							-L$$PROJECT_LIB_OPERATIONS \
							-L$$PROJECT_LIB_SVGCANVAS 
}