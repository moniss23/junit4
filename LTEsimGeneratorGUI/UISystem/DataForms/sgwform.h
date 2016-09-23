#ifndef SGWFORM_H
#define SGWFORM_H

#include <QWidget>

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


    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
signals:
    /**
     * @brief updateSgw signal used to get information from Window and update it in project
     * @param sgwSettings with Sgw configuration from Ui
     * @param QString with current project name
     */
    void updateSgw(const SgwSettings &sgwSettings,const QString &projectName);

public slots:
    /**
     * @brief loadAndSpawn slot is called by spawnWindow_Mme in MapWindow
     * copy SgwSettings configuration class from project and spawn SGW window
     *
     */
    void loadAndSpawn(const SgwSettings & sgwSettings, const QString &projectName, bool enable);


    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/
private slots:
    void on_buttonBox_accepted();
    void on_pbReset_clicked();
    void on_buttonBox_rejected();


    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
    /**
     * @brief setChanges function to override changes from ui to SgwSettings configuration class
     *
     */
    void setChanges();


    /**
     * @brief updateUi function to restore configuration to state before users changes
     *
     */
    void updateUi();
    void setReadOnly(bool value);

private:
    Ui::SGWForm *ui;            ///< GUI form pointer
    SgwSettings sgwSettings;    ///< SgwSettings class to store SGW configuration
    QString projectName;        ///< Current project name
};

#endif // SGWFORM_H
