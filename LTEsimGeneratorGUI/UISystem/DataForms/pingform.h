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
     */
    void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool *qciUsed, const int &pingIndex, const Ping &ping);

signals:
    /**
     * @brief savePingData is used to save Ping data in traffic
     * @param projectName is current project name
     * @param trafficName is current traffic name
     * @param CMindex is current custom model index
     * @param ping is data that will be saved
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
     * @brief clearUi is used to clear Ui
     */
    void clearUi();
    void setParameters();

private:
    Ui::PingForm *ui;

    Ping ping;
    QString projectName;
    QString trafficName;
    int currentCMindex;
    int currentPingIndex;
    bool *qciUsed;
    bool modification;
};

#endif // PINGFORM_H
