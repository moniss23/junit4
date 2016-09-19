#ifndef MMEFORM_H
#define MMEFORM_H

#include <QWidget>
#include <QString>

#include "Data/ProjectSettings/mmesettings.h"
#include "Data/ProjectSettings/pagingsettings.h"

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
     * @param mmeSettings with Mme configuration from Ui
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
    void loadAndSpawn(const MmeSettings &mmeSettings, const QString &projectName, bool enable);

private:
    /**
     * @brief setMmeChanges function to override changes from ui to MmeSettings configuration class
     *
     */
    void setMmeChanges();

    /**
     * @brief setPagingChanges function to override changes from ui to PagingSettings configuration class
     *
     */

    void setMmeParameters(MmeSettings mmeSettings);

    /**
     * @brief updateUi function to restore configuration to state before users changes
     *
     */
    void updateUi();
    void setReadOnly(bool value);

private:
    Ui::MmeForm *ui;                //< GUI form pointer
    MmeSettings mmeSettings;        //< MmeSettings class to store Mme configuration
    QString projectName;            //< Current project name
};

#endif // MMEFORM_H
