#-------------------------------------------------
#
# Project created by QtCreator 2015-07-07T13:59:42
#
#-------------------------------------------------

QT       += core gui testlib
QT       +=xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LTEsimGeneratorGUI
TEMPLATE = app
CONFIG   += testcase
CONFIG   += c++11


SOURCES += main.cpp\
    my_qlabel.cpp \
    management_window/parameterswindow.cpp \
    management_window/filedialog.cpp \
    management_window/helpdialog.cpp \
    management_window/projectmanagement.cpp \
    management_window/settings.cpp \
    maps/object_map/cell.cpp \
    maps/object_map/center.cpp \
    maps/object_map/handover.cpp \
    maps/parameters_map/channel_model/channelmodel.cpp \
    maps/parameters_map/channel_model/channelmodelform.cpp \
    maps/parameters_map/simulated_core_network/mme.cpp \
    maps/parameters_map/simulated_core_network/mmeform.cpp \
    maps/parameters_map/simulated_ue/ipexform.cpp \
    maps/parameters_map/simulated_ue/ipgwtg.cpp \
    maps/parameters_map/simulated_ue/ubsimform.cpp \
    maps/parameters_map/uctool/uctoolform.cpp \
    maps/parameters_map/mapwindow.cpp \
    maps/parameters_map/mapwindowlarge.cpp \
    maps/parameters_map/simulated_core_network/sgw.cpp \
    maps/parameters_map/simulated_core_network/sgwform.cpp \
    maps/parameters_map/maprange.cpp \
    maps/parameters_map/maprangeform.cpp \
    maps/parameters_map/maprangelargeform.cpp \
    maps/traffic_map/custom_model/addftpdl.cpp \
    maps/traffic_map/custom_model/addftpdlform.cpp \
    maps/traffic_map/custom_model/addftpul.cpp \
    maps/traffic_map/custom_model/addftpulform.cpp \
    maps/traffic_map/custom_model/addping.cpp \
    maps/traffic_map/custom_model/addpingform.cpp \
    maps/traffic_map/custom_model/addservicereq.cpp \
    maps/traffic_map/custom_model/addservicereqform.cpp \
    maps/traffic_map/custom_model/addstreamdl.cpp \
    maps/traffic_map/custom_model/addstreamdlform.cpp \
    maps/traffic_map/custom_model/addstreamul.cpp \
    maps/traffic_map/custom_model/addstreamulform.cpp \
    maps/traffic_map/custom_model/addsyncedping.cpp \
    maps/traffic_map/custom_model/addsyncedpingform.cpp \
    maps/traffic_map/custom_model/addvoip.cpp \
    maps/traffic_map/custom_model/addvoipform.cpp \
    maps/traffic_map/custom_model/custommodels.cpp \
    maps/traffic_map/statistics/statistics.cpp \
    maps/traffic_map/statistics/statisticsform.cpp \
    maps/traffic_map/tuningtraffic/tuningtraffic.cpp \
    maps/traffic_map/tuningtraffic/tuningtrafficform.cpp \
    maps/traffic_map/ue_param/ue.cpp \
    maps/traffic_map/ue_param/UE_param_form.cpp \
    maps/traffic_map/draguelabel.cpp \
    maps/traffic_map/map_traffic.cpp \
    maps/traffic_map/map_traffic_large.cpp \
    maps/traffic_map/timetraffic/timetraffic.cpp \
    maps/traffic_map/timetraffic/timetrafficform.cpp \
    doubleinputvalidator.cpp \
    maps/traffic_map/managementtemplate.cpp \
    maps/traffic_map_test/managementtemplate_test.cpp \
    maps/traffic_map/data_objects/handoverdata.cpp \
    maps/traffic_map_test/data_objects_test/handoverdata_test.cpp \
    maps/traffic_map/ue_param/uegroupdata.cpp \
    maps/traffic_map/statistics/statisticsdata.cpp \
    maps/traffic_map_test/statistics/statisticsdata_test.cpp\
    maps/traffic_map_test/ue_param_test/uegroupdata_test.cpp\
    maps/traffic_map_test/data_objects_test/celldata_test.cpp \
    maps/traffic_map/data_objects/celldata.cpp \
    maps/projectreaderwriter.cpp \
    common_constans.cpp \
    maps/traffic_map/mapdata.cpp \
    maps/traffic_map_test/mapdata_test.cpp \
    maps/traffic_map_test/map_components_test/mapmanagement_test.cpp \
    maps/traffic_map/map_components/mapmanagement.cpp \
    maps/traffic_map/map_components/myscrollareawidget.cpp \
    maps/traffic_map_test/map_components_test/myscrollareawidget_test.cpp \
    maps/traffic_map/map_components/custommodellabel.cpp \
    maps/traffic_map_test/map_components_test/custommodellabel_test.cpp \
    maps/traffic_map/map_components/statisticsbutton.cpp \
    maps/traffic_map_test/map_components_test/statisticsbutton_test.cpp \
    maps/traffic_map/map_components/timebutton.cpp \
    maps/traffic_map_test/map_components_test/timebutton_test.cpp \
    maps/traffic_map/map_components/tuningtrafficbutton.cpp \
    maps/traffic_map_test/map_components_test/tuningtrafficbutton_test.cpp \
    maps/testrunner.cpp

HEADERS  += \
    management_window/parameterswindow.h \
    my_qlabel.h \
    management_window/filedialog.h \
    management_window/helpdialog.h \
    management_window/projectmanagement.h \
    management_window/settings.h \
    maps/object_map/cell.h \
    maps/object_map/center.h \
    maps/object_map/handover.h \
    maps/parameters_map/channel_model/channelmodel.h \
    maps/parameters_map/channel_model/channelmodelform.h \
    maps/parameters_map/simulated_core_network/mme.h \
    maps/parameters_map/simulated_core_network/mmeform.h \
    maps/parameters_map/simulated_ue/ipexform.h \
    maps/parameters_map/simulated_ue/ipgwtg.h \
    maps/parameters_map/simulated_ue/ubsimform.h \
    maps/parameters_map/uctool/uctoolform.h \
    maps/parameters_map/mapwindow.h \
    maps/parameters_map/mapwindowlarge.h \
    maps/parameters_map/simulated_core_network/sgw.h \
    maps/parameters_map/simulated_core_network/sgwform.h \
    maps/parameters_map/maprange.h \
    maps/parameters_map/maprangeform.h \
    maps/parameters_map/maprangelargeform.h \
    management_window/encryption.h \
    maps/traffic_map/custom_model/addftpdl.h \
    maps/traffic_map/custom_model/addftpdlform.h \
    maps/traffic_map/custom_model/addftpul.h \
    maps/traffic_map/custom_model/addftpulform.h \
    maps/traffic_map/custom_model/addping.h \
    maps/traffic_map/custom_model/addpingform.h \
    maps/traffic_map/custom_model/addservicereq.h \
    maps/traffic_map/custom_model/addservicereqform.h \
    maps/traffic_map/custom_model/addstreamdl.h \
    maps/traffic_map/custom_model/addstreamdlform.h \
    maps/traffic_map/custom_model/addstreamul.h \
    maps/traffic_map/custom_model/addstreamulform.h \
    maps/traffic_map/custom_model/addsyncedping.h \
    maps/traffic_map/custom_model/addsyncedpingform.h \
    maps/traffic_map/custom_model/addvoip.h \
    maps/traffic_map/custom_model/addvoipform.h \
    maps/traffic_map/custom_model/custommodels.h \
    maps/traffic_map/statistics/statistics.h \
    maps/traffic_map/statistics/statisticsform.h \
    maps/traffic_map/tuningtraffic/tuningtraffic.h \
    maps/traffic_map/tuningtraffic/tuningtrafficform.h \
    maps/traffic_map/ue_param/ue.h \
    maps/traffic_map/ue_param/UE_param_form.h \
    maps/traffic_map/draguelabel.h \
    maps/traffic_map/map_traffic.h \
    maps/traffic_map/map_traffic_large.h \
    maps/traffic_map/timetraffic/timetraffic.h \
    maps/traffic_map/timetraffic/timetrafficform.h \
    doubleinputvalidator.h \
    dataelementsinterface.h \
    maps/traffic_map/managementtemplate.h \
    maps/traffic_map_test/managementtemplate_test.h \
    maps/traffic_map/data_objects/handoverdata.h \
    maps/traffic_map_test/data_objects_test/handoverdata_test.h \
    common_constans.h \
    maps/traffic_map/ue_param/uegroupdata.h \
    maps/traffic_map_test/ue_param_test/uegroupdata_test.h \
    maps/traffic_map/statistics/statisticsdata.h \
    maps/traffic_map_test/statistics/statisticsdata_test.h \
    maps/traffic_map_test/data_objects_test/celldata_test.h \
    maps/traffic_map/data_objects/celldata.h \
    maps/projectreaderwriter.h \
    maps/traffic_map/mapdata.h \
    maps/traffic_map_test/mapdata_test.h \
    maps/traffic_map_test/map_components_test/mapmanagement_test.h \
    maps/traffic_map/map_components/mapmanagement.h \
    maps/traffic_map/map_components/myscrollareawidget.h \
    maps/traffic_map_test/map_components_test/myscrollareawidget_test.h \
    maps/traffic_map/map_components/custommodellabel.h \
    maps/traffic_map_test/map_components_test/custommodellabel_test.h \
    maps/traffic_map/map_components/statisticsbutton.h \
    maps/traffic_map_test/map_components_test/statisticsbutton_test.h \
    maps/traffic_map/map_components/timebutton.h \
    maps/traffic_map_test/map_components_test/timebutton_test.h \
    maps/traffic_map/map_components/tuningtrafficbutton.h \
    maps/traffic_map_test/map_components_test/tuningtrafficbutton_test.h \
    maps/testrunner.h


FORMS    += \
    management_window/parameterswindow.ui \
    management_window/filedialog.ui \
    management_window/helpdialog.ui \
    management_window/projectmanagement.ui \
    management_window/settings.ui \
    maps/parameters_map/channel_model/channelmodelform.ui \
    maps/parameters_map/simulated_core_network/mmeform.ui \
    maps/parameters_map/simulated_ue/ipexform.ui \
    maps/parameters_map/simulated_ue/ubsimform.ui \
    maps/parameters_map/uctool/uctoolform.ui \
    maps/parameters_map/mapwindow.ui \
    maps/parameters_map/mapwindowlarge.ui \
    maps/parameters_map/simulated_core_network/sgwform.ui \
    maps/parameters_map/maprangeform.ui \
    maps/parameters_map/maprangelargeform.ui \
    maps/traffic_map/map_traffic.ui \
    maps/traffic_map/map_traffic_large.ui \
    maps/traffic_map/custom_model/addftpdlform.ui \
    maps/traffic_map/custom_model/addftpulform.ui \
    maps/traffic_map/custom_model/addpingform.ui \
    maps/traffic_map/custom_model/addservicereqform.ui \
    maps/traffic_map/custom_model/addstreamdlform.ui \
    maps/traffic_map/custom_model/addstreamulform.ui \
    maps/traffic_map/custom_model/addsyncedpingform.ui \
    maps/traffic_map/custom_model/addvoipform.ui \
    maps/traffic_map/custom_model/custommodels.ui \
    maps/traffic_map/statistics/statisticsform.ui \
    maps/traffic_map/tuningtraffic/tuningtrafficform.ui \
    maps/traffic_map/ue_param/UE_param_form.ui \
    maps/traffic_map/timetraffic/timetrafficform.ui \
    maps/traffic_map/managementtemplate.ui

OTHER_FILES += \
    logoLTEsim.png

RESOURCES += \
    Resource.qrc

DISTFILES +=

QT += widgets testlib
