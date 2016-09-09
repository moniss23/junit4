#ifndef CUSTOMMODELSLISTFORM_H
#define CUSTOMMODELSLISTFORM_H

#include <QMainWindow>
#include <QPalette>

#include "Data/TrafficSettings/custommodelsettings.h"

namespace Ui {
class CustomModelsListForm;
}

class CustomModelsListForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomModelsListForm(QWidget *parent = 0);
    ~CustomModelsListForm();

public slots:
    void open(const QString &projectName, const QString &trafficName);
    void loadData();
    void currentCustomModelChanged(const CustomModelSettings &customModelSettings);

signals:
    void updateCustomModel(const QString &projectName, const QString &trafficName, const int &index);
    void loadData(const QString &projectName, const QString &trafficName, const int &index);
    void spawnWindow_Ping(const QString &projectName, const QString &trafficName, const int &CMindex);

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

private:
    void refreshListView();
    void refreshQci();

private:
    Ui::CustomModelsListForm *ui;

    QPalette usedQci;
    QPalette unusedQci;

    QString projectName;
    QString trafficName;
    int currentCustomModelIndex;
    CustomModelSettings customModelSettings;

    const int AmountOfQci = 9;
};

#endif // CUSTOMMODELSLISTFORM_H
