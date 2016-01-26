#ifndef ADDFTPULFORM_H
#define ADDFTPULFORM_H

#include <QWidget>
#include "addftpul.h"
#include <QComboBox>
namespace Ui {
class AddFtpUlForm;
}

class AddFtpUlForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddFtpUlForm(QWidget *parent = 0);
    ~AddFtpUlForm();

    void setParameters(Addftpul *addftpul);
    QComboBox *qciAddFtpUlPointer;


    void addToList();
    void checkFileSize();

 private slots:
     void on_tet_filesize_returnPressed();
     void on_tet_minThroughput_returnPressed();
     void on_bt_save_clicked();
     void on_bt_cancel_clicked();

private:
    Ui::AddFtpUlForm *ui;
    Addftpul *addftpul;
    void SaveAll();
};

#endif // ADDFTPULFORM_H
