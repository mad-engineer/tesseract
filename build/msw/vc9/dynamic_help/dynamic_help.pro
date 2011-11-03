CODECFORTR   = UTF-8
CODECFORSRC  = UTF-8

TEMPLATE = vclib
CONFIG += staticlib
CONFIG -= dll

PROJECT_NAME = dynamic_help
PROJECT_NAME_D = dynamic_helpd

PROJECT_TESSERACT_INCLUDE_PATH = ../../../../include/tesseract
PROJECT_FORMS_PATH = ../../../../forms/$$PROJECT_NAME
PROJECT_INCLUDE_PATH = ../../../../include/$$PROJECT_NAME
PROJECT_SOURCE_PATH = ../../../../src/$$PROJECT_NAME

# Input
INCLUDEPATH  = 	$$PROJECT_INCLUDE_PATH \
				$$PROJECT_TESSERACT_INCLUDE_PATH


HEADERS += $$PROJECT_INCLUDE_PATH/dynamic_help.h

SOURCES += $$PROJECT_SOURCE_PATH/dynamic_help.cpp
	
# Output		   
win32 {

	CONFIG(Debug):TARGET = $$PROJECT_NAME_D
	CONFIG(Release):TARGET = $$PROJECT_NAME
		
	CONFIG(Debug):DESTDIR = ../../../../lib/mswd/vc9/x86/$$PROJECT_NAME/$$PROJECT_NAMED
	CONFIG(Release):DESTDIR = ../../../../lib/msw/vc9/x86/$$PROJECT_NAME/$$PROJECT_NAME

	CONFIG(Debug):OBJECTS_DIR = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAME
	CONFIG(Release):OBJECTS_DIR = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAME		
	
	CONFIG(Debug):OUTBASE = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAMED
	CONFIG(Release):OUTBASE = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAME	
	
    CONFIG(Debug):MOC_DIR = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAME
	CONFIG(Release):MOC_DIR = ../../../../tmp/msw/vc9/x86/$$PROJECT_NAME
	
	CONFIG(Debug):UI_DIR = ../../../../tmp/mswd/vc9/x86/$$PROJECT_NAME
	CONFIG(Release):UI_DIR = ../../../../tmp/msw/vc9/x86/$$PROJECT_NAME
}


