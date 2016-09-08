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

private:
    Ui::CustomModelsListForm *ui;

    QString projectName;
    QString trafficName;
    int currentCustomModelIndex;
};

#endif // CUSTOMMODELSLISTFORM_H
