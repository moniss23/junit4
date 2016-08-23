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
    ../LTEsimGeneratorGUI/ManagementWindow/Helpdialog/helpdialog.cpp \
#    ../LTEsimGeneratorGUI/Maps/Traffic/map_traffic.cpp \
    ../LTEsimGeneratorGUI/ManagementWindow/ProjectManagement/projectmanagement.cpp \
    ../LTEsimGeneratorGUI/Data/datasystem.cpp \
    ../LTEsimGeneratorGUI/ManagementWindow/AddProjectWindow/addProjectWindow.cpp \
    ../LTEsimGeneratorGUI/Data/project.cpp \
    ../LTEsimGeneratorGUI/Data/Objects/cell.cpp \
    ../LTEsimGeneratorGUI/Data/Objects/center.cpp \
    ../LTEsimGeneratorGUI/Data/Objects/handover.cpp \
    ../LTEsimGeneratorGUI/Data/Objects/trafficfiledata.cpp \
    ../LTEsimGeneratorGUI/Data/Objects/parametersfiledata.cpp \
    ../LTEsimGeneratorGUI/Data/appglobaldata.cpp \
    ../LTEsimGeneratorGUI/ManagementWindow/ProjectManagement/importprojectwindow.cpp \
    ../LTEsimGeneratorGUI/Data/Managers/filemanager.cpp \
    ../LTEsimGeneratorGUI/Data/Managers/scriptparsermanager.cpp \
    ../LTEsimGeneratorGUI/Data/ProjectSettings/datageneratorsettings.cpp \
    ltesimgeneratortests.cpp \
    UITests/addprojectwindowtest.cpp \
    UITests/projectmanagementwindowtest.cpp \
    DataTests/projecttest.cpp \
    DataTests/parametersfiledatatest.cpp \
    DataTests/trafficfiledatatest.cpp

HEADERS  += \
    ../LTEsimGeneratorGUI/ManagementWindow/Helpdialog/helpdialog.h \
#    ../LTEsimGeneratorGUI/Maps/Traffic/map_traffic.h \
    ../LTEsimGeneratorGUI/ManagementWindow/ProjectManagement/projectmanagement.h \
    ../LTEsimGeneratorGUI/Data/datasystem.h \
    ../LTEsimGeneratorGUI/ManagementWindow/AddProjectWindow/addProjectWindow.h \
    ../LTEsimGeneratorGUI/Data/project.h \
    ../LTEsimGeneratorGUI/Data/Objects/cell.h \
    ../LTEsimGeneratorGUI/Data/Objects/center.h \
    ../LTEsimGeneratorGUI/Data/Objects/handover.h \
    ../LTEsimGeneratorGUI/Data/Objects/trafficfiledata.h \
    ../LTEsimGeneratorGUI/Data/Objects/parametersfiledata.h \
    ../LTEsimGeneratorGUI/dataelementsinterface.h \
    ../LTEsimGeneratorGUI/Data/Interfaces/serializeinterface.h \
    ../LTEsimGeneratorGUI/Data/appglobaldata.h \
    ../LTEsimGeneratorGUI/Data/Managers/filemanager.h \
    ../LTEsimGeneratorGUI/Data/Managers/scriptparsermanager.h \
    ../LTEsimGeneratorGUI/ManagementWindow/ProjectManagement/importprojectwindow.h \
    ../LTEsimGeneratorGUI/Data/ProjectSettings/datageneratorsettings.h \
    UITests/addprojectwindowtest.h \
    UITests/projectmanagementwindowtest.h \
    DataTests/projecttest.h \
    DataTests/parametersfiledatatest.h \
    DataTests/trafficfiledatatest.h

FORMS    += \
    ../LTEsimGeneratorGUI/Ui/Windows/helpdialog.ui \
#    ../LTEsimGeneratorGUI/Ui/map_traffic.ui \
    ../LTEsimGeneratorGUI/Ui/Windows/projectmanagement.ui \
    ../LTEsimGeneratorGUI/Ui/Windows/addProjectWindow.ui \
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
    ../LTEsimGeneratorGUI/RbFiles/tune_traffic_models.rb \
    DataTests/dsdf
