#ifndef ADDPINGFORM_H
#define ADDPINGFORM_H

#include <QWidget>
#include "addping.h"
#include <QComboBox>

namespace Ui {
class AddPingForm;
}

class AddPingForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddPingForm(QWidget *parent = 0);
    ~AddPingForm();

    void setParameters(Addping *addping);

    QComboBox *qciAddpingPointer;


    void addToPingList();

private slots:


    void on_tet_numberOfPagins_returnPressed();

    void on_tet_interval_returnPressed();

    void on_tet_minRecievedPings_returnPressed();

    void on_bt_save_clicked();

    void on_bt_cancel_clicked();

private:
    Ui::AddPingForm *ui;
    Addping *addping;

    void SaveAll();
};

#endif // ADDPINGFORM_H
