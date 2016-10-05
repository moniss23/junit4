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
/**
 * @brief The NewMapWindow class is a graphical representation of Parameters script
 */
class NewMapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewMapWindow(QWidget *parent = 0);
    ~NewMapWindow();
/********************
 * PUBLIC WINDOW API
 ********************/
public slots:
    /**
     * @brief refreshWindow updates the diplayed data
     * @param project current data
     */
    void refreshWindow(const Project &project);
    /**
     * @brief loadAndOpen loads parameters necesary for the view and shows it
     * @param project is object with necesary data
     */
    void loadAndOpen(const Project &project);
    /**
     * @brief spawnWindow_MapView_handoverParams shows a tab with selected Handover parameters
     * @param clickedHo selected Handover
     * @param hoObj is data of current Handover
     */
    void spawnWindow_MapView_handoverParams(HandoverRepresentation *clickedHo, const Handover &hoObj);
    /**
     * @brief spawnWindow_MapView_cellParams shows a tab with selected Cell parameters
     * @param clickedCell selected Cell
     * @param cellObj is data of current Cell
     */
    void spawnWindow_MapView_cellParams(CellRepresentation *clickedCell, const QPair<Cell,Center> &cellObj);
    /**
     * @brief spawnWindow_MapRange shows the window with range of map parameters
     */
    void spawnWindow_MapRange();
    /**
     * @brief updateButtonsColor updates colors of buttons
     */
    void updateButtonsColor();
    /**
     * @brief addCellToScene adds a new CellRepresentation to the view
     * @param cellinfo information about all the cells with the new one
     */
    void addCellToScene(QPair<Cell,Center> &cellinfo);
    /**
     * @brief addHandoverToScene adds a new HandoverRepresentation to the view
     * @param handover information about the current Handover
     */
    void addHandoverToScene(Handover &handover);
    /**
     * @brief updateProject overwrites the Project object with changed data
     * @param project is the current Project's new data
     */
    void updateProject(Project &project);
signals:
    /**
     * @brief spawnWindow_Mme is a signal sent to show MME setting
     * @param projectNames is current Project's name
     */
    void spawnWindow_Mme(const QString& projectNames,bool);
    /**
     * @brief spawnWindow_Paging is a signal sent to show Paging setting
     * @param projectNames is current Project's name
     */
    void spawnWindow_Paging(const QString& projectName,bool);
    /**
     * @brief spawnWindow_Sgw is a signal sent to show SGW setting
     * @param projectNames is current Project's name
     */
    void spawnWindow_Sgw(const QString& projectName,bool);
    /**
     * @brief spawnWindow_Ipex is a signal sent to show IPEX setting
     * @param projectNames is current Project's name
     */
    void spawnWindow_Ipex(const QString& projectName,bool);
    /**
     * @brief spawnWindow_UBSim is a signal sent to show UBSim setting
     * @param projectNames is current Project's name
     */
    void spawnWindow_UBSim(const QString& projectName,bool);
    /**
     * @brief spawnWindow_ucTool is a signal sent to show UCTool setting
     * @param projectNames is current Project's name
     */
    void spawnWindow_ucTool(const QString &projectName,bool);
    /**
     * @brief spawnWindow_ChannelModel is a signal sent to show ChannelModel setting
     * @param projectNames is current Project's name
     */
    void spawnWindow_ChannelModel(const QString& projectName,bool);
    /**
     * @brief spawnWindow_mapRange is a signal sent to show MapRange setting
     * @param projectNames is current Project's name
     */
    void spawnWindow_mapRange(const QString &projectName);
    /**
     * @brief spawnWindow_GeneralConfiguration is a signal sent to show General setting
     * @param projectNames is current Project's name
     */
    void spawnWindow_GeneralConfiguration(const QString &projectName,bool);
    /**
     * @brief spawnWindow_Ue is a signal sent to show UE setting
     * @param projectNames is current Project's name
     */
    void spawnWindow_Ue(const QString &projectName,bool);

    /**
     * @brief updateUEsimulated is a signal sent to update UE simulation settings
     * @param projectName is current Project's name
     * @param checked determines if the window is read only
     */
    void updateUEsimulated(const QString& projectName, const bool& checked);
    /**
     * @brief updateCoreNetworkis a signal sent to update Core Network settings
     * @param projectName is current Project's name
     * @param checked determines if the window is read only
     */
    void updateCoreNetwork(const QString& projectName, const bool& checked);
    /**
     * @brief updatePaging a signal sent to update Paging settings
     * @param projectName is current Project's name
     * @param checked determines if the window is read only
     */
    void updatePaging(const QString& projectName, const bool& checked);
    /**
     * @brief updateUbSim a signal sent to update UBSim settings
     * @param projectName is current Project's name
     * @param checked determines if the window is read only
     */
    void updateUbSim(const QString& projectName, const bool& checked);
    /**
     * @brief updateUe a signal sent to update UEs' settings
     * @param projectName is current Project's name
     * @param checked determines if the window is read only
     */
    void updateUe(const QString& projectName, const bool& checked);
    /**
     * @brief updateSgw a signal sent to update SGW settings
     * @param projectName is current Project's name
     * @param checked determines if the window is read only
     */
    void updateSgw(const QString& projectName, const bool& checked);

    /**
     * @brief addCell is a signal sent to add a new Cell object representation
     * @param projectName is current Project's name
     */
    void addCell(const QString &projectName);
    /**
     * @brief addHandover is a signal sent to add a new Handover object representation
     * @param projectName is current Project's name
     */
    void addHandover(const QString &projectName);

    /**
     * @brief removeHandover is a signal sent to remove selected Handover object and its representation
     * @param handover is the selected Handover
     * @param projectName is current Project's name
     */
    void removeHandover(const Handover &handover, const QString &projectName);
    /**
     * @brief updateHandoveris a signal sent to update selected Handover object and its representation
     * @param handover is the selected Handover
     * @param projectName is current Project's name
     */
    void updateHandover(const Handover &handover, const QString &projectName);
    /**
     * @brief removeCell is a signal sent to remove selected Cell object and its representation
     * @param cell is the selected Cell
     * @param projectName is current Project's name
     */
    void removeCell(const QPair<Cell,Center> &cell, const QString &projectName);
    /**
     * @brief updateCell is a signal sent to update selected Cell object and  its representation
     * @param cell is information about selected Cell
     * @param cellName is selected cell name
     * @param projectName is current Project's name
     */
    void updateCell(const QPair<Cell,Center> &cell, const QString &cellName, const QString &projectName);

    /**
     * @brief saveProjectOnClose is a signal sent to update current Project with new data
     * @param projectName is current Project's name
     */
    void saveProjectOnClose(const QString &projectName);

    /**
     * @brief setEnabledUBSim is a signal sent to enable/disable UBSim
     * @param value is a value of whether to enable or disable it
     */
    void setEnabledUBSim(bool value);
    /**
     * @brief setEnabledPagingRate is a signal sent to enable/disable Paging Rate
     * @param value is a value of whether to enable or disable it
     */
    void setEnabledPagingRate(bool value);

/************************
 * BINDING TO UI BUTTONS
 ************************/
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
    /**
     * @brief closeEvent is an Event inherited from QMainWindow class
     * @param event is the even passed
     */
    void closeEvent(QCloseEvent *event);

private:
    Ui::NewMapWindow *ui;                        //<<< A pointer to the NewMapWindow object
    QHBoxLayout      *hBoxLayout;                //<<< A pointer to a horisontal layout
    QVBoxLayout      *vBoxLayout;                //<<< A pointer to a vertical layout
    MapView          *mapView;                   //<<< A pointer to the Map
    Project           project;                   //<<< A local copy of current Project

    CellRepresentation *clickedCell;             //<<< A pointer to a selected CellRepresentation
    HandoverRepresentation* clickedHandover;     //<<< A pointer to a selected HandoverRepresentation
};

#endif // NEWMAPWINDOW_H
