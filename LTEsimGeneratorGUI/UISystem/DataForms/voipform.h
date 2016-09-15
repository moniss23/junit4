#ifndef VOIPFORM_H
#define VOIPFORM_H

#include <QDialog>

#include "Data/TrafficSettings/CustomModelsData/voip.h"

namespace Ui {
class VoipForm;
}

/**
 * @brief The VoipForm class is responsible for showing and managing Voip data.
 */
class VoipForm : public QDialog
{
    Q_OBJECT

public:
    explicit VoipForm(QWidget *parent = 0);
    ~VoipForm();

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
     * @param voipIndex is current voip index
     * @param voip is local copy of data
     */
    void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool* qciUsed, const int &voipIndex, const Voip &voip);

signals:
    /**
     * @brief saveVoipData is used to save Voip data in traffic
     * @param projectName is current project name
     * @param trafficName is current traffic name
     * @param CMindex is current custom model index
     * @param voip is data that will be saved
     * @param pingIndex is current ping index
     * @param modification is flag which represents if ping is being added or modified
     */
    void saveVoipData(const QString &projectName, const QString &trafficName, const int &CMindex, const Voip &voip, const int &pingIndex, const bool &modification);

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
    Ui::VoipForm *ui;               ///<GUI form pointer

    Voip voip;                      ///<local copy of data
    QString projectName;            ///<current project name
    QString trafficName;            ///<current traffic name
    int currentCMindex;             ///<current custom model index
    int currentVoipIndex;           ///<current voip index
    bool modification;              ///<flag which represents if ping is being added or modified
    bool *qciUsed;                  ///<pointer to table of qci's states
};

#endif // VOIPFORM_H
