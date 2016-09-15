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

public slots:
    void loadAndSpawn(const QString &projectName, const QString &trafficFileName, const TuningTrafficData &tuningTrafficData);

private:
    Ui::TuningTrafficForm *ui;
    TuningTrafficData tuningTrafficData;

    bool saveClicked;
    bool cancelClicked;

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
