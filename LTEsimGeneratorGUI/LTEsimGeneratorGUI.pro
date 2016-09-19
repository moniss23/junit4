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
    Data/ProjectSettings/mmesettings.cpp \
    Data/ProjectSettings/maprange.cpp \
    Data/ProjectSettings/ubsimsettings.cpp \
    Data/ProjectSettings/generalconfigurationparameters.cpp \
    Data/ProjectSettings/ueparameters.cpp \
    Data/TrafficSettings/custommodelsettings.cpp \
    Data/TrafficSettings/CustomModelsData/ping.cpp \
    Data/TrafficSettings/CustomModelsData/voip.cpp \
    Data/TrafficSettings/CustomModelsData/ftpdl.cpp \
    Data/TrafficSettings/CustomModelsData/ftpul.cpp \
    Data/TrafficSettings/CustomModelsData/streamdl.cpp \
    Data/TrafficSettings/CustomModelsData/streamul.cpp \
    Data/TrafficSettings/CustomModelsData/syncedping.cpp \
    Data/TrafficSettings/CustomModelsData/servicereq.cpp \
    Data/ProjectSettings/Helpers/ueparametersparser.cpp \
    Data/ProjectSettings/Helpers/mapparser.cpp \
    Data/ProjectSettings/pagingsettings.cpp \
    Data/TrafficSettings/uedata.cpp \
    UISystem/DataForms/ueParametersForm.cpp \
    Data/TrafficSettings/statisticsData.cpp

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
    UISystem/DataForms/maprangeform.cpp \
    UISystem/Helpers/rubysyntaxhighlighter.cpp \
    UISystem/DataForms/UE_param_form.cpp \
    UISystem/Widgets/mapview.cpp \
    UISystem/Windows/trafficmap.cpp \
    UISystem/Windows/newmapwindow.cpp \
    UISystem/DataForms/generalconfigurationform.cpp \
    UISystem/DataForms/pingform.cpp \
    UISystem/DataForms/voipform.cpp \
    UISystem/DataForms/ftpdlform.cpp \
    UISystem/DataForms/ftpulform.cpp \
    UISystem/DataForms/streamdlform.cpp \
    UISystem/DataForms/streamulform.cpp \
    UISystem/DataForms/servicereqform.cpp \
    UISystem/DataForms/syncedpingform.cpp \
    UISystem/Widgets/handoverrepresentation.cpp \
    UISystem/Widgets/uerepresentation.cpp \
    UISystem/DataForms/pagingform.cpp \
    UISystem/DataForms/statisticsForm.cpp \
    UISystem/DataForms/ueform.cpp \
    UISystem/Windows/pagingrate.cpp \
    UISystem/DataForms/custommodelslistform.cpp


SOURCES += main.cpp\
    Maps/Traffic/UeParameters/uegroupdata.cpp \
    Maps/Traffic/Time/timeData.cpp \
    Maps/Traffic/Time/timeManager.cpp \
    Maps/Traffic/TrafficFileManagement/trafficfilemanagement.cpp \
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
    Data/ProjectSettings/uctoolsettings.h \
    Data/ProjectSettings/channelmodelsettings.h \
    Data/ProjectSettings/mmesettings.h \
    Data/ProjectSettings/ubsimsettings.h \
    Data/ProjectSettings/maprange.h \
    Data/ProjectSettings/generalconfigurationparameters.h \
    Data/ProjectSettings/ueparameters.h \
    Data/Interfaces/scriptable.h \
    Data/TrafficSettings/custommodelsettings.h \
    Data/TrafficSettings/CustomModelsData/ping.h \
    Data/TrafficSettings/CustomModelsData/voip.h \
    Data/TrafficSettings/CustomModelsData/ftpdl.h \
    Data/TrafficSettings/CustomModelsData/ftpul.h \
    Data/TrafficSettings/CustomModelsData/streamdl.h \
    Data/TrafficSettings/CustomModelsData/streamul.h \
    Data/TrafficSettings/CustomModelsData/syncedping.h \
    Data/TrafficSettings/CustomModelsData/servicereq.h \
    Data/TrafficSettings/statisticsData.h \
    Data/ProjectSettings/Helpers/ueparametersparser.h \
    Data/ProjectSettings/Helpers/mapparser.h \
    Data/TrafficSettings/uedata.cpp \
    Data/ProjectSettings/pagingsettings.h \
    UISystem/DataForms/ueParametersForm.h

#--------UI SYSTEM--------#
HEADERS  += \
    UISystem/uisystem.h \
    UISystem/Windows/addProjectWindow.h \
    UISystem/Windows/helpdialog.h \
    UISystem/Windows/importprojectwindow.h \
    UISystem/DataForms/ueform.h \
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
    UISystem/DataForms/maprangeform.h \
    UISystem/DataForms/UE_param_form.h \
    UISystem/Helpers/rubysyntaxhighlighter.h \
    UISystem/Widgets/mapview.h \
    UISystem/Widgets/handoverrepresentation.h \
    UISystem/Windows/newmapwindow.h \
    UISystem/Windows/trafficmap.h \
    UISystem/DataForms/generalconfigurationform.h \
    UISystem/DataForms/pingform.h \
    UISystem/DataForms/voipform.h \
    UISystem/DataForms/ftpdlform.h \
    UISystem/DataForms/ftpulform.h \
    UISystem/DataForms/streamdlform.h \
    UISystem/DataForms/streamulform.h \
    UISystem/DataForms/servicereqform.h \
    UISystem/DataForms/syncedpingform.h \
    UISystem/Widgets/cellrepresentation.h \
    UISystem/Widgets/uerepresentation.h \
    UISystem/DataForms/custommodelslistform.h \
    UISystem/Windows/pagingrate.h \
    UISystem/DataForms/pagingform.h \
    UISystem/DataForms/statisticsForm.h


HEADERS  += \
    Maps/Traffic/UeParameters/uegroupdata.h \
    Maps/Traffic/Time/timeData.h \
    Maps/Traffic/Time/timeManager.h \
    Maps/Traffic/CustomModel/customModel.h \
    Maps/Traffic/TrafficFileManagement/trafficfilemanagement.h \
    Maps/Traffic/Tuning/tuningTrafficData.h \
    Maps/Traffic/Tuning/tuningTrafficManager.h


FORMS    += \
    Ui/tuningtrafficform.ui \
    Ui/UE_param_form.ui \
    Ui/timeForm.ui \
    Ui/Windows/addProjectWindow.ui \
    Ui/Windows/parameterswindow.ui \
    Ui/Windows/settings.ui \
    Ui/Windows/projectmanagement.ui \
    Ui/Windows/helpdialog.ui \
    Ui/DataForms/statisticsform.ui \
    Ui/DataForms/ipexform.ui \
    Ui/DataForms/sgwform.ui \
    Ui/DataForms/mmeform.ui \
    Ui/DataForms/maprangeform.ui \
    Ui/DataForms/uctoolform.ui \
    Ui/DataForms/ubsimform.ui \
    Ui/DataForms/channelmodelform.ui \
    Ui/SmallDialogs/renamedialog.ui \
    Ui/Windows/newmapwindow.ui \
    Ui/Windows/trafficmap.ui \
    Ui/DataForms/custommodelslistform.ui \
    Ui/DataForms/pingform.ui \
    Ui/SmallDialogs/generalconfiguration.ui \
    Ui/DataForms/voipform.ui \
    Ui/DataForms/ftpdlform.ui \
    Ui/DataForms/ftpulform.ui \
    Ui/DataForms/streamdlform.ui \
    Ui/DataForms/streamulform.ui \
    Ui/DataForms/syncedpingform.ui \
    Ui/DataForms/servicereqform.ui \
    UISystem/DataForms/ueform.ui \
    Ui/DataForms/ueParametersForm.ui \
    Ui/SmallDialogs/pagingform.ui \
    Ui/Windows/paging_rate.ui

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


