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
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_restoreButton_clicked();

private:
    Ui::PingForm *ui;

    QString projectName;
    QString trafficName;
    int currentCMindex;
    bool *qciUsed;

    void clearUi();
};

#endif // PINGFORM_H
