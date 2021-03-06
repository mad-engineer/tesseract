include(../tesseract.pri)

TEMPLATE = vclib
CONFIG += staticlib
CONFIG -= dll

QT += core gui xml

PROJECT_NAME = projects

# Input
PROJECT_INCLUDE_PATH = $$SOLUTION_INCLUDE_PATH/$$PROJECT_NAME
INCLUDEPATH  += $$SOLUTION_INCLUDE_PATH\\base
HEADERS = 	$$PROJECT_INCLUDE_PATH\\projects.hpp
		   
# Forms
PROJECT_FORMS_PATH = $$SOLUTION_FORMS_PATH/$$PROJECT_NAME	 
FORMS = 	$$PROJECT_FORMS_PATH\\projects.ui \
			$$PROJECT_FORMS_PATH\\newprojectdialog.ui

#Sources		
PROJECT_SOURCE_PATH = $$SOLUTION_SOURCE_PATH/$$PROJECT_NAME
SOURCES = 	$$PROJECT_SOURCE_PATH/projects.cpp

win32 {

CONFIG(Debug):DESTDIR = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_DEBUG/$(ProjectName)
CONFIG(Release):DESTDIR = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_RELEASE/$(ProjectName)

} else {

CONFIG(Debug):DESTDIR = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_DEBUG/$$PROJECT_NAME
CONFIG(Release):DESTDIR = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_RELEASE/$$PROJECT_NAME

}