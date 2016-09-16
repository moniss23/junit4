#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <QDialog>

#include "Data/TrafficSettings/timeData.h"

namespace Ui {
class TimeForm;
}

class TimeForm : public QDialog
{
    Q_OBJECT

public:
    explicit TimeForm(QWidget *parent = 0);
    ~TimeForm();

public slots:
    void loadAndOpen(const QString& projectName, const QString& trafficName, const TimeData& timeData);

signals:
    void saveTimeData(const QString& projectName, const QString& trafficName, const TimeData& timeData);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_btn_restore_clicked();
    void on_gb_attdetRate1_toggled();
    void on_gb_attdetRate2_toggled();
    void on_txt_attachRate1_textChanged(QString);
    void on_txt_attachRate2_textChanged(QString);
    void on_tab1_printStatisticsWithRate_toggled(bool checked);
    void on_tab2_statisticsWithRate_toggled(bool checked);

private:
    void refreshUi();
    void setParametersValidation();
    void getParameters();

private:
    Ui::TimeForm *ui;

    TimeData timeData;
    QString projectName;
    QString trafficName;
};

#endif // TIMEMANAGER_H
