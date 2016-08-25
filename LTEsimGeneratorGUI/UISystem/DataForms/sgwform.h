#ifndef SGWFORM_H
#define SGWFORM_H

#include <QWidget>
#include <QMessageBox>

#include "Data/ProjectSettings/sgwsettings.h"

namespace Ui {
class SGWForm;
}
/**
 * @brief The SgwForm class is responsible for drawing UI form
 *        for Sgw configuration.
 */

class SgwForm : public QWidget
{
    Q_OBJECT

public:
    explicit SgwForm(QWidget *parent = 0);
    ~SgwForm();
signals:
    /**
     * @brief updateSgw signal used to get information from Window and update it in project
     * @param sgwSettings with Sgw configuration from Ui
     * @param QString with current project name
     */
    void updateSgw(const SgwSettings &sgwSettings,const QString &projectName);



private slots:

    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/

    void on_buttonBox_accepted();
    void on_pbReset_clicked();
    void on_buttonBox_rejected();



public slots:
    /**
     * @brief loadAndSpawn slot is called by spawnSgwWindow in MapWindow
     * copy SgwSettings configuration class from project and spawn SGW window
     *
     */
    void loadAndSpawn(const SgwSettings & sgwSettings, const QString &projectName);
private:
    /**
     * @brief setChanges function to override changes from ui to SgwSettings configuration class
     *
     */



    void setChanges();
    /**
     * @brief setDefaultParameters function to restore configuration to state before users changes
     *
     */

    void setDefaultParameters();

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
    Ui::SGWForm *ui;            //< GUI form pointer
    QMessageBox msg;            //< MsgBox to inform user about window status (config saved etc.)
    SgwSettings sgwSettings;    //< SgwSettings class to store SGW configuration
    QString projectName;        //< Current project name
};

#endif // SGWFORM_H