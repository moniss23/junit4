#ifndef SYNCEDPINGFORM_H
#define SYNCEDPINGFORM_H

#include <QDialog>

#include "Data/TrafficSettings/CustomModelsData/syncedping.h"

class QCheckBox;

namespace Ui {
class SyncedPingForm;
}
/**
 * @brief The SyncedPingForm class is responsible for showing and managing SyncedPing data.
 */
class SyncedPingForm : public QDialog
{
    Q_OBJECT

public:
    explicit SyncedPingForm(QWidget *parent = 0);
    ~SyncedPingForm();

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
     * @param syncedPingIndex is current syncedPing index
     * @param syncedPing is local copy of data
     */
    void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool* qciUsed, const int &syncedPingIndex, const SyncedPing &syncedPing);

signals:
    /**
     * @brief saveSyncedPingData is used to save syncedPing data in traffic
     * @param projectName is current project name
     * @param trafficName is current traffic name
     * @param CMindex is current custom model index
     * @param syncedPing is data that will be saved
     * @param syncedPingIndex is current syncedPing index
     * @param modification is flag that represents if syncedPing is being added or modified
     */
    void saveSyncedPingData(const QString &projectName, const QString &trafficName, const int &CMindex, const SyncedPing &syncedPing, const int &syncedPingIndex, const bool &modification);

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
    Ui::SyncedPingForm *ui;             ///<GUI form pointer
    QCheckBox *checkBoxPtr[9];          ///<table of pointers that point to GUI checkboxes

    SyncedPing syncedPing;              ///<local copy of data
    QString projectName;                ///<current project name
    QString trafficName;                ///<current traffic name
    int currentCMindex;                 ///<current custom model index
    int currentSyncedPingIndex;         ///<current syncedPing index
    bool *qciUsed;                      ///<pointer to table with qci's states
    bool modification;                  ///<flag that represents if syncedPing is being added or modified
};

#endif // SYNCEDPINGFORM_H

