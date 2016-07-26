#ifndef ADDVOIPFORM_H
#define ADDVOIPFORM_H

#include <QWidget>
#include "addvoip.h"
#include <QComboBox>
namespace Ui {
class AddVoipForm;
}

class AddVoipForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddVoipForm(QWidget *parent = 0);
    ~AddVoipForm();

    void setParameters(Addvoip *addvoip);
    QComboBox *qciAddVoipPointer;


    void addToList();

private slots:
    void on_bt_save_clicked();

    void on_bt_cancel_clicked();




    void on_tet_duration_returnPressed();

    void on_tet_activityFactor_returnPressed();

    void on_tet_maxTransferTime_returnPressed();

    void on_tet_minPacketsReceivedInTime_returnPressed();

private:
    Ui::AddVoipForm *ui;
    Addvoip *addvoip;

    void SaveAll();
};

#endif // ADDVOIPFORM_H
