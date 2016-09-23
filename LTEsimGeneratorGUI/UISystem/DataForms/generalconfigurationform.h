#ifndef GENERALCONFIGURATION_H
#define GENERALCONFIGURATION_H

#include <QWidget>
#include <QString>
#include "Data/ProjectSettings/generalconfigurationparameters.h"

namespace Ui {
class GeneralConfiguration;
}
/**
 * @brief The GeneralConfiguration class is responsible for showing and managing generationconfigurationform data.
 */

class GeneralConfiguration : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralConfiguration(QWidget *parent = 0);
    ~GeneralConfiguration();

    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
public slots:
    /**
     * @brief loadAndOpen is used to load data and show window
     * @param generalConfigurationPrameters is local coppy of data
     * @param projectName is current project name
     * @param enable is used to disable editing in traffic map
     */
    void loadAndOpen(const GeneralConfigurationParameters &generalConfigurationPrameters, const QString &projectName, bool enable);

signals:
    /**
     * @brief updateGeneralConfiguration signal is used to update generalConfigurationPrameters in project
     * @param generalConfigurationParameters data that is going to be updated
     * @param projectName current project name
     */
    void updateGeneralConfiguration(const GeneralConfigurationParameters &generalConfigurationParameters, const QString &projectName);

    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/
private slots:

    void on_restoreButton_clicked();

    void on_okButton_clicked();

    void on_cancelButton_clicked();

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
    /**
     * @brief updateUi is used to set ui fields from GeneralConfigurationParameters data
     */
    void updateUi();
    /**
     * @brief getParameters is used to get GeneralConfigurationParameters data from ui fields.
     */
    void getParameters();
    /**
     * @brief setReadOnly is used to disabled editing
     * @param value is bool value of possibility of editing fields
     */
    void setReadOnly(bool value);
private:
    Ui::GeneralConfiguration *ui;                                   //<<< GUI form pointer
    GeneralConfigurationParameters generalConfigurationParameters;  //<<< Local copy of data
    QString projectName;                                            //<<< Current Project name
};

#endif // GENERALCONFIGURATION_H
