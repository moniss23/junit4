#ifndef IPEXFORM_H
#define IPEXFORM_H

#include "Data/ProjectSettings/datageneratorsettings.h"

#include <QWidget>

namespace Ui {
class ipexForm;
}

class IpexForm : public QWidget
{
    Q_OBJECT

public:
    explicit IpexForm(QWidget *parent = 0);
    ~IpexForm();

signals:

    void updateDataGeneratorSettings(const DataGeneratorSettings &dataGeneratorSettings, const QString &projectName);

public slots:

    void loadAndSpawn(const DataGeneratorSettings &dataGeneratorSettings, const QString &projectName);

private slots:

    void on_buttonBox_rejected();

    void on_pbReset_clicked();

    void on_buttonBox_accepted();

private:
    void setDefaultParameters();
    void getParameters();

private:
    Ui::ipexForm *ui;
    DataGeneratorSettings dataGeneratorSettings;
    QString projectName;
};

#endif // IPEXFORM_H
