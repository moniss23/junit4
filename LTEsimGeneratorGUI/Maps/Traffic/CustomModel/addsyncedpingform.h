#ifndef ADDSYNCEDPINGFORM_H
#define ADDSYNCEDPINGFORM_H

#include <QWidget>
#include "addsyncedping.h"
#include <QComboBox>
namespace Ui {
class AddSyncedPingForm;
}

class AddSyncedPingForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddSyncedPingForm(QWidget *parent = 0);
    ~AddSyncedPingForm();

    void setParameters(Addsyncedping *addsyncedping);
    QComboBox *qciAddSyncedPingQci1;
    QComboBox *qciAddSyncedPingQci2;
    QComboBox *qciAddSyncedPingQci3;
    QComboBox *qciAddSyncedPingQci4;
    QComboBox *qciAddSyncedPingQci5;
    QComboBox *qciAddSyncedPingQci6;
    QComboBox *qciAddSyncedPingQci7;
    QComboBox *qciAddSyncedPingQci8;
    QComboBox *qciAddSyncedPingQci9;


    void addToList();
    void qciAddToList();

private slots:
    void on_tet_timeBetweenTasks_returnPressed();

    void on_tet_numberOfPings_returnPressed();

    void on_tet_interval_returnPressed();

    void on_tet_minReceivedPings_returnPressed();

    void on_bt_save_clicked();

    void on_bt_cancel_clicked();

private:
    Ui::AddSyncedPingForm *ui;
    Addsyncedping *addsyncedping;

    void SaveAll();
};

#endif // ADDSYNCEDPINGFORM_H
