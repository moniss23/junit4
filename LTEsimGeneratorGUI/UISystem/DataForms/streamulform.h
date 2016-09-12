#ifndef STREAMULFORM_H
#define STREAMULFORM_H

#include <QDialog>

#include "Data/TrafficSettings/CustomModelsData/streamul.h"

namespace Ui {
class StreamUlForm;
}

class StreamUlForm : public QDialog
{
    Q_OBJECT

public:
    explicit StreamUlForm(QWidget *parent = 0);
    ~StreamUlForm();

public slots:
    void loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool *qciUsed);

signals:
    void saveStreamUlData(const QString &projectName, const QString &trafficName, const int &CMindex, const StreamUl &streamUl);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

private:
    void clearUi();

private:
    Ui::StreamUlForm *ui;

    StreamUl streamUl;
    QString projectName;
    QString trafficName;
    int currentCMindex;
    bool *qciUsed;
};

#endif // STREAMULFORM_H
