#-------------------------------------------------
#
# Project created by QtCreator 2015-07-07T13:59:42
#
#-------------------------------------------------

QT       += core gui testlib
QT       +=xml
QT += widgets testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LTEsimGeneratorGUI
TEMPLATE = app
CONFIG   += testcase
CONFIG   += c++11


SOURCES += main.cpp\
    ManagementWindow/ParametersWindow/parameterswindow.cpp \
    ManagementWindow/Helpdialog/helpdialog.cpp \
    ManagementWindow/ProjectManagement/projectmanagement.cpp \
    ManagementWindow/Settings/settings.cpp \
    Maps/MapObjects/cell.cpp \
    Maps/MapObjects/center.cpp \
    Maps/MapObjects/handover.cpp \
    Maps/Parameters/ChannelModel/channelmodel.cpp \
    Maps/Parameters/ChannelModel/channelmodelform.cpp \
    Maps/Parameters/SimulatedCoreNetwork/Mme/mme.cpp \
    Maps/Parameters/SimulatedCoreNetwork/Mme/mmeform.cpp \
    Maps/Parameters/SimulatedUe/ipexform.cpp \
    Maps/Parameters/SimulatedUe/ipgwtg.cpp \
    Maps/Parameters/SimulatedUe/ubsimform.cpp \
    Maps/Parameters/UcTool/uctoolform.cpp \
    Maps/Parameters/MapWindow/mapwindow.cpp \
    Maps/Parameters/MapWindow/mapwindowlarge.cpp \
    Maps/Parameters/SimulatedCoreNetwork/Sgw/sgw.cpp \
    Maps/Parameters/SimulatedCoreNetwork/Sgw/sgwform.cpp \
    Maps/Parameters/MapRange/maprange.cpp \
    Maps/Parameters/MapRange/maprangeform.cpp \
    Maps/Parameters/MapRange/maprangelargeform.cpp \
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
    Maps/Traffic/CustomModel/custommodels.cpp \
    Maps/Traffic/Statistics/statistics.cpp \
    Maps/Traffic/Statistics/statisticsform.cpp \
    Maps/Traffic/Tuning/tuningtraffic.cpp \
    Maps/Traffic/Tuning/tuningtrafficform.cpp \
    Maps/Traffic/UeParameters/ue.cpp \
    Maps/Traffic/UeParameters/UE_param_form.cpp \
    Maps/Traffic/MapComponents/draguelabel.cpp \
    Maps/Traffic/MapTest/MapComponentsTest/draguelabel_test.cpp \
    Maps/Traffic/map_traffic.cpp \
    Maps/Traffic/map_traffic_large.cpp \
    Maps/Traffic/ManagementTemplate/managementtemplate.cpp \
    Maps/Traffic/MapTest/managementtemplate_test.cpp \
    Maps/Traffic/DataObjects/handoverdata.cpp \
    Maps/Traffic/MapTest/DataObjectsTest/HandoverDataTest/handoverdata_test.cpp \
    Maps/Traffic/UeParameters/uegroupdata.cpp \
    Maps/Traffic/Statistics/statisticsdata.cpp \
    Maps/Traffic/MapTest/Statistics/statisticsdata_test.cpp\
    Maps/Traffic/MapTest/UeParametersTest/uegroupdata_test.cpp\
    Maps/Traffic/MapTest/DataObjectsTest/CellDataTest/celldata_test.cpp \
    Maps/Traffic/DataObjects/celldata.cpp \
    ProjectReaderWriter/projectreaderwriter.cpp \
    Maps/Traffic/MapData/mapdata.cpp \
    Maps/Traffic/MapTest/mapdata_test.cpp \
    Maps/Traffic/MapTest/MapComponentsTest/mapmanagement_test.cpp \
    Maps/Traffic/MapComponents/mapmanagement.cpp \
    Maps/Traffic/MapComponents/myscrollareawidget.cpp \
    Maps/Traffic/MapTest/MapComponentsTest/myscrollareawidget_test.cpp \
    Maps/Traffic/MapComponents/custommodellabel.cpp \
    Maps/Traffic/MapTest/MapComponentsTest/custommodellabel_test.cpp \
    Maps/Traffic/MapComponents/statisticsbutton.cpp \
    Maps/Traffic/MapTest/MapComponentsTest/statisticsbutton_test.cpp \
    Maps/Traffic/MapComponents/timebutton.cpp \
    Maps/Traffic/MapTest/MapComponentsTest/timebutton_test.cpp \
    Maps/Traffic/MapComponents/tuningtrafficbutton.cpp \
    Maps/Traffic/MapTest/MapComponentsTest/tuningtrafficbutton_test.cpp \
    Maps/Traffic/MapTest/MapComponentsTest/scale_test.cpp \
    Maps/Traffic/MapComponents/addbutton.cpp \
    Maps/Traffic/MapTest/MapComponentsTest/addbutton_test.cpp \
    Maps/Traffic/MapComponents/cellarea.cpp \
    Maps/Traffic/MapTest/MapComponentsTest/cellarea_test.cpp \
    Maps/Traffic/MapComponents/handoverarea.cpp \
    Maps/Traffic/MapTest/MapComponentsTest/handoverarea_test.cpp \
    Maps/Traffic/MapTest/MapComponentsTest/compositionofareas_test.cpp \
    TestRunner/testrunner.cpp \
    ManagementWindow/Encryption/encryption.cpp \
    AppSettings/appsettings.cpp \
    DoubleInputValidator/doubleinputvalidator.cpp \
    my_qlabel.cpp \
    CommonConstans/common_constans.cpp \
    Maps/Traffic/Time/timeData.cpp \
    Maps/Traffic/Time/timeManager.cpp \
    ManagementWindow/AddProjectWindow/addProjectWindow.cpp

HEADERS  += \
    ManagementWindow/ParametersWindow/parameterswindow.h \
    ManagementWindow/Helpdialog/helpdialog.h \
    ManagementWindow/ProjectManagement/projectmanagement.h \
    ManagementWindow/Settings/settings.h \
    Maps/MapObjects/cell.h \
    Maps/MapObjects/center.h \
    Maps/MapObjects/handover.h \
    Maps/Parameters/ChannelModel/channelmodel.h \
    Maps/Parameters/ChannelModel/channelmodelform.h \
    Maps/Parameters/SimulatedCoreNetwork/Mme/mme.h \
    Maps/Parameters/SimulatedCoreNetwork/Mme/mmeform.h \
    Maps/Parameters/SimulatedUe/ipexform.h \
    Maps/Parameters/SimulatedUe/ipgwtg.h \
    Maps/Parameters/SimulatedUe/ubsimform.h \
    Maps/Parameters/UcTool/uctoolform.h \
    Maps/Parameters/MapWindow/mapwindow.h \
    Maps/Parameters/MapWindow/mapwindowlarge.h \
    Maps/Parameters/SimulatedCoreNetwork/Sgw/sgw.h \
    Maps/Parameters/SimulatedCoreNetwork/Sgw/sgwform.h \
    Maps/Parameters/MapRange/maprange.h \
    Maps/Parameters/MapRange/maprangeform.h \
    Maps/Parameters/MapRange/maprangelargeform.h \
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
    Maps/Traffic/CustomModel/custommodels.h \
    Maps/Traffic/Statistics/statistics.h \
    Maps/Traffic/Statistics/statisticsform.h \
    Maps/Traffic/Tuning/tuningtraffic.h \
    Maps/Traffic/Tuning/tuningtrafficform.h \
    Maps/Traffic/UeParameters/ue.h \
    Maps/Traffic/UeParameters/UE_param_form.h \
    Maps/Traffic/MapComponents/draguelabel.h \
    Maps/Traffic/MapTest/MapComponentsTest/draguelabel_test.h \
    Maps/Traffic/map_traffic.h \
    Maps/Traffic/map_traffic_large.h \
    dataelementsinterface.h \
    Maps/Traffic/ManagementTemplate/managementtemplate.h \
    Maps/Traffic/MapTest/managementtemplate_test.h \
    Maps/Traffic/DataObjects/handoverdata.h \
    Maps/Traffic/MapTest/DataObjectsTest/HandoverDataTest/handoverdata_test.h \
    Maps/Traffic/UeParameters/uegroupdata.h \
    Maps/Traffic/MapTest/UeParametersTest/uegroupdata_test.h \
    Maps/Traffic/Statistics/statisticsdata.h \
    Maps/Traffic/MapTest/Statistics/statisticsdata_test.h \
    Maps/Traffic/MapTest/DataObjectsTest/CellDataTest/celldata_test.h \
    Maps/Traffic/DataObjects/celldata.h \
    ProjectReaderWriter/projectreaderwriter.h \
    Maps/Traffic/MapData/mapdata.h \
    Maps/Traffic/MapTest/mapdata_test.h \
    Maps/Traffic/MapTest/MapComponentsTest/mapmanagement_test.h \
    Maps/Traffic/MapComponents/mapmanagement.h \
    Maps/Traffic/MapComponents/myscrollareawidget.h \
    Maps/Traffic/MapTest/MapComponentsTest/myscrollareawidget_test.h \
    Maps/Traffic/MapComponents/custommodellabel.h \
    Maps/Traffic/MapTest/MapComponentsTest/custommodellabel_test.h \
    Maps/Traffic/MapComponents/statisticsbutton.h \
    Maps/Traffic/MapTest/MapComponentsTest/statisticsbutton_test.h \
    Maps/Traffic/MapComponents/timebutton.h \
    Maps/Traffic/MapTest/MapComponentsTest/timebutton_test.h \
    Maps/Traffic/MapComponents/tuningtrafficbutton.h \
    Maps/Traffic/MapTest/MapComponentsTest/tuningtrafficbutton_test.h \
    Maps/Traffic/MapComponents/scale.h \
    Maps/Traffic/MapTest/MapComponentsTest/scale_test.h \
    Maps/Traffic/MapComponents/addbutton.h \
    Maps/Traffic/MapTest/MapComponentsTest/addbutton_test.h \
    Maps/Traffic/MapComponents/myobjectarea.h \
    Maps/Traffic/MapComponents/cellarea.h \
    Maps/Traffic/MapTest/MapComponentsTest/cellarea_test.h \
    Maps/Traffic/MapComponents/handoverarea.h \
    Maps/Traffic/MapTest/MapComponentsTest/handoverarea_test.h \
    Maps/Traffic/MapComponents/compositionofareas.h \
    Maps/Traffic/MapTest/MapComponentsTest/compositionofareas_test.h \
    TestRunner/testrunner.h \
    AppSettings/appsettings.h \
    DoubleInputValidator/doubleinputvalidator.h \
    my_qlabel.h \
    CommonConstans/common_constans.h \
    Maps/Traffic/Time/timeData.h \
    Maps/Traffic/Time/timeManager.h \
    ManagementWindow/AddProjectWindow/addProjectWindow.h

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
    Ui/statisticsform.ui \
    Ui/tuningtrafficform.ui \
    Ui/UE_param_form.ui \
    Ui/managementtemplate.ui \
    Ui/timeForm.ui \
    Ui/addProjectWindow.ui


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


