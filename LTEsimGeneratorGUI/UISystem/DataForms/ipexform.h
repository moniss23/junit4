#ifndef IPEXFORM_H
#define IPEXFORM_H

#include <QWidget>
#include "Data/ProjectSettings/datageneratorsettings.h"

namespace Ui {
class ipexForm;
}

/**
 * @brief The IpexForm class is responsible for showing and managing IpexSettings data.
 */
class IpexForm : public QWidget
{
    Q_OBJECT

public:
    explicit IpexForm(QWidget *parent = 0);
    ~IpexForm();


    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
signals:
    /**
     * @brief updateDataGeneratorSettings this signal is used to update DataGeneratorSettings in project
     * @param dataGeneratorSettings data with new values
     * @param projectName name of project to be updated
     */
    void updateDataGeneratorSettings(const DataGeneratorSettings &dataGeneratorSettings, const QString &projectName);

public slots:
    /**
     * @brief loadAndSpawn used to load data and show window
     * @param dataGeneratorSettings data that will be changed
     * @param projectName name of current project
     */
    void loadAndSpawn(const DataGeneratorSettings &dataGeneratorSettings, const QString &projectName, bool enable);


    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/
private slots:
    void on_pbReset_clicked();
    void on_okButton_clicked();
    void on_cancelButton_clicked();

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
    void on_RunIpexEnvoironementChbox_toggled(bool checked);

private:
    /**
     * @brief UpdateUi takes data from dataGeneratorSettings and update ui
     */
    void updateUi();

    /**
     * @brief getParameters takes data from ui and put it into dataGeneratorSettings object
     */
    void getParameters();

    void setReadOnly(bool value);
    void enableWindow(bool value);
private:
    Ui::ipexForm *ui;                               ///<GUI form pointer
    DataGeneratorSettings dataGeneratorSettings;    ///<Local copy of data
    QString projectName;                            ///<CurrentProject name
};

#endif // IPEXFORM_H
