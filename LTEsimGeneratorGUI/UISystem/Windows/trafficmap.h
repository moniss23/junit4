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

signals:
    void spawnWindow_Time(const QString &projectName, const QString &trafficName);
    void spawnWindow_CustomModels(const QString &projectName, const QString &trafficName);
    void spawnWindow_TuningTraffic(const QString &projectName, const QString &trafficName);
    void spawnWindow_Statistics(const QString &projectName, const QString &trafficFileName);

    void addUe(const QString &projectName, const QString &trafficFileName);
    void updateUe(const QString &projectName, const QString &trafficName, const UEData &ueData);
    void removeUe(const QString &projectName, const QString &trafficName, const UEData &ueData);

private slots:
    void on_pushButton_pressed();
    void on_addUeButton_clicked();
    void on_removeUeButton_clicked();
    void on_statisticsButton_clicked();
    void on_tunningTrafficButton_clicked();

private:
    Ui::TrafficMap *    ui;
    QHBoxLayout *       hBoxLayout1;
    QHBoxLayout *       hBoxLayout2;
    QVBoxLayout *       vBoxLayout;
    MapView *           mapView;

    TrafficFileData*    trafficFileData;
    Project             project;

    UeRepresentation*   clickedUe;
};

#endif // TRAFFICMAP_H
