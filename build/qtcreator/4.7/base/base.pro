include(../tesseract.pri)

TEMPLATE = vcapp

QT += gui \
	  core

PROJECT_NAME = base

PROJECT_LANG_PATH = $$SOLUTION_LANG_PATH/$$PROJECT_NAME
TRANSLATIONS += $$PROJECT_LANG_PATH/base_es.ts \
				$$PROJECT_LANG_PATH/base_de.ts 

# Other Projects
PROJECT_INCLUDE_PROJECTS = $$SOLUTION_INCLUDE_PATH/projects
PROJECT_INCLUDE_SVGCANVAS = $$SOLUTION_INCLUDE_PATH/svgcanvas
PROJECT_INCLUDE_OPERATIONS = $$SOLUTION_INCLUDE_PATH/operations
PROJECT_INCLUDE_DYNAMIC_HELP = $$SOLUTION_INCLUDE_PATH/dynamic_help

# Input Release Libs
PROJECT_LIB_PROJECTS = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_RELEASE/projects
PROJECT_LIB_SVGCANVAS = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_RELEASE/svgcanvas
PROJECT_LIB_OPERATIONS = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_RELEASE/operations
PROJECT_LIB_DYNAMIC_HELP = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_RELEASE/dynamic_help

# Input Debug Libs
PROJECT_LIB_PROJECTS_D = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_DEBUG/projects
PROJECT_LIB_SVGCANVAS_D = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_DEBUG/svgcanvas
PROJECT_LIB_OPERATIONS_D = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_DEBUG/operations
PROJECT_LIB_DYNAMIC_HELP_D = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_DEBUG/dynamic_help

# Input
PROJECT_INCLUDE_PATH = $$SOLUTION_INCLUDE_PATH/$$PROJECT_NAME
INCLUDEPATH += 	$$PROJECT_INCLUDE_PROJECTS \
				$$PROJECT_INCLUDE_DYNAMIC_HELP \
				$$PROJECT_INCLUDE_OPERATIONS \
				$$PROJECT_INCLUDE_SVGCANVAS \
				$(QTDIR2008)/include/QtXml \
				$(QTDIR2008)/include/QtSvg

HEADERS = $$PROJECT_INCLUDE_PATH/autocomplete.hpp \
           $$PROJECT_INCLUDE_PATH/basewidget.hpp \
           $$PROJECT_INCLUDE_PATH/command_list.hpp \
           $$PROJECT_INCLUDE_PATH/config.hpp \
           $$PROJECT_INCLUDE_PATH/editor.hpp \
           $$PROJECT_INCLUDE_PATH/generate_menu.hpp \
           $$PROJECT_INCLUDE_PATH/help.hpp \
           $$PROJECT_INCLUDE_PATH/main.hpp \
           $$PROJECT_INCLUDE_PATH/mainwindow.hpp \
           $$PROJECT_INCLUDE_PATH/navigator.hpp \
           $$PROJECT_INCLUDE_PATH/numberedtextview.hpp \
           $$PROJECT_INCLUDE_PATH/octave_connection.hpp \
           $$PROJECT_INCLUDE_PATH/operations.hpp \
		   $$PROJECT_INCLUDE_PATH/pkg_bind.hpp \
           $$PROJECT_INCLUDE_PATH/search_dialog.hpp \
           $$PROJECT_INCLUDE_PATH/session.hpp \
		   $$PROJECT_INCLUDE_PATH/simpleeditor.hpp \
		   $$PROJECT_INCLUDE_PATH/splash.hpp \
           $$PROJECT_INCLUDE_PATH/syntax.hpp \
           $$PROJECT_INCLUDE_PATH/table.hpp \
           $$PROJECT_INCLUDE_PATH/terminal.hpp \
           $$PROJECT_INCLUDE_PATH/variables_list.hpp \
           $$PROJECT_INCLUDE_PATH/window_list.hpp
		   
PROJECT_FORMS_PATH = $$SOLUTION_FORMS_PATH/$$PROJECT_NAME
FORMS  = 	$$PROJECT_FORMS_PATH/table_ui.ui

PROJECT_SOURCE_PATH = $$SOLUTION_SOURCE_PATH/$$PROJECT_NAME
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