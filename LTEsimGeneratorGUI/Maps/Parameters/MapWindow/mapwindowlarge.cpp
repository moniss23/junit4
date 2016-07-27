#include "mapwindowlarge.h"
#include "ui_mapwindowlarge.h"
#include <ManagementWindow/ParametersWindow/parameterswindow.h>
#include <Maps/MapObjects/cell.h>
#include <QString>
#include <QCloseEvent>
#include <ManagementWindow/Encryption/encryption.h>

extern ParametersWindow* p;
extern QString * tabChangedParams;

//extern const unsigned int cellCount=12;
//extern const unsigned int handoverCount=21;
//extern const unsigned int centerCount=12;

//extern cellName cellNames[cellCount];
//extern centerName centerNames[centerCount];
//extern handoverName handoverNames[handoverCount];

extern QString parametersFileContent;
extern QStringList parametersFileContentList;
extern QString savedParametersFileContent;
extern QStringList savedParametersFileContentList;
extern std::vector<QString> trafficFilesContent;
extern std::vector<QString> savedTrafficFilesContent;
extern bool paramFileChanged;
extern bool paramFileModified;
extern std::vector<bool> trafficFilesChanged;
extern std::vector<bool> trafficFilesModified;

extern bool enteringMapView;
extern bool changesPresent;

extern Cell *openCell;
extern Center *openCenter;
extern Handover *openHandover;

MapWindowLarge::MapWindowLarge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapWindowLarge)
{
    ui->setupUi(this);
    ui->tabWidget->hide();
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(2);

    qDebug()<<"----------------   checkpoint 0";

    createCenter();

    qDebug()<<"----------------   checkpoint 0.1";

    createCell();

    qDebug()<<"----------------   checkpoint 1";

    createHandover();
    createCoreNetwork();
    createUeSimulated();
    chmod = new ChannelModel();
    ipex = new Ipgwtg();
    mapRange = new MapRange();

    qDebug()<<"----------------   checkpoint 2";

    qDebug ()<<"mapawielosc" + QString::number(mapRange->getEastBoundMap());

    connect(ui->axis, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_Pressed()));
    connect(ui->cell62, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell62_clicked()));
    connect(ui->cell61, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell61_clicked()));
    connect(ui->cell52, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell52_clicked()));
    connect(ui->cell51, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell51_clicked()));
    connect(ui->cell42, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell42_clicked()));
    connect(ui->cell41, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell41_clicked()));
    connect(ui->cell32, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell32_clicked()));
    connect(ui->cell31, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell31_clicked()));
    connect(ui->cell22, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell22_clicked()));
    connect(ui->cell21, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell21_clicked()));
    connect(ui->cell12, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell12_clicked()));
    connect(ui->cell11, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell11_clicked()));

    connect(ui->cell64, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell64_clicked()));
    connect(ui->cell63, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell63_clicked()));
    connect(ui->cell54, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell54_clicked()));
    connect(ui->cell53, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell53_clicked()));
    connect(ui->cell44, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell44_clicked()));
    connect(ui->cell43, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell43_clicked()));
    connect(ui->cell34, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell34_clicked()));
    connect(ui->cell33, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell33_clicked()));
    connect(ui->cell24, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell24_clicked()));
    connect(ui->cell23, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell23_clicked()));
    connect(ui->cell14, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell14_clicked()));
    connect(ui->cell13, SIGNAL(Mouse_Pressed()), this, SLOT(on_cell13_clicked()));

    connect(ui->lblMME1, SIGNAL(Mouse_Pressed()), this, SLOT(on_lblMME_clicked()));
    connect(ui->lblSGW1, SIGNAL(Mouse_Pressed()), this, SLOT(on_lblSGW_clicked()));
    connect(ui->lblUCTool, SIGNAL(Mouse_Pressed()), this, SLOT(on_lblUCtool_clicked()));
    connect(ui->lblUBsim, SIGNAL(Mouse_Pressed()), this, SLOT(on_lblUBsim_clicked()));
    connect(ui->lblL1, SIGNAL(Mouse_Pressed()),this, SLOT(on_lblChannelModel_clicked()));
    connect(ui->lblIPEX, SIGNAL(Mouse_Pressed()), this, SLOT(on_lblIpex_clicked()));
    connect(ui->axis_x, SIGNAL(Mouse_Pressed()), this, SLOT(on_axis_x_clicked()));
    connect(ui->axis_y, SIGNAL(Mouse_Pressed()), this, SLOT(on_axis_y_clicked()));

    qDebug()<<"----------------   checkpoint 3";

    qDebug()<< "Nazwa celli: " + cell61->getCell() + " Nowa nazwa: " + cell61->getCell_new_name();
    changeMapRange_x_northBoundMap();
    changeMapRange_y_northBoundMap();
}

MapWindowLarge::~MapWindowLarge()
{
    delete ui;
}

void MapWindowLarge::createHandover(){
    tabHandover = new Handover*[53];
//    qDebug () << "\n\nRozmiar tablicy: " + QString::number(sizeof(**tabHandover));


     //new handovers
      handover12_13 = new Handover ("Handover12_13");
      handover13_22 = new Handover ("Handover13_22");
      handover22_23 = new Handover ("Handover22_23");
      handover22_33 = new Handover ("Handover22_33");
      handover32_33 = new Handover ("Handover32_33");
      handover33_42 = new Handover ("Handover33_42");
      handover42_43 = new Handover ("Handover42_43");
      handover42_53 = new Handover ("Handover42_53");
      handover52_53 = new Handover ("Handover52_53");
      handover53_62 = new Handover ("Handover53_62");
      handover62_63 = new Handover ("Handover62_63");
    //end new handovers


    handover11_12 = new Handover ("Handover11_12");
    handover61_62 = new Handover ("Handover61_62");
    handover51_61 = new Handover ("Handover51_61");
    handover52_62 = new Handover ("Handover52_62");
    handover52_61 = new Handover ("Handover52_61");
    handover51_52 = new Handover ("Handover51_52");
    handover42_52 = new Handover ("Handover42_52");
    handover41_42 = new Handover ("Handover41_42");
    handover32_42 = new Handover ("Handover32_42");
    handover22_32 = new Handover ("Handover22_32");
    handover21_22 = new Handover ("Handover21_22");
    handover12_22 = new Handover ("Handover12_22");
    handover12_21 = new Handover ("Handover12_21");
    handover32_41 = new Handover ("Handover32_41");
    handover11_21 = new Handover ("Handover11_21");
    handover21_31 = new Handover ("Handover21_31");
    handover21_32 = new Handover ("Handover21_32");
    handover31_32 = new Handover ("Handover31_32");
    handover31_41 = new Handover ("Handover31_41");
    handover41_52 = new Handover ("Handover41_52");
    handover41_51 = new Handover ("Handover41_51");

    handover13_14 = new Handover ("Handover13_14");
    handover63_64 = new Handover ("Handover63_64");
    handover53_63 = new Handover ("Handover53_63");
    handover54_64 = new Handover ("Handover54_64");
    handover54_63 = new Handover ("Handover54_63");
    handover53_54 = new Handover ("Handover53_54");
    handover44_54 = new Handover ("Handover44_54");
    handover43_44 = new Handover ("Handover43_44");
    handover34_44 = new Handover ("Handover34_44");
    handover24_34 = new Handover ("Handover24_34");
    handover23_24 = new Handover ("Handover23_24");
    handover14_24 = new Handover ("Handover14_24");
    handover14_23 = new Handover ("Handover14_23");
    handover34_43 = new Handover ("Handover34_43");
    handover13_23 = new Handover ("Handover13_23");
    handover23_33 = new Handover ("Handover23_33");
    handover23_34 = new Handover ("Handover23_34");
    handover33_34 = new Handover ("Handover33_34");
    handover33_43 = new Handover ("Handover33_43");
    handover43_54 = new Handover ("Handover43_54");
    handover43_53 = new Handover ("Handover43_53");
    //handover63

    tabHandover[0] = handover11_12;
    tabHandover[1] = handover11_21;
    tabHandover[2] = handover12_21;
    tabHandover[3] = handover12_22;
    tabHandover[4] = handover21_22;
    tabHandover[5] = handover21_31;
    tabHandover[6] = handover21_32;
    tabHandover[7] = handover22_32;
    tabHandover[8] = handover31_32;
    tabHandover[9] = handover31_41;
    tabHandover[10] = handover32_41;
    tabHandover[11] = handover32_42;
    tabHandover[12] = handover41_42;
    tabHandover[13] = handover41_51;
    tabHandover[14] = handover41_52;
    tabHandover[15] = handover42_52;
    tabHandover[16] = handover51_52;
    tabHandover[17] = handover51_61;
    tabHandover[18] = handover52_61;
    tabHandover[19] = handover52_62;
    tabHandover[20] = handover61_62;

    tabHandover[21] = handover13_14;
    tabHandover[22] = handover13_23;
    tabHandover[23] = handover14_23;
    tabHandover[24] = handover14_24;
    tabHandover[25] = handover23_24;
    tabHandover[26] = handover23_33;
    tabHandover[27] = handover23_34;
    tabHandover[28] = handover24_34;
    tabHandover[29] = handover33_34;
    tabHandover[30] = handover33_43;
    tabHandover[31] = handover34_43;
    tabHandover[32] = handover34_44;
    tabHandover[33] = handover43_44;
    tabHandover[34] = handover43_53;
    tabHandover[35] = handover43_54;
    tabHandover[36] = handover44_54;
    tabHandover[37] = handover53_54;
    tabHandover[38] = handover53_63;
    tabHandover[39] = handover54_63;
    tabHandover[40] = handover54_64;
    tabHandover[41] = handover63_64;

    tabHandover[42] = handover12_13;
    tabHandover[43] = handover13_22;
    tabHandover[44] = handover22_23;
    tabHandover[45] = handover22_33;
    tabHandover[46] = handover32_33;
    tabHandover[47] = handover33_42;
    tabHandover[48] = handover42_43;
    tabHandover[49] = handover42_53;
    tabHandover[50] = handover52_53;
    tabHandover[51] = handover53_62;
    tabHandover[52] = handover62_63;



//    for(unsigned int i=0; i<handoverCount; i++){
//        handoverNames[i].name=tabHandover[i]->getArea();
//        handoverNames[i].obj=tabHandover[i];
//    }

}

void MapWindowLarge::createCenter(){
    tabCenter = new Center*[24];

    qDebug()<<"-=-=-=-=-=-=-=-= checkpoint 0";

    center61 = new Center ("Center61");
    center62 = new Center ("Center62");
    center51 = new Center ("Center51");
    center52 = new Center ("Center52");
    center41 = new Center ("Center41");
    center42 = new Center ("Center42");
    center31 = new Center ("Center31");
    center32 = new Center ("Center32");
    center21 = new Center ("Center21");
    center22 = new Center ("Center22");
    center11 = new Center ("Center11");
    center12 = new Center ("Center12");

    qDebug()<<"-=-=-=-=-=-=-=-= checkpoint 1";

    center63 = new Center ("Center63");
    center64 = new Center ("Center64");
    center53 = new Center ("Center53");
    center54 = new Center ("Center54");
    center43 = new Center ("Center43");
    center44 = new Center ("Center44");
    center33 = new Center ("Center33");
    center34 = new Center ("Center34");
    center23 = new Center ("Center23");
    center24 = new Center ("Center24");
    center13 = new Center ("Center13");
    center14 = new Center ("Center14");


    qDebug()<<"-=-=-=-=-=-=-=-= checkpoint 2";

    tabCenter[0] = center11;
    tabCenter[1] = center12;
    tabCenter[2] = center21;
    tabCenter[3] = center22;
    tabCenter[4] = center31;
    tabCenter[5] = center32;
    tabCenter[6] = center41;
    tabCenter[7] = center42;
    tabCenter[8] = center51;
    tabCenter[9] = center52;
    tabCenter[10] = center61;
    tabCenter[11] = center62;


    qDebug()<<"-=-=-=-=-=-=-=-= checkpoint 3";

    tabCenter[12] = center13;
    tabCenter[13] = center14;
    tabCenter[14] = center23;
    tabCenter[15] = center24;
    tabCenter[16] = center33;
    tabCenter[17] = center34;
    tabCenter[18] = center43;
    tabCenter[19] = center44;
    tabCenter[20] = center53;
    tabCenter[21] = center54;
    tabCenter[22] = center63;
    tabCenter[23] = center64;


//    for(unsigned int i=0; i<centerCount; i++){
//        centerNames[i].name=tabCenter[i]->getArea();
//        centerNames[i].obj=tabCenter[i];
//    }
}

void MapWindowLarge::createCell(){
    cell61 = new Cell ("cell61");
    cell61->chBox = ui->checkBoxCell61;
    cell61->center = center61;
    if(!cell61->getCell_new_name().isEmpty())
        cell61->chBox->setText(cell61->getCell_new_name());
    cell62 = new Cell ("cell62");
    cell62->chBox = ui->checkBoxCell62;
    cell62->center = center62;
    if(!cell62->getCell_new_name().isEmpty())
        cell62->chBox->setText(cell62->getCell_new_name());
    cell52 = new Cell ("cell52");
    cell52->chBox = ui->checkBoxCell52;
    cell52->center = center52;
    if(!cell52->getCell_new_name().isEmpty())
        cell52->chBox->setText(cell52->getCell_new_name());
    cell51 = new Cell ("cell51");
    cell51->chBox = ui->checkBoxCell51;
    cell51->center = center51;
    if(!cell51->getCell_new_name().isEmpty())
        cell51->chBox->setText(cell51->getCell_new_name());
    cell42 = new Cell ("cell42");
    cell42->chBox = ui->checkBoxCell42;
    cell42->center = center42;
    if(!cell42->getCell_new_name().isEmpty())
        cell42->chBox->setText(cell42->getCell_new_name());
    cell41 = new Cell ("cell41");
    cell41->chBox = ui->checkBoxCell41;
    cell41->center = center41;
    if(!cell41->getCell_new_name().isEmpty())
        cell41->chBox->setText(cell41->getCell_new_name());
    cell32 = new Cell ("cell32");
    cell32->chBox = ui->checkBoxCell32;
    cell32->center = center32;
    if(!cell32->getCell_new_name().isEmpty())
        cell32->chBox->setText(cell32->getCell_new_name());
    cell31 = new Cell ("cell31");
    cell31->chBox = ui->checkBoxCell31;
    cell31->center = center31;
    if(!cell31->getCell_new_name().isEmpty())
        cell31->chBox->setText(cell31->getCell_new_name());
    cell22 = new Cell ("cell22");
    cell22->chBox = ui->checkBoxCell22;
    cell22->center = center22;
    if(!cell22->getCell_new_name().isEmpty())
        cell22->chBox->setText(cell22->getCell_new_name());
    cell21 = new Cell ("cell21");
    cell21->chBox = ui->checkBoxCell21;
    cell21->center = center21;
    if(!cell21->getCell_new_name().isEmpty())
        cell21->chBox->setText(cell21->getCell_new_name());
    cell12 = new Cell ("cell12");
    cell12->chBox = ui->checkBoxCell12;
    cell12->center = center12;
    if(!cell12->getCell_new_name().isEmpty())
        cell12->chBox->setText(cell12->getCell_new_name());
    cell11 = new Cell ("cell11");
    cell11->chBox = ui->checkBoxCell11;
    cell11->center = center11;
    if(!cell11->getCell_new_name().isEmpty())
        cell11->chBox->setText(cell11->getCell_new_name());

    cell63 = new Cell ("cell63");
    cell63->chBox = ui->checkBoxCell63;
    cell63->center = center63;
    if(!cell63->getCell_new_name().isEmpty())
        cell63->chBox->setText(cell63->getCell_new_name());
    cell64 = new Cell ("cell64");
    cell64->chBox = ui->checkBoxCell64;
    cell64->center = center64;
    if(!cell64->getCell_new_name().isEmpty())
        cell64->chBox->setText(cell64->getCell_new_name());
    cell54 = new Cell ("cell54");
    cell54->chBox = ui->checkBoxCell54;
    cell54->center = center54;
    if(!cell54->getCell_new_name().isEmpty())
        cell54->chBox->setText(cell54->getCell_new_name());
    cell53 = new Cell ("cell53");
    cell53->chBox = ui->checkBoxCell53;
    cell53->center = center53;
    if(!cell53->getCell_new_name().isEmpty())
        cell53->chBox->setText(cell53->getCell_new_name());
    cell44 = new Cell ("cell44");
    cell44->chBox = ui->checkBoxCell44;
    cell44->center = center44;
    if(!cell44->getCell_new_name().isEmpty())
        cell44->chBox->setText(cell44->getCell_new_name());
    cell43 = new Cell ("cell43");
    cell43->chBox = ui->checkBoxCell43;
    cell43->center = center43;
    if(!cell43->getCell_new_name().isEmpty())
        cell43->chBox->setText(cell43->getCell_new_name());
    cell34 = new Cell ("cell34");
    cell34->chBox = ui->checkBoxCell34;
    cell34->center = center34;
    if(!cell34->getCell_new_name().isEmpty())
        cell34->chBox->setText(cell34->getCell_new_name());
    cell33 = new Cell ("cell33");
    cell33->chBox = ui->checkBoxCell33;
    cell33->center = center33;
    if(!cell33->getCell_new_name().isEmpty())
        cell33->chBox->setText(cell33->getCell_new_name());
    cell24 = new Cell ("cell24");
    cell24->chBox = ui->checkBoxCell24;
    cell24->center = center24;
    if(!cell24->getCell_new_name().isEmpty())
        cell24->chBox->setText(cell24->getCell_new_name());
    cell23 = new Cell ("cell23");
    cell23->chBox = ui->checkBoxCell23;
    cell23->center = center23;
    if(!cell23->getCell_new_name().isEmpty())
        cell23->chBox->setText(cell23->getCell_new_name());
    cell14 = new Cell ("cell14");
    cell14->chBox = ui->checkBoxCell14;
    cell14->center = center14;
    if(!cell14->getCell_new_name().isEmpty())
        cell14->chBox->setText(cell14->getCell_new_name());
    cell13 = new Cell ("cell13");
    cell13->chBox = ui->checkBoxCell13;
    cell13->center = center13;
    if(!cell13->getCell_new_name().isEmpty())
        cell13->chBox->setText(cell13->getCell_new_name());

    tabCell = new Cell *[24];
    tabCell[0] = cell11;
    tabCell[1] = cell12;
    tabCell[2] = cell21;
    tabCell[3] = cell22;
    tabCell[4] = cell31;
    tabCell[5] = cell32;
    tabCell[6] = cell41;
    tabCell[7] = cell42;
    tabCell[8] = cell51;
    tabCell[9] = cell52;
    tabCell[10] = cell61;
    tabCell[11] = cell62;

    tabCell[12] = cell13;
    tabCell[13] = cell14;
    tabCell[14] = cell23;
    tabCell[15] = cell24;
    tabCell[16] = cell33;
    tabCell[17] = cell34;
    tabCell[18] = cell43;
    tabCell[19] = cell44;
    tabCell[20] = cell53;
    tabCell[21] = cell54;
    tabCell[22] = cell63;
    tabCell[23] = cell64;

//    for(unsigned int i=0; i<cellCount; i++){
//        cellNames[i].name=tabCell[i]->getCell();
//        cellNames[i].obj=tabCell[i];
//    }
}
void MapWindowLarge::createCoreNetwork()
{
    mme = new Mme;
    sgw = new Sgw;

    ui->checkBoxCoreNetwork->setChecked(mme->getSimulate_core());
    on_checkBoxCoreNetwork_clicked();
}

void MapWindowLarge::createUeSimulated()
{
    ue = new Ue();
    ui->checkBoxUE_simulated->setChecked(ue->getStart_ue_component());
    on_checkBoxUE_simulated_clicked();
}

void MapWindowLarge::closeEvent(QCloseEvent *event)
{
    msgExit.setText("The document has been modified.");
    msgExit.setInformativeText("Do you want to save your changes?");
    msgExit.setIcon(QMessageBox::Question);
    msgExit.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgExit.setDefaultButton(QMessageBox::Save);
    int ret = msgExit.exec();

    QString new_parametersFileContent="";

    switch (ret) {
      case QMessageBox::Save:
          // Save was clicked
          parametersFileContentList=this->generateParams();

          new_parametersFileContent="";
          for(int i=0; i<parametersFileContentList.size(); i++){
              new_parametersFileContent+=parametersFileContentList[i];
          }
          if(parametersFileContent!=new_parametersFileContent){
              changesPresent=true;
              parametersFileContent=new_parametersFileContent;
          }
          p->refreshPreview();

          showList(parametersFileContentList);
          event->accept();
          enteringMapView=false;
          p->show();
          break;
      case QMessageBox::Discard:
          // Don't Save was clicked
          enteringMapView=false;
          p->show();
          break;
      case QMessageBox::Cancel:
          // Cancel was clicked
          event->ignore();
          break;
      default:
          // should never be reached
          break;
    }

}
void MapWindowLarge::showList(QList<QString> list)
{
    QString str;
    for(int i=0; i<list.size(); i++)
        str += list[i];
    qDebug() <<str;
}


//--------------Show function  ---------------
void MapWindowLarge::showCellTabWiget()
{
    ui->tabWidget->insertTab(0,ui->tab,((openCell->getCell_new_name().isEmpty()) ? openCell->getCell() : openCell->getCell_new_name()));
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(2);
    ui->tabWidget->show();

}
void MapWindowLarge::showCenterTabWiget()
{
    ui->tabWidget->insertTab(0,ui->tab_2, ((openCenter->getNew_name_area().isEmpty()) ? openCenter->getArea() : openCenter->getNew_name_area()));
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(2);
    ui->tabWidget->show();
}
void MapWindowLarge::showHandoverTabWiget()
{
    ui->tabWidget->insertTab(0,ui->tab_3, openHandover->getArea());
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(2);
    ui->tabWidget->show();
}
//----------------- Myfunction -----------------

QStringList MapWindowLarge::generateParams(){

    int number_of_cell =24;         //24
    int number_of_Center=24;        //24
    int number_of_Handover= 53;      //42
    outputList<<"require 'etc'\n";
    outputList<<"module Parameters\n";
    //---------------------------------MME-----------------------------------------------------------
    outputList<< "\tdef Parameters.getMmeParameters() \n";
    outputList<<"\n\t\tdefault = {}";
    outputList<<"\n\t\tdefault[:simulate_core] = " + convertBoolToText(mme->getSimulate_core());
    outputList<<"\n\t\tdefault[:mme_names] = [\"" + mme->getMme_names() +"\"]";
    outputList<<"\n\t\tdefault[:mme_tais] = [\"" + mme->getMme_tais() +"\"]";
    outputList<<"\n\t\tdefault[:mmes] = " + mme->getMmes();
    outputList<<"\n\t\tdefault[:mme_s1ap_uris] = [\"" + mme->getMme_s1ap_uris() +"\"]";
    outputList<<"\n\t\tdefault[:s1ap_pluginFilterPath] = \"" + mme->getS1ap_pluginFilterPath() +"\"\n";
    outputList <<"\n\t\treturn default\n\tend\n";
    //---------------------------------Paging---------------------------------------------------------
    outputList<< "\tdef Parameters.getPagingGeneratorParameters()\n";
    outputList<<"\n\t\tdefault = {}";
    outputList<<"\n\t\t default[:generate_pagings] = " + convertBoolToText(mme->getGenerate_pagings());
    outputList<<"\n\t\t default[:generators] = " + mme->getGenerators();
    outputList<<"\n\t\t default[:paging_generator_names] = [\"" + mme->getPaging_generator_names().replace(", ","\", \"") + "\"]";
    outputList<<"\n\t\t default[:imsi_ranges] = [\"" + mme->getImsi_ranges().replace(", ","\", \"") + "\"]";
    outputList<<"\n\t\t default[:mme_codes] = [\"" + mme->getMme_codes().replace(", ","\", \"") + "\"]";
    outputList<<"\n\t\t default[:ue_paging_identity] = \"" + mme->getUe_paging_identity() + "\"";
    outputList<<"\n\t\t default[:paging_s1ap_uris] = [\"" + mme->getPaging_s1ap_uris().replace(", ","\", \"") + "\"]";
    outputList<<"\n\t\t default[:s1ap_checkASN1_constraints] = " + convertBoolToText(mme->getS1ap_checkASN1_constraints());
    outputList<<"\n\t\t default[:bundle_paging] = " + convertBoolToText(mme->getBundle_paging());
    outputList <<"\n\t\treturn default\n\tend\n";
    //---------------------------------SGW------------------------------------------------------------
    outputList<< "\tdef Parameters.getSgwParameters()\n";
    outputList<<"\n\t\tdefault = {}";
    outputList<<"\n\t\tdefault[:sgw_names] = [\"" + sgw->getNames() + "\"]";
    outputList<<"\n\t\tdefault[:sgw_ipAddresses] = [\"" + sgw->getIpAddresses() + "\"]";
    outputList<<"\n\t\tdefault[:apn_lists] = [\"" + sgw->getApnLists() + "\"]";
    outputList<<"\n\t\tdefault[:sgw_LDIs] = [\"" + sgw->getLDIs() + "\"]";
    outputList<<"\n\t\tdefault[:core_network_gateway] = " + convertBoolToText(sgw->getCore_network_gateway());
    outputList <<"\n\t\treturn default\n\tend\n";
    //---------------------------------UE-------------------------------------------------------------
    outputList<< "\tdef Parameters.getUeParameters()\n";
    outputList<<"\n\t\tdefault = {}";
    outputList<<"\n\t\tdefault[:start_ue_component] = " + convertBoolToText(ue->getStart_ue_component());
    outputList<<"\n\t\tdefault[:name] = \"" + ue->getName() +"\"";
    outputList<<"\n\t\tdefault[:l1l2_managers] = \"" + ue->getL1l2_managers() +"\"";
    outputList<<"\n\t\tdefault[:default[:rrc_pluginFilterPath] = \"" + ue->getRrc_pluginFilterPath() +"\"";
    outputList<<"\n\t\tdefault[:uctool_ip] = \"" + ue->getUctool_ip() +"\"";
    outputList<<"\n\t\tdefault[:uctool_cIds] = \"" + ue->getUctool_cIds() +"\"";
    outputList<<"\n\t\tdefault[:uctool_service_ip] = \"" + ue->getUctool_service_ip() +"\"";
    outputList<<"\n\t\tdefault[:ue_network_capability] = \"" + ue->getUe_network_capability() +"\"";
    outputList<<"\n\t\tdefault[:ue_keyDerivationAlgorithm] = \"" + ue->getUe_keyDerivationAlgorithm() +"\"";
    outputList<<"\n\t\tdefault[:ue_key] = \"" + ue->getUe_key() +"\"";
    outputList<<"\n\t\tdefault[:ue_op] = \"" + ue->getUe_op() +"\"";
    outputList <<"\n\t\treturn default\n\tend\n";
    //---------------------------------Cell objects---------------------------------------------------
    outputList << "\n\tdef Parameters.getRecParameters() \n";
    outputList << "\n\t\tdefault = {} [\n\t\tdefault[:rec] = \n\t\t {\n";
    for(int i =0; i<number_of_cell; i++){
        outputList << "\t\t\t:cell => \"" + tabCell[i]->getCell() + " " +tabCell[i]->getCell_new_name() +"\",\n";
        outputList << "\t\t\t:site => \"" + tabCell[i]->getSite() +"\",\n";
        outputList << "\t\t\t:pci => " + tabCell[i]->getPci() +",\n";
        outputList << "\t\t\t:position_X => " + tabCell[i]->getPosition_X() +",\n";
        outputList << "\t\t\t:position_Y => " + tabCell[i]->getPosition_Y() +",\n";
        outputList << "\t\t\t:earfcnDl => " + tabCell[i]->getEarfcnDl() + +",\n";
        outputList << "\t\t\t:transmitPower => " + tabCell[i]->getTransmitPower() +",\n";
        outputList << "\t\t\t:ulNoiseAndInterference => " + tabCell[i]->getUlNoiseAndInterference()+"\n";
        if (i != number_of_cell-1)
            outputList << "\t\t}.{\n";
    }
    outputList << "\t\t}\n\t\t] \n\treturn default \n\tend";

    outputList << "\n\tdef Parameters.getTraffBehaviourParameters() \n\t\tdefault = {}";
    outputList << "\n\t\tdefault[:imsiMapRange] = \"" + ue->getImsiMapRange() +"\"\n";

    outputList <<"\n\t\tdefault[:southBoundMap] = " + QString::number(mapRange->getSouthBoundMap());
    outputList <<"\n\t\tdefault[:northBoundMap] = " + QString::number(mapRange->getNorthBoundMap());
    outputList <<"\n\t\tdefault[:westBoundMap] = " + QString::number(mapRange->getWestBoundMap());
    outputList <<"\n\t\tdefault[:eastBoundMap] = " + QString::number(mapRange->getEastBoundMap());

    outputList <<"\n\t\tdefault[:areas] = [ \n\t\t{";
    for(int i =0 ; i<number_of_Center ; i++){
        outputList <<"\n\t\t\t:area => \"" +tabCenter[i]->getArea() + " " +tabCenter[i]->getNew_name_area() + "\",";
        outputList <<"\n\t\t\t:southBoundary => " +tabCenter[i]->getSouthBoundary() + ",";
        outputList <<"\n\t\t\t:northBoundary => " +tabCenter[i]->getNorthBoundary() + ",";
        outputList <<"\n\t\t\t:westBoundary => " +tabCenter[i]->getWestBoundary() + ",";
        outputList <<"\n\t\t\t:eastBoundary => " +tabCenter[i]->getEastBoundary();
        outputList <<"\n\t\t},{";
    }
    for(int i =0 ; i<number_of_Handover ; i++){
        outputList <<"\n\t\t\t:area => \"" +tabHandover[i]->getArea() + "\",";
        outputList <<"\n\t\t\t:southBoundary => " +tabHandover[i]->getSouthBoundary() + ",";
        outputList <<"\n\t\t\t:northBoundary => " +tabHandover[i]->getNorthBoundary() + ",";
        outputList <<"\n\t\t\t:westBoundary => " +tabHandover[i]->getWestBoundary() + ",";
        outputList <<"\n\t\t\t:eastBoundary => " +tabHandover[i]->getEastBoundary();
        if (i != number_of_Handover-1)
            outputList << "\n\t\t},{";
    }
    //---------------------------------Ipex-----------------------------------------------------------------
    QStringList tmp = ipex->getUserDataGen().replace("\n", "\\n\" +*\n\t\t\t\t\"").split("*");
    outputList <<"\n\t\t}";
    outputList <<"\n\t\tdefault[:dataGenerator] = \"" + ipex->getDataGenerator()+"\"";
    outputList <<"\n\t\tdefault[:userDataGen] = \"" + tmp[0];
    for(int i=1; i<tmp.size();i++)
        outputList << tmp[i];
    outputList.last() += "\"";
    outputList <<"\n\t\tdefault[:start_isp_simulator] = " + convertBoolToText(ipex->getStart_isp_simulator());
    outputList <<"\n\t\tdefault[:ipgwtg_ipAddress] = \"" + ipex->getIpgwtg_ipAddress() + "\"";
    outputList <<"\n\t\tdefault[:ipgwtg_inband_signaling] = " + convertBoolToText(ipex->getIpgwtg_inband_signaling());
    outputList <<"\n\t\tdefault[:ipgwtg_port] = " + ipex->getIpgwtg_port();
    outputList <<"\n\t\tdefault[:ipgwtg_ftp_sender_connect_put] = " +convertBoolToText(ipex->getIpgwtg_ftp_sender_connect_put());
    outputList <<"\n\t\treturn default\n\tend";
    //--------------------------------UBsim------------------------------------------------------------------
    outputList <<"\n\n\tdef Parameters.getUbsimConfigParameters()";
    outputList <<"\n\t\tdefault = {}";
    outputList <<"\n\t\tdefault[:ueTypesDir] = \"" + ue->getUeTypesDir() + "\"";
    outputList <<"\n\t\tdefault[:csTrafficModelsDir] = \"" + ue->getCsTrafficModelsDir()+ "\"";
    outputList <<"\n\t\tdefault[:psTrafficModelsDir] = \"" + ue->getPsTrafficModelsDir()+ "\"";
    outputList <<"\n\t\tdefault[:mobilityModelsDir] = \"" + ue->getMobilityModelsDir()+ "\"";
    outputList <<"\n\t\tdefault[:visualization] = " + convertBoolToText(ue->getVisualization());
    outputList <<"\n\t\tdefault[:ubsim_patches] = \"" + ue->getUbsim_patches()+ "\"";
    outputList <<"\n\t\treturn default\n\tend";
    //--------------------------------ChanelModel-------------------------------------------------------------
    outputList <<"\n\n\tdef Parameters.getChannelModelConfigParameters()";
    outputList <<"\n\t\tdefault = {}";
    outputList <<"\n\t\tdefault[:model_set_name] = \"" + chmod->getModel_set_name() + "\"";
    outputList <<"\n\t\tdefault[:pdcch_drop_dl_assignment_rate] = " + chmod->getPdcch_drop_dl_assignment_rate();
    outputList <<"\n\t\tdefault[:pdcch_drop_grant_rate] = " + chmod->getPdcch_drop_grant_rate();
    outputList <<"\n\t\tdefault[:pdsch_transport_block_decoded_error_rate] = " + chmod->getPdsch_transport_block_decoded_error_rate();
    outputList <<"\n\t\tdefault[:phich_nack_to_ack_error_rate] = " + chmod->getPhich_nack_to_ack_error_rate();
    outputList <<"\n\t\tdefault[:phich_drop_harq_feedback_rate] = " + chmod->getPhich_drop_harq_feedback_rate();
    outputList <<"\n\t\tdefault[:pusch_transport_block_decoded_error_rate] = " + chmod->getPusch_transport_block_decoded_error_rate();
    outputList <<"\n\t\tdefault[:pusch_drop_transport_block_rate] = " + chmod->getPusch_drop_transport_block_rate();
    outputList <<"\n\t\tdefault[:puxch_nack_to_ack_error_rate] = " + chmod->getPuxch_nack_to_ack_error_rate();
    outputList <<"\n\t\tdefault[:puxch_dtx_to_ack_error_rate] = " + chmod->getPuxch_dtx_to_ack_error_rate();
    outputList <<"\n\t\tdefault[:puxch_ack_to_nack_error_rate] = " + chmod->getPuxch_ack_to_nack_error_rate();
    outputList <<"\n\t\tdefault[:puxch_drop_scheduling_request_rate] = " +chmod->getPuxch_drop_scheduling_request_rate();
    outputList <<"\n\t\tdefault[:dlni_noise] = " + chmod->getDlni_noise();
    outputList <<"\n\t\tdefault[:dlni_interference] = " + chmod->getDlni_interference();
    outputList <<"\n\t\tdefault[:dl_pathloss_min_pathloss] = " + chmod->getDl_pathloss_min_pathloss();
    outputList <<"\n\t\tdefault[:dl_pathloss_max_pathloss] = " + chmod->getDl_pathloss_max_pathloss();
    outputList <<"\n\t\tdefault[:dl_pathloss_time_min_to_max] = " + chmod->getDl_pathloss_time_min_to_max();
    outputList <<"\n\t\tdefault[:dl_pathloss_distribute_ues] = " + convertBoolToText(chmod->getDl_pathloss_distribute_ues());
    outputList <<"\n\t\tdefault[:pathloss_based_feedback_sinr_threshold] = " + chmod->getPathloss_based_feedback_sinr_threshold();
    outputList <<"\n\t\treturn default\n\tend";
    outputList <<"\nend";
    //    QString list;
    //    for(int i=0; i<outputList.size(); i++)
    //        list += outputList[i];

    //    qDebug() <<list;

    return outputList;

}
QString MapWindowLarge::convertBoolToText(bool value){
    QString result;
    if (value==true)
        return result= "true";
    else return result = "false";

}

//------------Fill functions------------------------------------------------------
void MapWindowLarge::fillParams(Center *object){
   ui->eastBoundary->setText(object->getEastBoundary());
   ui->westBoundary->setText(object->getWestBoundary());
   ui->southBoundary->setText(object->getSouthBoundary());
   ui->northBoundary->setText(object->getNorthBoundary());
   showCenterTabWiget();
}
void MapWindowLarge::fillParams(Handover *object){

   ui->eastHandovernoundary->setText(object->getEastBoundary());
   ui->westHandovernoundary->setText(object->getWestBoundary());
   ui->soutHandovernoundary->setText(object->getSouthBoundary());
   ui->northHandovernoundary->setText(object->getNorthBoundary());
   showHandoverTabWiget();
}
void MapWindowLarge::fillParams(Cell *object){
    if(object->getCell_new_name().isEmpty())
        ui->cell->setText(object->getCell());
    else ui->cell->setText(object->getCell_new_name());
    ui->site->setText(object->getSite());
    ui->pci->setText(object->getPci());
    ui->position_X->setText(object->getPosition_X());
    ui->position_Y->setText(object->getPosition_Y());
    ui->earfcnDl->setText(object->getEarfcnDl());
    ui->transmitPower->setText(object->getTransmitPower());
    ui->ulNoiseAndInterference->setText(object->getUlNoiseAndInterference());
    showCellTabWiget();
}
//------------Save functions--------------------------------------------------
void MapWindowLarge::saveParams(Center *object){
    listErrors.clear();
    if (validationPosition(ui->eastBoundary->text()))
        object->setEastBoundary(ui->eastBoundary->text());
            else listErrors << "East boundary of area: "+ui->eastBoundary->text() +"\n";
    if (validationPosition(ui->northBoundary->text()))
        object->setNorthBoundary(ui->northBoundary->text());
            else listErrors << "North boundary of area: "+ui->northBoundary->text() +"\n";
    if (validationPosition(ui->southBoundary->text()))
        object->setSouthBoundary(ui->southBoundary->text());
            else listErrors << "South boundary of area: "+ui->southBoundary->text() +"\n";
    if (validationPosition(ui->westBoundary->text()))
        object->setWestBoundary(ui->westBoundary->text());
            else listErrors << "West boundary of area: "+ui->westBoundary->text() +"\n";
    if (!listErrors.isEmpty()){
        showMessageError(listErrors);
    }
}
void MapWindowLarge::saveParams(Handover *object){
    listErrors.clear();
    if (validationPosition(ui->eastHandovernoundary->text()))
        object->setEastBoundary(ui->eastHandovernoundary->text());
            else listErrors << "East boundary of area: "+ui->eastHandovernoundary->text() +"\n";
    if(validationPosition(ui->northHandovernoundary->text()))
        object->setNorthBoundary(ui->northHandovernoundary->text());
            else listErrors << "North boundary of area: "+ui->northHandovernoundary->text() +"\n";
    if(validationPosition(ui->soutHandovernoundary->text()))
        object->setSouthBoundary(ui->soutHandovernoundary->text());
            else listErrors << "West boundary of area: "+ui->soutHandovernoundary->text() +"\n";
    if(validationPosition(ui->westHandovernoundary->text()))
        object->setWestBoundary(ui->westHandovernoundary->text());
            else listErrors << "North boundary of area: "+ui->westHandovernoundary->text() +"\n";
    if (!listErrors.isEmpty()){
        showMessageError(listErrors);
    }
}
void MapWindowLarge::saveParams(Cell *object){
    listErrors.clear();
    if (validationNameCell(ui->cell->text())){
 //       object->setCell(ui->cell->text());
        object->setCell_new_name(ui->cell->text());
        object->chBox->setText(ui->cell->text());                                       //change name CheckBox
        object->center->setNew_name_area("center" + ui->cell->text().remove(QString("cell")));   //change name Center
        qDebug () << "Nowa nazwa Centra: " + object->center->getNew_name_area();
        ui->tabWidget->setTabText( 0 , ui->cell->text());                               //change naem tabWiget
    }else listErrors <<" Name Cell: " +ui->cell->text()+"\n";
    object->setSite(ui->site->text());
    object->setPci(ui->pci->text());
    if (validationPosition(ui->position_X->text()))
        object->setPosition_X(ui->position_X->text()); else listErrors <<" Position X: " +ui->position_X->text()+"\n";
    if (validationPosition(ui->position_Y->text()))
        object->setPosition_Y(ui->position_Y->text()); else listErrors.append(" Position Y: " + ui->position_Y->text() +"\n");
    object->setEarfcnDl(ui->earfcnDl->text());
    if (validationTransmitPower(ui->transmitPower->text()))
        object->setTransmitPower(ui->transmitPower->text()); else listErrors << " Transmit Power: " + ui->transmitPower->text() +"\n";
    object->setUlNoiseAndInterference(ui->ulNoiseAndInterference->text());
    if (!listErrors.isEmpty()){
        showMessageError(listErrors);
    }
}
//--------------------------------------------------------------------------
bool MapWindowLarge::validationPosition(QString textForValidation){
        QRegExp rx("^\\d\\d?\\d?\\d?\\d?$");
        if (rx.indexIn(textForValidation) <0){
            return false;
        }else return true;
}
bool MapWindowLarge::validationTransmitPower(QString textForValidation){
     QRegExp rx("^-?\\d\\d?\\d?$");
    if (rx.indexIn(textForValidation) <0){
                return false;
    }else return true;
}

bool MapWindowLarge::validationNameCell(QString textForValidation)
{
    if( openCell->getCell() == textForValidation)
        return true;
    for (int i = 0; i< 12; i++){
        if(textForValidation == tabCell[i]->getCell())
           return false;
    }
    return true;
}

void MapWindowLarge::showMessageError(QList<QString> listErrors){
    QString errorMessage = "";
    for(int i=0; i<listErrors.size();i++)
        errorMessage += listErrors[i];
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Warning");
    msgBox.setText("Error, wrong  value: ");
    msgBox.setInformativeText(errorMessage);
    msgBox.exec();
    listErrors.clear();
}


//---------------------------------------------------------------------------
void MapWindowLarge::on_Center61_clicked()
{
   openCenter = center61;
   openCell = NULL;
   openHandover = NULL;
   fillParams(center61);
}
void MapWindowLarge::on_Center62_clicked()
{
    openCenter = center62;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center62);
}
void MapWindowLarge::on_Center52_clicked()
{
    openCenter = center52;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center52);
}
void MapWindowLarge::on_Center51_clicked()
{
    openCenter = center51;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center51);
}
void MapWindowLarge::on_Center42_clicked()
{
    openCenter = center42;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center42);
}
void MapWindowLarge::on_Center41_clicked()
{
    openCenter = center41;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center41);
}
void MapWindowLarge::on_Center32_clicked()
{
    openCenter = center32;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center32);
}
void MapWindowLarge::on_Center31_clicked()
{
    openCenter = center31;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center31);
}
void MapWindowLarge::on_Center22_clicked()
{
    openCenter = center22;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center22);
}
void MapWindowLarge::on_Center21_clicked()
{
    openCenter = center21;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center21);
}
void MapWindowLarge::on_Center12_clicked()
{
    openCenter = center12;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center12);
}
void MapWindowLarge::on_Center11_clicked()
{
    openCenter = center11;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center11);
}
void MapWindowLarge::on_Center63_clicked()
{
   openCenter = center63;
   openCell = NULL;
   openHandover = NULL;
   fillParams(center63);
}
void MapWindowLarge::on_Center64_clicked()
{
    openCenter = center64;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center64);
}
void MapWindowLarge::on_Center54_clicked()
{
    openCenter = center54;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center54);
}
void MapWindowLarge::on_Center53_clicked()
{
    openCenter = center53;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center53);
}
void MapWindowLarge::on_Center44_clicked()
{
    openCenter = center44;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center44);
}
void MapWindowLarge::on_Center43_clicked()
{
    openCenter = center43;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center43);
}
void MapWindowLarge::on_Center34_clicked()
{
    openCenter = center34;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center34);
}
void MapWindowLarge::on_Center33_clicked()
{
    openCenter = center33;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center33);
}
void MapWindowLarge::on_Center24_clicked()
{
    openCenter = center24;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center24);
}
void MapWindowLarge::on_Center23_clicked()
{
    openCenter = center23;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center23);
}
void MapWindowLarge::on_Center14_clicked()
{
    openCenter = center14;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center14);
}
void MapWindowLarge::on_Center13_clicked()
{
    openCenter = center13;
    openCell = NULL;
    openHandover = NULL;
    fillParams(center13);
}

//-----------Handover funcion-------------------------

void MapWindowLarge::on_Handover61_62_clicked()
{
    openHandover = handover61_62;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover61_62);
}

void MapWindowLarge::on_Handover51_61_clicked()
{
    openHandover = handover51_61;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover51_61);
}
void MapWindowLarge::on_Handover52_61_clicked()
{
    openHandover = handover52_61;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover52_61);
}

void MapWindowLarge::on_Handover52_62_clicked()
{
    openHandover = handover52_62;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover52_62);
}

void MapWindowLarge::on_Handover51_52_clicked()
{
    openHandover = handover51_52;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover51_52);
}

void MapWindowLarge::on_Handover41_51_clicked()
{
    openHandover = handover41_51;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover41_51);
}

void MapWindowLarge::on_Handover41_52_clicked()
{
    openHandover = handover41_52;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover41_52);
}

void MapWindowLarge::on_Handover42_52_clicked()
{
    openHandover = handover42_52;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover42_52);
}

void MapWindowLarge::on_Handover41_42_clicked()
{
    openHandover = handover41_42;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover41_42);
}

void MapWindowLarge::on_Handover31_41_clicked()
{
    openHandover = handover31_41;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover31_41);
}

void MapWindowLarge::on_Handover32_41_clicked()
{
    openHandover = handover32_41;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover32_41);
}

void MapWindowLarge::on_Handover32_42_clicked()
{
    openHandover = handover32_42;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover32_42);
}

void MapWindowLarge::on_Handover31_32_clicked()
{
    openHandover = handover31_32;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover31_32);
}

void MapWindowLarge::on_Handover21_31_clicked()
{
    openHandover = handover21_31;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover21_31);
}

void MapWindowLarge::on_Handover21_32_clicked()
{
    openHandover = handover21_32;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover21_32);
}

void MapWindowLarge::on_Handover22_32_clicked()
{
    openHandover = handover22_32;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover22_32);
}

void MapWindowLarge::on_Handover21_22_clicked()
{
    openHandover = handover21_22;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover21_22);
}

void MapWindowLarge::on_Handover11_21_clicked()
{
    openHandover = handover11_21;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover11_21);
}

void MapWindowLarge::on_Handover12_21_clicked()
{
    openHandover = handover12_21;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover12_21);
}

void MapWindowLarge::on_Handover12_22_clicked()
{
    openHandover = handover12_22;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover12_22);
}

void MapWindowLarge::on_Handover11_12_clicked()
{
    openHandover = handover11_12;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover11_12);
}

void MapWindowLarge::on_Handover63_64_clicked()
{
    openHandover = handover63_64;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover63_64);
}


void MapWindowLarge::on_Handover53_63_clicked()
{
    openHandover = handover53_63;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover53_63);
}
void MapWindowLarge::on_Handover54_63_clicked()
{
    openHandover = handover54_63;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover54_63);
}

void MapWindowLarge::on_Handover54_64_clicked()
{
    openHandover = handover54_64;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover54_64);
}

void MapWindowLarge::on_Handover53_54_clicked()
{
    openHandover = handover53_54;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover53_54);
}

void MapWindowLarge::on_Handover43_53_clicked()
{
    openHandover = handover43_53;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover43_53);
}

void MapWindowLarge::on_Handover43_54_clicked()
{
    openHandover = handover43_54;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover43_54);
}

void MapWindowLarge::on_Handover44_54_clicked()
{
    openHandover = handover44_54;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover44_54);
}

void MapWindowLarge::on_Handover43_44_clicked()
{
    openHandover = handover43_44;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover43_44);
}

void MapWindowLarge::on_Handover33_43_clicked()
{
    openHandover = handover33_43;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover33_43);
}

void MapWindowLarge::on_Handover34_43_clicked()
{
    openHandover = handover34_43;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover34_43);
}

void MapWindowLarge::on_Handover34_44_clicked()
{
    openHandover = handover34_44;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover34_44);
}

void MapWindowLarge::on_Handover33_34_clicked()
{
    openHandover = handover33_34;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover33_34);
}

void MapWindowLarge::on_Handover23_33_clicked()
{
    openHandover = handover23_33;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover23_33);
}

void MapWindowLarge::on_Handover23_34_clicked()
{
    openHandover = handover23_34;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover23_34);
}

void MapWindowLarge::on_Handover24_34_clicked()
{
    openHandover = handover24_34;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover24_34);
}

void MapWindowLarge::on_Handover23_24_clicked()
{
    openHandover = handover23_24;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover23_24);
}

void MapWindowLarge::on_Handover13_23_clicked()
{
    openHandover = handover13_23;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover13_23);
}

void MapWindowLarge::on_Handover14_23_clicked()
{
    openHandover = handover14_23;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover14_23);
}

void MapWindowLarge::on_Handover14_24_clicked()
{
    openHandover = handover14_24;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover14_24);
}

void MapWindowLarge::on_Handover13_14_clicked()
{
    openHandover = handover13_14;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover13_14);
}

void MapWindowLarge::on_Handover12_13_clicked()
{
    openHandover = handover12_13;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover12_13);
}

void MapWindowLarge::on_Handover13_22_clicked()
{
    openHandover = handover13_22;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover13_22);
}
void MapWindowLarge::on_Handover22_23_clicked()
{
    openHandover = handover22_23;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover22_23);
}

void MapWindowLarge::on_Handover22_33_clicked()
{
    openHandover = handover22_33;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover22_33);
}

void MapWindowLarge::on_Handover32_33_clicked()
{
    openHandover = handover32_33;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover32_33);
}

void MapWindowLarge::on_Handover33_42_clicked()
{
    openHandover = handover33_42;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover33_42);
}

void MapWindowLarge::on_Handover42_43_clicked()
{
    openHandover = handover42_43;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover42_43);
}

void MapWindowLarge::on_Handover42_53_clicked()
{
    openHandover = handover42_53;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover42_53);
}

void MapWindowLarge::on_Handover52_53_clicked()
{
    openHandover = handover52_53;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover52_53);
}

void MapWindowLarge::on_Handover53_62_clicked()
{
    openHandover = handover53_62;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover53_62);
}

void MapWindowLarge::on_Handover62_63_clicked()
{
    openHandover = handover62_63;
    openCell = NULL;
    openCenter = NULL;
    fillParams(handover62_63);
}

//-----------Cell funcion ----------------------------

void MapWindowLarge::on_cell61_clicked()
{
    openCell= tabCell[10];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[10]);

}
void MapWindowLarge::on_cell62_clicked()
{
    openCell= tabCell[11];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[11]);
}
void MapWindowLarge::on_cell51_clicked()
{
    openCell= tabCell[8];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[8]);

}
void MapWindowLarge::on_cell52_clicked()
{
    openCell= tabCell[9];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[9]);
}
void MapWindowLarge::on_cell41_clicked()
{
    openCell= tabCell[6];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[6]);

}
void MapWindowLarge::on_cell42_clicked()
{
    openCell= tabCell[7];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[7]);
}
void MapWindowLarge::on_cell31_clicked()
{
    openCell= tabCell[4];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[4]);

}
void MapWindowLarge::on_cell32_clicked()
{
    openCell= tabCell[5];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[5]);
}
void MapWindowLarge::on_cell21_clicked()
{
    openCell= tabCell[2];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[2]);

}
void MapWindowLarge::on_cell22_clicked()
{
    openCell= tabCell[3];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[3]);
}
void MapWindowLarge::on_cell11_clicked()
{
    openCell= tabCell[0];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[0]);

}
void MapWindowLarge::on_cell12_clicked()
{
    openCell= tabCell[1];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[1]);
}

void MapWindowLarge::on_cell63_clicked()
{
    openCell= cell63;
    openHandover = NULL;
    openCenter = NULL;
    fillParams(cell63);

}
void MapWindowLarge::on_cell64_clicked()
{
    openCell= cell64;
    openHandover = NULL;
    openCenter = NULL;
    fillParams(cell64);
}
void MapWindowLarge::on_cell53_clicked()
{
    openCell= cell53;
    openHandover = NULL;
    openCenter = NULL;
    fillParams(cell53);

}
void MapWindowLarge::on_cell54_clicked()
{
    openCell= cell54;
    openHandover = NULL;
    openCenter = NULL;
    fillParams(cell54);
}
void MapWindowLarge::on_cell43_clicked()
{
    openCell= cell43;
    openHandover = NULL;
    openCenter = NULL;
    fillParams(cell43);

}
void MapWindowLarge::on_cell44_clicked()
{
    openCell= cell44;
    openHandover = NULL;
    openCenter = NULL;
    fillParams(cell44);
}
void MapWindowLarge::on_cell33_clicked()
{
    openCell= cell33;
    openHandover = NULL;
    openCenter = NULL;
    fillParams(cell33);

}
void MapWindowLarge::on_cell34_clicked()
{
    openCell= cell34;
    openHandover = NULL;
    openCenter = NULL;
    fillParams(cell34);
}
void MapWindowLarge::on_cell23_clicked()
{
    openCell= cell23;
    openHandover = NULL;
    openCenter = NULL;
    fillParams(cell23);

}
void MapWindowLarge::on_cell24_clicked()
{
    openCell= cell24;
    openHandover = NULL;
    openCenter = NULL;
    fillParams(cell24);
}
void MapWindowLarge::on_cell13_clicked()
{
    openCell= cell13;
    openHandover = NULL;
    openCenter = NULL;
    fillParams(cell13);

}
void MapWindowLarge::on_cell14_clicked()
{
    openCell= cell14;
    openHandover = NULL;
    openCenter = NULL;
    fillParams(cell14);
}


//----------------------edit parameters----------------

void MapWindowLarge::on_cell_returnPressed()
{
    saveParams(openCell);
}

void MapWindowLarge::on_site_returnPressed()
{
    saveParams(openCell);
}

void MapWindowLarge::on_position_X_returnPressed()
{
  saveParams(openCell);
}

void MapWindowLarge::on_pci_returnPressed()
{
    saveParams(openCell);
}

void MapWindowLarge::on_position_Y_returnPressed()
{
    saveParams(openCell);
}

void MapWindowLarge::on_earfcnDl_returnPressed()
{
    saveParams(openCell);
}

void MapWindowLarge::on_transmitPower_returnPressed()
{
    saveParams(openCell);
}

void MapWindowLarge::on_ulNoiseAndInterference_returnPressed()
{
    saveParams(openCell);
}

void MapWindowLarge::on_pbSetCellParams_clicked()
{
   ui->tabWidget->hide();
   saveParams(openCell);
}
//------------------------end edit parameters ------------------------------------
void MapWindowLarge::on_southBoundary_returnPressed()
{

    saveParams(openCenter);
}

void MapWindowLarge::on_northBoundary_returnPressed()
{
    saveParams(openCenter);
}

void MapWindowLarge::on_westBoundary_returnPressed()
{
    saveParams(openCenter);
}

void MapWindowLarge::on_eastBoundary_returnPressed()
{
    saveParams(openCenter);
}

void MapWindowLarge::on_pbSetCenterParams_clicked()
{
    ui->tabWidget->hide();
    saveParams(openCenter);
}
//------------------------------------------------------------------------------------

void MapWindowLarge::on_soutHandovernoundary_returnPressed()
{
    saveParams(openHandover);
}

void MapWindowLarge::on_northHandovernoundary_returnPressed()
{
    saveParams(openHandover);
}

void MapWindowLarge::on_westHandovernoundary_returnPressed()
{
    saveParams(openHandover);
}

void MapWindowLarge::on_eastHandovernoundary_returnPressed()
{
    saveParams(openHandover);
}

void MapWindowLarge::on_pbsetHandoverParams_clicked()
{
    saveParams(openHandover);
    ui->tabWidget->hide();
}
//--------------on/off cell ---------------------------------
void MapWindowLarge::on_checkBoxCell61_clicked()
{

    if (!ui->checkBoxCell61->isChecked() )
    {
        ui->cell61->setEnabled(false);
        ui->Center61->setEnabled(false);
        ui->Handover61_62->setEnabled(false);
        ui->Handover51_61->setEnabled(false);
        ui->Handover52_61->setEnabled(false);

    }else{
        ui->cell61->setEnabled(true);
        ui->Center61->setEnabled(true);
        if(ui->cell62->isEnabled())
            ui->Handover61_62->setEnabled(true);
        if(ui->cell51->isEnabled())
            ui->Handover51_61->setEnabled(true);
        if(ui->cell52->isEnabled())
            ui->Handover52_61->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell62_clicked()
{

    if (!ui->checkBoxCell62->isChecked())
    {
        ui->cell62->setEnabled(false);
        ui->Center62->setEnabled(false);
        ui->Handover61_62->setEnabled(false);
        ui->Handover52_62->setEnabled(false);
        ui->Handover62_63->setEnabled(false);
        ui->Handover53_62->setEnabled(false);
    }else{
        ui->cell62->setEnabled(true);
        ui->Center62->setEnabled(true);
        if(ui->cell61->isEnabled())
            ui->Handover61_62->setEnabled(true);
        if(ui->cell52->isEnabled())
            ui->Handover52_62->setEnabled(true);
        if(ui->cell63->isEnabled())
            ui->Handover62_63->setEnabled(true);
        if(ui->cell53->isEnabled())
            ui->Handover53_62->setEnabled(true);
    }
     showActiveLine();
     ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell51_clicked()
{
    if (!ui->checkBoxCell51->isChecked() )
    {
        ui->cell51->setEnabled(false);
        ui->Center51->setEnabled(false);
        ui->Handover51_52->setEnabled(false);
        ui->Handover51_61->setEnabled(false);
        ui->Handover41_51->setEnabled(false);
    }else{
        ui->cell51->setEnabled(true);
        ui->Center51->setEnabled(true);
        if(ui->cell52->isEnabled())
            ui->Handover51_52->setEnabled(true);
        if(ui->cell61->isEnabled())
            ui->Handover51_61->setEnabled(true);
        if(ui->cell41->isEnabled())
            ui->Handover41_51->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell52_clicked()
{
    if (!ui->checkBoxCell52->isChecked() )
    {
        ui->cell52->setEnabled(false);
        ui->Center52->setEnabled(false);
        ui->Handover52_61->setEnabled(false);
        ui->Handover52_62->setEnabled(false);
        ui->Handover41_52->setEnabled(false);
        ui->Handover42_52->setEnabled(false);
        ui->Handover51_52->setEnabled(false);
        ui->Handover52_53->setEnabled(false);
    }else{
        ui->cell52->setEnabled(true);
        ui->Center52->setEnabled(true);
        if(ui->cell61->isEnabled())
            ui->Handover52_61->setEnabled(true);
        if(ui->cell62->isEnabled())
            ui->Handover52_62->setEnabled(true);
        if(ui->cell41->isEnabled())
            ui->Handover41_52->setEnabled(true);
        if(ui->cell42->isEnabled())
            ui->Handover42_52->setEnabled(true);
        if(ui->cell51->isEnabled())
            ui->Handover51_52->setEnabled(true);
        if(ui->cell53->isEnabled())
            ui->Handover52_53->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell41_clicked()
{
    if (!ui->checkBoxCell41->isChecked() )
    {
        ui->cell41->setEnabled(false);
        ui->Center41->setEnabled(false);
        ui->Handover41_42->setEnabled(false);
        ui->Handover41_51->setEnabled(false);
        ui->Handover41_52->setEnabled(false);
        ui->Handover32_41->setEnabled(false);
        ui->Handover31_41->setEnabled(false);
    }else{
        ui->cell41->setEnabled(true);
        ui->Center41->setEnabled(true);
        if(ui->cell42->isEnabled())
            ui->Handover41_42->setEnabled(true);
        if(ui->cell51->isEnabled())
            ui->Handover41_51->setEnabled(true);
        if(ui->cell52->isEnabled())
            ui->Handover41_52->setEnabled(true);
        if(ui->cell32->isEnabled())
            ui->Handover32_41->setEnabled(true);
        if(ui->cell31->isEnabled())
            ui->Handover31_41->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell42_clicked()
{
    if (!ui->checkBoxCell42->isChecked() )
    {
        ui->cell42->setEnabled(false);
        ui->Center42->setEnabled(false);
        ui->Handover42_52->setEnabled(false);
        ui->Handover32_42->setEnabled(false);
        ui->Handover41_42->setEnabled(false);
        ui->Handover42_53->setEnabled(false);
        ui->Handover42_43->setEnabled(false);
        ui->Handover33_42->setEnabled(false);
    }else{
        ui->cell42->setEnabled(true);
        ui->Center42->setEnabled(true);
        if(ui->cell52->isEnabled())
            ui->Handover42_52->setEnabled(true);
        if(ui->cell32->isEnabled())
            ui->Handover32_42->setEnabled(true);
        if(ui->cell41->isEnabled())
            ui->Handover41_42->setEnabled(true);
        if(ui->cell53->isEnabled())
             ui->Handover42_53->setEnabled(true);
        if(ui->cell43->isEnabled())
             ui->Handover42_43->setEnabled(true);
        if(ui->cell33->isEnabled())
             ui->Handover33_42->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell31_clicked()
{
    if (!ui->checkBoxCell31->isChecked() )
    {
        ui->cell31->setEnabled(false);
        ui->Center31->setEnabled(false);
        ui->Handover31_32->setEnabled(false);
        ui->Handover31_41->setEnabled(false);
        ui->Handover21_31->setEnabled(false);

    }else{
        ui->cell31->setEnabled(true);
        ui->Center31->setEnabled(true);
        if(ui->cell32->isEnabled())
            ui->Handover31_32->setEnabled(true);
        if(ui->cell41->isEnabled())
            ui->Handover31_41->setEnabled(true);
        if(ui->cell21->isEnabled())
            ui->Handover21_31->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell32_clicked()
{
    if (!ui->checkBoxCell32->isChecked() )
    {
        ui->cell32->setEnabled(false);
        ui->Center32->setEnabled(false);
        ui->Handover32_41->setEnabled(false);
        ui->Handover32_42->setEnabled(false);
        ui->Handover21_32->setEnabled(false);
        ui->Handover22_32->setEnabled(false);
        ui->Handover31_32->setEnabled(false);
        ui->Handover32_33->setEnabled(false);
    }else{
        ui->cell32->setEnabled(true);
        ui->Center32->setEnabled(true);
        if(ui->cell41->isEnabled())
            ui->Handover32_41->setEnabled(true);
        if(ui->cell42->isEnabled())
            ui->Handover32_42->setEnabled(true);
        if(ui->cell21->isEnabled())
            ui->Handover21_32->setEnabled(true);
        if(ui->cell22->isEnabled())
            ui->Handover22_32->setEnabled(true);
        if(ui->cell31->isEnabled())
            ui->Handover31_32->setEnabled(true);
        if(ui->cell33->isEnabled())
            ui->Handover32_33->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell21_clicked()
{
    if (!ui->checkBoxCell21->isChecked() )
    {
        ui->cell21->setEnabled(false);
        ui->Center21->setEnabled(false);
        ui->Handover21_22->setEnabled(false);
        ui->Handover21_31->setEnabled(false);
        ui->Handover21_32->setEnabled(false);
        ui->Handover11_21->setEnabled(false);
        ui->Handover12_21->setEnabled(false);
    }else{
        ui->cell21->setEnabled(true);
        ui->Center21->setEnabled(true);
        if(ui->cell22->isEnabled())
            ui->Handover21_22->setEnabled(true);
        if(ui->cell31->isEnabled())
            ui->Handover21_31->setEnabled(true);
        if(ui->cell32->isEnabled())
            ui->Handover21_32->setEnabled(true);
        if(ui->cell11->isEnabled())
            ui->Handover11_21->setEnabled(true);
        if(ui->cell12->isEnabled())
            ui->Handover12_21->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell22_clicked()
{
    if (!ui->checkBoxCell22->isChecked() )
    {
        ui->cell22->setEnabled(false);
        ui->Center22->setEnabled(false);
        ui->Handover22_32->setEnabled(false);
        ui->Handover12_22->setEnabled(false);
        ui->Handover21_22->setEnabled(false);
        ui->Handover22_33->setEnabled(false);
        ui->Handover22_23->setEnabled(false);
        ui->Handover13_22->setEnabled(false);
    }else{
        ui->cell22->setEnabled(true);
        ui->Center22->setEnabled(true);
        if(ui->cell32->isEnabled())
            ui->Handover22_32->setEnabled(true);
        if(ui->cell12->isEnabled())
            ui->Handover12_22->setEnabled(true);
        if(ui->cell21->isEnabled())
            ui->Handover21_22->setEnabled(true);
        if(ui->cell33->isEnabled())
            ui->Handover22_33->setEnabled(true);
        if(ui->cell23->isEnabled())
            ui->Handover22_23->setEnabled(true);
        if(ui->cell13->isEnabled())
            ui->Handover13_22->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell11_clicked()
{
    if (!ui->checkBoxCell11->isChecked() )
    {
        ui->cell11->setEnabled(false);
        ui->Center11->setEnabled(false);
        ui->Handover11_12->setEnabled(false);
        ui->Handover11_21->setEnabled(false);
    }else{
        ui->cell11->setEnabled(true);
        ui->Center11->setEnabled((true));
        if(ui->cell12->isEnabled())
            ui->Handover11_12->setEnabled((true));
        if(ui->cell21->isEnabled())
            ui->Handover11_21->setEnabled((true));
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell12_clicked()
{
    if (!ui->checkBoxCell12->isChecked() )
    {
        ui->cell12->setEnabled(false);
        ui->Center12->setEnabled(false);
        ui->Handover12_21->setEnabled(false);
        ui->Handover12_22->setEnabled(false);
        ui->Handover11_12->setEnabled(false);
        ui->Handover12_13->setEnabled(false);
    }else{
        ui->cell12->setEnabled((true));
        ui->Center12->setEnabled((true));
        if(ui->cell21->isEnabled())
            ui->Handover12_21->setEnabled((true));
        if(ui->cell22->isEnabled())
            ui->Handover12_22->setEnabled((true));
        if(ui->cell11->isEnabled())
            ui->Handover11_12->setEnabled((true));
        if(ui->cell13->isEnabled())
            ui->Handover12_13->setEnabled((true));
    }
    showActiveLine();
    ui->tabWidget->hide();
}
//------------Large Map show and hide cell--------------------------
void MapWindowLarge::on_checkBoxCell63_clicked()
{
    if (!ui->checkBoxCell63->isChecked() )
    {
        ui->cell63->setEnabled(false);
        ui->Center63->setEnabled(false);
        ui->Handover63_64->setEnabled(false);
        ui->Handover53_63->setEnabled(false);
        ui->Handover54_63->setEnabled(false);
        ui->Handover62_63->setEnabled(false);
    }else{
        ui->cell63->setEnabled(true);
        ui->Center63->setEnabled(true);
        if(ui->cell64->isEnabled())
            ui->Handover63_64->setEnabled(true);
        if(ui->cell53->isEnabled())
            ui->Handover53_63->setEnabled(true);
        if(ui->cell54->isEnabled())
            ui->Handover54_63->setEnabled(true);
        if(ui->cell62->isEnabled())
            ui->Handover62_63->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell64_clicked()
{

    if (!ui->checkBoxCell64->isChecked())
    {
        ui->cell64->setEnabled(false);
        ui->Center64->setEnabled(false);
        ui->Handover63_64->setEnabled(false);
        ui->Handover54_64->setEnabled(false);
    }else{
        ui->cell64->setEnabled(true);
        ui->Center64->setEnabled(true);
        if(ui->cell63->isEnabled())
            ui->Handover63_64->setEnabled(true);
        if(ui->cell54->isEnabled())
            ui->Handover54_64->setEnabled(true);
    }
     showActiveLine();
     ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell53_clicked()
{
    if (!ui->checkBoxCell53->isChecked() )
    {
        ui->cell53->setEnabled(false);
        ui->Center53->setEnabled(false);
        ui->Handover53_54->setEnabled(false);
        ui->Handover53_63->setEnabled(false);
        ui->Handover43_53->setEnabled(false);
        ui->Handover52_53->setEnabled(false);
        ui->Handover53_62->setEnabled(false);
        ui->Handover42_53->setEnabled(false);
    }else{
        ui->cell53->setEnabled(true);
        ui->Center53->setEnabled(true);
        if(ui->cell54->isEnabled())
            ui->Handover53_54->setEnabled(true);
        if(ui->cell63->isEnabled())
            ui->Handover53_63->setEnabled(true);
        if(ui->cell43->isEnabled())
            ui->Handover43_53->setEnabled(true);
        if(ui->cell52->isEnabled())
            ui->Handover52_53->setEnabled(true);
        if(ui->cell62->isEnabled())
            ui->Handover53_62->setEnabled(true);
        if(ui->cell42->isEnabled())
            ui->Handover42_53->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell54_clicked()
{
    if (!ui->checkBoxCell54->isChecked() )
    {
        ui->cell54->setEnabled(false);
        ui->Center54->setEnabled(false);
        ui->Handover54_63->setEnabled(false);
        ui->Handover54_64->setEnabled(false);
        ui->Handover43_54->setEnabled(false);
        ui->Handover44_54->setEnabled(false);
        ui->Handover53_54->setEnabled(false);
    }else{
        ui->cell54->setEnabled(true);
        ui->Center54->setEnabled(true);
        if(ui->cell63->isEnabled())
            ui->Handover54_63->setEnabled(true);
        if(ui->cell64->isEnabled())
            ui->Handover54_64->setEnabled(true);
        if(ui->cell43->isEnabled())
            ui->Handover43_54->setEnabled(true);
        if(ui->cell44->isEnabled())
            ui->Handover44_54->setEnabled(true);
        if(ui->cell53->isEnabled())
            ui->Handover53_54->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell43_clicked()
{
    if (!ui->checkBoxCell43->isChecked() )
    {
        ui->cell43->setEnabled(false);
        ui->Center43->setEnabled(false);
        ui->Handover43_44->setEnabled(false);
        ui->Handover43_53->setEnabled(false);
        ui->Handover43_54->setEnabled(false);
        ui->Handover34_43->setEnabled(false);
        ui->Handover33_43->setEnabled(false);
        ui->Handover42_43->setEnabled(false);
    }else{
        ui->cell43->setEnabled(true);
        ui->Center43->setEnabled(true);
        if(ui->cell44->isEnabled())
            ui->Handover43_44->setEnabled(true);
        if(ui->cell53->isEnabled())
            ui->Handover43_53->setEnabled(true);
        if(ui->cell54->isEnabled())
            ui->Handover43_54->setEnabled(true);
        if(ui->cell34->isEnabled())
            ui->Handover34_43->setEnabled(true);
        if(ui->cell33->isEnabled())
            ui->Handover33_43->setEnabled(true);
        if(ui->cell42->isEnabled())
            ui->Handover42_43->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell44_clicked()
{
    if (!ui->checkBoxCell44->isChecked() )
    {
        ui->cell44->setEnabled(false);
        ui->Center44->setEnabled(false);
        ui->Handover44_54->setEnabled(false);
        ui->Handover34_44->setEnabled(false);
        ui->Handover43_44->setEnabled(false);
    }else{
        ui->cell44->setEnabled(true);
        ui->Center44->setEnabled(true);
        if(ui->cell54->isEnabled())
            ui->Handover44_54->setEnabled(true);
        if(ui->cell34->isEnabled())
            ui->Handover34_44->setEnabled(true);
        if(ui->cell43->isEnabled())
            ui->Handover43_44->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell33_clicked()
{
    if (!ui->checkBoxCell33->isChecked() )
    {
        ui->cell33->setEnabled(false);
        ui->Center33->setEnabled(false);
        ui->Handover33_34->setEnabled(false);
        ui->Handover33_43->setEnabled(false);
        ui->Handover33_43->setEnabled(false);
        ui->Handover32_33->setEnabled(false);
        ui->Handover33_42->setEnabled(false);
        ui->Handover22_33->setEnabled(false);
    }else{
        ui->cell33->setEnabled(true);
        ui->Center33->setEnabled(true);
        if(ui->cell34->isEnabled())
            ui->Handover33_34->setEnabled(true);
        if(ui->cell43->isEnabled())
            ui->Handover33_43->setEnabled(true);
        if(ui->cell43->isEnabled())
            ui->Handover33_43->setEnabled(true);
        if(ui->cell32->isEnabled())
            ui->Handover32_33->setEnabled(true);
        if(ui->cell42)
            ui->Handover33_42->setEnabled(true);
        if(ui->cell22->isEnabled())
            ui->Handover22_33->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell34_clicked()
{
    if (!ui->checkBoxCell34->isChecked() )
    {
        ui->cell34->setEnabled(false);
        ui->Center34->setEnabled(false);
        ui->Handover34_43->setEnabled(false);
        ui->Handover34_44->setEnabled(false);
        ui->Handover23_34->setEnabled(false);
        ui->Handover24_34->setEnabled(false);
        ui->Handover33_34->setEnabled(false);
    }else{
        ui->cell34->setEnabled(true);
        ui->Center34->setEnabled(true);
        if(ui->cell43->isEnabled())
            ui->Handover34_43->setEnabled(true);
        if(ui->cell44->isEnabled())
            ui->Handover34_44->setEnabled(true);
        if(ui->cell23->isEnabled())
            ui->Handover23_34->setEnabled(true);
        if(ui->cell24->isEnabled())
            ui->Handover24_34->setEnabled(true);
        if(ui->cell33->isEnabled())
            ui->Handover33_34->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell23_clicked()
{
    if (!ui->checkBoxCell23->isChecked() )
    {
        ui->cell23->setEnabled(false);
        ui->Center23->setEnabled(false);
        ui->Handover23_24->setEnabled(false);
        ui->Handover23_33->setEnabled(false);
        ui->Handover23_34->setEnabled(false);
        ui->Handover13_23->setEnabled(false);
        ui->Handover22_23->setEnabled(false);
        //ui->Handover12_23->setEnabled(false);
    }else{
        ui->cell23->setEnabled(true);
        ui->Center23->setEnabled(true);
        if(ui->cell24->isEnabled())
            ui->Handover23_24->setEnabled(true);
        if(ui->cell33->isEnabled())
            ui->Handover23_33->setEnabled(true);
        if(ui->cell34->isEnabled())
            ui->Handover23_34->setEnabled(true);
        if(ui->cell13->isEnabled())
            ui->Handover13_23->setEnabled(true);
        if(ui->cell12->isEnabled())
            ui->Handover14_23->setEnabled(true);
        if(ui->cell22->isEnabled())
            ui->Handover22_23->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell24_clicked()
{
    if (!ui->checkBoxCell24->isChecked() )
    {
        ui->cell24->setEnabled(false);
        ui->Center24->setEnabled(false);
        ui->Handover24_34->setEnabled(false);
        ui->Handover14_24->setEnabled(false);
        ui->Handover23_24->setEnabled(false);
    }else{
        ui->cell24->setEnabled(true);
        ui->Center24->setEnabled(true);
        if(ui->cell34->isEnabled())
            ui->Handover24_34->setEnabled(true);
        if(ui->cell14->isEnabled())
            ui->Handover14_24->setEnabled(true);
        if(ui->cell23->isEnabled())
            ui->Handover23_24->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell13_clicked()
{
    if (!ui->checkBoxCell13->isChecked() )
    {
        ui->cell13->setEnabled(false);
        ui->Center13->setEnabled(false);
        ui->Handover13_14->setEnabled(false);
        ui->Handover13_23->setEnabled(false);
        ui->Handover12_13->setEnabled(false);
        ui->Handover13_22->setEnabled(false);
    }else{
        ui->cell13->setEnabled(true);
        ui->Center13->setEnabled((true));
        if(ui->cell14->isEnabled())
            ui->Handover13_14->setEnabled(true);
        if(ui->cell23->isEnabled())
            ui->Handover13_23->setEnabled(true);
        if(ui->cell12->isEnabled())
            ui->Handover12_13->setEnabled(true);
        if(ui->cell22->isEnabled())
            ui->Handover13_22->setEnabled(true);
    }
    showActiveLine();
    ui->tabWidget->hide();
}
void MapWindowLarge::on_checkBoxCell14_clicked()
{
    if (!ui->checkBoxCell14->isChecked() )
    {
        ui->cell14->setEnabled(false);
        ui->Center14->setEnabled(false);
        ui->Handover14_23->setEnabled(false);
        ui->Handover14_24->setEnabled(false);
        ui->Handover13_14->setEnabled((false));
    }else{
        ui->cell14->setEnabled((true));
        ui->Center14->setEnabled((true));
        if(ui->cell23->isEnabled())
            ui->Handover14_23->setEnabled((true));
        if(ui->cell24->isEnabled())
            ui->Handover14_24->setEnabled((true));
        if(ui->cell13->isEnabled())
            ui->Handover13_14->setEnabled((true));

    }
    showActiveLine();
    ui->tabWidget->hide();
}


//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMm
void MapWindowLarge::Mouse_Pressed()
{

    msgBox.setWindowTitle("Warning");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText(trUtf8(("File was changed")));
    msgBox.setInformativeText(trUtf8("Do you want to save changes?"));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);

if(openCell!=NULL && wasChangeonCell())
{
    int ret = msgBox.exec();

    switch (ret) {
        case QMessageBox::Save:
                   saveParams(openCell);
                   ui->tabWidget->hide();
                   openCell = NULL;
                   openCenter = NULL;
                   openHandover = NULL;
                    break;
                 case QMessageBox::Discard:
                       ui->tabWidget->hide();
                       openCell = NULL;
                       openCenter = NULL;
                       openHandover = NULL;
                    break;
                 case QMessageBox::Cancel:
                      msgBox.close();
                      openCenter = NULL;
                      openHandover = NULL;//przestawienie bedzie mozna usunac bo bedzie ustawion w metodach pressed
                    break;
                 default:
                    //never induced
                    break;
                  }
}else if(openCell!=NULL)
{
    ui->tabWidget->hide();
    openCell=NULL;
}

if(openCenter!=NULL && wasChangeonCenter())
{
    int ret = msgBox.exec();

    switch (ret) {
        case QMessageBox::Save:
                   saveParams(openCenter);
                   ui->tabWidget->hide();
                   openCell = NULL;
                   openCenter = NULL;
                   openHandover = NULL;
                    break;
                 case QMessageBox::Discard:
                       ui->tabWidget->hide();
                       openCell = NULL;
                       openCenter = NULL;
                       openHandover = NULL;
                    break;
                 case QMessageBox::Cancel:
                      msgBox.close();
                      openCell = NULL;
                      openHandover = NULL;//przestawienie bedzie mozna usunac bo bedzie ustawion w metodach pressed
                    break;
                 default:
                    //never induced
                    break;
                  }
}else if(openCenter!=NULL)
{
    ui->tabWidget->hide();
    openCenter=NULL;
}

if(openHandover !=NULL && wasChangeonHandover())
{
    int ret = msgBox.exec();

    switch (ret) {
        case QMessageBox::Save:
                   saveParams(openHandover);
                   ui->tabWidget->hide();
                   openCell = NULL;
                   openCenter = NULL;
                   openHandover = NULL;
                    break;
                 case QMessageBox::Discard:
                       ui->tabWidget->hide();
                       openCell = NULL;
                       openCenter = NULL;
                       openHandover = NULL;
                    break;
                 case QMessageBox::Cancel:
                      msgBox.close();
                      openCell = NULL;
                      openCenter = NULL;//przestawienie bedzie mozna usunac bo bedzie ustawion w metodach pressed
                    break;
                 default:
                    //never induced
                    break;
                  }
}else if(openHandover!=NULL)
{
    ui->tabWidget->hide();
    openHandover=NULL;
}


}


void MapWindowLarge::on_pbRestoreCell_clicked()
{
    openCell->resetParams();
    fillParams(openCell);
}

void MapWindowLarge::on_pbRestoreHandover_clicked()
{
    openHandover->resetParams();
    fillParams(openHandover);
}


void MapWindowLarge::on_pbRestoreCenter_clicked()
{
     openCenter->resetParams();
     fillParams(openCenter);
}

void MapWindowLarge::showActiveLine()
{
    //----------------line cell 61/62 ----------------------------------------------------------------------------------------------------------------------
    if( (ui->checkBoxCell61->isChecked() || ui->checkBoxCell62->isChecked()) || (ui->checkBoxCell63->isChecked() || ui->checkBoxCell64->isChecked()) ){
        ui->line61->show();
        ui->line62->show();
        ui->line52->show();
        ui->line42->show();
        ui->line32->show();
        ui->line22->show();
        ui->line12->show();
        ui->line->show();
    }
    if( (!ui->checkBoxCell61->isChecked() && !ui->checkBoxCell62->isChecked()) && (!ui->checkBoxCell63->isChecked() && !ui->checkBoxCell64->isChecked())){
        ui->line62->hide();
        ui->line61->hide();
    }
    //----------------line cell 51/52 ----------------------------------------------------------------------------------------------------------------------
    if(ui->checkBoxCell51->isChecked() || ui->checkBoxCell52->isChecked() || ui->checkBoxCell53->isChecked() || ui->checkBoxCell54->isChecked()){
        ui->line51->show();
        ui->line52->show();
        ui->line42->show();
        ui->line32->show();
        ui->line22->show();
        ui->line12->show();
        ui->line->show();
    }
    if( (!ui->checkBoxCell51->isChecked() && !ui->checkBoxCell52->isChecked()) && !ui->checkBoxCell53->isChecked() && !ui->checkBoxCell54->isChecked() ){
        ui->line51->hide();
    }
    if (!ui->checkBoxCell61->isChecked() && !ui->checkBoxCell62->isChecked()){
        if(!ui->checkBoxCell51->isChecked() && !ui->checkBoxCell52->isChecked())
            if((!ui->checkBoxCell63->isChecked() && !ui->checkBoxCell64->isChecked()))
                if(!ui->checkBoxCell53->isChecked() && !ui->checkBoxCell54->isChecked())
                ui->line52->hide();
    }
    //----------------line cell 41/42 ----------------------------------------------------------------------------------------------------------------------
    if( ui->checkBoxCell41->isChecked() || ui->checkBoxCell42->isChecked() || ui->checkBoxCell43->isChecked() || ui->checkBoxCell44->isChecked() ){
        ui->line41->show();
        ui->line42->show();
        ui->line32->show();
        ui->line22->show();
        ui->line12->show();
        ui->line->show();
    }
    if( (!ui->checkBoxCell41->isChecked() && !ui->checkBoxCell42->isChecked()) && !ui->checkBoxCell43->isChecked() && !ui->checkBoxCell44->isChecked() ){
       ui->line41->hide();
    }
    if (!ui->checkBoxCell61->isChecked() && !ui->checkBoxCell62->isChecked()){
        if(!ui->checkBoxCell51->isChecked() && !ui->checkBoxCell52->isChecked())
            if(!ui->checkBoxCell41->isChecked() && !ui->checkBoxCell42->isChecked())
                if (!ui->checkBoxCell63->isChecked() && !ui->checkBoxCell64->isChecked())
                    if(!ui->checkBoxCell53->isChecked() && !ui->checkBoxCell54->isChecked())
                        if(!ui->checkBoxCell43->isChecked() && !ui->checkBoxCell44->isChecked())
                             ui->line42->hide();
    }
    //----------------line cell 31/32 ----------------------------------------------------------------------------------------------------------------------
    if( ui->checkBoxCell31->isChecked() || ui->checkBoxCell32->isChecked() ||  ui->checkBoxCell33->isChecked() || ui->checkBoxCell34->isChecked()){
        ui->line31->show();
        ui->line32->show();
        ui->line22->show();
        ui->line12->show();
        ui->line->show();
    }
    if( (!ui->checkBoxCell31->isChecked() && !ui->checkBoxCell32->isChecked()) && !ui->checkBoxCell33->isChecked() && !ui->checkBoxCell34->isChecked() ){
       ui->line31->hide();
    }
    if (!ui->checkBoxCell61->isChecked() && !ui->checkBoxCell62->isChecked()){
        if(!ui->checkBoxCell51->isChecked() && !ui->checkBoxCell52->isChecked())
            if(!ui->checkBoxCell41->isChecked() && !ui->checkBoxCell42->isChecked())
                 if(!ui->checkBoxCell31->isChecked() && !ui->checkBoxCell32->isChecked())
                     if (!ui->checkBoxCell63->isChecked() && !ui->checkBoxCell64->isChecked())
                         if(!ui->checkBoxCell53->isChecked() && !ui->checkBoxCell54->isChecked())
                             if(!ui->checkBoxCell43->isChecked() && !ui->checkBoxCell44->isChecked())
                                  if(!ui->checkBoxCell33->isChecked() && !ui->checkBoxCell34->isChecked())
                                        ui->line32->hide();
    }
    //----------------line cell 21/22 ----------------------------------------------------------------------------------------------------------------------
    if( ui->checkBoxCell21->isChecked() || ui->checkBoxCell22->isChecked() || ui->checkBoxCell23->isChecked() || ui->checkBoxCell24->isChecked()){
        ui->line21->show();
        ui->line22->show();
        ui->line12->show();
        ui->line->show();
    }
    if( (!ui->checkBoxCell21->isChecked() && !ui->checkBoxCell22->isChecked()) && (!ui->checkBoxCell23->isChecked() && !ui->checkBoxCell23->isChecked()) ){
       ui->line21->hide();
    }
    if (!ui->checkBoxCell61->isChecked() && !ui->checkBoxCell62->isChecked()){
        if(!ui->checkBoxCell51->isChecked() && !ui->checkBoxCell52->isChecked())
            if(!ui->checkBoxCell41->isChecked() && !ui->checkBoxCell42->isChecked())
                 if(!ui->checkBoxCell31->isChecked() && !ui->checkBoxCell32->isChecked())
                     if(!ui->checkBoxCell21->isChecked() && !ui->checkBoxCell22->isChecked())
                         if (!ui->checkBoxCell63->isChecked() && !ui->checkBoxCell64->isChecked())
                             if(!ui->checkBoxCell53->isChecked() && !ui->checkBoxCell54->isChecked())
                                 if(!ui->checkBoxCell43->isChecked() && !ui->checkBoxCell44->isChecked())
                                      if(!ui->checkBoxCell33->isChecked() && !ui->checkBoxCell34->isChecked())
                                          if(!ui->checkBoxCell23->isChecked() && !ui->checkBoxCell24->isChecked())
                                                ui->line22->hide();

    }
    //----------------line cell 11/12 ----------------------------------------------------------------------------------------------------------------------
    if( ui->checkBoxCell11->isChecked() || ui->checkBoxCell12->isChecked() || ui->checkBoxCell13->isChecked() || ui->checkBoxCell14->isChecked()){
        ui->line11->show();
        ui->line12->show();
        ui->line->show();
    }
    if( (!ui->checkBoxCell11->isChecked() && !ui->checkBoxCell12->isChecked()) && !ui->checkBoxCell13->isChecked() && !ui->checkBoxCell14->isChecked() ){
       ui->line11->hide();
    }
    if (!ui->checkBoxCell61->isChecked() && !ui->checkBoxCell62->isChecked()){
        if(!ui->checkBoxCell51->isChecked() && !ui->checkBoxCell52->isChecked())
            if(!ui->checkBoxCell41->isChecked() && !ui->checkBoxCell42->isChecked())
                if(!ui->checkBoxCell31->isChecked() && !ui->checkBoxCell32->isChecked())
                    if(!ui->checkBoxCell21->isChecked() && !ui->checkBoxCell22->isChecked())
                        if(!ui->checkBoxCell11->isChecked() && !ui->checkBoxCell12->isChecked())
                            if (!ui->checkBoxCell63->isChecked() && !ui->checkBoxCell64->isChecked())
                                if(!ui->checkBoxCell53->isChecked() && !ui->checkBoxCell54->isChecked())
                                    if(!ui->checkBoxCell43->isChecked() && !ui->checkBoxCell44->isChecked())
                                        if(!ui->checkBoxCell33->isChecked() && !ui->checkBoxCell34->isChecked())
                                            if(!ui->checkBoxCell23->isChecked() && !ui->checkBoxCell24->isChecked())
                                                if(!ui->checkBoxCell13->isChecked() && !ui->checkBoxCell14->isChecked()){
                                                    ui->line12->hide();
                                                    ui->line->hide();
                                                }
    }
}
//----------------change Map scale ---------------------------------------------------------------
void MapWindowLarge::changeMapRange_x_northBoundMap()
{
    int max_map = mapRange->getNorthBoundMap();
    int scale = max_map/7;
    int position_zero = 1000+scale;
    ui->y->setText(QString::number(position_zero));
    ui->y_2->setText(QString::number(position_zero +scale));
    ui->y_3->setText(QString::number(position_zero +2*scale));
    ui->y_4->setText(QString::number(position_zero +3*scale));
    ui->y_5->setText(QString::number(position_zero +4*scale));
    ui->y_6->setText(QString::number(position_zero +5*scale));

    counter_cell = 0;
    counter_center = 0;
    couter_handover = 0;
    divisor = 0;
    for (int i = 0; i<6 ; i++)
        changeCenterValue_Y(position_zero + scale*i);
    counter_cell = 12;
    counter_center = 12;
    couter_handover = 21;
    divisor = 0;
    for (int i = 0; i<6 ; i++)
        changeCenterValue_Y(position_zero + scale*i);

}

void MapWindowLarge::changeMapRange_y_northBoundMap()
{

    int max_map = mapRange->getEastBoundMap();
    int scale = max_map/5;
    ui->x->setText(QString::number(scale));
    ui->x_2->setText(QString::number(2*scale));
    ui->x_3->setText(QString::number(3*scale));
    ui->x_4->setText(QString::number(4*scale));

    counter_cell =0;
    counter_center =0;
    couter_handover =0;
    divisor = 0;
    for (int i= 1; i<=2;i++)
        changeCenterValue_X(scale*i);

    counter_cell =12;
    counter_center =12;
    couter_handover =21;
    divisor = 4;
    for (int i= 3; i<=4;i++)
        changeCenterValue_X1(scale*i, scale);
}

void MapWindowLarge::changeCenterValue_Y(int scale)
{
    divisor+=1;
    tabCenter[counter_center]->setSouthBoundary(QString::number(scale+100));
    tabCenter[counter_center++]->setNorthBoundary(QString::number(scale-100));
    tabCenter[counter_center]->setSouthBoundary(QString::number(scale+100));
    tabCenter[counter_center++]->setNorthBoundary(QString::number(scale-100));
    tabCell[counter_cell++]->setPosition_Y(QString::number(scale));
    tabCell[counter_cell++]->setPosition_Y(QString::number(scale));
    tabHandover[couter_handover]->setSouthBoundary(QString::number(scale-500));
    tabHandover[couter_handover++]->setNorthBoundary(QString::number(scale+500));
    if(couter_handover==52)
        return;
    tabHandover[couter_handover]->setSouthBoundary(QString::number(scale + (scale/divisor -4500)/2));
    tabHandover[couter_handover++]->setNorthBoundary(QString::number(scale + scale/divisor - (scale/divisor -4500)/2));
    tabHandover[couter_handover]->setSouthBoundary(QString::number(scale + (scale/divisor -4500)/2));
    tabHandover[couter_handover++]->setNorthBoundary(QString::number(scale +  scale/divisor - (scale/divisor -4500)/2));
    tabHandover[couter_handover]->setSouthBoundary(QString::number(scale + (scale/divisor -4500)/2));
    tabHandover[couter_handover++]->setNorthBoundary(QString::number(scale +  scale/divisor - (scale/divisor -4500)/2));
}

void MapWindowLarge::changeCenterValue_X(int scale)
{
    divisor+=2;

    for (int i = counter_cell; i<12 ; i+= 4){
        tabCell[i]->setPosition_X(QString::number(scale));
        tabCenter[i]->setWestBoundary(QString::number(scale-100));
        tabCenter[i]->setEastBoundary(QString::number(scale+100));
    }
    for (int i = counter_cell + 2; i<12 ; i+= 4){
        tabCell[i]->setPosition_X(QString::number(scale/divisor + scale));
        tabCenter[i]->setWestBoundary(QString::number(scale/divisor + scale -100));
        tabCenter[i]->setEastBoundary(QString::number(scale/divisor + scale -100));
    }
    counter_cell++;
    int scale_1 = scale/(divisor-1);
    for(int i = couter_handover; i<=22; i+=8){
        if(couter_handover == 0){
            tabHandover[i]->setWestBoundary(QString::number(scale + (scale_1 -4500)/2));
            tabHandover[i]->setEastBoundary(QString::number(scale + scale_1 - (scale_1-4500)/2));

            tabHandover[i+1]->setWestBoundary(QString::number(scale+1000));
            tabHandover[i+1]->setEastBoundary(QString::number(scale+2000));
            if(i<16){
            tabHandover[i+5]->setWestBoundary(QString::number(scale+1000));
            tabHandover[i+5]->setEastBoundary(QString::number(scale+2000));
            }

        }else{
            tabHandover[i]->setWestBoundary(QString::number(scale - scale_1/2 + (scale_1-4500)/2));
            tabHandover[i]->setEastBoundary(QString::number(scale + scale_1/2 - (scale_1-4500)/2));
            if (i<14){
                tabHandover[i-1]->setWestBoundary(QString::number(scale+1000));
                tabHandover[i-1]->setEastBoundary(QString::number(scale+2000));
                tabHandover[i-2]->setWestBoundary(QString::number(scale-2000));
                tabHandover[i-2]->setEastBoundary(QString::number(scale-1000));

                tabHandover[i+2]->setWestBoundary(QString::number(scale-2000));
                tabHandover[i+2]->setEastBoundary(QString::number(scale-1000));
                tabHandover[i+3]->setWestBoundary(QString::number(scale+1000));
                tabHandover[i+3]->setEastBoundary(QString::number(scale+2000));
                tabHandover[i+6]->setWestBoundary(QString::number(scale-2000));
                tabHandover[i+6]->setEastBoundary(QString::number(scale-1000));
                tabHandover[i+7]->setWestBoundary(QString::number(scale+1000));
                tabHandover[i+7]->setEastBoundary(QString::number(scale+2000));
            }
        }
    }
    couter_handover += 4;
}

void MapWindowLarge::changeCenterValue_X1(int scale,int one_scale)
{
    divisor+=2;

    for (int i = counter_cell; i<24 ; i+= 4){
        tabCell[i]->setPosition_X(QString::number(scale));
        tabCenter[i]->setWestBoundary(QString::number(scale-100));
        tabCenter[i]->setEastBoundary(QString::number(scale+100));
    }
    for (int i = counter_cell + 2; i<24 ; i+= 4){
        tabCell[i]->setPosition_X(QString::number(scale + one_scale/2));
        tabCenter[i]->setWestBoundary(QString::number(one_scale/2 + scale -100));
        tabCenter[i]->setEastBoundary(QString::number(one_scale/2 + scale +100));
    }
    counter_cell++;
    for(int i = couter_handover; i<=44; i+=8){
        if(couter_handover == 21){
            tabHandover[i]->setWestBoundary(QString::number(scale + (one_scale -4500)/2));
            tabHandover[i]->setEastBoundary(QString::number(scale + one_scale - (one_scale-4500)/2));
            tabHandover[i+1]->setWestBoundary(QString::number(scale+1000));
            tabHandover[i+1]->setEastBoundary(QString::number(scale+2000));
            if(i<36){
            tabHandover[i+5]->setWestBoundary(QString::number(scale+1000));
            tabHandover[i+5]->setEastBoundary(QString::number(scale+2000));
            }

        }else{
            tabHandover[i]->setWestBoundary(QString::number(scale - one_scale/2 + (one_scale-4500)/2));
            tabHandover[i]->setEastBoundary(QString::number(scale + one_scale/2 - (one_scale-4500)/2));
            if (i<36){
                tabHandover[i-1]->setWestBoundary(QString::number(scale+1000));
                tabHandover[i-1]->setEastBoundary(QString::number(scale+2000));
                tabHandover[i-2]->setWestBoundary(QString::number(scale-2000));
                tabHandover[i-2]->setEastBoundary(QString::number(scale-1000));

                tabHandover[i+2]->setWestBoundary(QString::number(scale-2000));
                tabHandover[i+2]->setEastBoundary(QString::number(scale-1000));
                tabHandover[i+3]->setWestBoundary(QString::number(scale+1000));
                tabHandover[i+3]->setEastBoundary(QString::number(scale+2000));
                tabHandover[i+6]->setWestBoundary(QString::number(scale-2000));
                tabHandover[i+6]->setEastBoundary(QString::number(scale-1000));
                tabHandover[i+7]->setWestBoundary(QString::number(scale+1000));
                tabHandover[i+7]->setEastBoundary(QString::number(scale+2000));
            }
        }
    }
    couter_handover += 4;
}




//--------------------Reset flag for Core Network and UE simulated-----------------------
void MapWindowLarge::resetFlags()
{
    qDebug ()<< "jestem w reset flag";
    if (mme->getSimulate_core() && sgw->getCore_network_gateway()){
        ui->checkBoxCoreNetwork->setChecked(true);
        mme->setSimulate_core(true);
        sgw->setCore_network_gateway(true);
    }else {
        ui->checkBoxCoreNetwork->setChecked(false);
        mme->setSimulate_core(false);
        sgw->setCore_network_gateway(false);
    }
    ui->checkBoxUE_simulated->setChecked(ue->getStart_ue_component());
}



//--------------------ON/OFF MME, SGW and Paging-----------------------------------------
void
MapWindowLarge::on_checkBoxCoreNetwork_clicked()
{
    if(!ui->checkBoxCoreNetwork->isChecked()){
        ui->checkBoxCoreNetwork->setText("Simulated Core Network Off");
        mme->setSimulate_core(false);
        mme->setGenerate_pagings(false);
        sgw->setCore_network_gateway(false);
        ui->frame_Core_Network->setFrameStyle(QFrame::WinPanel | QFrame::Raised);
    }else{
        ui->checkBoxCoreNetwork->setText("Simulated Core Network On");
        mme->setSimulate_core(true);
        sgw->setCore_network_gateway(true);
        ui->frame_Core_Network->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
        }
    viewSGW.setParameters(sgw);
    viewMME.setParameters(mme);

}
//----------------------ON/OFF UE Simulated -------------------------------------------
void MapWindowLarge::on_checkBoxUE_simulated_clicked()
{
    if(!ui->checkBoxUE_simulated->isChecked()){
        ui->checkBoxUE_simulated->setText(" Simulated UE Off");
        ue->setStart_ue_component(false);
        ui->frame_UE_simulated->setFrameStyle(QFrame::Panel | QFrame::Raised);
    }else{
        ui->checkBoxUE_simulated->setText(" Simulated UE On");
        ue->setStart_ue_component(true);
        ui->frame_UE_simulated->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
    }
    viewUBsim.setParameters(ue);
    viewUCtool.setParameters(ue);

}

//--------------------------OPEN MME WINDOW ---------------------------------------
void MapWindowLarge::on_lblMME_clicked(){
    viewMME.close();
    viewMME.setParameters(mme);
    viewMME.show();


}

void MapWindowLarge::on_lblSGW_clicked()
{
    viewSGW.close();
    sgw->setCore_network_gateway(mme->getSimulate_core());
    viewSGW.setParameters(sgw);
    viewSGW.show();
}
void MapWindowLarge::on_lblUCtool_clicked(){
    viewUCtool.close();
    viewUCtool.setParameters(ue);
    viewUCtool.show();
}

void MapWindowLarge::on_lblUBsim_clicked()
{
    viewUBsim.close();
    viewUBsim.setParameters(ue);
    viewUBsim.show();
}

void MapWindowLarge::on_lblChannelModel_clicked()
{
    viewCannelModel.close();
    viewCannelModel.setParameters(chmod);
    viewCannelModel.show();
}

void MapWindowLarge::on_lblIpex_clicked()
{
    viewIpex.close();
    viewIpex.setParameters(ipex, ue->getStart_ue_component());
    viewIpex.show();
}

void MapWindowLarge::on_axis_y_clicked()
{
    viewMapRange.close();
    viewMapRange.setParameters(this->mapRange, 1);
    viewMapRange.show();
    changeMapRange_x_northBoundMap();
}

void MapWindowLarge::on_axis_x_clicked()
{
    viewMapRange.close();
    viewMapRange.setParameters(mapRange, 0);
    viewMapRange.show();
    changeMapRange_y_northBoundMap();
}

bool MapWindowLarge::wasChangeonCell()
{
    if(openCell->getCell_new_name().isEmpty()){
        if(openCell->getCell().trimmed() != ui->cell->text().trimmed()){
            return true;
        }
    }else{
        if(openCell->getCell_new_name().trimmed() != ui->cell->text().trimmed())
            return true;
    }
    if (openCell->getSite().trimmed() != ui->site->text().trimmed()){
        return true;
    }else if (openCell->getPci().trimmed() != ui->pci->text().trimmed()){
        return true;
    }else if (openCell->getPosition_X().trimmed() != ui->position_X->text().trimmed()){
        return true;
    }else if (openCell->getPosition_Y().trimmed()!= ui->position_Y->text().trimmed()){
        return true;
    }else if (openCell->getEarfcnDl().trimmed() != ui->earfcnDl->text().trimmed()){
        return true;
    }else if (openCell->getTransmitPower().trimmed() != ui->transmitPower->text().trimmed()){
        return true;
    }else if (openCell->getUlNoiseAndInterference().trimmed() != ui->ulNoiseAndInterference->text().trimmed()){
        return true;
    }else{
        return false;
    }
}

bool MapWindowLarge::wasChangeonCenter()
{
    if(openCenter->getSouthBoundary().trimmed() != ui->southBoundary->text().trimmed()){
        return true;
    }else if(openCenter->getNorthBoundary().trimmed() != ui->northBoundary->text().trimmed()){
        return true;
    }else if(openCenter->getWestBoundary().trimmed() != ui->westBoundary->text().trimmed()){
        return true;
    }else if(openCenter->getEastBoundary().trimmed() != ui->eastBoundary->text().trimmed()){
        return true;
    }else{
        return false;
    }
}

bool MapWindowLarge::wasChangeonHandover()
{
    if(openHandover->getEastBoundary().trimmed() != ui->eastHandovernoundary->text().trimmed()){
        return true;
    }else if(openHandover->getNorthBoundary().trimmed() != ui->northHandovernoundary->text().trimmed()){
        return true;
    }else if(openHandover->getSouthBoundary().trimmed() != ui->soutHandovernoundary->text().trimmed()){
        return true;
    }else if(openHandover->getWestBoundary().trimmed() != ui->westHandovernoundary->text().trimmed()){
        return true;
    }else{
        return false;
    }

}


