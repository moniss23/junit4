#ifndef CUSTOMMODELSLISTFORM_H
#define CUSTOMMODELSLISTFORM_H

#include <QMainWindow>
#include <QPalette>

#include "Data/TrafficSettings/custommodelsettings.h"

class QPushButton;

namespace Ui {
class CustomModelsListForm;
}
/**
 * @brief The CustomModelsListForm class is responsible for showing and managing CustomModelSettings data.
 */
class CustomModelsListForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomModelsListForm(QWidget *parent = 0);
    ~CustomModelsListForm();

    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
public slots:
    /**
     * @brief open slot is used to set local projectName,trafficName, cmUsed instances and show window.
     * @param projectName is current project's name instance
     * @param trafficName is current traffic's name instance
     * @param cmUsed is current traffic's table of used custom models
     */
    void open(const QString &projectName, const QString &trafficName, bool *cmUsed);
    /**
     * @brief currentCustomModelChanged is used to set local Custom model instance
     * @param customModelSettings is current custom model data
     * @param cmUsed is current traffic's table of used custom models
     */
    void currentCustomModelChanged(const CustomModelSettings &customModelSettings, bool * cmUsed);

signals:
    /**
     * @brief loadData signal is used to update current local Custom model
     * @param projectName current project's name
     * @param trafficName current traffic's name
     * @param index is index of custom model we are working on
     */
    void loadData(const QString &projectName, const QString &trafficName, const int &index);
    /**
     * @brief spawnWindow_Ping signal is used to spawn window PingForm
     * @param projectName current project's name
     * @param trafficName current traffic's name
     * @param CMindex is index of current custom model
     */
    void spawnWindow_Ping(const QString &projectName, const QString &trafficName, const int &CMindex);
    /**
     * @brief spawnWindow_Voip signal is used to spawn window VoipForm
     * @param projectName current project's name
     * @param trafficName current traffic's name
     * @param CMindex is index of current custom model
     */
    void spawnWindow_Voip(const QString &projectName, const QString &trafficName, const int &CMindex);
    /**
     * @brief spawnWindow_FtpDl signal is used to spawn window FtpDlForm
     * @param projectName current project's name
     * @param trafficName current traffic's name
     * @param CMindex is index of current custom model
     */
    void spawnWindow_FtpDl(const QString &projectName, const QString &trafficName, const int &CMindex);
    /**
     * @brief spawnWindow_FtpUl signal is used to spawn window FtpUlForm
     * @param projectName current project's name
     * @param trafficName current traffic's name
     * @param CMindex is index of current custom model
     */
    void spawnWindow_FtpUl(const QString &projectName, const QString &trafficName, const int &CMindex);
    /**
     * @brief spawnWindow_StreamDl signal is used to spawn window StreamDl
     * @param projectName current project's name
     * @param trafficName current traffic's name
     * @param CMindex is index of current custom model
     */
    void spawnWindow_StreamDl(const QString &projectName, const QString &trafficName, const int &CMindex);
    /**
     * @brief spawnWindow_StreamUl signal is used to spawn window StreamUl
     * @param projectName current project's name
     * @param trafficName current traffic's name
     * @param CMindex is index of current custom model
     */
    void spawnWindow_StreamUl(const QString &projectName, const QString &trafficName, const int &CMindex);
    /**
     * @brief spawnWindow_SyncedPing signal is used to spawn window SyncedPing
     * @param projectName current project's name
     * @param trafficName current traffic's name
     * @param CMindex is index of current custom model
     */
    void spawnWindow_SyncedPing(const QString &projectName, const QString &trafficName, const int &CMindex);
    /**
     * @brief spawnWindow_ServiceReq signal is used to spawn window SyncedPing
     * @param projectName current project's name
     * @param trafficName current traffic's name
     * @param CMindex is index of current custom model
     */
    void spawnWindow_ServiceReq(const QString &projectName, const QString &trafficName, const int &CMindex);

    void deleteCustomModelItem(const QString &projectName, const QString &trafficName, const QString &item, const int &index, const int &CMindex);

    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/
private slots:
    void on_CM1Button_clicked();
    void on_CM2Button_clicked();
    void on_CM3Button_clicked();
    void on_CM4Button_clicked();
    void on_CM5Button_clicked();
    void on_CM6Button_clicked();
    void on_CM7Button_clicked();
    void on_CM8Button_clicked();
    void on_CM9Button_clicked();
    void on_CM10Button_clicked();
    void on_AddPingButton_clicked();
    void on_AddVoipButton_clicked();
    void on_AddFtpDlButton_clicked();
    void on_AddFtpUlButton_clicked();
    void on_AddStreamDlButton_clicked();
    void on_AddStreamUlButton_clicked();
    void on_AddSyncedPingButton_clicked();
    void on_AddServiceReqButton_clicked();
    void on_exitButton_clicked();
    void on_deleteButton_clicked();
    void on_listWidget_doubleClicked(const QModelIndex &index);

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
    /**
     * @brief refreshListView is used to refresh added items on the list
     */
    void refreshListView();
    /**
     * @brief refreshQci is used to refresh used qcies
     */
    void refreshQci();
    /**
     * @brief setAutoFillButtonsBG is used to set autoFillBackground on every custom model's button
     */
    void setAutoFillButtonsBG();
    /**
     * @brief setButtonsPointers is used to fill cmButtonsPtr table of pointers with buttons pointers
     */
    void setButtonsPointers();
    /**
     * @brief refreshCmButtonsColors is used to set custom models' buttons coloring
     * @param index is index of last clicked button
     */
    void refreshCmButtonsColors(const int &index);

private:
    Ui::CustomModelsListForm *ui;                   ///<<< GUI Form pointer

    QPalette usedQci;                               ///< Palette for used qci
    QPalette unusedQci;                             ///< Palette for unused qci

    QPushButton *cmButtonsPtr[10];                  ///< table of pointers which points to ui->buttons

    QString projectName;                            ///< current project's name
    QString trafficName;                            ///< current traffic's name
    int currentCustomModelIndex;                    ///< current custom model index
    CustomModelSettings customModelSettings;        ///< local copy of custom model data
    bool * cmUsed;                                  ///< pointer to table of used custom models
};

#endif // CUSTOMMODELSLISTFORM_H
