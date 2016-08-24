#include <QDebug>
#include <QString>
#include <QCloseEvent>

#include "mapwindow.h"
#include "ui_mapwindow.h"
#include <Data/Objects/cell.h>
#include <UISystem/Windows/parameterswindow.h>

extern QString parametersFileContent;
extern QStringList parametersFileContentList;

//Temporary global variables for checkboxCells
bool tmp_chkCell11 = true;
bool tmp_chkCell12 = true;
bool tmp_chkCell21 = true;
bool tmp_chkCell22 = true;
bool tmp_chkCell31 = true;
bool tmp_chkCell32 = true;
bool tmp_chkCell41 = true;
bool tmp_chkCell42 = true;
bool tmp_chkCell51 = true;
bool tmp_chkCell52 = true;
bool tmp_chkCell61 = true;
bool tmp_chkCell62 = true;
//.........

Cell *openCell;
Center *openCenter;
Handover *openHandover;

MapWindow::MapWindow(const Project &project, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MapWindow),
    project(project)
{
    ui->setupUi(this);

    ui->mapObjectsWidget->hide();
    ui->mapObjectsWidget->removeTab(0);
    ui->mapObjectsWidget->removeTab(1);
    ui->mapObjectsWidget->removeTab(2);

    createCenter();
    createCell();

    createHandover();
    createCoreNetwork();
    createUeSimulated();
    chmod = new ChannelModel();
    ipex = new Ipgwtg();
    mapRange = new MapRange();

    anyChangesInMap = false;

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

    connect(ui->lblMME1, SIGNAL(Mouse_Pressed()), this, SLOT(on_lblMME_clicked()));
    connect(ui->lblSGW1, SIGNAL(Mouse_Pressed()), this, SLOT(on_lblSGW_clicked()));
    connect(ui->lblUCTool, SIGNAL(Mouse_Pressed()), this, SLOT(on_lblUCtool_clicked()));
    connect(ui->lblUBsim, SIGNAL(Mouse_Pressed()), this, SLOT(on_lblUBsim_clicked()));
    connect(ui->lblL1, SIGNAL(Mouse_Pressed()),this, SLOT(on_lblChannelModel_clicked()));
    connect(ui->lblIPEX, SIGNAL(Mouse_Pressed()), this, SLOT(on_lblIpex_clicked()));
    connect(ui->axis_x, SIGNAL(Mouse_Pressed()), this, SLOT(on_axis_x_clicked()));
    connect(ui->axis_y, SIGNAL(Mouse_Pressed()), this, SLOT(on_axis_y_clicked()));
    connect(ui->SaveButton,SIGNAL (clicked()), this, SLOT(save_button_clicked()));
    connect(ui->RestoreButton,SIGNAL (clicked()), this, SLOT(restore_button_clicked()));

    changeMapRange_y_northBoundMap();
    changeMapRange_x_northBoundMap();
}
void MapWindow::createHandover() {
    tabHandover.resize(21);
    tabHandover[0] = new Handover ("Handover11_12");
    tabHandover[1] = new Handover ("Handover11_21");
    tabHandover[2] = new Handover ("Handover12_21");
    tabHandover[3] = new Handover ("Handover12_22");
    tabHandover[4] = new Handover ("Handover21_22");
    tabHandover[5] = new Handover ("Handover21_31");
    tabHandover[6] = new Handover ("Handover21_32");
    tabHandover[7] = new Handover ("Handover22_32");
    tabHandover[8] = new Handover ("Handover31_32");
    tabHandover[9] = new Handover ("Handover31_41");
    tabHandover[10] = new Handover ("Handover32_41");
    tabHandover[11] = new Handover ("Handover32_42");
    tabHandover[12] = new Handover ("Handover41_42");
    tabHandover[13] = new Handover ("Handover41_51");
    tabHandover[14] = new Handover ("Handover41_52");
    tabHandover[15] = new Handover ("Handover42_52");
    tabHandover[16] = new Handover ("Handover51_52");
    tabHandover[17] = new Handover ("Handover51_61");
    tabHandover[18] = new Handover ("Handover52_61");
    tabHandover[19] = new Handover ("Handover52_62");
    tabHandover[20] = new Handover ("Handover61_62");
}

// Center11, Center12, Center21...
void MapWindow::createCenter() {

    tabCenter.resize(12);
    for(int i=0; i<12; ++i) {
        tabCenter[i] = new Center("Center"+QString::number(i/2 + 1)+QString::number(i%2 + 1));
    }
}

// cell11, cell12, cell21...
void MapWindow::createCell() {

    tabCell.resize(12);
    for(int i=0; i<12; ++i) {
        tabCell[i] = new Cell("cell"+QString::number(i/2+1) + QString::number(i%2+1));
        tabCell[i]->center = tabCenter[i];
        if(not tabCell[i]->getCell_new_name().isEmpty()) {
            tabCell[i]->chBox->setText(tabCell[i]->getCell_new_name());
        }
    }

    tabCell[0]->chBox = ui->checkBoxCell11;
    tabCell[1]->chBox = ui->checkBoxCell12;
    tabCell[2]->chBox = ui->checkBoxCell21;
    tabCell[3]->chBox = ui->checkBoxCell22;
    tabCell[4]->chBox = ui->checkBoxCell31;
    tabCell[5]->chBox = ui->checkBoxCell32;
    tabCell[6]->chBox = ui->checkBoxCell41;
    tabCell[7]->chBox = ui->checkBoxCell42;
    tabCell[8]->chBox = ui->checkBoxCell51;
    tabCell[9]->chBox = ui->checkBoxCell52;
    tabCell[10]->chBox = ui->checkBoxCell61;
    tabCell[11]->chBox = ui->checkBoxCell62;
}

void MapWindow::createCoreNetwork()
{
    mme = new Mme;
    sgw = new Sgw;

    ui->checkBoxCoreNetwork->setChecked(mme->getSimulate_core());
    on_checkBoxCoreNetwork_clicked();
}

void MapWindow::createUeSimulated()
{
    ue = new Ue();
    ui->checkBoxUE_simulated->setChecked(ue->getStart_ue_component());
    on_checkBoxUE_simulated_clicked();
}

void MapWindow::closeEvent(QCloseEvent *event)
{
    if (!anyChangesInMap) {
        this->close();
        event->accept();
        return;
    }
    msgExit.setText("The document has been modified.");
    msgExit.setInformativeText("Do you want to save your changes?");
    msgExit.setIcon(QMessageBox::Question);
    msgExit.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgExit.setDefaultButton(QMessageBox::Save);

    int ret = msgExit.exec();
    QString new_parametersFileContent;

    switch (ret) {
    case QMessageBox::Save:
        // Save was clicked
        anyChangesInMap=true;
        parametersFileContentList=this->generateParams();

        // move changes to the global QString
        new_parametersFileContent="";
        for(int i=0; i<parametersFileContentList.size(); i++){
            new_parametersFileContent+=parametersFileContentList[i];
        }
        if(new_parametersFileContent!=parametersFileContent){
            parametersFileContent=new_parametersFileContent;
        }

        event->accept();
        saveCellsCheckboxes();
        break;
    case QMessageBox::Discard:
        // Don't Save was clicked
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

MapWindow::~MapWindow()
{
    delete ui;
}
//--------------Show function  ---------------
void MapWindow::showCellTabWiget()
{
    ui->mapObjectsWidget->insertTab(0,ui->tab, (openCell->getCell_new_name().isEmpty()) ? openCell->getCell() : openCell->getCell_new_name());
    ui->mapObjectsWidget->removeTab(1);
    ui->mapObjectsWidget->removeTab(2);
    ui->mapObjectsWidget->show();

}
void MapWindow::showCenterTabWiget()
{
    ui->mapObjectsWidget->insertTab(0,ui->tab_2, ((openCenter->getNew_name_area().isEmpty()) ? openCenter->getArea() : openCenter->getNew_name_area()));
    ui->mapObjectsWidget->removeTab(1);
    ui->mapObjectsWidget->removeTab(2);
    ui->mapObjectsWidget->show();
}
void MapWindow::showHandoverTabWiget()
{
    ui->mapObjectsWidget->insertTab(0,ui->tab_3, openHandover->getArea());
    ui->mapObjectsWidget->removeTab(1);
    ui->mapObjectsWidget->removeTab(2);
    ui->mapObjectsWidget->show();
}
//----------------- Myfunction -----------------

QStringList MapWindow::generateParams(){

    int number_of_cell =12;      //12
    int number_of_Center=12;       //12
    int number_of_Handover=21;     //21
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

    return outputList;
}

QString MapWindow::convertBoolToText(bool value){
    QString result;
    if (value==true)
        return result= "true";
    else return result = "false";

}

//------------Fill functions------------------------------------------------------
void MapWindow::fillParams(Center *object){
   ui->mapObjectsWidget->setTabText(1, object->getArea());
   ui->eastBoundary->setText(object->getEastBoundary());
   ui->westBoundary->setText(object->getWestBoundary());
   ui->southBoundary->setText(object->getSouthBoundary());
   ui->northBoundary->setText(object->getNorthBoundary());
   showCenterTabWiget();
}
void MapWindow::fillParams(Handover *object){

   ui->eastHandovernoundary->setText(object->getEastBoundary());
   ui->westHandovernoundary->setText(object->getWestBoundary());
   ui->soutHandovernoundary->setText(object->getSouthBoundary());
   ui->northHandovernoundary->setText(object->getNorthBoundary());
   showHandoverTabWiget();
}
void MapWindow::fillParams(Cell *object){
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
void MapWindow::saveParams(Center *object){
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
    anyChangesInMap = true;
}
void MapWindow::saveParams(Handover *object){
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
    anyChangesInMap = true;
}
void MapWindow::saveParams(Cell *object){
    listErrors.clear();
    if (validationNameCell(ui->cell->text())){
 //       object->setCell(ui->cell->text());
        object->setCell_new_name(ui->cell->text());
        object->chBox->setText(ui->cell->text());                                       //change name CheckBox
        object->center->setNew_name_area("center" + ui->cell->text().remove(QString("cell")));   //change name Center
        ui->mapObjectsWidget->setTabText( 0 , ui->cell->text());                               //change naem tabWiget
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
    anyChangesInMap = true;
}
//--------------------------------------------------------------------------
bool MapWindow::validationPosition(QString textForValidation){
        QRegExp rx("^\\d\\d?\\d?\\d?\\d?$");
        if (rx.indexIn(textForValidation) <0){
            return false;
        }else return true;
}
bool MapWindow::validationTransmitPower(QString textForValidation){
     QRegExp rx("^-?\\d\\d?\\d?$");
    if (rx.indexIn(textForValidation) <0){
                return false;
    }else return true;
}

bool MapWindow::validationNameCell(QString textForValidation)
{
    if( openCell->getCell() == textForValidation)
        return true;
    for (int i = 0; i< 12; i++){
        if(textForValidation == tabCell[i]->getCell())
           return false;
    }
    return true;
}

void MapWindow::showMessageError(QList<QString> listErrors){
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
//-----------------------SAVE/RESTORE----------------------------
void MapWindow::save_button_clicked()
{
    QString new_parametersFileContent;
    parametersFileContentList=this->generateParams();

    // move changes to the global QString
    new_parametersFileContent.clear();
    for(int i=0; i<parametersFileContentList.size(); i++){
        new_parametersFileContent+=parametersFileContentList[i];
    }
    if(new_parametersFileContent!=parametersFileContent){
        parametersFileContent=new_parametersFileContent;
    }
    saveCellsCheckboxes();
    anyChangesInMap = false;
    this->close();
}
void MapWindow::restore_button_clicked()
{
    msgBox.setText("Are you sure?");
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    int restoreDefault = msgBox.exec();
    if (restoreDefault==QMessageBox::Yes){
        parametersFileContentList=this->generateParams();
    }
}

//---------------------------------------------------------------------------

void MapWindow::on_Center61_clicked()
{
   openCenter = tabCenter[10];
   openCell = NULL;
   openHandover = NULL;
   fillParams(tabCenter[10]);
}
void MapWindow::on_Center62_clicked()
{
    openCenter = tabCenter[11];
    openCell = NULL;
    openHandover = NULL;
    fillParams(tabCenter[11]);
}
void MapWindow::on_Center52_clicked()
{
    openCenter = tabCenter[9];
    openCell = NULL;
    openHandover = NULL;
    fillParams(tabCenter[9]);
}
void MapWindow::on_Center51_clicked()
{
    openCenter = tabCenter[8];
    openCell = NULL;
    openHandover = NULL;
    fillParams(tabCenter[8]);
}
void MapWindow::on_Center42_clicked()
{
    openCenter = tabCenter[7];
    openCell = NULL;
    openHandover = NULL;
    fillParams(tabCenter[7]);
}
void MapWindow::on_Center41_clicked()
{
    openCenter = tabCenter[6];
    openCell = NULL;
    openHandover = NULL;
    fillParams(tabCenter[6]);
}
void MapWindow::on_Center32_clicked()
{
    openCenter = tabCenter[5];
    openCell = NULL;
    openHandover = NULL;
    fillParams(tabCenter[5]);
}
void MapWindow::on_Center31_clicked()
{
    openCenter = tabCenter[4];
    openCell = NULL;
    openHandover = NULL;
    fillParams(tabCenter[4]);
}
void MapWindow::on_Center22_clicked()
{
    openCenter = tabCenter[3];
    openCell = NULL;
    openHandover = NULL;
    fillParams(tabCenter[3]);
}
void MapWindow::on_Center21_clicked()
{
    openCenter = tabCenter[2];
    openCell = NULL;
    openHandover = NULL;
    fillParams(tabCenter[2]);
}
void MapWindow::on_Center12_clicked()
{
    openCenter = tabCenter[1];
    openCell = NULL;
    openHandover = NULL;
    fillParams(tabCenter[1]);
}
void MapWindow::on_Center11_clicked()
{
    openCenter = tabCenter[0];
    openCell = NULL;
    openHandover = NULL;
    fillParams(tabCenter[0]);
}

//-----------Handover funcion-------------------------

void MapWindow::on_Handover61_62_clicked()
{
    openHandover = tabHandover[20];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[20]);
}

void MapWindow::on_Handover51_61_clicked()
{
    openHandover = tabHandover[17];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[17]);
}
void MapWindow::on_Handover52_61_clicked()
{
    openHandover = tabHandover[18];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[18]);
}

void MapWindow::on_Handover52_62_clicked()
{
    openHandover = tabHandover[19];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[19]);
}

void MapWindow::on_Handover51_52_clicked()
{
    openHandover = tabHandover[16];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[16]);
}

void MapWindow::on_Handover41_51_clicked()
{
    openHandover = tabHandover[13];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[13]);
}

void MapWindow::on_Handover41_52_clicked()
{
    openHandover = tabHandover[14];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[14]);
}

void MapWindow::on_Handover42_52_clicked()
{
    openHandover = tabHandover[15];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[15]);
}

void MapWindow::on_Handover41_42_clicked()
{
    openHandover = tabHandover[12];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[12]);
}

void MapWindow::on_Handover31_41_clicked()
{
    openHandover = tabHandover[9];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[9]);
}

void MapWindow::on_Handover32_41_clicked()
{
    openHandover = tabHandover[10];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[10]);
}

void MapWindow::on_Handover32_42_clicked()
{
    openHandover = tabHandover[11];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[11]);
}

void MapWindow::on_Handover31_32_clicked()
{
    openHandover = tabHandover[8];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[8]);
}

void MapWindow::on_Handover21_31_clicked()
{
    openHandover = tabHandover[5];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[5]);
}

void MapWindow::on_Handover21_32_clicked()
{
    openHandover = tabHandover[6];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[6]);
}

void MapWindow::on_Handover22_32_clicked()
{
    openHandover = tabHandover[7];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[7]);
}

void MapWindow::on_Handover21_22_clicked()
{
    openHandover = tabHandover[4];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[4]);
}

void MapWindow::on_Handover11_21_clicked()
{
    openHandover = tabHandover[1];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[1]);
}

void MapWindow::on_Handover12_21_clicked()
{
    openHandover = tabHandover[2];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[2]);
}

void MapWindow::on_Handover12_22_clicked()
{
    openHandover = tabHandover[3];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[3]);
}

void MapWindow::on_Handover11_12_clicked()
{
    openHandover = tabHandover[0];
    openCell = NULL;
    openCenter = NULL;
    fillParams(tabHandover[0]);
}

//-----------Cell funcion ----------------------------


void MapWindow::on_cell61_clicked()
{
    openCell= tabCell[10];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[10]);

}
void MapWindow::on_cell62_clicked()
{
    openCell= tabCell[11];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[11]);
}
void MapWindow::on_cell51_clicked()
{
    openCell= tabCell[8];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[8]);

}
void MapWindow::on_cell52_clicked()
{
    openCell= tabCell[9];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[9]);
}
void MapWindow::on_cell41_clicked()
{
    openCell= tabCell[6];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[6]);

}
void MapWindow::on_cell42_clicked()
{
    openCell= tabCell[7];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[7]);
}
void MapWindow::on_cell31_clicked()
{
    openCell= tabCell[4];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[4]);

}
void MapWindow::on_cell32_clicked()
{
    openCell= tabCell[5];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[5]);
}
void MapWindow::on_cell21_clicked()
{
    openCell= tabCell[2];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[2]);

}
void MapWindow::on_cell22_clicked()
{
    openCell= tabCell[3];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[3]);
}
void MapWindow::on_cell11_clicked()
{
    openCell= tabCell[0];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[0]);

}
void MapWindow::on_cell12_clicked()
{
    openCell= tabCell[1];
    openHandover = NULL;
    openCenter = NULL;
    fillParams(tabCell[1]);
}

//----------------------edit parameters----------------

void MapWindow::on_cell_returnPressed()
{
    saveParams(openCell);
}

void MapWindow::on_site_returnPressed()
{
    saveParams(openCell);
}

void MapWindow::on_position_X_returnPressed()
{
  saveParams(openCell);
}

void MapWindow::on_pci_returnPressed()
{
    saveParams(openCell);
}

void MapWindow::on_position_Y_returnPressed()
{
    saveParams(openCell);
}

void MapWindow::on_earfcnDl_returnPressed()
{
    saveParams(openCell);
}

void MapWindow::on_transmitPower_returnPressed()
{
    saveParams(openCell);
}

void MapWindow::on_ulNoiseAndInterference_returnPressed()
{
    saveParams(openCell);
}

void MapWindow::on_pbSetCellParams_clicked()
{
   ui->mapObjectsWidget->hide();
   saveParams(openCell);
}
//------------------------end edit parameters ------------------------------------
void MapWindow::on_southBoundary_returnPressed()
{

    saveParams(openCenter);
}

void MapWindow::on_northBoundary_returnPressed()
{
    saveParams(openCenter);
}

void MapWindow::on_westBoundary_returnPressed()
{
    saveParams(openCenter);
}

void MapWindow::on_eastBoundary_returnPressed()
{
    saveParams(openCenter);
}

void MapWindow::on_pbSetCenterParams_clicked()
{
    ui->mapObjectsWidget->hide();
    saveParams(openCenter);
}
//------------------------------------------------------------------------------------

void MapWindow::on_soutHandovernoundary_returnPressed()
{
    saveParams(openHandover);
}

void MapWindow::on_northHandovernoundary_returnPressed()
{
    saveParams(openHandover);
}

void MapWindow::on_westHandovernoundary_returnPressed()
{
    saveParams(openHandover);
}

void MapWindow::on_eastHandovernoundary_returnPressed()
{
    saveParams(openHandover);
}

void MapWindow::on_pbsetHandoverParams_clicked()
{
    saveParams(openHandover);
    ui->mapObjectsWidget->hide();
}
//--------------on/off cell ---------------------------------
void MapWindow::on_checkBoxCell61_clicked()
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
    ui->mapObjectsWidget->hide();
}
void MapWindow::on_checkBoxCell62_clicked()
{

    if (!ui->checkBoxCell62->isChecked())
    {
        ui->cell62->setEnabled(false);
        ui->Center62->setEnabled(false);
        ui->Handover61_62->setEnabled(false);
        ui->Handover52_62->setEnabled(false);
    }else{
        ui->cell62->setEnabled(true);
        ui->Center62->setEnabled(true);
        if(ui->cell61->isEnabled())
            ui->Handover61_62->setEnabled(true);
        if(ui->cell52->isEnabled())
            ui->Handover52_62->setEnabled(true);
    }
     showActiveLine();
     ui->mapObjectsWidget->hide();
}
void MapWindow::on_checkBoxCell51_clicked()
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
    ui->mapObjectsWidget->hide();
}
void MapWindow::on_checkBoxCell52_clicked()
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
    }
    showActiveLine();
    ui->mapObjectsWidget->hide();
}
void MapWindow::on_checkBoxCell41_clicked()
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
    ui->mapObjectsWidget->hide();
}
void MapWindow::on_checkBoxCell42_clicked()
{
    if (!ui->checkBoxCell42->isChecked() )
    {
        ui->cell42->setEnabled(false);
        ui->Center42->setEnabled(false);
        ui->Handover42_52->setEnabled(false);
        ui->Handover32_42->setEnabled(false);
        ui->Handover41_42->setEnabled(false);
    }else{
        ui->cell42->setEnabled(true);
        ui->Center42->setEnabled(true);
        if(ui->cell52->isEnabled())
            ui->Handover42_52->setEnabled(true);
        if(ui->cell32->isEnabled())
            ui->Handover32_42->setEnabled(true);
        if(ui->cell41->isEnabled())
            ui->Handover41_42->setEnabled(true);
    }
    showActiveLine();
    ui->mapObjectsWidget->hide();
}
void MapWindow::on_checkBoxCell31_clicked()
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
    ui->mapObjectsWidget->hide();
}
void MapWindow::on_checkBoxCell32_clicked()
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
    }
    showActiveLine();
    ui->mapObjectsWidget->hide();
}
void MapWindow::on_checkBoxCell21_clicked()
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
    ui->mapObjectsWidget->hide();
}
void MapWindow::on_checkBoxCell22_clicked()
{
    if (!ui->checkBoxCell22->isChecked() )
    {
        ui->cell22->setEnabled(false);
        ui->Center22->setEnabled(false);
        ui->Handover22_32->setEnabled(false);
        ui->Handover12_22->setEnabled(false);
        ui->Handover21_22->setEnabled(false);
    }else{
        ui->cell22->setEnabled(true);
        ui->Center22->setEnabled(true);
        if(ui->cell32->isEnabled())
            ui->Handover22_32->setEnabled(true);
        if(ui->cell12->isEnabled())
            ui->Handover12_22->setEnabled(true);
        if(ui->cell21->isEnabled())
            ui->Handover21_22->setEnabled(true);
    }
    showActiveLine();
    ui->mapObjectsWidget->hide();
}
void MapWindow::on_checkBoxCell11_clicked()
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
    ui->mapObjectsWidget->hide();
}
void MapWindow::on_checkBoxCell12_clicked()
{
    if (!ui->checkBoxCell12->isChecked() )
    {
        ui->cell12->setEnabled(false);
        ui->Center12->setEnabled(false);
        ui->Handover12_21->setEnabled(false);
        ui->Handover12_22->setEnabled(false);
        ui->Handover11_12->setEnabled((false));
    }else{
        ui->cell12->setEnabled((true));
        ui->Center12->setEnabled((true));
        if(ui->cell21->isEnabled())
            ui->Handover12_21->setEnabled((true));
        if(ui->cell22->isEnabled())
            ui->Handover12_22->setEnabled((true));
        if(ui->cell11->isEnabled())
            ui->Handover11_12->setEnabled((true));
    }
    showActiveLine();
    ui->mapObjectsWidget->hide();
}

void MapWindow::Mouse_Pressed()
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
                   ui->mapObjectsWidget->hide();
                   openCell = NULL;
                   openCenter = NULL;
                   openHandover = NULL;
                    break;
                 case QMessageBox::Discard:
                       ui->mapObjectsWidget->hide();
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
    ui->mapObjectsWidget->hide();
    openCell=NULL;
}

if(openCenter!=NULL && wasChangeonCenter())
{
    int ret = msgBox.exec();

    switch (ret) {
        case QMessageBox::Save:
                   saveParams(openCenter);
                   ui->mapObjectsWidget->hide();
                   openCell = NULL;
                   openCenter = NULL;
                   openHandover = NULL;
                    break;
                 case QMessageBox::Discard:
                       ui->mapObjectsWidget->hide();
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
    ui->mapObjectsWidget->hide();
    openCenter=NULL;
}

if(openHandover !=NULL && wasChangeonHandover())
{
    int ret = msgBox.exec();

    switch (ret) {
        case QMessageBox::Save:
                   saveParams(openHandover);
                   ui->mapObjectsWidget->hide();
                   openCell = NULL;
                   openCenter = NULL;
                   openHandover = NULL;
                    break;
                 case QMessageBox::Discard:
                       ui->mapObjectsWidget->hide();
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
    ui->mapObjectsWidget->hide();
    openHandover=NULL;
}


}
//end of mouse pressed

void MapWindow::on_pbRestoreCell_clicked()
{
    openCell->resetParams();
    fillParams(openCell);
}

void MapWindow::on_pbRestoreHandover_clicked()
{
    openHandover->resetParams();
    fillParams(openHandover);
}


void MapWindow::on_pbRestoreCenter_clicked()
{
     openCenter->resetParams();
     fillParams(openCenter);
}

void MapWindow::showActiveLine()
{
    //----------------line cell 61/62 ----------------------------------------------------------------------------------------------------------------------
    if( (ui->checkBoxCell61->isChecked() || ui->checkBoxCell62->isChecked()) ){
        ui->line61->show();
        ui->line62->show();
        ui->line52->show();
        ui->line42->show();
        ui->line32->show();
        ui->line22->show();
        ui->line12->show();
        ui->line->show();
    }
    if( (!ui->checkBoxCell61->isChecked() && !ui->checkBoxCell62->isChecked()) ){
        ui->line62->hide();
        ui->line61->hide();
    }
    //----------------line cell 51/52 ----------------------------------------------------------------------------------------------------------------------
    if(ui->checkBoxCell51->isChecked() || ui->checkBoxCell52->isChecked()){
        ui->line51->show();
        ui->line52->show();
        ui->line42->show();
        ui->line32->show();
        ui->line22->show();
        ui->line12->show();
        ui->line->show();
    }
    if( (!ui->checkBoxCell51->isChecked() && !ui->checkBoxCell52->isChecked()) ){
        ui->line51->hide();
    }
    if (!ui->checkBoxCell61->isChecked() && !ui->checkBoxCell62->isChecked()){
        if(!ui->checkBoxCell51->isChecked() && !ui->checkBoxCell52->isChecked())
            ui->line52->hide();
    }
    //----------------line cell 41/42 ----------------------------------------------------------------------------------------------------------------------
    if( ui->checkBoxCell41->isChecked() || ui->checkBoxCell42->isChecked()){
        ui->line41->show();
        ui->line42->show();
        ui->line32->show();
        ui->line22->show();
        ui->line12->show();
        ui->line->show();
    }
    if( (!ui->checkBoxCell41->isChecked() && !ui->checkBoxCell42->isChecked()) ){
       ui->line41->hide();
    }
    if (!ui->checkBoxCell61->isChecked() && !ui->checkBoxCell62->isChecked()){
        if(!ui->checkBoxCell51->isChecked() && !ui->checkBoxCell52->isChecked())
            if(!ui->checkBoxCell41->isChecked() && !ui->checkBoxCell42->isChecked())
                ui->line42->hide();
    }
    //----------------line cell 31/32 ----------------------------------------------------------------------------------------------------------------------
    if( ui->checkBoxCell31->isChecked() || ui->checkBoxCell32->isChecked()){
        ui->line31->show();
        ui->line32->show();
        ui->line22->show();
        ui->line12->show();
        ui->line->show();
    }
    if( (!ui->checkBoxCell31->isChecked() && !ui->checkBoxCell32->isChecked()) ){
       ui->line31->hide();
    }
    if (!ui->checkBoxCell61->isChecked() && !ui->checkBoxCell62->isChecked()){
        if(!ui->checkBoxCell51->isChecked() && !ui->checkBoxCell52->isChecked())
            if(!ui->checkBoxCell41->isChecked() && !ui->checkBoxCell42->isChecked())
                 if(!ui->checkBoxCell31->isChecked() && !ui->checkBoxCell32->isChecked())
                     ui->line32->hide();
    }
    //----------------line cell 21/22 ----------------------------------------------------------------------------------------------------------------------
    if( ui->checkBoxCell21->isChecked() || ui->checkBoxCell22->isChecked()){
        ui->line21->show();
        ui->line22->show();
        ui->line12->show();
        ui->line->show();
    }
    if( (!ui->checkBoxCell21->isChecked() && !ui->checkBoxCell22->isChecked()) ){
       ui->line21->hide();
    }
    if (!ui->checkBoxCell61->isChecked() && !ui->checkBoxCell62->isChecked()){
        if(!ui->checkBoxCell51->isChecked() && !ui->checkBoxCell52->isChecked())
            if(!ui->checkBoxCell41->isChecked() && !ui->checkBoxCell42->isChecked())
                 if(!ui->checkBoxCell31->isChecked() && !ui->checkBoxCell32->isChecked())
                     if(!ui->checkBoxCell21->isChecked() && !ui->checkBoxCell22->isChecked())
                        ui->line22->hide();
    }
    //----------------line cell 11/12 ----------------------------------------------------------------------------------------------------------------------
    if( ui->checkBoxCell11->isChecked() || ui->checkBoxCell12->isChecked()){
        ui->line11->show();
        ui->line12->show();
        ui->line->show();
    }
    if( (!ui->checkBoxCell11->isChecked() && !ui->checkBoxCell12->isChecked()) ){
       ui->line11->hide();
    }
    if (!ui->checkBoxCell61->isChecked() && !ui->checkBoxCell62->isChecked()){
        if(!ui->checkBoxCell51->isChecked() && !ui->checkBoxCell52->isChecked())
            if(!ui->checkBoxCell41->isChecked() && !ui->checkBoxCell42->isChecked())
                 if(!ui->checkBoxCell31->isChecked() && !ui->checkBoxCell32->isChecked())
                     if(!ui->checkBoxCell21->isChecked() && !ui->checkBoxCell22->isChecked())
                        if(!ui->checkBoxCell11->isChecked() && !ui->checkBoxCell12->isChecked()){
                            ui->line12->hide();
                            ui->line->hide();
                        }

    }
}
//----------------change Map scale ---------------------------------------------------------------
void MapWindow::changeMapRange_x_northBoundMap()
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

}

void MapWindow::changeMapRange_y_northBoundMap()
{
    int max_map = this->mapRange->getEastBoundMap();
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
}

void MapWindow::saveCellsCheckboxes()
{
    tmp_chkCell11 = ui->checkBoxCell11->isChecked();
    tmp_chkCell12 = ui->checkBoxCell12->isChecked();
    tmp_chkCell21 = ui->checkBoxCell21->isChecked();
    tmp_chkCell22 = ui->checkBoxCell22->isChecked();
    tmp_chkCell31 = ui->checkBoxCell31->isChecked();
    tmp_chkCell32 = ui->checkBoxCell32->isChecked();
    tmp_chkCell41 = ui->checkBoxCell41->isChecked();
    tmp_chkCell42 = ui->checkBoxCell42->isChecked();
    tmp_chkCell51 = ui->checkBoxCell51->isChecked();
    tmp_chkCell52 = ui->checkBoxCell52->isChecked();
    tmp_chkCell61 = ui->checkBoxCell61->isChecked();
    tmp_chkCell62 = ui->checkBoxCell62->isChecked();
}

void MapWindow::changeCenterValue_Y(int scale)
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
    if(couter_handover==21)
        return;
    tabHandover[couter_handover]->setSouthBoundary(QString::number(scale + (scale/divisor -4500)/2));
    tabHandover[couter_handover++]->setNorthBoundary(QString::number(scale + scale/divisor - (scale/divisor -4500)/2));
    tabHandover[couter_handover]->setSouthBoundary(QString::number(scale + (scale/divisor -4500)/2));
    tabHandover[couter_handover++]->setNorthBoundary(QString::number(scale +  scale/divisor - (scale/divisor -4500)/2));
    tabHandover[couter_handover]->setSouthBoundary(QString::number(scale + (scale/divisor -4500)/2));
    tabHandover[couter_handover++]->setNorthBoundary(QString::number(scale +  scale/divisor - (scale/divisor -4500)/2));
}

void MapWindow::changeCenterValue_X(int scale)
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





//--------------------Reset flag for Core Network and UE simulated-----------------------
void MapWindow::resetFlags()
{
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
void MapWindow::on_checkBoxCoreNetwork_clicked()
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
void MapWindow::on_checkBoxUE_simulated_clicked()
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
void MapWindow::on_lblMME_clicked(){
    viewMME.close();
    viewMME.setParameters(mme);
    viewMME.set_checkboxactive(this->ui->checkBoxCoreNetwork->isChecked());
    viewMME.show();
}

void MapWindow::on_lblSGW_clicked()
{
    viewSGW.close();
    sgw->setCore_network_gateway(mme->getSimulate_core());
    viewSGW.setParameters(sgw);
    viewSGW.set_checkboxactive(this->ui->checkBoxCoreNetwork->isChecked());
    viewSGW.show();
}
void MapWindow::on_lblUCtool_clicked(){
    viewUCtool.close();
    viewUCtool.setParameters(ue);
    viewUCtool.set_checkboxactive(this->ui->checkBoxUE_simulated->isChecked());
    viewUCtool.show();
}

void MapWindow::on_lblUBsim_clicked()
{
    viewUBsim.close();
    viewUBsim.setParameters(ue);
    viewUBsim.set_checkboxactive(this->ui->checkBoxUE_simulated->isChecked());
    viewUBsim.show();
}

void MapWindow::on_lblChannelModel_clicked()
{
    viewCannelModel.close();
    viewCannelModel.setParameters(chmod);
    viewCannelModel.show();
}

void MapWindow::on_lblIpex_clicked()
{
    emit SpawnWindow_Ipex(project.name);
}

void MapWindow::on_axis_y_clicked()
{
    viewMapRange.close();
    viewMapRange.setParameters(mapRange, 1);
    viewMapRange.show();
    changeMapRange_x_northBoundMap();
}

void MapWindow::on_axis_x_clicked()
{
    viewMapRange.close();
    viewMapRange.setParameters(mapRange, 0);
    viewMapRange.show();
    changeMapRange_y_northBoundMap();
}

bool MapWindow::wasChangeonCell()
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

bool MapWindow::wasChangeonCenter()
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

bool MapWindow::wasChangeonHandover()
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
