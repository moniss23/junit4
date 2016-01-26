#ifndef ADDSERVICEREQFORM_H
#define ADDSERVICEREQFORM_H

#include <QWidget>
#include "addservicereq.h"
#include <QComboBox>
namespace Ui {
class AddServiceReqForm;
}

class AddServiceReqForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddServiceReqForm(QWidget *parent = 0);
    ~AddServiceReqForm();

    void setParameters(Addservicereq *addservicereq);


    QComboBox *qciAddServiceReqQci1;
    QComboBox *qciAddServiceReqQci2;
    QComboBox *qciAddServiceReqQci3;
    QComboBox *qciAddServiceReqQci4;
    QComboBox *qciAddServiceReqQci5;
    QComboBox *qciAddServiceReqQci6;
    QComboBox *qciAddServiceReqQci7;
    QComboBox *qciAddServiceReqQci8;
    QComboBox *qciAddServiceReqQci9;


    void addToList();
    void qciAddToList();

private slots:


    void on_tet_timeToWaitFroAttach_returnPressed();

    void on_tet_intervalBetweenUlData_returnPressed();

    void on_bt_save_clicked();

    void on_pt_cancel_clicked();

private:
    Ui::AddServiceReqForm *ui;
    Addservicereq *addservicereq;

    void SaveAll();
};

#endif // ADDSERVICEREQFORM_H
