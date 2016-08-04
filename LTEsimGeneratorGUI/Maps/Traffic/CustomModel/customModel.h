#ifndef customModel_H
#define customModel_H

#include <QMainWindow>

namespace Ui {
class newCustomModel;
}

class customModel : public QMainWindow
{
    Q_OBJECT

public:
    explicit customModel(QWidget *parent = 0);
    ~customModel();

    void set_custom_name(QString name);

private slots:
    void on_checkBoxPing_clicked();

    void on_checkBoxVoip_clicked();

    void on_checkBoxFTPDl_clicked();

    void on_checkBoxFTPUl_clicked();

    void on_checkBoxStreamDl_clicked();

    void on_checkBoxStreamUl_clicked();

    void on_checkBoxSyncedPing_clicked();

    void on_checkBoxServiceReq_clicked();

private:
    Ui::newCustomModel *ui;
    QString name;
};

#endif // customModel_H
