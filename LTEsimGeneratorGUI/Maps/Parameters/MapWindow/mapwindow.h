#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QMainWindow>
#include <Maps/MapObjects/cell.h>
#include <Maps/MapObjects/center.h>
#include <Maps/MapObjects/handover.h>
#include <Maps/Parameters/SimulatedCoreNetwork/Mme/mme.h>
#include <Maps/Parameters/SimulatedCoreNetwork/Sgw/sgw.h>
#include <QList>
#include <QMessageBox>
#include <Maps/Parameters/SimulatedCoreNetwork/Mme/mmeform.h>
#include <Maps/Parameters/SimulatedCoreNetwork/Sgw/sgwform.h>
#include <Maps/Parameters/SimulatedUe/ubsimform.h>
#include <Maps/Parameters/SimulatedUe/ipexform.h>
#include <Maps/Parameters/UcTool/uctoolform.h>
#include <Maps/Traffic/UeParameters/ue.h>
#include <Maps/Parameters/ChannelModel/channelmodel.h>
#include <Maps/Parameters/ChannelModel/channelmodelform.h>
#include <Maps/Parameters/SimulatedUe/ipgwtg.h>
#include <Maps/Parameters/SimulatedUe/ipexform.h>
#include <Maps/Parameters/MapRange/maprange.h>
#include <Maps/Parameters/MapRange/maprangeform.h>

#include <QStringList>
#include <QString>

namespace Ui {
class MapWindow;
}

class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    void closeEvent(QCloseEvent *event);

    explicit MapWindow(QWidget *parent = 0);
    ~MapWindow();
    QMessageBox k;
    Mme* mme;
    Sgw* sgw;
    Ue* ue;
    ChannelModel *chmod;
    Ipgwtg *ipex;
    MapRange *mapRange;

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

    Handover** tabHandover;
    Handover* handover61_62;
    Handover* handover51_61;
    Handover* handover52_62;
    Handover* handover52_61;
    Handover* handover51_52;
    Handover* handover42_52;
    Handover* handover41_42;
    Handover* handover32_42;
    Handover* handover22_32;
    Handover* handover21_22;
    Handover* handover12_22;
    Handover* handover12_21;
    Handover* handover32_41;
    Handover* handover11_21;
    Handover* handover21_31;
    Handover* handover21_32;
    Handover* handover31_32;
    Handover* handover31_41;
    Handover* handover41_52;
    Handover* handover41_51;
    Handover* handover11_12;

    void changeMapRange_x_northBoundMap();
    void changeMapRange_y_northBoundMap();
    void saveCellsCheckboxes();

    void changeCenterValue_Y(int scale);
    void changeCenterValue_X(int scale);

    void resetFlags();                 //Reset falgs Core Network and Simulate Core
    QList<QString> outputList;
    void showList(QList<QString> list);
private slots:

    void on_Center61_clicked();
    void on_Center62_clicked();
    void on_Center52_clicked();
    void on_Center51_clicked();
    void on_Center42_clicked();
    void on_Center41_clicked();
    void on_Center32_clicked();
    void on_Center31_clicked();
    void on_Center22_clicked();
    void on_Center21_clicked();
    void on_Center12_clicked();
    void on_Center11_clicked();
    void on_Handover61_62_clicked();

    void save_button_clicked();
    void restore_button_clicked();

    void showCellTabWiget();
    void showHandoverTabWiget();
    void showCenterTabWiget();

    void fillParams(Handover *object);
    void fillParams(Center *object);
    void fillParams(Cell *object);
    void saveParams(Cell *object);
    void saveParams(Center *openCenter);
    void saveParams(Handover *openHandover);

    void createCell();
    void createCenter();
    void createHandover();

    QStringList generateParams();
    void on_pbSetCellParams_clicked();

    void on_cell_returnPressed();
    void on_site_returnPressed();
    void on_position_X_returnPressed();
    void on_pci_returnPressed();
    void on_position_Y_returnPressed();
    void on_earfcnDl_returnPressed();
    void on_transmitPower_returnPressed();
    void on_ulNoiseAndInterference_returnPressed();

    void on_cell61_clicked();
    void on_cell62_clicked();
    void on_cell51_clicked();
    void on_cell52_clicked();
    void on_cell41_clicked();
    void on_cell42_clicked();
    void on_cell31_clicked();
    void on_cell32_clicked();
    void on_cell21_clicked();
    void on_cell22_clicked();
    void on_cell11_clicked();
    void on_cell12_clicked();

    void on_pbSetCenterParams_clicked();
    void on_Handover51_61_clicked();
    void on_Handover52_61_clicked();
    void on_Handover52_62_clicked();
    void on_Handover51_52_clicked();
    void on_Handover41_51_clicked();
    void on_Handover41_52_clicked();
    void on_Handover42_52_clicked();
    void on_Handover41_42_clicked();
    void on_Handover31_41_clicked();
    void on_Handover32_41_clicked();
    void on_Handover32_42_clicked();
    void on_Handover31_32_clicked();
    void on_Handover21_31_clicked();
    void on_Handover21_32_clicked();
    void on_Handover22_32_clicked();
    void on_Handover21_22_clicked();
    void on_Handover11_21_clicked();
    void on_Handover12_21_clicked();
    void on_Handover12_22_clicked();
    void on_Handover11_12_clicked();

    void on_southBoundary_returnPressed();
    void on_northBoundary_returnPressed();
    void on_westBoundary_returnPressed();
    void on_eastBoundary_returnPressed();

    void on_soutHandovernoundary_returnPressed();
    void on_northHandovernoundary_returnPressed();
    void on_westHandovernoundary_returnPressed();
    void on_eastHandovernoundary_returnPressed();

    void on_pbsetHandoverParams_clicked();

    void on_checkBoxCell61_clicked();
    void on_checkBoxCell62_clicked();
    void on_checkBoxCell51_clicked();
    void on_checkBoxCell52_clicked();
    void on_checkBoxCell41_clicked();
    void on_checkBoxCell42_clicked();
    void on_checkBoxCell31_clicked();
    void on_checkBoxCell32_clicked();
    void on_checkBoxCell21_clicked();
    void on_checkBoxCell22_clicked();
    void on_checkBoxCell11_clicked();
    void on_checkBoxCell12_clicked();

    void Mouse_Pressed();                       //Add slot to mouse press on label

    void on_pbRestoreCell_clicked();
    void on_pbRestoreHandover_clicked();
    void on_pbRestoreCenter_clicked();

    void on_checkBoxCoreNetwork_clicked();
    void on_checkBoxUE_simulated_clicked();

    void on_lblMME_clicked();
    void on_lblSGW_clicked();
    void on_lblUCtool_clicked();
    void on_lblUBsim_clicked();
    void on_lblChannelModel_clicked();
    void on_lblIpex_clicked();

    void on_axis_y_clicked();
    void on_axis_x_clicked();



private:
    Ui::MapWindow *ui;
    QMessageBox msgBox;
    QList <QString> listErrors;
    QMessageBox msgExit;

    bool validationPosition(QString textForValidation);
    bool validationTransmitPower(QString textForValidation);
    bool validationNameCell(QString textForValidation);
    void showMessageError(QList<QString> listErrors);

    void createCoreNetwork();
    void createUeSimulated();

    void showActiveLine();

    bool wasChangeonCell();
    bool wasChangeonCenter();
    bool wasChangeonHandover();


    MmeForm viewMME;
    SGWForm viewSGW;
    UCtoolForm viewUCtool;
    UBsimForm viewUBsim;
    ChannelModelForm viewCannelModel;
    ipexForm viewIpex;
    MapRangeForm viewMapRange;

    //values use to change values in object if we change scale map
    int counter_cell;
    int counter_center;
    int couter_handover;
    int divisor;

    QString convertBoolToText(bool value);
};

#endif // MAPWINDOW_H
