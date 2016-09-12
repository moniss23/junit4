#ifndef STREAMDLFORM_H
#define STREAMDLFORM_H

#include <QDialog>

#include "Data/TrafficSettings/CustomModelsData/streamdl.h"

namespace Ui {
class StreamDlForm;
}

class StreamDlForm : public QDialog
{
    Q_OBJECT

public:
    explicit StreamDlForm(QWidget *parent = 0);
    ~StreamDlForm();

public slots:
    void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool *qciUsed);

signals:
    void saveStreamDlData(const QString &projectName, const QString &trafficName, const int &CMindex, const StreamDl &streamDl);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

private:
    void clearUi();

private:
    Ui::StreamDlForm *ui;

    StreamDl streamDl;
    QString projectName;
    QString trafficName;
    int currentCMindex;
    bool *qciUsed;
};

#endif // STREAMDLFORM_H
