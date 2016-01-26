#ifndef MAP_TRAFFIC_LARGE_H
#define MAP_TRAFFIC_LARGE_H

#include <QMainWindow>
#include "draguelabel.h"
#include "my_qlabel.h"
#include <QtWidgets>
#include "maps/traffic_map/ue_param/UE_param_form.h"
#include "maps/traffic_map/custom_model/custommodels.h"
#include "maps/parameters_map/maprange.h"
#include <QList>
#include "maps/traffic_map/statistics/statisticsform.h"
#include "maps/object_map/cell.h"
#include "maps/object_map/center.h"
#include "maps/traffic_map/tuningtraffic/tuningtraffic.h"
#include "maps/traffic_map/tuningtraffic/tuningtrafficform.h"


class Custommodels;

namespace Ui {
class Map_traffic_large;
}

class Map_traffic_large : public QMainWindow
{
    Q_OBJECT

public:
    DragUELabel **tab_UE_large;
    int counter_UE_large;
    //QString tab_position_names[12];
    MapRange *mapRange_traffic_large;
    explicit Map_traffic_large(QWidget *parent = 0);
    ~Map_traffic_large();



    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent( QMouseEvent * event ) Q_DECL_OVERRIDE;
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

    Cell* cell63;
    Cell* cell64;
    Cell* cell54;
    Cell* cell53;
    Cell* cell44;
    Cell* cell43;
    Cell* cell34;
    Cell* cell33;
    Cell* cell24;
    Cell* cell23;
    Cell* cell14;
    Cell* cell13;

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

    Center* center63;
    Center* center64;
    Center* center53;
    Center* center54;
    Center* center43;
    Center* center44;
    Center* center33;
    Center* center34;
    Center* center23;
    Center* center24;
    Center* center13;
    Center* center14;

    //from small map
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
    void show_UE_params11();
    void show_UE_params12();
    void show_UE_params13();
    void show_UE_params14();
    void show_UE_params15();
    void show_UE_params16();
    void show_UE_params17();
    void show_UE_params18();
    void show_UE_params19();
    void show_UE_params20();

    //big map



    //Map_scale
    void changeMapRange_x_northBoundMap_large();
    void changeMapRange_y_northBoundMap_large();


private:
    Ui::Map_traffic_large *ui;


    Custommodels** viewCustomModels1;
    int number1;
    my_qlabel* my_label_array[10];
    Tuningtraffic *tuningtraffic;
    Statistics *statistics;
    StatisticsForm viewStatistics;
    TuningTrafficForm viewTuningtraffic;
    QComboBox* combo_box;



    //from small map
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
    Form viewUE11;
    Form viewUE12;
    Form viewUE13;
    Form viewUE14;
    Form viewUE15;
    Form viewUE16;
    Form viewUE17;
    Form viewUE18;
    Form viewUE19;
    Form viewUE20;

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
    Form* pointerUE11;
    Form* pointerUE12;
    Form* pointerUE13;
    Form* pointerUE14;
    Form* pointerUE15;
    Form* pointerUE16;
    Form* pointerUE17;
    Form* pointerUE18;
    Form* pointerUE19;
    Form* pointerUE20;

    Form* pointerempty;








    std::vector<DragUELabel*> vectorUE;
    Custommodels* viewCustomModels;
    QMessageBox msgExit;

    //values use to change values in object if we change scale map
    int counter_cell;
    int counter_center;
    int couter_handover;
    int divisor;

signals:
    void Mouse_Pressed();
    void pressed();
private slots:

    void on_lbl_custom1_clicked();
    void on_lbl_custom2_clicked();
    void on_lbl_custom3_clicked();
    void on_lbl_custom4_clicked();
    void on_lbl_custom5_clicked();
    void on_lbl_custom6_clicked();
    void on_lbl_custom7_clicked();
    void on_lbl_custom8_clicked();
    void on_lbl_custom9_clicked();
    void on_lbl_custom10_clicked();
    void on_bt_statistics_clicked();
    void on_add_button_clicked();
    void on_remove_button_clicked();
    void createCell();
    void on_bt_tuningtraffic_clicked();

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

#endif // MAP_TRAFFIC_LARGE_H
