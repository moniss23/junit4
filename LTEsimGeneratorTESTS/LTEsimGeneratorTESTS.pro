#-------------------------------------------------
#
# Project created by QtCreator 2016-07-29T16:56:01
#
#-------------------------------------------------

QT       += testlib
QT       += core
QT       += gui
QT       += xml
QT       += widgets


TARGET = ltesimgeneratortests
#CONFIG   += console
CONFIG   += testcase
CONFIG   += c++11

TEMPLATE = app
INCLUDEPATH += ../LTEsimGeneratorGui

DEFINES += SRCDIR=\\\"$$PWD/\\\"

SOURCES += \
    ../LTEsimGeneratorGUI/AppSettings/appsettings.cpp \
    ../LTEsimGeneratorGUI/ManagementWindow/Encryption/encryption.cpp \
    ltesimgeneratortests.cpp

HEADERS  += \
    ../LTEsimGeneratorGui/AppSettings/appsettings.h \
    ../LTEsimGeneratorGUI/ManagementWindow/Encryption/encryption.h

