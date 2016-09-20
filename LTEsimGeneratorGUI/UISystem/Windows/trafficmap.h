#ifndef TRAFFICMAP_H
#define TRAFFICMAP_H

#include <QMainWindow>

#include "Data/project.h"
#include "Data/Objects/trafficfiledata.h"

class MapView;
class QHBoxLayout;
class QVBoxLayout;
class UeRepresentation;

namespace Ui {
class TrafficMap;
}

class TrafficMap : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrafficMap(QWidget *parent = 0);
    ~TrafficMap();

public slots:
    void loadAndOpen(const Project &project, TrafficFileData *trafficFileData);
    void refreshWindow(const Project &project, TrafficFileData *trafficFileData);
    void updateUe_MapView(UeRepresentation*,const QString &projectName, const QString &trafficName, const UEData &ueData);
    void spawnWindow_UeParams(UeRepresentation* ueRepresentation, const QString &ueDataName);
    void updateUeDataInUeRepresentation(const UEData& ueData, int x, int y);
    void updateButtonsColor();
signals:
    void spawnWindow_Time(const QString &projectName, const QString &trafficName);
    void spawnWindow_CustomModels(const QString &projectName, const QString &trafficName);
    void spawnWindow_TuningTraffic(const QString &projectName, const QString &trafficName);
    void spawnWindow_Statistics(const QString &projectName, const QString &trafficFileName);

    void spawnWindow_UCTool(const QString &projectName,bool enable);
    void spawnWindow_Mme(const QString &projectName,bool enable);
    void spawnWindow_UBsim(const QString &projectName,bool enable);
    void spawnWindow_Paging(const QString &projectName,bool enable);
    void spawnWindow_ChannelModels(const QString &projectName,bool enable);
    void spawnWindow_Sgw(const QString &projectName,bool enable);
    void spawnWindow_GeneralSettings(const QString &projectName,bool enable);
    void spawnWindow_Ipex(const QString &projectName,bool enable);
    void spawnWindow_Ue(const QString &projectName,bool enable);
    void spawnWindow_ueParams(const QString &ueDataName, const QString& projectName, const QString& trafficName);
    void spawnWindow_PagingRate(const QString &projectName);
    void addUe(const QString &projectName, const QString &trafficFileName);
    void updateUe(const QString &projectName, const QString &trafficName, const UEData &ueData);
    void removeUe(const QString &projectName, const QString &trafficName, const UEData &ueData);
    void saveProjectOnMapTrafficClose(const QString &projectName);
    void setEnabledPagingRate(bool value);
    void setEnabledUBSim(bool value);
private slots:
    void on_pushButton_pressed();
    void on_addUeButton_clicked();
    void on_removeUeButton_clicked();
    void on_statisticsButton_clicked();
    void on_tunningTrafficButton_clicked();
    void on_ucToolButton_clicked();
    void on_channelModelsButton_clicked();
    void on_ubSimButton_clicked();
    void on_ueButton_clicked();
    void on_ipexButton_clicked();
    void on_sgwButton_clicked();
    void on_pagingButton_clicked();
    void on_mmeButton_clicked();
    void on_generalSettingsButton_clicked();
    void on_PagingRateButton_clicked();
    void on_timeButton_clicked();

private:
    void closeEvent(QCloseEvent *event);

private:
    Ui::TrafficMap *    ui;
    QHBoxLayout *       hBoxLayout1;
    QHBoxLayout *       hBoxLayout2;
    QVBoxLayout *       vBoxLayout;
    MapView *           mapView;

    TrafficFileData*    trafficFileData;
    Project             project;

    UeRepresentation*   ueRepresentation;

    UeRepresentation*   clickedUe;
};

#endif // TRAFFICMAP_H
