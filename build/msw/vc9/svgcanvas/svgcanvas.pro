CODECFORTR   = UTF-8
CODECFORSRC  = UTF-8

VCPROJ_KEYWORD  = Qt4VSv1.0
QMAKE_COMPILER_DEFINES  += _MSC_VER=1500 WIN32

TEMPLATE = vclib
CONFIG += staticlib
CONFIG -= dll

QT -= gui
QT -= core
 
PROJECT_NAME = svgcanvas
PROJECT_NAME_D = svgcanvasd

PROJECT_FORMS_PATH = ../../../../forms/$$PROJECT_NAME
PROJECT_INCLUDE_PATH = ../../../../include/$$PROJECT_NAME
PROJECT_SOURCE_PATH = ../../../../src/$$PROJECT_NAME

# Input
INCLUDEPATH += 	$(QTDIR2008)/include/QtXml \
				$(QTDIR2008)/include/QtSvg \
				$(QTDIR2008)/include/QtCore \
				$(QTDIR2008)/include/QtGui \
				../../../../include/tesseract \
				../../../../include/$(ProjectName)

HEADERS = $$PROJECT_INCLUDE_PATH/svgcanvas.hpp
		   
FORMS = $$PROJECT_FORMS_PATH/export_to_dialog.ui
			
SOURCES = $$PROJECT_SOURCE_PATH/svgcanvas.cpp


# Output		   
win32 {
	
	CONFIG(Debug):TARGET = $$PROJECT_NAME_D
	CONFIG(Release):TARGET = $$PROJECT_NAME
		
	CONFIG(Debug):DESTDIR = ../../../../lib/mswd/vc9/x86/$$PROJECT_NAME
	CONFIG(Release):DESTDIR = ../../../../lib/msw/vc9/x86/$$PROJECT_NAME

	CONFIG(Debug):OBJECTS_DIR = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAME
	CONFIG(Release):OBJECTS_DIR = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAME		
	
	CONFIG(Debug):OUTBASE = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAMED
	CONFIG(Release):OUTBASE = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAME	
	
    CONFIG(Debug):MOC_DIR = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAME
	CONFIG(Release):MOC_DIR = ../../../../tmp/msw/vc9/x86/$$PROJECT_NAME
	
	CONFIG(Debug):UI_DIR = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAME
	CONFIG(Release):UI_DIR = ../../../../tmp/msw/vc9/x86/$$PROJECT_NAME
	
	CONFIG(Debug):LIBS = -lQtSvgd4 -lQtXmld4
	
	CONFIG(Release):LIBS = -lQtSvg4 -lQtXml4
	
}