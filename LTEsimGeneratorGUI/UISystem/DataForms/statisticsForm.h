#ifndef STATISTICS_H
#define STATISTICS_H

#include <QWidget>

#include "Data/TrafficSettings/statisticsData.h"

namespace Ui {
class StatisticsForm;
}
/**
 * @brief The StatisticsForm class is responsible for showing and managing statisticsData.
 */
class StatisticsForm : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsForm(QWidget *parent = 0);
    ~StatisticsForm();

public slots:
    /**
     * @brief loadAndSpawn is used to load data and show window
     * @param projectName is current project name
     * @param trafficFileName is current traffic name
     * @param statisticsData is local copy of data
     */
    void loadAndSpawn(const QString &projectName, const QString &trafficFileName, const StatisticsData& statisticsData);

signals:
    /**
     * @brief updateStatisticsData signal to save local copy of statisticsData
     * @param projectName is current project name
     * @param trafficFileName is current traffic name
     * @param statisticsData is local copy of data
     */
    void updateStatisticsData(const QString &projectName, const QString &trafficFileName, const StatisticsData& statisticsData);

private slots:
    void on_restoreButton_clicked();
    void on_saveButton_clicked();
    void on_pushButton_clicked();

    void on_bearerStatusWordsCheckBox_toggled(bool checked);
    void on_bearerRohcCheckBox_toggled(bool checked);
    void on_bearerErrorCheckBox_toggled(bool checked);
    void on_writePdcpuToFileCheckBox_toggled(bool checked);
    void on_tguStatsCheckBox_toggled(bool checked);
    void on_writeIpexToFileCheckBox_toggled(bool checked);
    void on_writeGeneralStatisticsToFileCheckBox_toggled(bool checked);

private:
    /**
     * @brief refreshUi is used when window needs to refresh state
     */
    void refreshUi();
    /**
     * @brief saveStatisticsData is used to take data from ui and save it in local copy
     */
    void saveStatisticsData();

private:
    Ui::StatisticsForm* ui;             ///<GUI form pointer

    QString projectName;                ///<current project name
    QString trafficFileName;            ///<current traffic name
    StatisticsData statisticsData;      ///<local copy of data
};

#endif // STATISTICS_H
