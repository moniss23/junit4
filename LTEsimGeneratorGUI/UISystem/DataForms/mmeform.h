#ifndef MMEFORM_H
#define MMEFORM_H

#include <QWidget>
#include <QMessageBox>
#include <QString>

#include "Data/ProjectSettings/mmesettings.h"

namespace Ui {
class MmeForm;
}
/*
* @brief The MmeForm class is responsible for drawing UI form
*        for Mme and Paging configuration.
*/

class MmeForm : public QWidget
{
    Q_OBJECT

public:
    explicit MmeForm(QWidget *parent = 0);
    ~MmeForm();

signals:

    /**
     * @brief updateMme signal used to get information from Window and update it in project
     * @param mmeSettings with MMe configuration from Ui
     * @param QString with current project name
     */
    void updateMme(const MmeSettings &mmeSettings, const QString &projectName);

private slots:

    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_pbReset_clicked();

public slots:
    /**
     * @brief loadAndSpawn slot is called by spawnWindow_Mme in MapWindow
     * copy MmeSettings configuration class from project and spawn MME window
     *
     */
    void loadAndSpawn(const MmeSettings &mmeSettings, const QString &projectName);

private:
    /**
     * @brief setChanges function to override changes from ui to MmeSettings configuration class
     *
     */
    void setChanges();
    /**
     * @brief setDefaultParameters function to copy configuration to from mmeSettings gived as argument
     *
     */
    void setParameters(MmeSettings mmeSettings);
    /**
     * @brief setDefaultParameters function to restore configuration to state before users changes
     *
     */
    void setDefaultParameters();

private:
    Ui::MmeForm *ui;                //< GUI form pointer
    MmeSettings mmeSettings;        //< MmeSettings class to store Mme configuration
    QMessageBox msg;                //< MsgBox to inform user about window status (config saved etc.)
    QString projectName;            //< Current project name
};

#endif // MMEFORM_H
