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
CONFIG   += c++14

TEMPLATE = app
INCLUDEPATH += ../LTEsimGeneratorGUI

DEFINES += SRCDIR=\\\"$$PWD/\\\"

SOURCES += \
    ../LTEsimGeneratorGUI/UISystem/Windows/helpdialog.cpp \
    ../LTEsimGeneratorGUI/UISystem/Windows/projectmanagement.cpp \
    ../LTEsimGeneratorGUI/UISystem/Windows/importprojectwindow.cpp \
    ../LTEsimGeneratorGUI/UISystem/Windows/addProjectWindow.cpp \
    ../LTEsimGeneratorGUI/Data/project.cpp \
    ../LTEsimGeneratorGUI/Data/Objects/cell.cpp \
    ../LTEsimGeneratorGUI/Data/Objects/center.cpp \
    ../LTEsimGeneratorGUI/Data/Objects/handover.cpp \
    ../LTEsimGeneratorGUI/Data/Objects/trafficfiledata.cpp \
    ../LTEsimGeneratorGUI/Data/Objects/parametersfiledata.cpp \
    ../LTEsimGeneratorGUI/Data/appglobaldata.cpp \
    ../LTEsimGeneratorGUI/Data/datasystem.cpp \
    ../LTEsimGeneratorGUI/Data/Managers/filemanager.cpp \
    ../LTEsimGeneratorGUI/Data/Managers/scriptparsermanager.cpp \
    ../LTEsimGeneratorGUI/Data/ProjectSettings/datageneratorsettings.cpp \
    ../LTEsimGeneratorGUI/Data/ProjectSettings/sgwsettings.cpp \
    ../LTEsimGeneratorGUI/Data/ProjectSettings/uctoolsettings.cpp \
    ../LTEsimGeneratorGUI/Data/ProjectSettings/channelmodelsettings.cpp \
    ../LTEsimGeneratorGUI/UISystem/DataForms/sgwform.cpp \
    ../LTEsimGeneratorGUI/Data/ProjectSettings/mmesettings.cpp \
    ../LTEsimGeneratorGUI/Data/ProjectSettings/pagingsettings.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/Statistics/statisticsData.cpp \
    ltesimgeneratortests.cpp \
    UITests/addprojectwindowtest.cpp \
    UITests/projectmanagementwindowtest.cpp \
    DataTests/projecttest.cpp \
    DataTests/parametersfiledatatest.cpp \
    DataTests/trafficfiledatatest.cpp \
    DataTests/ManagersTests/scriptparsermanagertest.cpp

HEADERS  += \
    ../LTEsimGeneratorGUI/UISystem/Windows/helpdialog.h \
    ../LTEsimGeneratorGUI/UISystem/Windows/projectmanagement.h \
    ../LTEsimGeneratorGUI/UISystem/Windows/importprojectwindow.h \
    ../LTEsimGeneratorGUI/UISystem/Windows/addProjectWindow.h \
    ../LTEsimGeneratorGUI/Data/datasystem.h \
    ../LTEsimGeneratorGUI/Data/project.h \
    ../LTEsimGeneratorGUI/Data/Objects/cell.h \
    ../LTEsimGeneratorGUI/Data/Objects/center.h \
    ../LTEsimGeneratorGUI/Data/Objects/handover.h \
    ../LTEsimGeneratorGUI/Data/Objects/trafficfiledata.h \
    ../LTEsimGeneratorGUI/Data/Objects/parametersfiledata.h \
    ../LTEsimGeneratorGUI/Data/Interfaces/serializeinterface.h \
    ../LTEsimGeneratorGUI/Data/appglobaldata.h \
    ../LTEsimGeneratorGUI/Data/Managers/filemanager.h \
    ../LTEsimGeneratorGUI/Data/Managers/scriptparsermanager.h \
    ../LTEsimGeneratorGUI/Data/ProjectSettings/sgwsettings.h \
    ../LTEsimGeneratorGUI/Data/ProjectSettings/uctoolsettings.h \
    ..//LTEsimGeneratorGUI/UISystem/DataForms/sgwform.h \
    ../LTEsimGeneratorGUI/Data/ProjectSettings/mmesettings.h \
    ../LTEsimGeneratorGUI/Data/ProjectSettings/datageneratorsettings.h \
    ../LTEsimGeneratorGUI/Data/ProjectSettings/channelmodelsettings.h \
    ../LTEsimGeneratorGUI/Data/ProjectSettings/pagingsettings.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/Statistics/statisticsData.h \
    UITests/addprojectwindowtest.h \
    UITests/projectmanagementwindowtest.h \
    DataTests/projecttest.h \
    DataTests/parametersfiledatatest.h \
    DataTests/trafficfiledatatest.h \
    DataTests/ManagersTests/scriptparsermanagertest.h

FORMS    += \
    ../LTEsimGeneratorGUI/Ui/Windows/helpdialog.ui \
    ../LTEsimGeneratorGUI/Ui/Windows/projectmanagement.ui \
    ../LTEsimGeneratorGUI/Ui/Windows/addProjectWindow.ui \
    ../LTEsimGeneratorGUI/Ui/DataForms/sgwform.ui \
    ../LTEsimGeneratorGUI/Ui/DataForms/mmeform.ui
  #  ../LTEsimGeneratorGUI/Ui/uctoolform.ui \

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
    ../LTEsimGeneratorGUI/RbFiles/tune_traffic_models.rb \
    DataTests/dsdf
