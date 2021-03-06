#ifndef CHANNELMODELFORM_H
#define CHANNELMODELFORM_H

#include <QWidget>
#include <QMessageBox>

#include "Data/ProjectSettings/channelmodelsettings.h"

namespace Ui {
class ChannelModelForm;
}
/**
 * @brief The ChannelModelForm classis responsible for showing and managing ChannelModelSettings data.
 */

class ChannelModelForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelModelForm(QWidget *parent = 0);
    ~ChannelModelForm();

    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
public slots:
    /**
     * @brief loadAndOpen is used to load data and show window.
     * @param channelModelSettings data that we are working on
     * @param projectName current project name
     */
    void loadAndOpen(const ChannelModelSettings &channelModelSettings, const QString &projectName, bool enable);

signals:
    /**
     * @brief updateChannelModelSettings signal is used to update channelModelSettings in project
     * @param channelModelSettings data that is going to be updated
     * @param projectName current project name
     */
    void updateChannelModelSettings(const ChannelModelSettings &channelModelSettings, const QString &projectName);

    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/
private slots:
    void on_restoreDefaults_clicked();
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_checkBox_toggled(bool checked);

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/

private:
    /**
     * @brief updateUi is used to set ui fields from channelModelSettings data
     */
    void updateUi();
    /**
     * @brief getParameters is used to get channelModelSettings data from ui fields.
     */
    void getParameters();

    void setReadOnly(bool value);
    void enableWindow(bool value);
private:
    Ui::ChannelModelForm *ui;                   ///< GUI form pointer
    ChannelModelSettings channelModelSettings;  ///< Local copy of data
    QString projectName;                        ///< Current Project name
};

#endif // CHANNELMODELFORM_H
