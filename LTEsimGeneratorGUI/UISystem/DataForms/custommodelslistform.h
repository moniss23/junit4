#ifndef CUSTOMMODELSLISTFORM_H
#define CUSTOMMODELSLISTFORM_H

#include <QMainWindow>

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

signals:
    void updateCustomModel(const QString &projectName, const QString &trafficName, const int &index);
    void loadData(const QString &projectName, const QString &trafficName, const int &index);

private slots:
    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

private:
    Ui::CustomModelsListForm *ui;

    QString projectName;
    QString trafficName;
    int currentCustomModelIndex;
};

#endif // CUSTOMMODELSLISTFORM_H
