#ifndef TUNINGTRAFFICMANAGER_H
#define TUNINGTRAFFICMANAGER_H

#include <QWidget>
#include "tuningTrafficData.h"
#include <UISystem/DataForms/UE_param_form.h>

namespace Ui {
class TuningTrafficForm;
}

class TuningTrafficManager : public QWidget
{
    Q_OBJECT

public:
    explicit TuningTrafficManager(QWidget *parent = 0);
    ~TuningTrafficManager();
    void setUEGroup(Form* form);

signals:
    void saveTuningTrafficData(const QString &projectName, const QString &trafficFileName, const TuningTrafficData &tuningTrafficData);
    void restoreTuningTrafficData(const QString &projectName, const QString &trafficFileName); //something wierd is happening and it does not work

public slots:
    void loadAndSpawn(const QString &projectName, const QString &trafficFileName, const TuningTrafficData tuningTrafficData);
    void restoreTuningTrafficData(const TuningTrafficData &tuningTrafficData); //something wierd is happening and it does not work

private slots:
    void on_csSaveButton_clicked();

    void on_psSaveButton_clicked();

    void on_mobilitySaveButton_clicked();

    void on_saveButton_clicked();

    void on_cancelButton_clicked();

    void on_csComboBox_currentIndexChanged(int index);

    void on_psComboBox_currentIndexChanged(int index);

    void on_mobilityComboBox_currentIndexChanged(int index);

    void on_restoreButton_clicked();

private:
    Ui::TuningTrafficForm *ui;
    TuningTrafficData tuningTrafficData;

    QString projectName;
    QString trafficFileName;

    struct TuningTrafficUEModel
    {
        QString cs;
        QString ps;
        QString area;
    } UEGroup;
};

#endif // TUNINGTRAFFICMANAGER_H
