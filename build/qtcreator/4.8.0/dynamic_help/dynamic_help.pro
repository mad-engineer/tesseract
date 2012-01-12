include(../tesseract.pri)

TEMPLATE = vclib
CONFIG += staticlib
CONFIG -= dll

PROJECT_NAME = dynamic_help

QT += core gui xml

# Includes
PROJECT_INCLUDE_PATH = $$SOLUTION_INCLUDE_PATH/$$PROJECT_NAME
INCLUDEPATH  += $$SOLUTION_INCLUDE_PATH/base \
				$$SOLUTION_INCLUDE_PATH/config

HEADERS = $$PROJECT_INCLUDE_PATH/dynamic_help.hpp

# Sources
PROJECT_SOURCE_PATH = $$SOLUTION_SOURCE_PATH/$$PROJECT_NAME
SOURCES = $$PROJECT_SOURCE_PATH/dynamic_help.cpp

win32 {

CONFIG(Debug):DESTDIR = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_DEBUG/$(ProjectName)
CONFIG(Release):DESTDIR = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_RELEASE/$(ProjectName)

} else {

CONFIG(Debug):DESTDIR = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_DEBUG/$$PROJECT_NAME
CONFIG(Release):DESTDIR = $$SOLUTION_LIB_PATH/$$ARCHITECTURE_PATH_RELEASE/$$PROJECT_NAME

}