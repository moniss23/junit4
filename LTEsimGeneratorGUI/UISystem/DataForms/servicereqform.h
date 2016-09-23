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
     * @param serviceReqIndex is current servceReq index
     * @param serviceReq is local copy of data
     */
    void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool* qciUsed, const int &serviceReqIndex, const ServiceReq &serviceReq);

signals:
    /**
     * @brief saveServiceReqData is used to save serviceReq data in traffic
     * @param projectName is current project name
     * @param trafficName is current traffic name
     * @param CMindex is current custom model index
     * @param serviceReq is data that will be saved
     * @param serviceReqIndex is current serviceReq index
     * @param modification is flag that represents if serviceReq is being added or modified
     */
    void saveServiceReqData(const QString &projectName, const QString &trafficName, const int &CMindex, const ServiceReq &serviceReq, const int &serviceReqIndex, const bool &modification);

    /***********************************************
     *  BINDINGS TO UI BUTTONS                     *
     ***********************************************/
private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_restoreButton_clicked();

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/

private:
    /**
     * @brief refreshUi is used when window needs to refresh state
     */
    void refreshUi();
    /**
     * @brief setPtrToCheckbox is used to set checkBoxPtr to point on ui's qci's checkboxes
     */
    void setPtrToCheckbox();

private:
    Ui::ServiceReqForm *ui;         ///<GUI form pointer
    QCheckBox *checkBoxPtr[9];      ///<table of pointers that point to GUI checkboxes

    ServiceReq serviceReq;          ///<local copy of data
    QString projectName;            ///<current project name
    QString trafficName;            ///<current traffic name
    int currentCMindex;             ///<current custom model index
    int currentServiceReqIndex;     ///<current serviceReq index
    bool *qciUsed;                  ///<pointer to table with qci's states
    bool modification;              ///<flag that represents if syncedPing is being added or modified
};

#endif // SERVICEREQFORM_H
