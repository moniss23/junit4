#ifndef STATISTICSFORM_H
#define STATISTICSFORM_H

#include <QWidget>
#include <maps/traffic_map/statistics/statistics.h>
namespace Ui {
class StatisticsForm;
}

class StatisticsForm : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsForm(QWidget *parent = 0);
    ~StatisticsForm();

    void set_checkboxactive(bool check);
    bool get_checkboxactive();
    void setParameters(Statistics *statistics);
private slots:
    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_5_clicked();

    void on_checkBox_6_clicked();

    void on_checkBox_7_clicked();

    void on_checkBox_8_clicked();

    void on_checkBox_9_clicked();

    void on_checkBox_10_clicked();

    void on_checkBox_11_clicked();

    void on_checkBox_12_clicked();

    void on_checkBox_13_clicked();

    void on_checkBox_14_clicked();

    void on_checkBox_15_clicked();

    void on_checkBox_16_clicked();

    void on_checkBox_17_clicked();

    void on_checkBox_18_clicked();

    void on_checkBox_19_clicked();

    void on_checkBox_20_clicked();

    void on_checkBox_21_clicked();


private:
    Ui::StatisticsForm *ui;
    Statistics *statistics;

};

#endif // STATISTICSFORM_H
