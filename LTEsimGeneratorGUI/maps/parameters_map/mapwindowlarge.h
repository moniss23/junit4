#ifndef MAPWINDOWLARGE_H
#define MAPWINDOWLARGE_H

#include <QWidget>
#include <QListWidget>
#include <QMainWindow>
#include "maps/object_map/cell.h"
#include "maps/object_map/center.h"
#include "maps/object_map/handover.h"
#include "maps/parameters_map/simulated_core_network/mme.h"
#include "maps/parameters_map/simulated_core_network/sgw.h"
#include <QList>
#include <QMessageBox>
#include "maps/parameters_map/simulated_core_network/mmeform.h"
#include "maps/parameters_map/simulated_core_network/sgwform.h"
#include "maps/parameters_map/uctool/uctoolform.h"
#include "maps/parameters_map/simulated_ue/ubsimform.h"
#include "maps/traffic_map/ue_param/ue.h"
#include "maps/parameters_map/channel_model/channelmodel.h"
#include "maps/parameters_map/channel_model/channelmodelform.h"
#include "maps/parameters_map/simulated_ue/ipgwtg.h"
#include "maps/parameters_map/simulated_ue/ipexform.h"
#include "maprange.h"
#include "maprangelargeform.h"
#include <QStringList>
#include <QString>

namespace Ui {
class MapWindowLarge;
}

class MapWindowLarge : public QWidget
{
    Q_OBJECT

public:
    void closeEvent(QCloseEvent *event);
    explicit MapWindowLarge(QWidget *parent = 0);
    ~MapWindowLarge();

    Ui::MapWindowLarge *ui;

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

    Handover* handover63_64;
    Handover* handover53_63;
    Handover* handover54_64;
    Handover* handover54_63;
    Handover* handover53_54;
    Handover* handover44_54;
    Handover* handover43_44;
    Handover* handover34_44;
    Handover* handover24_34;
    Handover* handover23_24;
    Handover* handover14_24;
    Handover* handover14_23;
    Handover* handover34_43;
    Handover* handover13_23;
    Handover* handover23_33;
    Handover* handover23_34;
    Handover* handover33_34;
    Handover* handover33_43;
    Handover* handover43_54;
    Handover* handover43_53;
    Handover* handover13_14;

    Handover* handover12_13;
    Handover* handover13_22;
    Handover* handover22_23;
    Handover* handover22_33;
    Handover* handover32_33;
    Handover* handover33_42;
    Handover* handover42_43;
    Handover* handover42_53;
    Handover* handover52_53;
    Handover* handover53_62;
    Handover* handover62_63;


    void changeMapRange_x_northBoundMap();
    void changeMapRange_y_northBoundMap();

    void changeCenterValue_Y(int scale);
    void changeCenterValue_X(int scale);
    void changeCenterValue_X1(int scale, int one_scale);

    void resetFlags();                 //Reset falgs Core Network and Simulate Core
    QList<QString> outputList;
    void showList(QList<QString> list);

private:


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
    MapRangeLargeForm viewMapRange;

    //values use to change values in object if we change scale map
    int counter_cell;
    int counter_center;
    int couter_handover;
    int divisor;

    QString convertBoolToText(bool value);



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

    void on_Center63_clicked();
    void on_Center64_clicked();
    void on_Center54_clicked();
    void on_Center53_clicked();
    void on_Center44_clicked();
    void on_Center43_clicked();
    void on_Center34_clicked();
    void on_Center33_clicked();
    void on_Center24_clicked();
    void on_Center23_clicked();
    void on_Center14_clicked();
    void on_Center13_clicked();

    void on_Handover61_62_clicked();

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

    void on_cell63_clicked();
    void on_cell64_clicked();
    void on_cell53_clicked();
    void on_cell54_clicked();
    void on_cell43_clicked();
    void on_cell44_clicked();
    void on_cell33_clicked();
    void on_cell34_clicked();
    void on_cell23_clicked();
    void on_cell24_clicked();
    void on_cell13_clicked();
    void on_cell14_clicked();

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

    void on_Handover53_63_clicked();
    void on_Handover54_63_clicked();
    void on_Handover54_64_clicked();
    void on_Handover53_54_clicked();
    void on_Handover43_53_clicked();
    void on_Handover43_54_clicked();
    void on_Handover44_54_clicked();
    void on_Handover43_44_clicked();
    void on_Handover33_43_clicked();
    void on_Handover34_43_clicked();
    void on_Handover34_44_clicked();
    void on_Handover33_34_clicked();
    void on_Handover23_33_clicked();
    void on_Handover23_34_clicked();
    void on_Handover24_34_clicked();
    void on_Handover23_24_clicked();
    void on_Handover13_23_clicked();
    void on_Handover14_23_clicked();
    void on_Handover14_24_clicked();
    void on_Handover13_14_clicked();
    void on_Handover63_64_clicked();

    void on_Handover12_13_clicked();
    void on_Handover13_22_clicked();
    void on_Handover22_23_clicked();
    void on_Handover22_33_clicked();
    void on_Handover32_33_clicked();
    void on_Handover33_42_clicked();
    void on_Handover42_43_clicked();
    void on_Handover42_53_clicked();
    void on_Handover52_53_clicked();
    void on_Handover53_62_clicked();
    void on_Handover62_63_clicked();

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

    void on_checkBoxCell63_clicked();
    void on_checkBoxCell64_clicked();
    void on_checkBoxCell53_clicked();
    void on_checkBoxCell54_clicked();
    void on_checkBoxCell43_clicked();
    void on_checkBoxCell44_clicked();
    void on_checkBoxCell33_clicked();
    void on_checkBoxCell34_clicked();
    void on_checkBoxCell23_clicked();
    void on_checkBoxCell24_clicked();
    void on_checkBoxCell13_clicked();
    void on_checkBoxCell14_clicked();

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
};

#endif // MAPWINDOWLARGE_H
