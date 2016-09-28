#ifndef STREAMULFORM_H
#define STREAMULFORM_H

#include <QDialog>

#include "Data/TrafficSettings/CustomModelsData/streamul.h"

namespace Ui {
class StreamUlForm;
}

/**
 * @brief The StreamUlForm class is responsible for showing and managing streamUl data.
 */
class StreamUlForm : public QDialog
{
    Q_OBJECT

public:
    explicit StreamUlForm(QWidget *parent = 0);
    ~StreamUlForm();

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
     * @param streamUlIndex is current streamUl index
     * @param streamUl is local copy of data
     */
     void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool *qciUsed, const int &streamUlIndex, const StreamUl &streamUl);

signals:
    /**
     * @brief saveStreamUlData is used to save streamUl data in traffic
     * @param projectName is current project name
     * @param trafficName is current traffic name
     * @param CMindex is current custom model index
     * @param streamUl is data that will be saved
     * @param streamUlIndex is current streamUl index
     * @param modification represnts if streamUl is being added or modified
     */
    void saveStreamUlData(const QString &projectName, const QString &trafficName, const int &CMindex, const StreamUl &streamUl, const int &streamUlIndex, const bool &modification);

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
    Ui::StreamUlForm *ui;           ///<GUI form pointer

    StreamUl streamUl;              ///<local copy of data
    QString projectName;            ///<current project name
    QString trafficName;            ///<current traffic name
    int currentCMindex;             ///<current custom model index
    int currentStreamUlIndex;       ///<current streamUl index
    bool *qciUsed;                  ///<pointer to table with qci's states
    bool modification;              ///<flag that represents if streamUl is being added or modified
};

#endif // STREAMULFORM_H
