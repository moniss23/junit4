#ifndef FTPDLFORM_H
#define FTPDLFORM_H

#include <QDialog>

#include "Data/TrafficSettings/CustomModelsData/ftpdl.h"

namespace Ui {
class FtpDlForm;
}

/**
 * @brief The FtpDlForm class is responsible for showing and managing FtpDl data.
 */
class FtpDlForm : public QDialog
{
    Q_OBJECT

public:
    explicit FtpDlForm(QWidget *parent = 0);
    ~FtpDlForm();

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
     * @brief saveFtpDlData is used to save FtpDl data in traffic
     * @param projectName is current project name
     * @param trafficName is current traffic name
     * @param CMindex is current custom model index
     * @param ftpDl is data that will be saved
     */
    void saveFtpDlData(const QString &projectName, const QString &trafficName, const int &CMindex, const FtpDl &ftpDl);

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
    Ui::FtpDlForm *ui;              ///<GUI form pointer

    FtpDl ftpDl;
    QString projectName;            ///<current project name
    QString trafficName;            ///<current traffic name
    int currentCMindex;             ///<current custom model index
    bool *qciUsed;                  ///<pointer to table with qci's states
};

#endif // FTPDLFORM_H
