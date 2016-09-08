#ifndef NEWMAPWINDOW_H
#define NEWMAPWINDOW_H

#include <QMainWindow>

#include "Data/project.h"

class MapView;
class QHBoxLayout;
class QVBoxLayout;
class CellRepresentation;
class HandoverRepresentation;

namespace Ui {
class NewMapWindow;
}

class NewMapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewMapWindow(QWidget *parent = 0);
    ~NewMapWindow();

public slots:
    void loadAndOpen(const Project &project);
    void spawnWindow_MapView_handoverParams(HandoverRepresentation*, const Handover&);
    void spawnWindow_MapView_cellParams(CellRepresentation*, const QPair<Cell,Center>&);
    void spawnWindow_MapRange();

signals:
    void spawnWindow_Mme(const QString& projectName);
    void spawnWindow_Sgw(const QString& projectName);
    void spawnWindow_Ipex(const QString& projectName);
    void spawnWindow_UBSim(const QString& projectName);
    void spawnWindow_ucTool(const QString &projectName);
    void spawnWindow_ChannelModel(const QString& projectName);
    void spawnWindow_mapRange(const QString &projectName);

    void updateUEsimulated(const QString& projectName, const bool& checked);
    void updateCoreNetwork(const QString& projectName, const bool& checked);

    void removeHandover(const Handover &handover, const QString &projectName);
    void updateHandover(const Handover &handover, const QString &projectName);
    void removeCell(const QPair<Cell,Center> &cell, const QString &projectName);
    void updateCell(const QPair<Cell,Center> &cell, const QString &projectName);

private slots:
    void on_mmeButton_pressed();
    void on_sgwButton_pressed();
    void on_ipexButton_pressed();
    void on_ubSimButton_pressed();
    void on_ucToolButton_pressed();
    void on_channelModelsButton_pressed();
    void on_ueCheckbox_toggled(bool checked);
    void on_coreNetworkCheckbox_toggled(bool checked);

    void on_removeCellBtn_clicked();
    void on_setCellParamsBtn_clicked();
    void on_removeHandoverBtn_clicked();
    void on_setHandoverParamsBtn_clicked();

private:
    Ui::NewMapWindow *ui;
    QHBoxLayout      *hBoxLayout;
    QVBoxLayout      *vBoxLayout;
    MapView          *mapView;
    Project           project;

    CellRepresentation *clickedCell;
    HandoverRepresentation* clickedHandover;
};

#endif // NEWMAPWINDOW_H
