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
     */
    void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool* qciUsed);

signals:
    /**
     * @brief saveSyncedPingData is used to save syncedPing data in traffic
     * @param projectName is current project name
     * @param trafficName is current traffic name
     * @param CMindex is current custom model index
     * @param syncedPing is data that will be saved
     */
    void saveSyncedPingData(const QString &projectName, const QString &trafficName, const int &CMindex, const SyncedPing &syncedPing);

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
    Ui::SyncedPingForm *ui;             ///<GUI form pointer
    QCheckBox *checkBoxPtr[9];          ///<GUI checkboxes table of pointers

    QString projectName;                ///<current project name
    QString trafficName;                ///<current traffic name
    int currentCMindex;                 ///<current custom model index
    bool *qciUsed;                      ///<pointer to table with qci's states
};

#endif // SYNCEDPINGFORM_H

