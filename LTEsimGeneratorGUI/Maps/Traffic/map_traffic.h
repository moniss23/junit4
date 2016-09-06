#ifndef MAP_TRAFFIC_H
#define MAP_TRAFFIC_H

#include "Data/datasystem.h"
#include "Data/Objects/cell.h"
#include "Data/ProjectSettings/maprange.h"
#include "Maps/Traffic/CustomModel/customModel.h"
#include "Maps/Traffic/MapComponents/draguelabel.h"
#include "Maps/Traffic/Statistics/statisticsManager.h"
#include "Maps/Traffic/Tuning/tuningTrafficManager.h"
#include "Maps/Traffic/Time/timeManager.h"
#include "my_qlabel.h"

#include <QComboBox>
#include <QMainWindow>
#include <QObject>
#include <QMessageBox>

class Custommodels;
class customModel;

namespace Ui {
class Map_traffic;
}


class Map_traffic : public QMainWindow
{
    Q_OBJECT

public:

    explicit Map_traffic(QWidget *parent = 0);
    DragUELabel **tab_UE;
    DragUELabel *last_element_traffic;
    int counter_UE;
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

private:
    Ui::Map_traffic *ui;
    customModel** viewcustomModel;

    QMap<QString, QString>* parseCM(QStringList customModelListToParse);
    void parseSavedList();
    void getIndex();

    my_qlabel* my_label_array[10];
    TuningTrafficData *tuningtraffic;
    TimeData* timetraffic;
    StatisticsData *statistics;
    StatisticsManager viewStatistics;
    TuningTrafficManager viewTuningtraffic;
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

    QVector<DragUELabel*> vectorUE;
    customModel* viewcustomModel1;
    QMessageBox msgExit;

    int tmp_counter_UE;

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

};

#endif // MAP_TRAFFIC_H
