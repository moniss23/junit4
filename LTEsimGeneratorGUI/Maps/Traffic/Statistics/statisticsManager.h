#ifndef STATISTICSFORM_H
#define STATISTICSFORM_H

#include <QWidget>
#include<QCheckBox>
#include <Maps/Traffic/Statistics/statisticsData.h>
namespace Ui {
class StatisticsForm;
}

class StatisticsManager : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsManager(QWidget *parent = 0);
    ~StatisticsManager();

signals:
    void restoreDefaultValues();
    void updateStatisticsData(const StatisticsData& statisticsData);

public slots:
    void showStatisticsWindow(const StatisticsData& statisticsData);

private slots:
    void on_restoreButton_clicked();
    void on_saveButton_clicked();

private:
    Ui::StatisticsForm *ui;
    StatisticsData localStats;
    QVector<QCheckBox*>* checkBoxes;
    bool isUiSetUp;
    bool wereChangesMade;

};

#endif // STATISTICSFORM_H
