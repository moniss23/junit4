#ifndef UEPARAMETERSMANAGER_H
#define UEPARAMETERSMANAGER_H

#include <QWidget>
#include "Data/TrafficSettings/uedata.h"

namespace Ui {
class UeParametersForm;
}

class UeParametersForm : public QWidget
{
    Q_OBJECT

public:
    explicit UeParametersForm(QWidget *parent = 0);
    ~UeParametersForm();

    const static QStringList CSSTRINGLIST;
    const static QStringList PSSTRINGLIST;
    const static QStringList MOBILITYSTRINGLIST;
    const static QStringList UESTRINGLIST;

public slots:
    void loadAndOpen(const QString& projectName, const QString& trafficName, const UEData& ueData, const QStringList &customModelsList, const QStringList &cellsAndHo);

signals:
    void saveUEData(const QString& projectName, const QString& trafficName, const QString& ueDataName, const UEData& uedata);

private slots:
    void on_pairNameLineEdit_editingFinished();

    void on_amountOfPairsSpinBox_editingFinished();

    void on_frstMobilityModelComboBox_currentIndexChanged(int index);

    void on_scndMobilityModelComboBox_currentIndexChanged(int index);

    void on_frstCsModelComboBox_currentIndexChanged(int index);

    void on_scndCsModelComboBox_currentIndexChanged(int index);

    void on_frstPsModelComboBox_currentIndexChanged(int index);

    void on_scndPsModelComboBox_currentIndexChanged(int index);

    void on_frstUeTypeComboBox_currentIndexChanged(int index);

    void on_scndUeTypeComboBox_currentIndexChanged(int index);

    void on_restoreChangesButton_clicked();

    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    void refreshUi();

private:
    Ui::UeParametersForm *ui;

    QString projectName;
    QString trafficName;
    UEData ueData;

    QStringList cellsAndHandovers;
    QStringList customModelsList;
};

#endif // UEPARAMETERSMANAGER_H
