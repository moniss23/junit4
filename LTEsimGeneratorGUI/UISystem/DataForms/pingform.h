#ifndef PINGFORM_H
#define PINGFORM_H

#include <QDialog>
#include "Data/TrafficSettings/CustomModelsData/ping.h"

namespace Ui {
class PingForm;
}

class PingForm : public QDialog
{
    Q_OBJECT

public:
    explicit PingForm(QWidget *parent = 0);
    ~PingForm();

public slots:
    void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool *qciUsed);

signals:
    void savePingData(const QString &projectName, const QString &trafficName, const int &CMindex, const Ping &ping);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::PingForm *ui;

    Ping ping;
    QString projectName;
    QString trafficName;
    int currentCMindex;
    bool *qciUsed;
};

#endif // PINGFORM_H
