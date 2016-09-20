#ifndef UBSIMFORM_H
#define UBSIMFORM_H

#include <QWidget>
#include <QString>

#include "Data/ProjectSettings/ubsimsettings.h"
#include "Data/ProjectSettings/ueparameters.h"

namespace Ui {
class UBsimForm;
}
/**
 *  UBsimForm class is responsible for showing and managing UBSimSettings data.
 */
class UBsimForm : public QWidget
{
    Q_OBJECT

public:
    explicit UBsimForm(QWidget *parent = 0);
    ~UBsimForm();

    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
public slots:
    /**
     * @brief loadAndOpen is used to load ubSimSettings data and show window.
     * @param ubSimSettings is data that we are working on
     * @param projectName is current project name
     */
    void loadAndOpen(const UBSimSettings &ubSimSettings, const UeParameters &UeParameters, const QString &projectName, bool enable);

signals:
    /**
     * @brief updateUBSimSettings signal is used to update ubSimSettings data in project
     * @param ubSimSettings is data that we want to update
     * @param projectName is current project name
     */
    void updateUBSimSettings(const UBSimSettings &ubSimSettings, const QString &projectName);

    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_pbReset_clicked();

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
    void on_ubSimGuiCheckbox_stateChanged(int arg1);
    void disableWindow(bool state);

private:
    /**
     * @brief updateUi is used to set ui fields values from ubSimSettings data
     */
    void updateUi();
    /**
     * @brief getParameters is used to set ubSimSettings data from ui fields
     */
    void getParameters();


    void setReadOnly(bool value);
private:
    Ui::UBsimForm *ui;                      //<<< GUI form pointer
    UBSimSettings ubSimSettings;            //<<< UBSIM Settings
    UeParameters  ueParameters;                 //<<< Ue Settings
    QString projectName;                    //<<< Current project name
};

#endif // UBSIMFORM_H
