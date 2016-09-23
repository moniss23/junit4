#ifndef PINGFORM_H
#define PINGFORM_H

#include <QDialog>

#include "Data/TrafficSettings/CustomModelsData/ping.h"

namespace Ui {
class PingForm;
}
/**
 * @brief The PingForm class is responsible for showing and managing Ping data.
 */
class PingForm : public QDialog
{
    Q_OBJECT

public:
    explicit PingForm(QWidget *parent = 0);
    ~PingForm();


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
     * @param pingIndex is current ping index
     * @param ping is local copy of data
     */
    void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool *qciUsed, const int &pingIndex, const Ping &ping);

signals:
    /**
     * @brief savePingData is used to save Ping data in traffic
     * @param projectName is current project name
     * @param trafficName is current traffic name
     * @param CMindex is current custom model index
     * @param ping is data that will be saved
     * @param pingIndex is current ping index
     * @param modification flag which represents if ping is being added or modified
     */
    void savePingData(const QString &projectName, const QString &trafficName, const int &CMindex, const Ping &ping, const int &pingIndex, const bool &modification);

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

private:
    Ui::PingForm *ui;                   ///<GUI form pointer

    Ping ping;                          ///<local copy of data
    QString projectName;                ///<current project name
    QString trafficName;                ///<current traffic name
    int currentCMindex;                 ///<current custom model index
    int currentPingIndex;               ///<current ping index
    bool *qciUsed;                      ///<pointer to table of qci's states
    bool modification;                  ///<flag which represents if ping is being added or modified
};

#endif // PINGFORM_H
