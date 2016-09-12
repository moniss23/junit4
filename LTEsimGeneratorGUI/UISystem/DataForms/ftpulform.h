#ifndef FTPULFORM_H
#define FTPULFORM_H

#include <QDialog>

namespace Ui {
class FtpUlForm;
}

class FtpUlForm : public QDialog
{
    Q_OBJECT

public:
    explicit FtpUlForm(QWidget *parent = 0);
    ~FtpUlForm();

private:
    Ui::FtpUlForm *ui;
};

#endif // FTPULFORM_H
