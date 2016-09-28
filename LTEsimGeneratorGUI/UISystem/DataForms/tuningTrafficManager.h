#ifndef TUNINGTRAFFICMANAGER_H
#define TUNINGTRAFFICMANAGER_H

#include <QWidget>
#include "Data/TrafficSettings/tuningTrafficData.h"
#include "Data/TrafficSettings/uedata.h"
#include "UISystem/DataForms/UE_param_form.h"

namespace Ui {
class TuningTrafficForm;
}

/**
 * @brief The TuningTrafficManager class is responsible for showing and managing TuningTrafficData
 */
class TuningTrafficManager : public QWidget
{
    Q_OBJECT

public:
    explicit TuningTrafficManager(QWidget *parent = 0);
    ~TuningTrafficManager();

    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
public slots:
    /**
     * @brief loadAndSpawn method is used to load TuningTrafficData to a window and spawning it.
     * @param projectName name of current project
     * @param trafficFileName name of  current TrafficFile
     * @param comboBoxesLists currently chosen CP/PS/Mobility parameters
     * @param tuningTrafficData data to copy and work on
     */
    void loadAndSpawn(const QString &projectName, const QString &trafficFileName, const std::tuple<QStringList,QStringList,QStringList> &comboBoxesLists, const TuningTrafficData tuningTrafficData);
    /**
     * @brief restoreTuningTrafficData is used to restore changes in local copy of TuningTrafficData to previous values
     * @param tuningTrafficData is unchanged data
     */
    void restoreTuningTrafficData(const TuningTrafficData &tuningTrafficData);

signals:
    /**
     * @brief saveTuningTrafficData is signal sent to overwrite TuningTrafficData in certain TrafficFile
     * @param projectName name of current project
     * @param trafficFileName name of current TrafficFile
     * @param tuningTrafficData data to be saved
     */
    void saveTuningTrafficData(const QString &projectName, const QString &trafficFileName, const TuningTrafficData &tuningTrafficData);
    /**
     * @brief restoreTuningTrafficData is signal sent when local data is going to be reset to previous state
     * @param projectName name of current project
     * @param trafficFileName name of current TrafficFile
     */
    void restoreTuningTrafficData(const QString &projectName, const QString &trafficFileName);

    /***********************************************
     *  BINDINGS TO UI BUTTONS                     *
     ***********************************************/
private slots:
    void on_csSaveButton_clicked();

    void on_psSaveButton_clicked();

    void on_mobilitySaveButton_clicked();

    void on_saveButton_clicked();

    void on_cancelButton_clicked();

    void on_csComboBox_currentIndexChanged(int index);

    void on_psComboBox_currentIndexChanged(int index);

    void on_mobilityComboBox_currentIndexChanged(int index);

    void on_restoreButton_clicked();

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
    /**
     * @brief fillComboBoxes method fills comboBoxes with parameters assigned to UEs
     * @param comboBoxesLists are StringLists with chosen parameters names
     */
    void fillComboBoxes(const std::tuple<QStringList,QStringList,QStringList> &comboBoxesLists);

private:
    Ui::TuningTrafficForm *ui;                   ///< GUI form pointer
    TuningTrafficData tuningTrafficData;         ///< TuningTraffic data

    QString projectName;                         ///< Current project name
    QString trafficFileName;                     ///< Current trafic file name
};

#endif // TUNINGTRAFFICMANAGER_H
