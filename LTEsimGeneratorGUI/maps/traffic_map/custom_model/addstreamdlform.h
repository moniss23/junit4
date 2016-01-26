#ifndef ADDSTREAMDLFORM_H
#define ADDSTREAMDLFORM_H

#include <QWidget>
#include "addstreamdl.h"
#include <QComboBox>
namespace Ui {
class AddStreamDlForm;
}

class AddStreamDlForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddStreamDlForm(QWidget *parent = 0);
    ~AddStreamDlForm();

    void setParameters(Addstreamdl *addstreamdl);

    QComboBox *qciAddStreamDlPointer;


    void addToList();
private slots:

    void on_tet_speed_returnPressed();

    void on_tet_duration_returnPressed();

    void on_tet_minThroughput_returnPressed();

    void on_bt_save_clicked();

    void on_bt_cancel_clicked();

private:
    Ui::AddStreamDlForm *ui;
    Addstreamdl *addstreamdl;

    void SaveAll();
};

#endif // ADDSTREAMDLFORM_H
