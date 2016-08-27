#ifndef UCTOOLFORM_H
#define UCTOOLFORM_H

#include <QWidget>
#include <QMessageBox>

#include "Data/ProjectSettings/uctoolsettings.h"

namespace Ui {
class UCtoolForm;
}

class UCtoolForm : public QWidget
{
    Q_OBJECT

public:
    explicit UCtoolForm(QWidget *parent = 0);
    ~UCtoolForm();

    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
public slots:
    /**
     * @brief loadAndOpen is used to load data and show window
     * @param ucToolSettings data that will be changed
     * @param projectName name of current project
     */
    void loadAndOpen(const UCToolSettings &ucToolSettings, const QString &projectName);

signals:
    /**
     * @brief updateUCToolSettings signal to update current project ucToolSettings
     * @param ucToolSettings data with new values
     * @param projectName name of project too be updated
     */
    void updateUCToolSettings(const UCToolSettings &ucToolSettings, const QString & projectName);


    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_pbReset_clicked();


    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
    /**
     * @brief setDefaultParameters fill ui fields with values from ucToolSettings object
     */
    void setDefaultParameters();

    /**
     * @brief getParameters takes data from ui and put into ucToolSettings object
     */
    void getParameters();

private:
    Ui::UCtoolForm *ui;                 ///< GUI form pointer
    UCToolSettings ucToolSettings;      ///< Local copy of data
    QString projectName;                ///< Current project name
};

#endif // UCTOOLFORM_H
