#ifndef STATISTICSFORM_H
#define STATISTICSFORM_H

#include <QWidget>
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

    void setCheckBoxActive(bool check);
    bool getCheckBoxActive();
    void setParameters(StatisticsData* statistics, AppSettings* appSettings);

private slots:
    void on_restoreButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::StatisticsForm *ui;
    StatisticsData* statisticsPtr;
    StatisticsData* localStatistics;
    QVector<QCheckBox*>* checkBoxes;
    bool isUiSetUp;
    bool wereChangesMade;

};

#endif // STATISTICSFORM_H
