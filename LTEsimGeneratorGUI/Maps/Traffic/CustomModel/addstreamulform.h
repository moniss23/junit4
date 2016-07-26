#ifndef ADDSTREAMULFORM_H
#define ADDSTREAMULFORM_H

#include <QWidget>
#include "addstreamul.h"
#include <QComboBox>
namespace Ui {
class AddStreamUlForm;
}

class AddStreamUlForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddStreamUlForm(QWidget *parent = 0);
    ~AddStreamUlForm();

    void setParameters(Addstreamul *addstreamul);

    QComboBox *qciAddStreamUlPointer;


    void addToList();

private slots:

    void on_tet_speed_returnPressed();

    void on_tet_duration_returnPressed();

    void on_tet_minThroughput_returnPressed();

    void on_bt_save_clicked();

    void on_bt_cancel_clicked();

private:
    Ui::AddStreamUlForm *ui;
    Addstreamul *addstreamul;

    void SaveAll();
};

#endif // ADDSTREAMULFORM_H
