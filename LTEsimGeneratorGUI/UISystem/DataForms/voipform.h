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
     */
    void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool* qciUsed);

signals:
    /**
     * @brief saveVoipData is used to save Voip data in traffic
     * @param projectName is current project name
     * @param trafficName is current traffic name
     * @param CMindex is current custom model index
     * @param voip is data that will be saved
     */
    void saveVoipData(const QString &projectName, const QString &trafficName, const int &CMindex, const Voip &voip);

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

private:
    Ui::VoipForm *ui;               ///<GUI form pointer

    Voip voip;
    QString projectName;            ///<current project name
    QString trafficName;            ///<current traffic name
    int currentCMindex;             ///<current custom model index
    bool *qciUsed;                  ///<pointer to table with qci's states
};

#endif // VOIPFORM_H
