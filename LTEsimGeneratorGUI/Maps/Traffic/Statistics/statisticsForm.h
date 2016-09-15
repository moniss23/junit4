#ifndef STATISTICS_H
#define STATISTICS_H

#include <QWidget>
#include <QCheckBox>
#include <QHBoxLayout>
#include <Maps/Traffic/Statistics/statisticsData.h>

namespace Ui {
class StatisticsForm;
}

class StatisticsForm : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsForm(QWidget *parent = 0);
    ~StatisticsForm();

signals:
    /**
     * @brief restoreDefaultVAlues is a signal sent to TrafficWindowManager to update local copy of StatisticsData
     * with original values
     */
    void restoreDefaultValues();
    /**
     * @brief updateStatisticsData is a signal sent to TrafficWindowManager tosave changes made on local copy
     * of StatisticsData
     */
    void updateStatisticsData(const QString &projectName, const QString &trafficFileName, const StatisticsData& statisticsData);

public slots:
    /**
     * @brief showStatisticsWindow is a slot that generates the Statistics.ui for provided StatisticsData dynamicly
     * @param statisticsData is object that provides necesary data to display Statistics.ui properly
     */
    void loadAndSpawn(const QString &projectName, const QString &trafficFileName, const StatisticsData& statisticsData);

private slots:
    /**
     * @brief on_restoreButton_clicked is an automaticly generated slot that executes when restoreButton is clicked
     */
    void on_restoreButton_clicked();
    /**
     * @brief on_saveButton_clicked is an automaticly generated slot that executes when saveButton is clicked
     */
    void on_saveButton_clicked();

    void on_writePdcpuToFileCheckBox_clicked(bool checked);

    void on_bearerErrorCheckBox_clicked(bool checked);

    void on_bearerRohcCheckBox_clicked(bool checked);

    void on_bearerStatusWordsCheckBox_clicked(bool checked);

    void on_tguStatsCheckBox_clicked(bool checked);

    void on_writeIpexToFileCheckBox_clicked(bool checked);

    void on_writeGeneralStatisticsToFileCheckBox_clicked(bool checked);

    void on_pushButton_clicked();

private:
    Ui::StatisticsForm* ui;

    QString projectName;
    QString trafficFileName;
    StatisticsData statisticsData;

private:
    void updateView();
    void saveStatisticsData();
};

#endif // STATISTICS_H
