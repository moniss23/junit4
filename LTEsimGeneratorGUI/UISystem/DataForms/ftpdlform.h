#ifndef FTPDLFORM_H
#define FTPDLFORM_H

#include <QDialog>

#include "Data/TrafficSettings/CustomModelsData/ftpdl.h"

namespace Ui {
class FtpDlForm;
}

class FtpDlForm : public QDialog
{
    Q_OBJECT

public:
    explicit FtpDlForm(QWidget *parent = 0);
    ~FtpDlForm();

public slots:
    void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool* qciUsed);

signals:
    void saveFtpDlData(const QString &projectName, const QString &trafficName, const int &CMindex, const FtpDl &ftpDl);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

private:
    void clearUi();

private:
    Ui::FtpDlForm *ui;

    FtpDl ftpDl;
    QString projectName;
    QString trafficName;
    int currentCMindex;
    bool *qciUsed;
};

#endif // FTPDLFORM_H
