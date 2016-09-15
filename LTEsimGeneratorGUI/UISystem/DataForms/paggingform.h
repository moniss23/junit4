#ifndef paggingFORM_H
#define paggingFORM_H

#include <QWidget>
#include "Data/ProjectSettings/paggingsettings.h"
namespace Ui {
class PaggingForm;
}

class PaggingForm : public QWidget
{
    Q_OBJECT

public:
    explicit PaggingForm(QWidget *parent = 0);
    ~PaggingForm();
    void setDefaultParameters();

signals:
    /**
     * @brief updatePagging signal used to get information from Window and update it in project
     * @param paggingSettings with Pagging configuration from Ui
     * @param QString with current project name
     */
    void updatePagging(const PaggingSettings &paggingSettings, const QString &projectName);
public slots:
    void loadAndSpawn(const PaggingSettings &paggingSettings, const QString &projectName, bool enable);

private slots:
    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/

    void on_RestoreButton_clicked();

    void on_OkButton_clicked();

    void on_CancelButton_clicked();

private:
    /**
     * @brief setChanges function to override changes from ui to PaggingSettings configuration class
     *
     */
    void setChanges();
    /**
     * @brief setPaggingParameters function to copy configuration to from paggingSettings gived as argument
     *
     */
    void setPaggingParameters(PaggingSettings paggingSettings);

    void setReadOnly(bool value);

private:
    Ui::PaggingForm *ui;             //< GUI form pointer
    PaggingSettings paggingSettings;  //< PaggingSettings class to store Pagging configuration
    QString projectName;            //< Current project name
};

#endif // paggingFORM_H
