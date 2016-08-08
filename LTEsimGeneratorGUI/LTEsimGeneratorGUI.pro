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

CONFIG   += c++11
CONFIG   += qtestlib

SOURCES += main.cpp\
    ManagementWindow/ParametersWindow/parameterswindow.cpp \
    ManagementWindow/Helpdialog/helpdialog.cpp \
    ManagementWindow/ProjectManagement/projectmanagement.cpp \
    ManagementWindow/Settings/settings.cpp \
    Maps/Parameters/ChannelModel/channelmodel.cpp \
    Maps/Parameters/ChannelModel/channelmodelform.cpp \
    Maps/Parameters/SimulatedCoreNetwork/Mme/mme.cpp \
    Maps/Parameters/SimulatedCoreNetwork/Mme/mmeform.cpp \
    Maps/Parameters/SimulatedUe/ipexform.cpp \
    Maps/Parameters/SimulatedUe/ipgwtg.cpp \
    Maps/Parameters/SimulatedUe/ubsimform.cpp \
    Maps/Parameters/UcTool/uctoolform.cpp \
    Maps/Parameters/MapWindow/mapwindow.cpp \
    Maps/Parameters/SimulatedCoreNetwork/Sgw/sgw.cpp \
    Maps/Parameters/SimulatedCoreNetwork/Sgw/sgwform.cpp \
    Maps/Parameters/MapRange/maprange.cpp \
    Maps/Parameters/MapRange/maprangeform.cpp \
    Maps/Traffic/CustomModel/addftpdl.cpp \
    Maps/Traffic/CustomModel/addftpdlform.cpp \
    Maps/Traffic/CustomModel/addftpul.cpp \
    Maps/Traffic/CustomModel/addftpulform.cpp \
    Maps/Traffic/CustomModel/addping.cpp \
    Maps/Traffic/CustomModel/addpingform.cpp \
    Maps/Traffic/CustomModel/addservicereq.cpp \
    Maps/Traffic/CustomModel/addservicereqform.cpp \
    Maps/Traffic/CustomModel/addstreamdl.cpp \
    Maps/Traffic/CustomModel/addstreamdlform.cpp \
    Maps/Traffic/CustomModel/addstreamul.cpp \
    Maps/Traffic/CustomModel/addstreamulform.cpp \
    Maps/Traffic/CustomModel/addsyncedping.cpp \
    Maps/Traffic/CustomModel/addsyncedpingform.cpp \
    Maps/Traffic/CustomModel/addvoip.cpp \
    Maps/Traffic/CustomModel/addvoipform.cpp \
    Maps/Traffic/Tuning/tuningtraffic.cpp \
    Maps/Traffic/Tuning/tuningtrafficform.cpp \
    Maps/Traffic/UeParameters/ue.cpp \
    Maps/Traffic/UeParameters/UE_param_form.cpp \
    Maps/Traffic/MapComponents/draguelabel.cpp \
    Maps/Traffic/map_traffic.cpp \
    Maps/Traffic/ManagementTemplate/managementtemplate.cpp \
    Maps/Traffic/DataObjects/handoverdata.cpp \
    Maps/Traffic/UeParameters/uegroupdata.cpp \
    Maps/Traffic/DataObjects/celldata.cpp \
    ProjectReaderWriter/projectreaderwriter.cpp \
    Maps/Traffic/MapData/mapdata.cpp \
    Maps/Traffic/MapComponents/mapmanagement.cpp \
    Maps/Traffic/MapComponents/myscrollareawidget.cpp \
    Maps/Traffic/MapComponents/custommodellabel.cpp \
    Maps/Traffic/MapComponents/statisticsbutton.cpp \
    Maps/Traffic/MapComponents/timebutton.cpp \
    Maps/Traffic/MapComponents/tuningtrafficbutton.cpp \
    Maps/Traffic/MapComponents/addbutton.cpp \
    Maps/Traffic/MapComponents/cellarea.cpp \
    Maps/Traffic/MapComponents/handoverarea.cpp \
    ManagementWindow/Encryption/encryption.cpp \
    AppSettings/appsettings.cpp \
    my_qlabel.cpp \
    CommonConstans/common_constans.cpp \
    Maps/Traffic/Time/timeData.cpp \
    Maps/Traffic/Time/timeManager.cpp \
    ManagementWindow/AddProjectWindow/addProjectWindow.cpp \
    Data/project.cpp \
    Maps/Traffic/Statistics/statisticsManager.cpp \
    Maps/Traffic/Statistics/statisticsData.cpp  \
    Data/appglobaldata.cpp \
    ManagementWindow/ProjectManagement/importprojectwindow.cpp \
    Maps/Traffic/CustomModel/customModel.cpp \
    Maps/Traffic/CustomModel/oldcustommodels.cpp \
    FileManager/filemanager.cpp \
    Data/cell.cpp \
    Data/center.cpp \
    Data/handover.cpp

HEADERS  += \
    ManagementWindow/ParametersWindow/parameterswindow.h \
    ManagementWindow/Helpdialog/helpdialog.h \
    ManagementWindow/ProjectManagement/projectmanagement.h \
    ManagementWindow/Settings/settings.h \
    Maps/Parameters/ChannelModel/channelmodel.h \
    Maps/Parameters/ChannelModel/channelmodelform.h \
    Maps/Parameters/SimulatedCoreNetwork/Mme/mme.h \
    Maps/Parameters/SimulatedCoreNetwork/Mme/mmeform.h \
    Maps/Parameters/SimulatedUe/ipexform.h \
    Maps/Parameters/SimulatedUe/ipgwtg.h \
    Maps/Parameters/SimulatedUe/ubsimform.h \
    Maps/Parameters/UcTool/uctoolform.h \
    Maps/Parameters/MapWindow/mapwindow.h \
    Maps/Parameters/SimulatedCoreNetwork/Sgw/sgw.h \
    Maps/Parameters/SimulatedCoreNetwork/Sgw/sgwform.h \
    Maps/Parameters/MapRange/maprange.h \
    Maps/Parameters/MapRange/maprangeform.h \
    ManagementWindow/Encryption/encryption.h \
    Maps/Traffic/CustomModel/addftpdl.h \
    Maps/Traffic/CustomModel/addftpdlform.h \
    Maps/Traffic/CustomModel/addftpul.h \
    Maps/Traffic/CustomModel/addftpulform.h \
    Maps/Traffic/CustomModel/addping.h \
    Maps/Traffic/CustomModel/addpingform.h \
    Maps/Traffic/CustomModel/addservicereq.h \
    Maps/Traffic/CustomModel/addservicereqform.h \
    Maps/Traffic/CustomModel/addstreamdl.h \
    Maps/Traffic/CustomModel/addstreamdlform.h \
    Maps/Traffic/CustomModel/addstreamul.h \
    Maps/Traffic/CustomModel/addstreamulform.h \
    Maps/Traffic/CustomModel/addsyncedping.h \
    Maps/Traffic/CustomModel/addsyncedpingform.h \
    Maps/Traffic/CustomModel/addvoip.h \
    Maps/Traffic/CustomModel/addvoipform.h \
    Maps/Traffic/Tuning/tuningtraffic.h \
    Maps/Traffic/Tuning/tuningtrafficform.h \
    Maps/Traffic/UeParameters/ue.h \
    Maps/Traffic/UeParameters/UE_param_form.h \
    Maps/Traffic/MapComponents/draguelabel.h \
    Maps/Traffic/map_traffic.h \
    Maps/Traffic/ManagementTemplate/managementtemplate.h \
    Maps/Traffic/DataObjects/handoverdata.h \
    Maps/Traffic/UeParameters/uegroupdata.h \
    Maps/Traffic/DataObjects/celldata.h \
    ProjectReaderWriter/projectreaderwriter.h \
    Maps/Traffic/MapData/mapdata.h \
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
    AppSettings/appsettings.h \
    my_qlabel.h \
    CommonConstans/common_constans.h \
    Maps/Traffic/Time/timeData.h \
    Maps/Traffic/Time/timeManager.h \
    ManagementWindow/AddProjectWindow/addProjectWindow.h \
    Data/project.h \
    Maps/Traffic/Statistics/statisticsData.h \
    Maps/Traffic/Statistics/statisticsManager.h \
    dataelementsinterface.h \
    Data/serializeinterface.h \
    Data/appglobaldata.h \
    ManagementWindow/ProjectManagement/importprojectwindow.h \
    Maps/Traffic/CustomModel/customModel.h \
    Maps/Traffic/CustomModel/oldcustommodels.h \
    FileManager/filemanager.h \
    Data/cell.h \
    Data/center.h \
    Data/handover.h


FORMS    += \
    Ui/parameterswindow.ui \
    Ui/helpdialog.ui \
    Ui/projectmanagement.ui \
    Ui/settings.ui \
    Ui/channelmodelform.ui \
    Ui/mmeform.ui \
    Ui/ipexform.ui \
    Ui/ubsimform.ui \
    Ui/uctoolform.ui \
    Ui/mapwindow.ui \
    Ui/mapwindowlarge.ui \
    Ui/sgwform.ui \
    Ui/maprangeform.ui \
    Ui/maprangelargeform.ui \
    Ui/map_traffic.ui \
    Ui/map_traffic_large.ui \
    Ui/addftpdlform.ui \
    Ui/addftpulform.ui \
    Ui/addpingform.ui \
    Ui/addservicereqform.ui \
    Ui/addstreamdlform.ui \
    Ui/addstreamulform.ui \
    Ui/addsyncedpingform.ui \
    Ui/addvoipform.ui \
    Ui/custommodels.ui \
    Ui/tuningtrafficform.ui \
    Ui/UE_param_form.ui \
    Ui/managementtemplate.ui \
    Ui/timeForm.ui \
    Ui/addProjectWindow.ui \
    Ui/statisticsForm.ui \
    Ui/customModel.ui


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


