include(../tesseract.pri)

TEMPLATE = vclib
CONFIG += staticlib
CONFIG -= dll

QT -= gui
QT -= core
 
PROJECT_NAME = svgcanvas

# Includes
PROJECT_INCLUDE_PATH = $$SOLUTION_INCLUDE_PATH/$$PROJECT_NAME
INCLUDEPATH += 	$(QTDIR2008)/include/QtXml \
				$(QTDIR2008)/include/QtSvg \
				$(QTDIR2008)/include/QtCore \
				$(QTDIR2008)/include/QtGui \
				../../../../include/base

HEADERS = $$PROJECT_INCLUDE_PATH/svgcanvas.hpp

# Forms
PROJECT_FORMS_PATH = $$SOLUTION_FORMS_PATH/$$PROJECT_NAME	
FORMS = $$PROJECT_FORMS_PATH/export_to_dialog.ui

# Sources
PROJECT_SOURCE_PATH = $$SOLUTION_SOURCE_PATH/$$PROJECT_NAME
SOURCES = $$PROJECT_SOURCE_PATH/svgcanvas.cpp

# Lib input		   
CONFIG(Debug):LIBS += -lQtSvgd4 -lQtXmld4
CONFIG(Release):LIBS += -lQtSvg4 -lQtXml4

win32 {

CONFIG(Debug):DESTDIR = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_DEBUG/$(ProjectName)
CONFIG(Release):DESTDIR = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_RELEASE/$(ProjectName)

} else {

CONFIG(Debug):DESTDIR = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_DEBUG/$$PROJECT_NAME
CONFIG(Release):DESTDIR = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_RELEASE/$$PROJECT_NAME

}