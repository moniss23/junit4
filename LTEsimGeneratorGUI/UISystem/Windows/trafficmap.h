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

/**
 * @brief The TrafficMap class represents graphical representation of traffic script
 */
class TrafficMap : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrafficMap(QWidget *parent = 0);
    ~TrafficMap();

    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
public slots:
    /**
     * @brief loadAndOpen is used to load data and show window
     * @param project i current project
     * @param trafficFileData is current trafficFileData
     */
    void loadAndOpen(const Project &project, TrafficFileData *trafficFileData);
    /**
     * @brief refreshWindow is used to update displayed data
     * @param project is current project data
     * @param trafficFileData is current traffic data
     */
    void refreshWindow(const Project &project, TrafficFileData *trafficFileData);
    /**
     * @brief updateUe_MapView is used to update ue data on ue mouse release event
     * @param projectName is current project name
     * @param trafficName is current traffic name
     * @param ueData is current clicked ue data
     */
    void updateUe_MapView(UeRepresentation*,const QString &projectName, const QString &trafficName, const UEData &ueData);
    /**
     * @brief spawnWindow_UeParams is used to spawn ue parameters window
     * @param ueRepresentation is current double clicked ue
     * @param ueDataName is current double clicked ue data
     */
    void spawnWindow_UeParams(UeRepresentation* ueRepresentation, const QString &ueDataName);
    /**
     * @brief updateButtonsColor is used to update rbs buttons color
     */
    void updateButtonsColor();
    /**
     * @brief addUeToScene is used to add ue representation to scene
     * @param ueData is current ue data
     * @param ueDataIndex is current ue data index
     */
    void addUeToScene(UEData &ueData, int ueDataIndex);
    /**
     * @brief updateUeDataInUeRepresentation is used to update ue data in clicked ue representation
     * @param ueData is current clicked ue data
     */
    void updateUeDataInUeRepresentation(const UEData& ueData);

signals:
    /**
     * @brief spawnWindow_Time signal is used to spawn timeForm window
     * @param projectName is current project name
     * @param trafficName is current traffic name
     */
    void spawnWindow_Time(const QString &projectName, const QString &trafficName);
    /**
     * @brief spawnWindow_CustomModels signal is used to spawn customModelListForm window
     * @param projectName is current project name
     * @param trafficName is current traffic name
     */
    void spawnWindow_CustomModels(const QString &projectName, const QString &trafficName);
    /**
     * @brief spawnWindow_TuningTraffic signal is used to spawn tunningTrafficForm window
     * @param projectName is current project name
     * @param trafficName is current traffic name
     */
    void spawnWindow_TuningTraffic(const QString &projectName, const QString &trafficName);
    /**
     * @brief spawnWindow_Statistics signal is used to spawn statisticsForm window
     * @param projectName is current project name
     * @param trafficFileName is current traffic name
     */
    void spawnWindow_Statistics(const QString &projectName, const QString &trafficFileName);
    /**
     * @brief spawnWindow_UCTool signal is used to spawn UCToolForm window
     * @param projectName is current project name
     * @param enable is flag that represent if window is editable, false = editable
     */
    void spawnWindow_UCTool(const QString &projectName,bool enable);
    /**
     * @brief spawnWindow_Mme signal is used to spawn MmeForm window
     * @param projectName is current project name
     * @param enable is flag that represent if window is editable, false = editable
     */
    void spawnWindow_Mme(const QString &projectName,bool enable);
    /**
     * @brief spawnWindow_UBsim signal is used to spawn UBsimForm window
     * @param projectName is current project name
     * @param enable is flag that represent if window is editable, false = editable
     */
    void spawnWindow_UBsim(const QString &projectName,bool enable);
    /**
     * @brief spawnWindow_Paging signal is used to spawn PagingForm window
     * @param projectName is current project name
     * @param enable is flag that represent if window is editable, false = editable
     */
    void spawnWindow_Paging(const QString &projectName,bool enable);
    /**
     * @brief spawnWindow_ChannelModels signal is used to spawn ChannelModelsForm window
     * @param projectName is current project name
     * @param enable is flag that represent if window is editable, false = editable
     */
    void spawnWindow_ChannelModels(const QString &projectName,bool enable);
    /**
     * @brief spawnWindow_Sgw signal is used to spawn SgwForm window
     * @param projectName is current project name
     * @param enable is flag that represent if window is editable, false = editable
     */
    void spawnWindow_Sgw(const QString &projectName,bool enable);
    /**
     * @brief spawnWindow_GeneralSettings signal is used to spawn GeneralSettingsForm window
     * @param projectName is current project name
     * @param enable is flag that represent if window is editable, false = editable
     */
    void spawnWindow_GeneralSettings(const QString &projectName,bool enable);
    /**
     * @brief spawnWindow_Ipex signal is used to spawn IpexForm window
     * @param projectName is current project name
     * @param enable is flag that represent if window is editable, false = editable
     */
    void spawnWindow_Ipex(const QString &projectName,bool enable);
    /**
     * @brief spawnWindow_Ue signal is used to spawn UeForm window
     * @param projectName is current project name
     * @param enable is flag that represent if window is editable, false = editable
     */
    void spawnWindow_Ue(const QString &projectName,bool enable);
    /**
     * @brief spawnWindow_ueParams signal is used to spawn UeParametersForm window
     * @param ueDataName is current double clicked ue data name
     * @param projectName is current project name
     * @param trafficName is current traffic name
     */
    void spawnWindow_ueParams(const QString &ueDataName, const QString& projectName, const QString& trafficName);
    /**
     * @brief spawnWindow_PagingRate signal is used to spawn PagingRateForm window
     * @param projectName is current project name
     */
    void spawnWindow_PagingRate(const QString &projectName);
    /**
     * @brief addUe signal is used to add ue representation to scene
     * @param projectName is current project name
     * @param trafficFileName is current traffic name
     */
    void addUe(const QString &projectName, const QString &trafficFileName);
    /**
     * @brief updateUe signal is used to update ue data in representation
     * @param projectName is current project name
     * @param trafficName is current traffic name
     * @param ueData is data of the added ue
     */
    void updateUe(const QString &projectName, const QString &trafficName, const UEData &ueData);
    /**
     * @brief removeUe signal is used to remove clicked ue from scene
     * @param projectName is current project name
     * @param trafficName is current traffic name
     * @param ueData is data of ue that is being removed
     */
    void removeUe(const QString &projectName, const QString &trafficName, const UEData &ueData);
    /**
     * @brief saveProjectOnMapTrafficClose signal is used to save project on traffic map exit button clicked
     * @param projectName is current project name
     */
    void saveProjectOnMapTrafficClose(const QString &projectName);
    /**
     * @brief setEnabledPagingRate signal is used to set state of PagingRate
     * @param value is flag that represnt state of PagingRate, true = enabled
     */
    void setEnabledPagingRate(bool value);
    /**
     * @brief setEnabledUBSim signal is used to set state of UBsim
     * @param value is flag that represnt state of UBsim, true = enabled
     */
    void setEnabledUBSim(bool value);

    /***********************************************
     *  BINDINGS TO UI BUTTONS                     *
     ***********************************************/
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

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
    void closeEvent(QCloseEvent *event);

private:
    Ui::TrafficMap *    ui;                                         ///< Pointer to GUI Form
    QHBoxLayout *       hBoxLayout;                                 ///< Horizontal layout that contains map view and viewLayout
    QVBoxLayout *       vBoxLayout;                                 ///< Vertical layout that contains widgets
    MapView *           mapView;                                    ///< Map widget

    TrafficFileData*    trafficFileData;                            ///< current traffic file data
    Project             project;                                    ///< current project data

    QVector<UeRepresentation*> doubleClickedUe {nullptr, nullptr};  ///< container of current double-clicked ue
    QVector<UeRepresentation*> clickedUe {nullptr, nullptr};        ///< container of current clicked ue
};

#endif // TRAFFICMAP_H
