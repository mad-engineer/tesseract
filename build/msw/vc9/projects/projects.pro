CODECFORTR   = UTF-8
CODECFORSRC  = UTF-8

TEMPLATE = vclib
CONFIG += staticlib
CONFIG -= dll

PROJECT_NAME = projects
PROJECT_NAME_D = projectsd

PROJECT_FORMS_PATH = ../../../../forms/$$PROJECT_NAME
PROJECT_INCLUDE_PATH = ../../../../include/$$PROJECT_NAME
PROJECT_SOURCE_PATH = ../../../../src/$$PROJECT_NAME


# Input
INCLUDEPATH  = ../../../../include/projects \
               ../../../../include/tesseract

HEADERS = 	$$PROJECT_INCLUDE_PATH/projects.h
		   
FORMS = 	$$PROJECT_FORMS_PATH/projects.ui \
			$$PROJECT_FORMS_PATH/newprojectdialog.ui
			
SOURCES = 	$$PROJECT_SOURCE_PATH/projects.cpp

DEFINES += COMPILE_PORTABLE_TESSERACT
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
}