#ifndef STREAMDLFORM_H
#define STREAMDLFORM_H

#include <QDialog>

#include "Data/TrafficSettings/CustomModelsData/streamdl.h"

namespace Ui {
class StreamDlForm;
}

/**
 * @brief The StreamDlForm class is responsible for showing and managing streamDl data.
 */
class StreamDlForm : public QDialog
{
    Q_OBJECT

public:
    explicit StreamDlForm(QWidget *parent = 0);
    ~StreamDlForm();

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
    void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool *qciUsed);

signals:
    /**
     * @brief saveStreamDlData is used to save streamDl data in traffic
     * @param projectName is current project name
     * @param trafficName is current traffic name
     * @param CMindex is current custom model index
     * @param streamDl is data that will be saved
     */
    void saveStreamDlData(const QString &projectName, const QString &trafficName, const int &CMindex, const StreamDl &streamDl);

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
    Ui::StreamDlForm *ui;           ///<GUI form pointer

    StreamDl streamDl;
    QString projectName;            ///<current project name
    QString trafficName;            ///<current traffic name
    int currentCMindex;             ///<current custom model index
    bool *qciUsed;                  ///<pointer to table with qci's states
};

#endif // STREAMDLFORM_H
