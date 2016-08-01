#ifndef MAP_TRAFFIC_H
#define MAP_TRAFFIC_H

#include <QMainWindow>
#include <QComboBox>
#include <QHash>
#include <QtWidgets>
#include <Maps/Traffic/UeParameters/UE_param_form.h>
#include <Maps/Traffic/CustomModel/custommodels.h>
#include <Maps/Parameters/MapRange/maprange.h>
#include <QList>
#include <Maps/MapObjects/cell.h>
#include <Maps/MapObjects/center.h>
#include <Maps/Traffic/Statistics/statisticsManager.h>
#include <Maps/Traffic/Tuning/tuningtrafficform.h>
#include <Maps/Traffic/MapComponents/draguelabel.h>
#include <Maps/Traffic/Time/timeData.h>
#include <Maps/Traffic/Time/timeManager.h>
#include <my_qlabel.h>

class Custommodels;

namespace Ui {
class Map_traffic;
}


class Map_traffic : public QMainWindow
{
    Q_OBJECT

public:

    explicit Map_traffic(AppSettings* appSettings, QWidget *parent = 0);
    DragUELabel **tab_UE;
    DragUELabel *last_element_traffic;
    int counter_UE;
    //QString tab_position_names[12];
    MapRange *mapRange_traffic;
    QComboBox *combo_pointer;

    void parseListToAddPingEtcCM1();
    void parseListToAddPingEtcCM2();
    void parseListToAddPingEtcCM3();
    void parseListToAddPingEtcCM4();
    void parseListToAddPingEtcCM5();
    void parseListToAddPingEtcCM6();
    void parseListToAddPingEtcCM7();
    void parseListToAddPingEtcCM8();
    void parseListToAddPingEtcCM9();
    void parseListToAddPingEtcCM10();


    ~Map_traffic();

    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent * event ) Q_DECL_OVERRIDE;

    void closeEvent(QCloseEvent *event);

    Cell* *tabCell;
    Cell* cell61;
    Cell* cell62;
    Cell* cell52;
    Cell* cell51;
    Cell* cell42;
    Cell* cell41;
    Cell* cell32;
    Cell* cell31;
    Cell* cell22;
    Cell* cell21;
    Cell* cell12;
    Cell* cell11;

    Center** tabCenter;
    Center* center61;
    Center* center62;
    Center* center51;
    Center* center52;
    Center* center41;
    Center* center42;
    Center* center31;
    Center* center32;
    Center* center21;
    Center* center22;
    Center* center11;
    Center* center12;


    void show_UE_empty();
    void show_UE_params1();
    void show_UE_params2();
    void show_UE_params3();
    void show_UE_params4();
    void show_UE_params5();
    void show_UE_params6();
    void show_UE_params7();
    void show_UE_params8();
    void show_UE_params9();
    void show_UE_params10();
//    void show_UE_params11_12();
//    void show_UE_params11_21();
//    void show_UE_params12_21();
//    void show_UE_params12_22();
//    void show_UE_params21_22();
//    void show_UE_params21_31();
//    void show_UE_params21_32();
//    void show_UE_params22_32();
//    void show_UE_params31_32();
//    void show_UE_params31_41();
//    void show_UE_params32_41();
//    void show_UE_params32_42();
//    void show_UE_params41_42();
//    void show_UE_params41_51();
//    void show_UE_params41_52();
//    void show_UE_params42_52();
//    void show_UE_params51_52();
//    void show_UE_params51_61();
//    void show_UE_params52_61();
//    void show_UE_params52_62();
//    void show_UE_params61_62();


    //Map_scale
    void changeMapRange_x_northBoundMap();
    void changeMapRange_y_northBoundMap();

private:
    Ui::Map_traffic *ui;

    AppSettings* appSettings;

    Custommodels** viewCustomModels1;
    int number1;

    QMap<QString, QString>* parseCM(QStringList customModelListToParse);
    void parseSavedList();
    void getIndex();

    my_qlabel* my_label_array[10];
    Tuningtraffic *tuningtraffic;
    TimeData* timetraffic;
    StatisticsData *statistics;
    StatisticsManager viewStatistics;
    TuningTrafficForm viewTuningtraffic;
    TimeManager viewTimeTraffic;

    QComboBox* combo_box;
    Form **tableview;

    Form viewUE1;
    Form viewUE2;
    Form viewUE3;
    Form viewUE4;
    Form viewUE5;
    Form viewUE6;
    Form viewUE7;
    Form viewUE8;
    Form viewUE9;
    Form viewUE10;

    Form viewempty;



    Form* pointerUE1;
    Form* pointerUE2;
    Form* pointerUE3;
    Form* pointerUE4;
    Form* pointerUE5;
    Form* pointerUE6;
    Form* pointerUE7;
    Form* pointerUE8;
    Form* pointerUE9;
    Form* pointerUE10;

    Form* pointerempty;

    std::vector<DragUELabel*> vectorUE;
    Custommodels* viewCustomModels;
    QMessageBox msgExit;

    //values use to change values in object if we change scale map
    int counter_cell;
    int counter_center;
    int couter_handover;
    int tmp_counter_UE;
    int divisor;

    bool toBool(QString value);

signals:
    void Mouse_Pressed();
    void pressed();
private slots:

    void on_bt_statistics_clicked();
    void on_bt_tuningtraffic_clicked();
    void on_bt_time_clicked();
    void on_add_button_clicked();
    void on_remove_button_clicked();
    void createCell();
    void on_CM1_clicked();
    void on_CM2_clicked();
    void on_CM3_clicked();
    void on_CM4_clicked();
    void on_CM5_clicked();
    void on_CM6_clicked();
    void on_CM7_clicked();
    void on_CM8_clicked();
    void on_CM9_clicked();
    void on_CM10_clicked();

};

#endif // MAP_TRAFFIC_H
