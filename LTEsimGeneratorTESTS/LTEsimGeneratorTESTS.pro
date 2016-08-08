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
    ../LTEsimGeneratorGUI/ManagementWindow/ParametersWindow/parameterswindow.cpp \
    ../LTEsimGeneratorGUI/ManagementWindow/Helpdialog/helpdialog.cpp \
    ../LTEsimGeneratorGUI/ManagementWindow/ProjectManagement/projectmanagement.cpp \
    ../LTEsimGeneratorGUI/ManagementWindow/Settings/settings.cpp \
    ../LTEsimGeneratorGUI/Maps/MapObjects/cell.cpp \
    ../LTEsimGeneratorGUI/Maps/MapObjects/center.cpp \
    ../LTEsimGeneratorGUI/Maps/MapObjects/handover.cpp \
    ../LTEsimGeneratorGUI/Maps/Parameters/ChannelModel/channelmodel.cpp \
    ../LTEsimGeneratorGUI/Maps/Parameters/ChannelModel/channelmodelform.cpp \
    ../LTEsimGeneratorGUI/Maps/Parameters/SimulatedCoreNetwork/Mme/mme.cpp \
    ../LTEsimGeneratorGUI/Maps/Parameters/SimulatedCoreNetwork/Mme/mmeform.cpp \
    ../LTEsimGeneratorGUI/Maps/Parameters/SimulatedUe/ipexform.cpp \
    ../LTEsimGeneratorGUI/Maps/Parameters/SimulatedUe/ipgwtg.cpp \
    ../LTEsimGeneratorGUI/Maps/Parameters/SimulatedUe/ubsimform.cpp \
    ../LTEsimGeneratorGUI/Maps/Parameters/UcTool/uctoolform.cpp \
    ../LTEsimGeneratorGUI/Maps/Parameters/MapWindow/mapwindow.cpp \
    ../LTEsimGeneratorGUI/Maps/Parameters/SimulatedCoreNetwork/Sgw/sgw.cpp \
    ../LTEsimGeneratorGUI/Maps/Parameters/SimulatedCoreNetwork/Sgw/sgwform.cpp \
    ../LTEsimGeneratorGUI/Maps/Parameters/MapRange/maprange.cpp \
    ../LTEsimGeneratorGUI/Maps/Parameters/MapRange/maprangeform.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addftpdl.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addftpdlform.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addftpul.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addftpulform.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addping.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addpingform.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addservicereq.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addservicereqform.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addstreamdl.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addstreamdlform.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addstreamul.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addstreamulform.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addsyncedping.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addsyncedpingform.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addvoip.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addvoipform.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/Tuning/tuningtraffic.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/Tuning/tuningtrafficform.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/UeParameters/ue.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/UeParameters/UE_param_form.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/draguelabel.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/map_traffic.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/ManagementTemplate/managementtemplate.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/DataObjects/handoverdata.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/UeParameters/uegroupdata.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/DataObjects/celldata.cpp \
    ../LTEsimGeneratorGUI/ProjectReaderWriter/projectreaderwriter.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapData/mapdata.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/mapmanagement.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/myscrollareawidget.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/custommodellabel.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/statisticsbutton.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/timebutton.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/tuningtrafficbutton.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/addbutton.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/cellarea.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/handoverarea.cpp \
    ../LTEsimGeneratorGUI/ManagementWindow/Encryption/encryption.cpp \
    ../LTEsimGeneratorGUI/AppSettings/appsettings.cpp \
    ../LTEsimGeneratorGUI/my_qlabel.cpp \
    ../LTEsimGeneratorGUI/CommonConstans/common_constans.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/Time/timeData.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/Time/timeManager.cpp \
    ../LTEsimGeneratorGUI/ManagementWindow/AddProjectWindow/addProjectWindow.cpp \
    ../LTEsimGeneratorGUI/Data/project.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/Statistics/statisticsManager.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/Statistics/statisticsData.cpp  \
    ../LTEsimGeneratorGUI/Data/appglobaldata.cpp \
    ../LTEsimGeneratorGUI/ManagementWindow/ProjectManagement/importprojectwindow.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/customModel.cpp \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/oldcustommodels.cpp \
    ../LTEsimGeneratorGUI/ManagementWindow/ProjectManagement/projectmanagementwindowtest.cpp \
    ../LTEsimGeneratorGUI/ManagementWindow/AddProjectWindow/addprojectwindowtest.cpp \
    ltesimgeneratortests.cpp

HEADERS  += \
    ../LTEsimGeneratorGUI/ManagementWindow/ParametersWindow/parameterswindow.h \
    ../LTEsimGeneratorGUI/ManagementWindow/Helpdialog/helpdialog.h \
    ../LTEsimGeneratorGUI/ManagementWindow/ProjectManagement/projectmanagement.h \
    ../LTEsimGeneratorGUI/ManagementWindow/Settings/settings.h \
    ../LTEsimGeneratorGUI/Maps/MapObjects/cell.h \
    ../LTEsimGeneratorGUI/Maps/MapObjects/center.h \
    ../LTEsimGeneratorGUI/Maps/MapObjects/handover.h \
    ../LTEsimGeneratorGUI/Maps/Parameters/ChannelModel/channelmodel.h \
    ../LTEsimGeneratorGUI/Maps/Parameters/ChannelModel/channelmodelform.h \
    ../LTEsimGeneratorGUI/Maps/Parameters/SimulatedCoreNetwork/Mme/mme.h \
    ../LTEsimGeneratorGUI/Maps/Parameters/SimulatedCoreNetwork/Mme/mmeform.h \
    ../LTEsimGeneratorGUI/Maps/Parameters/SimulatedUe/ipexform.h \
    ../LTEsimGeneratorGUI/Maps/Parameters/SimulatedUe/ipgwtg.h \
    ../LTEsimGeneratorGUI/Maps/Parameters/SimulatedUe/ubsimform.h \
    ../LTEsimGeneratorGUI/Maps/Parameters/UcTool/uctoolform.h \
    ../LTEsimGeneratorGUI/Maps/Parameters/MapWindow/mapwindow.h \
    ../LTEsimGeneratorGUI/Maps/Parameters/SimulatedCoreNetwork/Sgw/sgw.h \
    ../LTEsimGeneratorGUI/Maps/Parameters/SimulatedCoreNetwork/Sgw/sgwform.h \
    ../LTEsimGeneratorGUI/Maps/Parameters/MapRange/maprange.h \
    ../LTEsimGeneratorGUI/Maps/Parameters/MapRange/maprangeform.h \
    ../LTEsimGeneratorGUI/ManagementWindow/Encryption/encryption.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addftpdl.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addftpdlform.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addftpul.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addftpulform.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addping.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addpingform.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addservicereq.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addservicereqform.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addstreamdl.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addstreamdlform.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addstreamul.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addstreamulform.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addsyncedping.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addsyncedpingform.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addvoip.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/addvoipform.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/Tuning/tuningtraffic.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/Tuning/tuningtrafficform.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/UeParameters/ue.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/UeParameters/UE_param_form.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/draguelabel.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/map_traffic.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/ManagementTemplate/managementtemplate.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/DataObjects/handoverdata.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/UeParameters/uegroupdata.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/DataObjects/celldata.h \
    ../LTEsimGeneratorGUI/ProjectReaderWriter/projectreaderwriter.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapData/mapdata.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/mapmanagement.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/myscrollareawidget.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/custommodellabel.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/statisticsbutton.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/timebutton.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/tuningtrafficbutton.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/scale.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/addbutton.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/myobjectarea.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/cellarea.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/handoverarea.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/MapComponents/compositionofareas.h \
    ../LTEsimGeneratorGUI/AppSettings/appsettings.h \
    ../LTEsimGeneratorGUI/my_qlabel.h \
    ../LTEsimGeneratorGUI/CommonConstans/common_constans.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/Time/timeData.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/Time/timeManager.h \
    ../LTEsimGeneratorGUI/ManagementWindow/AddProjectWindow/addProjectWindow.h \
    ../LTEsimGeneratorGUI/Data/project.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/Statistics/statisticsData.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/Statistics/statisticsManager.h \
    ../LTEsimGeneratorGUI/dataelementsinterface.h \
    ../LTEsimGeneratorGUI/Data/serializeinterface.h \
    ../LTEsimGeneratorGUI/Data/appglobaldata.h \
    ../LTEsimGeneratorGUI/ManagementWindow/ProjectManagement/importprojectwindow.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/customModel.h \
    ../LTEsimGeneratorGUI/ManagementWindow/ProjectManagement/projectmanagementwindowtest.h \
    ../LTEsimGeneratorGUI/ManagementWindow/AddProjectWindow/addprojectwindowtest.h \
    ../LTEsimGeneratorGUI/Maps/Traffic/CustomModel/oldcustommodels.h

FORMS    += \
    ../LTEsimGeneratorGUI/Ui/parameterswindow.ui \
    ../LTEsimGeneratorGUI/Ui/helpdialog.ui \
    ../LTEsimGeneratorGUI/Ui/projectmanagement.ui \
    ../LTEsimGeneratorGUI/Ui/settings.ui \
    ../LTEsimGeneratorGUI/Ui/channelmodelform.ui \
    ../LTEsimGeneratorGUI/Ui/mmeform.ui \
    ../LTEsimGeneratorGUI/Ui/ipexform.ui \
    ../LTEsimGeneratorGUI/Ui/ubsimform.ui \
    ../LTEsimGeneratorGUI/Ui/uctoolform.ui \
    ../LTEsimGeneratorGUI/Ui/mapwindow.ui \
    ../LTEsimGeneratorGUI/Ui/mapwindowlarge.ui \
    ../LTEsimGeneratorGUI/Ui/sgwform.ui \
    ../LTEsimGeneratorGUI/Ui/maprangeform.ui \
    ../LTEsimGeneratorGUI/Ui/maprangelargeform.ui \
    ../LTEsimGeneratorGUI/Ui/map_traffic.ui \
    ../LTEsimGeneratorGUI/Ui/map_traffic_large.ui \
    ../LTEsimGeneratorGUI/Ui/addftpdlform.ui \
    ../LTEsimGeneratorGUI/Ui/addftpulform.ui \
    ../LTEsimGeneratorGUI/Ui/addpingform.ui \
    ../LTEsimGeneratorGUI/Ui/addservicereqform.ui \
    ../LTEsimGeneratorGUI/Ui/addstreamdlform.ui \
    ../LTEsimGeneratorGUI/Ui/addstreamulform.ui \
    ../LTEsimGeneratorGUI/Ui/addsyncedpingform.ui \
    ../LTEsimGeneratorGUI/Ui/addvoipform.ui \
    ../LTEsimGeneratorGUI/Ui/custommodels.ui \
    ../LTEsimGeneratorGUI/Ui/tuningtrafficform.ui \
    ../LTEsimGeneratorGUI/Ui/UE_param_form.ui \
    ../LTEsimGeneratorGUI/Ui/managementtemplate.ui \
    ../LTEsimGeneratorGUI/Ui/timeForm.ui \
    ../LTEsimGeneratorGUI/Ui/addProjectWindow.ui \
    ../LTEsimGeneratorGUI/Ui/statisticsForm.ui \
    ../LTEsimGeneratorGUI/Ui/customModel.ui


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
