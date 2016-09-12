#ifndef VOIPFORM_H
#define VOIPFORM_H

#include <QDialog>

#include "Data/TrafficSettings/CustomModelsData/voip.h"

namespace Ui {
class VoipForm;
}

class VoipForm : public QDialog
{
    Q_OBJECT

public:
    explicit VoipForm(QWidget *parent = 0);
    ~VoipForm();

public slots:
    void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool* qciUsed);

signals:
    void saveVoipData(const QString &projectName, const QString &trafficName, const int &CMindex, const Voip &voip);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

private:
    void clearUi();

private:
    Ui::VoipForm *ui;

    Voip voip;
    QString projectName;
    QString trafficName;
    int currentCMindex;
    bool *qciUsed;
};

#endif // VOIPFORM_H
