#ifndef TIMETRAFFICFORM_H
#define TIMETRAFFICFORM_H

#include <QDialog>
#include "timetraffic.h"

namespace Ui {
class TimeTrafficForm;
}

class TimeTrafficForm : public QDialog
{
    Q_OBJECT

public:
    explicit TimeTrafficForm(QWidget *parent = 0);
    ~TimeTrafficForm();
    void setParameters(TimeTraffic* timeTraffic);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_btn_restore_clicked();
    void on_rd_statsRate1_toggled();
    void on_rd_statsRate2_toggled();
    void on_gb_attdetRate1_toggled();
    void on_gb_attdetRate2_toggled();
    void on_txt_attachRate1_textChanged(QString);
    void on_txt_attachRate2_textChanged(QString);

private:
    Ui::TimeTrafficForm *ui;
    TimeTraffic* timeTraffic;

    int pairs;
    void parametersValidation();
    int convert_tab1_trafficDuration();
    int convert_tab2_trafficDuration();

    void SaveAll();
    QString saveToString();
};

#endif // TIMETRAFFICFORM_H
