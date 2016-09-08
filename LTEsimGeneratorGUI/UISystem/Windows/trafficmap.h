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

signals:
    void spawnWindow_Statistics(const QString &projectName, const QString &trafficFileName);

public slots:
    void loadAndOpen(const Project &project, const TrafficFileData &trafficFileData);

private slots:
    void on_statisticsButton_clicked();

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
