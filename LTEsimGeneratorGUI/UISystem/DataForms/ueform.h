#ifndef UEFORM_H
#define UEFORM_H

#include <QWidget>
#include "Data/ProjectSettings/ueparameters.h"

namespace Ui {
class UeForm;
}

/**
 * @brief The UeForm class represents a window that provides UE Components settings
 */
class UeForm : public QWidget
{
    Q_OBJECT

public:
    explicit UeForm(QWidget *parent = 0);
    ~UeForm();
public slots:
    void loadAndOpen(const UeParameters &ueParameters, const QString &projectName, bool enable);

signals:
    /**
     * @brief updateUeSettings signal is used to update ueSettings data in project
     * @param ueSettings is data that we want to update
     * @param projectName is current project name
     */
    void updateUeSettings(const UeParameters &ueParameters, const QString &projectName);

    void enableUBSim(bool state);
    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/
private slots:

    void on_restoreDefault_clicked();

    void on_OkButton_clicked();

    void on_CancelButton_clicked();

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/

    void on_checkBox_stateChanged(int arg1);

private:
    /**
     * @brief updateUi is used to set ui fields values from UeSettings data
     */
    void updateUi();
    /**
     * @brief getParameters is used to set ueSettings data from ui fields
     */
    void getParameters();
    void setReadOnly(bool enable);
    void enableWindow(bool start);
private:
    Ui::UeForm *ui;                             ///< GUI form pointer
    UeParameters  ueParameters;                 ///< Ue Settings
    QString projectName;                        ///< Current project name
};

#endif // UEFORM_H
