#ifndef GENERALCONFIGURATION_H
#define GENERALCONFIGURATION_H

#include <QWidget>
#include <QString>
#include "Data/ProjectSettings/generalconfigurationparameters.h"

namespace Ui {
class GeneralConfiguration;
}

class GeneralConfiguration : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralConfiguration(QWidget *parent = 0);
    ~GeneralConfiguration();

public slots:
    void loadAndOpen(const GeneralConfigurationParameters &generalConfigurationPrameters, const QString &projectName);

signals:

    void updateGeneralConfiguration(const GeneralConfigurationParameters &generalConfigurationParameters, const QString &projectName);

private slots:

    void on_restoreButton_clicked();

    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    void updateUi();
    void getParameters();

private:
    Ui::GeneralConfiguration *ui;
    GeneralConfigurationParameters generalConfigurationParameters;
    QString projectName;
};

#endif // GENERALCONFIGURATION_H
