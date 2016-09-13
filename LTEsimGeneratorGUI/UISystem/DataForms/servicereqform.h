#ifndef SERVICEREQFORM_H
#define SERVICEREQFORM_H

#include <QDialog>

#include "Data/TrafficSettings/CustomModelsData/servicereq.h"

class QCheckBox;

namespace Ui {
class ServiceReqForm;
}

/**
 * @brief The ServiceReqForm class is responsible for showing and managing ServiceReq data.
 */
class ServiceReqForm : public QDialog
{
    Q_OBJECT

public:
    explicit ServiceReqForm(QWidget *parent = 0);
    ~ServiceReqForm();

    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
public slots:
    /**
     * @brief loadAndOpen is used to load data and show window
     * @param projectName is current project name
     * @param trafficName is current traffic name
     * @param CMindex is current custom model index
     * @param qciUsed is table of qci's states
     */
    void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool* qciUsed);

signals:
    /**
     * @brief saveServiceReqData is used to save serviceReq data in traffic
     * @param projectName is current project name
     * @param trafficName is current traffic name
     * @param CMindex is current custom model index
     * @param serviceReq is data that will be saved
     */
    void saveServiceReqData(const QString &projectName, const QString &trafficName, const int &CMindex, const ServiceReq &serviceReq);

    /***********************************************
     *  BINDINGS TO UI BUTTONS                     *
     ***********************************************/
private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
    /**
     * @brief clearUi is used to clear Ui
     */
    void clearUi();
    /**
     * @brief setPtrToCheckbox is used to set checkBoxPtr to point on ui's qci's checkboxes
     */
    void setPtrToCheckbox();

private:
    Ui::ServiceReqForm *ui;         ///<GUI form pointer
    QCheckBox *checkBoxPtr[9];      ///<GUI checkboxes table of pointers

    QString projectName;            ///<current project name
    QString trafficName;            ///<current traffic name
    int currentCMindex;             ///<current custom model index
    bool *qciUsed;                  ///<pointer to table with qci's states
};

#endif // SERVICEREQFORM_H
