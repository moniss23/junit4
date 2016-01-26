#ifndef ADDFTPDLFORM_H
#define ADDFTPDLFORM_H

#include <QWidget>
#include "addftpdl.h"
#include <QComboBox>

namespace Ui {
class AddFtpDlForm;
}

class AddFtpDlForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddFtpDlForm(QWidget *parent = 0);
    ~AddFtpDlForm();
    void setParameters(Addftpdl *addftpdl);
    QComboBox *qciAddFtpDlPointer;


    void addToList();
    void checkFileSize();

private slots:

    void on_tet_filesize_returnPressed();
    void on_tet_minThroughput_returnPressed();
    void on_bt_save_clicked();
    void on_bt_cancel_clicked();

private:
    Ui::AddFtpDlForm *ui;
    Addftpdl *addftpdl;
    void SaveAll();
};

#endif // ADDFTPDLFORM_H
