#ifndef FTPDLFORM_H
#define FTPDLFORM_H

#include <QDialog>

namespace Ui {
class FtpDlForm;
}

class FtpDlForm : public QDialog
{
    Q_OBJECT

public:
    explicit FtpDlForm(QWidget *parent = 0);
    ~FtpDlForm();

private:
    Ui::FtpDlForm *ui;
};

#endif // FTPDLFORM_H
