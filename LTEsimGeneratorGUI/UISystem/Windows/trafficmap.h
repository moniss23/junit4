#ifndef TRAFFICMAP_H
#define TRAFFICMAP_H

#include <QMainWindow>

#include "Data/Objects/trafficfiledata.h"
#include "Data/project.h"

class MapView;
class QHBoxLayout;
class QVBoxLayout;

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
    void loadAndOpen(const Project &project, const TrafficFileData &trafficFileData);

signals:
    void spawnWindow_Statistics(const QString &projectName, const QString &trafficFileName);
    void spawnWindow_CustomModels(const QString &projectName, const QString &trafficName);
    void spawnWindow_Time(const QString &projectName, const QString &trafficName);
    void spawnWindow_TuningTraffic(const QString &projectName, const QString &trafficName);

private slots:
    void on_pushButton_pressed();
    void on_statisticsButton_clicked();
    void on_tunningTrafficButton_clicked();

private:
    Ui::TrafficMap *    ui;
    QHBoxLayout *       hBoxLayout1;
    QHBoxLayout *       hBoxLayout2;
    QVBoxLayout *       vBoxLayout;
    MapView *           mapView;

    TrafficFileData     trafficFileData;
    Project             project;
};

#endif // TRAFFICMAP_H
