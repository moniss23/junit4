#ifndef SYNCEDPINGFORM_H
#define SYNCEDPINGFORM_H

#include <QDialog>

#include "Data/TrafficSettings/CustomModelsData/syncedping.h"

class QCheckBox;

namespace Ui {
class SyncedPingForm;
}

class SyncedPingForm : public QDialog
{
    Q_OBJECT

public:
    explicit SyncedPingForm(QWidget *parent = 0);
    ~SyncedPingForm();

public slots:
    void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool* qciUsed);

signals:
    void saveSyncedPingData(const QString &projectName, const QString &trafficName, const int &CMindex, const SyncedPing &syncedPing);


private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

private:
    void clearUi();
    void setPtrToCheckbox();

private:
    Ui::SyncedPingForm *ui;
    QCheckBox *checkBoxPtr[9];

    QString projectName;
    QString trafficName;
    int currentCMindex;
    bool *qciUsed;
};

#endif // SYNCEDPINGFORM_H

