#ifndef FTPULFORM_H
#define FTPULFORM_H

#include <QDialog>

#include "Data/TrafficSettings/CustomModelsData/ftpul.h"

namespace Ui {
class FtpUlForm;
}

/**
 * @brief The FtpUlForm class is responsible for showing and managing FtpUl data.
 */
class FtpUlForm : public QDialog
{
    Q_OBJECT

public:
    explicit FtpUlForm(QWidget *parent = 0);
    ~FtpUlForm();

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
     * @brief saveFtpUlData is used to save Ping data in traffic
     * @param projectName is current project name
     * @param trafficName is current traffic name
     * @param CMindex is current custom model index
     * @param ftpUl is data that will be saved
     */
    void saveFtpUlData(const QString &projectName, const QString &trafficName, const int &CMindex, const FtpUl &ftpUl);

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
     * @brief clearUi is used to clear Ui.
     */
    void clearUi();

private:
    Ui::FtpUlForm *ui;              ///<GUI form pointer

    FtpUl ftpUl;
    QString projectName;            ///<current project name
    QString trafficName;            ///<current traffic name
    int currentCMindex;             ///<current custom model index
    bool *qciUsed;                  ///<pointer to table with qci's states
};

#endif // FTPULFORM_H
