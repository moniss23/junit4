#ifndef SERVICEREQFORM_H
#define SERVICEREQFORM_H

#include <QDialog>

namespace Ui {
class ServiceReqForm;
}

class ServiceReqForm : public QDialog
{
    Q_OBJECT

public:
    explicit ServiceReqForm(QWidget *parent = 0);
    ~ServiceReqForm();

private:
    Ui::ServiceReqForm *ui;
};

#endif // SERVICEREQFORM_H
