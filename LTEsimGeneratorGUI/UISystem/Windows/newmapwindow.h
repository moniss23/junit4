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
    void refreshWindow(const Project &project);
    void loadAndOpen(const Project &project);
    void spawnWindow_MapView_handoverParams(HandoverRepresentation*, const Handover&);
    void spawnWindow_MapView_cellParams(CellRepresentation*, const QPair<Cell,Center>&);
    void spawnWindow_MapRange();
    void updateButtonsColor();
    void addCellToScene(QPair<Cell,Center> &cellinfo);
    void addHandoverToScene(Handover &handover);
    void updateProject(Project &project);
signals:
    void spawnWindow_Mme(const QString& projectNames,bool);
    void spawnWindow_Paging(const QString& projectName,bool);
    void spawnWindow_Sgw(const QString& projectName,bool);
    void spawnWindow_Ipex(const QString& projectName,bool);
    void spawnWindow_UBSim(const QString& projectName,bool);
    void spawnWindow_ucTool(const QString &projectName,bool);
    void spawnWindow_ChannelModel(const QString& projectName,bool);
    void spawnWindow_mapRange(const QString &projectName);
    void spawnWindow_GeneralConfiguration(const QString &projectName,bool);
    void spawnWindow_Ue(const QString &projectName,bool);

    void updateUEsimulated(const QString& projectName, const bool& checked);
    void updateCoreNetwork(const QString& projectName, const bool& checked);
    void updatePaging(const QString& projectName, const bool& checked);
    void updateUbSim(const QString& projectName, const bool& checked);
    void updateUe(const QString& projectName, const bool& checked);
    void updateSgw(const QString& projectName, const bool& checked);

    void addCell(const QString &projectName);
    void addHandover(const QString &projectName);

    void removeHandover(const Handover &handover, const QString &projectName);
    void updateHandover(const Handover &handover, const QString &projectName);
    void removeCell(const QPair<Cell,Center> &cell, const QString &projectName);
    void updateCell(const QPair<Cell,Center> &cell, const QString &cellName, const QString &projectName);

    void saveProjectOnClose(const QString &projectName);

    void setEnabledUBSim(bool value);
    void setEnabledPagingRate(bool value);

private slots:
    void on_mmeButton_pressed();
    void on_pagingButton_pressed();
    void on_sgwButton_pressed();
    void on_ipexButton_pressed();
    void on_ubSimButton_pressed();
    void on_ueButton_pressed();
    void on_ucToolButton_pressed();
    void on_channelModelsButton_pressed();

    void on_addCellBtn_clicked();
    void on_removeCellBtn_clicked();

    void on_addHandoverBtn_clicked();
    void on_removeHandoverBtn_clicked();

    void on_setCellParamsBtn_clicked();
    void on_setHandoverParamsBtn_clicked();
    void on_generalSettingsButton_clicked();

private:

    void closeEvent(QCloseEvent *event);
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
