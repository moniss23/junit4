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
    bool getCancelClicked() const;
    void setCancelClicked(bool value);

private slots:
    void on_txt_attachRate1_textChanged(QString value);
    void on_txt_attachRate2_textChanged(QString value);
    void on_buttonBox_accepted();
    void on_btn_restore_clicked();
    void on_buttonBox_rejected();
    void on_rd_statsRate1_toggled();
    void on_rd_statsRate2_toggled();
    void on_gb_attdetRate1_toggled();
    void on_gb_attdetRate2_toggled();

private:
    Ui::TimeTrafficForm *ui;
    TimeTraffic* timeTraffic;


    int pairs;
    bool cancelClicked;
    bool saveClicked;
    void parametersValidation();
    int convert_tab1_trafficDuration();
    int convert_tab2_trafficDuration();
    void saveTemporarySettings();
    void readTemporarySettings();
    void SaveAll();
    QString saveToString();
};

#endif // TIMETRAFFICFORM_H
