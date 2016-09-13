#ifndef SERVICEREQFORM_H
#define SERVICEREQFORM_H

#include <QDialog>

#include "Data/TrafficSettings/CustomModelsData/servicereq.h"

class QCheckBox;

namespace Ui {
class ServiceReqForm;
}

class ServiceReqForm : public QDialog
{
    Q_OBJECT

public:
    explicit ServiceReqForm(QWidget *parent = 0);
    ~ServiceReqForm();


public slots:
    void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool* qciUsed);

signals:
    void saveServiceReqData(const QString &projectName, const QString &trafficName, const int &CMindex, const ServiceReq &serviceReq);


private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

private:
    void clearUi();
    void setPtrToCheckbox();

private:
    Ui::ServiceReqForm *ui;
    QCheckBox *checkBoxPtr[9];

    QString projectName;
    QString trafficName;
    int currentCMindex;
    bool *qciUsed;
};

#endif // SERVICEREQFORM_H
