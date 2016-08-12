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
INCLUDEPATH += ../LTEsimGeneratorGUI

DEFINES += SRCDIR=\\\"$$PWD/\\\"

SOURCES += \
    ../LTEsimGeneratorGUI/ManagementWindow/Helpdialog/helpdialog.cpp \
    ../LTEsimGeneratorGUI/ManagementWindow/ProjectManagement/projectmanagement.cpp \
    ../LTEsimGeneratorGUI/DataSystem/datasystem.cpp \
    ../LTEsimGeneratorGUI/ManagementWindow/AddProjectWindow/addProjectWindow.cpp \
    ../LTEsimGeneratorGUI/Data/project.cpp \
    ../LTEsimGeneratorGUI/Data/trafficdata.cpp \
    ../LTEsimGeneratorGUI/Data/appglobaldata.cpp \
    ../LTEsimGeneratorGUI/ManagementWindow/ProjectManagement/importprojectwindow.cpp \
    ../LTEsimGeneratorGUI/Data/filemanager.cpp \
    ltesimgeneratortests.cpp \
    UITests/addprojectwindowtest.cpp \
    UITests/projectmanagementwindowtest.cpp

HEADERS  += \
    ../LTEsimGeneratorGUI/ManagementWindow/Helpdialog/helpdialog.h \
    ../LTEsimGeneratorGUI/ManagementWindow/ProjectManagement/projectmanagement.h \
    ../LTEsimGeneratorGUI/DataSystem/datasystem.h \
    ../LTEsimGeneratorGUI/ManagementWindow/AddProjectWindow/addProjectWindow.h \
    ../LTEsimGeneratorGUI/Data/project.h \
    ../LTEsimGeneratorGUI/Data/trafficdata.h \
    ../LTEsimGeneratorGUI/dataelementsinterface.h \
    ../LTEsimGeneratorGUI/Data/serializeinterface.h \
    ../LTEsimGeneratorGUI/Data/appglobaldata.h \
    ../LTEsimGeneratorGUI/Data/filemanager.h \
    ../LTEsimGeneratorGUI/ManagementWindow/ProjectManagement/importprojectwindow.h \
    UITests/addprojectwindowtest.h \
    UITests/projectmanagementwindowtest.h

FORMS    += \
    ../LTEsimGeneratorGUI/Ui/helpdialog.ui \
    ../LTEsimGeneratorGUI/Ui/projectmanagement.ui \
    ../LTEsimGeneratorGUI/Ui/addProjectWindow.ui \
    ../LTEsimGeneratorGUI/Ui/uctoolform.ui \

OTHER_FILES += \
    ../LTEsimGeneratorGUI/logoLTEsim.png

RESOURCES += \
    ../LTEsimGeneratorGUI/Resource.qrc

DISTFILES += \
    ../LTEsimGeneratorGUI/Images/MapItems/axis.png \
    ../LTEsimGeneratorGUI/Images/MapItems/dottedline.png \
    ../LTEsimGeneratorGUI/Images/MapItems/dottedline_vertical.png \
    ../LTEsimGeneratorGUI/Images/MapItems/line.png \
    ../LTEsimGeneratorGUI/Images/MapItems/line_vertical.png \
    ../LTEsimGeneratorGUI/Images/MapItems/line_vertical_long.png \
    ../LTEsimGeneratorGUI/Images/MapItems/RBS.png \
    ../LTEsimGeneratorGUI/Images/MapItems/round2.png \
    ../LTEsimGeneratorGUI/Images/MapItems/round_cell.png \
    ../LTEsimGeneratorGUI/Images/MapItems/slanted_line.png \
    ../LTEsimGeneratorGUI/Images/MapItems/srio.png \
    ../LTEsimGeneratorGUI/RbFiles/parameters.rb \
    ../LTEsimGeneratorGUI/RbFiles/tune_traffic_models.rb
