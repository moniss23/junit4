#ifndef UEPARAMETERSMANAGER_H
#define UEPARAMETERSMANAGER_H

#include <QWidget>
#include "Data/TrafficSettings/uedata.h"

namespace Ui {
class UeParametersForm;
}
/**
 * @brief The UeParametersForm class is responsible for showing and managing UEData.
 */

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

    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
public slots:
    /**
     * @brief loadAndOpen is used to load data and show window.
     * @param projectName current project name
     * @param trafficName current traffic name
     * @param ueData data that we are working on
     * @param customModelsList list of custom models that are added as items to PS model behaviour
     * @param cellsAndHo list of calls and hanovers that are added as items to Area
     */
    void loadAndOpen(const QString& projectName, const QString& trafficName, const UEData& ueData, const QStringList &customModelsList, const QStringList &cellsAndHo);

signals:
    /**
     * @brief saveUEData signal is used to save UE data in project
     * @param projectName current project name
     * @param trafficName current traffic name
     * @param ueDataName name of data taht is going to be saved
     * @param uedata data that is going to be saved
     */
    void saveUEData(const QString& projectName, const QString& trafficName, const QString& ueDataName, UEData &uedata);

    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/
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

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
    /**
     * @brief refreshUi is used when window needs to refresh state
     */
    void refreshUi();

private:
    Ui::UeParametersForm *ui;               ///<GUI form pointer

    QString projectName;                    ///<current project name
    QString trafficName;                    ///<current traffic name
    UEData ueData;                          ///<local copy of data

    QStringList cellsAndHandovers;          ///<calls and handovers list
    QStringList customModelsList;           ///<custom models list
};

#endif // UEPARAMETERSMANAGER_H
