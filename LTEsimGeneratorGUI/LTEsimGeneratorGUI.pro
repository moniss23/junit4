#-------------------------------------------------
#
# Project created by QtCreator 2015-07-07T13:59:42
#
#-------------------------------------------------

QT += core
QT += xml
QT += gui
QT += widgets

TARGET = LTEsimGeneratorGUI
TEMPLATE = app

CONFIG   += c++14

#--------DATA SYSTEM--------#
SOURCES += \
    Data/Managers/filemanager.cpp \
    Data/Objects/cell.cpp \
    Data/Objects/center.cpp \
    Data/Objects/handover.cpp \
    Data/Objects/parametersfiledata.cpp \
    Data/Objects/trafficfiledata.cpp \
    Data/project.cpp \
    Data/appglobaldata.cpp \
    Data/datasystem.cpp \
    Data/Managers/scriptparsermanager.cpp \
    Data/ProjectSettings/datageneratorsettings.cpp \
    Data/ProjectSettings/sgwsettings.cpp \
    UISystem/Widgets/cellrepresentation.cpp \
    Data/ProjectSettings/uctoolsettings.cpp \
    Data/ProjectSettings/channelmodelsettings.cpp \
    Data/ProjectSettings/pagingsettings.cpp \
    Data/ProjectSettings/mmesettings.cpp \
    Data/ProjectSettings/ubsimsettings.cpp \
    UISystem/Widgets/handoverrepresentation.cpp


#--------UI SYSTEM--------#
SOURCES += \
    UISystem/uisystem.cpp \
    UISystem/Windows/addProjectWindow.cpp \
    UISystem/Windows/helpdialog.cpp \
    UISystem/Windows/importprojectwindow.cpp \
    UISystem/Windows/parameterswindow.cpp \
    UISystem/Windows/projectmanagement.cpp \
    UISystem/Windows/renamedialog.cpp \
    UISystem/Windows/settings.cpp \
    UISystem/DataForms/ipexform.cpp \
    UISystem/DataForms/uctoolform.cpp \
    UISystem/DataForms/mmeform.cpp \
    UISystem/DataForms/sgwform.cpp \
    UISystem/DataForms/channelmodelform.cpp \
    UISystem/DataForms/ubsimform.cpp \
    UISystem/Helpers/rubysyntaxhighlighter.cpp \
    UISystem/Widgets/mapview.cpp


SOURCES += main.cpp\
    Maps/Parameters/MapWindow/mapwindow.cpp \
    Maps/Parameters/MapRange/maprange.cpp \
    Maps/Parameters/MapRange/maprangeform.cpp \
    Maps/Traffic/UeParameters/ue.cpp \
    Maps/Traffic/UeParameters/UE_param_form.cpp \
    Maps/Traffic/MapComponents/draguelabel.cpp \
    Maps/Traffic/map_traffic.cpp \
    Maps/Traffic/ManagementTemplate/managementtemplate.cpp \
    Maps/Traffic/UeParameters/uegroupdata.cpp \
    Maps/Traffic/MapComponents/mapmanagement.cpp \
    Maps/Traffic/MapComponents/myscrollareawidget.cpp \
    Maps/Traffic/MapComponents/custommodellabel.cpp \
    Maps/Traffic/MapComponents/statisticsbutton.cpp \
    Maps/Traffic/MapComponents/timebutton.cpp \
    Maps/Traffic/MapComponents/tuningtrafficbutton.cpp \
    Maps/Traffic/MapComponents/addbutton.cpp \
    Maps/Traffic/MapComponents/cellarea.cpp \
    Maps/Traffic/MapComponents/handoverarea.cpp \
    my_qlabel.cpp \
    Maps/Traffic/Time/timeData.cpp \
    Maps/Traffic/Time/timeManager.cpp \
    Maps/Traffic/Statistics/statisticsManager.cpp \
    Maps/Traffic/Statistics/statisticsData.cpp  \
    Maps/Traffic/CustomModel/customModel.cpp \
    Maps/Traffic/TrafficFileManagement/trafficfilemanagement.cpp \
    Maps/Parameters/parametersfilemanagement.cpp \
    Maps/Traffic/Tuning/tuningTrafficManager.cpp \
    Maps/Traffic/Tuning/tuningTrafficData.cpp


#--------DATA SYSTEM--------#
HEADERS  += \
    Data/Managers/filemanager.h \
    Data/Objects/cell.h \
    Data/Objects/center.h \
    Data/Objects/handover.h \
    Data/Objects/parametersfiledata.h \
    Data/Objects/trafficfiledata.h \
    Data/project.h \
    Data/Interfaces/serializeinterface.h \
    Data/appglobaldata.h \
    Data/datasystem.h \
    Data/Managers/scriptparsermanager.h \
    Data/ProjectSettings/datageneratorsettings.h \
    Data/ProjectSettings/sgwsettings.h \
    UISystem/Widgets/cellrepresentation.h \
    Data/ProjectSettings/uctoolsettings.h \
    Data/ProjectSettings/channelmodelsettings.h \
    Data/ProjectSettings/pagingsettings.h \
    Data/ProjectSettings/mmesettings.h \
    Data/ProjectSettings/ubsimsettings.h \
    UISystem/Widgets/handoverrepresentation.h


#--------UI SYSTEM--------#
HEADERS  += \
    UISystem/uisystem.h \
    UISystem/Windows/addProjectWindow.h \
    UISystem/Windows/helpdialog.h \
    UISystem/Windows/importprojectwindow.h \
    UISystem/Windows/parameterswindow.h \
    UISystem/Windows/projectmanagement.h \
    UISystem/Windows/renamedialog.h \
    UISystem/Windows/settings.h \
    UISystem/DataForms/ipexform.h \
    UISystem/DataForms/uctoolform.h \
    UISystem/DataForms/mmeform.h \
    UISystem/DataForms/sgwform.h \
    UISystem/DataForms/channelmodelform.h \
    UISystem/DataForms/ubsimform.h \
    UISystem/Helpers/rubysyntaxhighlighter.h \
    UISystem/Widgets/mapview.h


HEADERS  += \
    Maps/Parameters/MapWindow/mapwindow.h \
    Maps/Parameters/MapRange/maprange.h \
    Maps/Parameters/MapRange/maprangeform.h \
    Maps/Traffic/UeParameters/ue.h \
    Maps/Traffic/UeParameters/UE_param_form.h \
    Maps/Traffic/MapComponents/draguelabel.h \
    Maps/Traffic/map_traffic.h \
    Maps/Traffic/ManagementTemplate/managementtemplate.h \
    Maps/Traffic/UeParameters/uegroupdata.h \
    Maps/Traffic/MapComponents/mapmanagement.h \
    Maps/Traffic/MapComponents/myscrollareawidget.h \
    Maps/Traffic/MapComponents/custommodellabel.h \
    Maps/Traffic/MapComponents/statisticsbutton.h \
    Maps/Traffic/MapComponents/timebutton.h \
    Maps/Traffic/MapComponents/tuningtrafficbutton.h \
    Maps/Traffic/MapComponents/scale.h \
    Maps/Traffic/MapComponents/addbutton.h \
    Maps/Traffic/MapComponents/myobjectarea.h \
    Maps/Traffic/MapComponents/cellarea.h \
    Maps/Traffic/MapComponents/handoverarea.h \
    Maps/Traffic/MapComponents/compositionofareas.h \
    my_qlabel.h \
    Maps/Traffic/Time/timeData.h \
    Maps/Traffic/Time/timeManager.h \
    Maps/Traffic/Statistics/statisticsData.h \
    Maps/Traffic/Statistics/statisticsManager.h \
    Maps/Traffic/CustomModel/customModel.h \
    Maps/Traffic/TrafficFileManagement/trafficfilemanagement.h \
    Maps/Parameters/parametersfilemanagement.h \
    Maps/Traffic/Tuning/tuningTrafficData.h \
    Maps/Traffic/Tuning/tuningTrafficManager.h


FORMS    += \
    Ui/mapwindow.ui \
    Ui/maprangeform.ui \
    Ui/map_traffic.ui \
    Ui/custommodels.ui \
    Ui/tuningtrafficform.ui \
    Ui/UE_param_form.ui \
    Ui/managementtemplate.ui \
    Ui/timeForm.ui \
    Ui/customModel.ui \
    Ui/renamedialog.ui \
    Ui/Windows/addProjectWindow.ui \
    Ui/Windows/parameterswindow.ui \
    Ui/Windows/settings.ui \
    Ui/Windows/projectmanagement.ui \
    Ui/Windows/helpdialog.ui \
    Ui/statistics.ui \
    Ui/DataForms/ipexform.ui \
    Ui/DataForms/sgwform.ui \
    Ui/DataForms/mmeform.ui \
    Ui/DataForms/uctoolform.ui \
    Ui/DataForms/ubsimform.ui \
    Ui/DataForms/channelmodelform.ui


OTHER_FILES += \
    logoLTEsim.png

RESOURCES += \
    Resource.qrc

DISTFILES += \
    Images/MapItems/axis.png \
    Images/MapItems/dottedline.png \
    Images/MapItems/dottedline_vertical.png \
    Images/MapItems/line.png \
    Images/MapItems/line_vertical.png \
    Images/MapItems/line_vertical_long.png \
    Images/MapItems/RBS.png \
    Images/MapItems/round2.png \
    Images/MapItems/round_cell.png \
    Images/MapItems/slanted_line.png \
    Images/MapItems/srio.png \
    RbFiles/parameters.rb \
    RbFiles/tune_traffic_models.rb


