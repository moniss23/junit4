#ifndef STATISTICS_H
#define STATISTICS_H

#include <QWidget>
#include<QCheckBox>
#include <Maps/Traffic/Statistics/statisticsData.h>
namespace Ui {
class Statistics;
}

class StatisticsManager : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsManager(QWidget *parent = 0);
    ~StatisticsManager();

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
    void updateStatisticsData(const StatisticsData& statisticsData);

public slots:
    /**
     * @brief showStatisticsWindow is a slot that generates the Statistics.ui for provided StatisticsData dynamicly
     * @param statisticsData is object that provides necesary data to display Statistics.ui properly
     */
    void showStatisticsWindow(const StatisticsData& statisticsData);

private slots:
    /**
     * @brief on_restoreButton_clicked is an automaticly generated slot that executes when restoreButton is clicked
     */
    void on_restoreButton_clicked();
    /**
     * @brief on_saveButton_clicked is an automaticly generated slot that executes when saveButton is clicked
     */
    void on_saveButton_clicked();

private:
    Ui::Statistics *ui;
    StatisticsData localStats;
    QVector<QCheckBox*>* checkBoxes;
    bool isUiSetUp;
    bool wereChangesMade;

};

#endif // STATISTICS_H
