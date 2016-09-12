#ifndef FTPULFORM_H
#define FTPULFORM_H

#include <QDialog>
#include "Data/TrafficSettings/CustomModelsData/ftpul.h"

namespace Ui {
class FtpUlForm;
}

class FtpUlForm : public QDialog
{
    Q_OBJECT

public:
    explicit FtpUlForm(QWidget *parent = 0);
    ~FtpUlForm();

public slots:
    void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool* qciUsed);

signals:
    void saveFtpUlData(const QString &projectName, const QString &trafficName, const int &CMindex, const FtpUl &ftpUl);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

private:
    void clearUi();

private:
    Ui::FtpUlForm *ui;

    FtpUl ftpUl;
    QString projectName;
    QString trafficName;
    int currentCMindex;
    bool *qciUsed;
};

#endif // FTPULFORM_H
