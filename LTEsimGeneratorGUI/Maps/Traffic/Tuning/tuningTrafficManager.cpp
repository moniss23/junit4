#include <QDoubleValidator>

#include "tuningTrafficManager.h"
#include "ui_tuningtrafficform.h"

bool tmp_areaChecked;

//Saved structure of chosen tuning parameters
QStringList tuningParametersContentList;

TuningTrafficManager::TuningTrafficManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TuningTrafficForm)
{
    ui->setupUi(this);
    this->setWindowTitle("Tuning traffic");
    setFixedSize(sizeHint());
    setParametersValidation();
    CSSaveParameters = QVector<TuningTrafficData::CSParameters* >();
    PSSaveParameters = QVector<TuningTrafficData::PSParameters* >();
    areaSaveParameters = QVector<TuningTrafficData::Areas* >();

    CSSaveParameters.push_back(new TuningTrafficData::CSParameters());
    PSSaveParameters.push_back(new TuningTrafficData::PSParameters());
    areaSaveParameters.push_back(new TuningTrafficData::Areas());

    cancelClicked = false;
    saveClicked = false;
}

TuningTrafficManager::~TuningTrafficManager()
{
    delete ui;
    for (int i = 0; i < CSSaveParameters.size(); ++i){
        delete CSSaveParameters[i];
    }
    CSSaveParameters.clear();

    for (int i = 0; i < PSSaveParameters.size(); ++i){
        delete PSSaveParameters[i];
    }
    PSSaveParameters.clear();

    for (int i = 0; i < areaSaveParameters.size(); ++i){
        delete areaSaveParameters[i];
    }
    areaSaveParameters.clear();
}

void TuningTrafficManager::setParameters()
{
    for (int i = 0; i < CSSaveParameters.size(); ++i)
    {
        if (!isinCsCombobox(CSSaveParameters[i]->cs_name)){
            ui->cs_combobox->addItem(CSSaveParameters[i]->cs_name);
        }
        ui->tet_call_intensity->setText(CSSaveParameters[i]->call_intensity);
        ui->tet_call_duration->setText(CSSaveParameters[i]->call_duration);
        ui->tet_recovery_start_interval->setText(CSSaveParameters[i]->recovery_start_interval);
    }
    for (int i = 0; i < PSSaveParameters.size(); ++i)
    {
        if (!isInPsCombobox(PSSaveParameters[i]->ps_name)){
            ui->ps_combobox->addItem(PSSaveParameters[i]->ps_name);
        }
        ui->tet_ps_duration->setText(PSSaveParameters[i]->ps_duration);
        ui->tet_ps_intensity->setText(PSSaveParameters[i]->ps_intensity);
    }
    for (int i = 0; i < areaSaveParameters.size(); ++i)
    {
        if (!isInAreaCombobox(areaSaveParameters[i]->area_name) && areaSaveParameters[i]->area_name != ""){
            ui->area_combobox->addItem(areaSaveParameters[i]->area_name);
        }
        ui->tet_speed->setText(areaSaveParameters[i]->speed);
        ui->tet_granularity->setText(areaSaveParameters[i]->granularity);
    }
    ui->cs_combobox->setCurrentIndex(tuningTrafficData->get_csBehaviorIndex());
    ui->ps_combobox->setCurrentIndex(tuningTrafficData->get_psBehaviorIndex());
    ui->area_combobox->setCurrentIndex(tuningTrafficData->get_AreaIndex());
    ui->chb_area->setChecked(tmp_areaChecked);
}


void TuningTrafficManager::SaveAll()
{
    tuningTrafficData->set_csBehaviorIndex(0);
    tuningTrafficData->set_psBehaviorIndex(0);
    tuningTrafficData->set_AreaIndex(0);
    tmp_areaChecked = ui->chb_area->isChecked();

    copyCSParams(tuningTrafficData->getCSParamGroup());
    copyPSParams(tuningTrafficData->getPSParamGroup());
    copyAreaParams(tuningTrafficData->getAreaGroup());
}

void TuningTrafficManager::setParametersValidation()
{
    ui->tet_ps_intensity->setValidator(new QDoubleValidator(0, 100, 3, this));
    ui->tet_recovery_start_interval->setValidator(new QDoubleValidator(0, 100, 3, this));
    ui->tet_ps_duration->setValidator(new QDoubleValidator(0, 100, 3, this));
    ui->tet_call_duration->setValidator(new QDoubleValidator(0, 100, 3, this));
    ui->tet_call_intensity->setValidator(new QDoubleValidator(0, 100, 3, this));
    ui->tet_granularity->setValidator(new QIntValidator(0,100,this));
    ui->tet_speed->setValidator(new QIntValidator(0, 100, this));
}

void TuningTrafficManager::copyCSParams(const QVector<TuningTrafficData::CSParameters *> &value)
{
    for (int i = 0; i < value.size(); ++i) {
        CSSaveParameters[i]->call_duration = value[i]->call_duration;
        CSSaveParameters[i]->call_intensity = value[i]->call_intensity;
        CSSaveParameters[i]->cs_name = value[i]->cs_name;
        CSSaveParameters[i]->recovery_start_interval = value[i]->recovery_start_interval;
    }
}

void TuningTrafficManager::copyPSParams(const QVector<TuningTrafficData::PSParameters *> &value)
{
    for (int i = 0; i < value.size(); ++i) {
        PSSaveParameters[i]->ps_duration = value[i]->ps_duration;
        PSSaveParameters[i]->ps_intensity = value[i]->ps_intensity;
        PSSaveParameters[i]->ps_name = value[i]->ps_name;
    }
}

void TuningTrafficManager::copyAreaParams(const QVector<TuningTrafficData::Areas *> &value)
{
    for (int i = 0; i < value.size(); ++i) {
        areaSaveParameters[i]->speed = value[i]->speed;
        areaSaveParameters[i]->granularity = value[i]->granularity;
        areaSaveParameters[i]->area_name = value[i]->area_name;
    }
}

void TuningTrafficManager::readTemporaryParameters(TuningTrafficData* tuningTrafficData)
{
    this->tuningTrafficData = tuningTrafficData;
    for (int i = 0; i < this->tuningTrafficData->getCSParamGroup().size(); ++i) {
        if (!isinCsCombobox(tuningTrafficData->getCs_Name(i))){
            ui->cs_combobox->addItem(this->tuningTrafficData->getCs_Name(i));
        }
        ui->tet_call_intensity->setText(tuningTrafficData->getCall_intensity(i));
        ui->tet_call_duration->setText(tuningTrafficData->getCall_duration(i));
        ui->tet_recovery_start_interval->setText(tuningTrafficData->getRecovery_start_interval(i));
    }
    for (int i = 0; i < this->tuningTrafficData->getPSParamGroup().size(); ++i) {
        if (!isInPsCombobox(tuningTrafficData->getPs_Name(i))){
            ui->ps_combobox->addItem(this->tuningTrafficData->getPs_Name(i));
        }
        ui->tet_ps_duration->setText(tuningTrafficData->getPs_duration(i));
        ui->tet_ps_intensity->setText(tuningTrafficData->getPS_intensity(i));
    }
    for (int i = 0; i < this->tuningTrafficData->getAreaGroup().size(); ++i) {
        if (!isInAreaCombobox(tuningTrafficData->getArea_name(i)) && tuningTrafficData->getArea_name(i) != ""){
            ui->area_combobox->addItem(this->tuningTrafficData->getArea_name(i));
        }
        ui->tet_speed->setText(tuningTrafficData->getSpeed(i));
        ui->tet_granularity->setText(tuningTrafficData->getGranularity(i));
    }
    ui->cs_combobox->setCurrentIndex(tuningTrafficData->get_csBehaviorIndex());
    ui->ps_combobox->setCurrentIndex(tuningTrafficData->get_psBehaviorIndex());
    ui->area_combobox->setCurrentIndex(tuningTrafficData->get_AreaIndex());

    ui->chb_area->setChecked(tmp_areaChecked);
}

QString TuningTrafficManager::saveToString()
{
    QString tuningParametersContent;
    if (ui->cs_combobox->count()==0 && ui->ps_combobox->count() == 0) {
        return QString();
    }

    tuningParametersContent.append("CS_MODELS:\n\n");
    for (int i = 0; i < CSSaveParameters.size(); ++i) {

        tuningParametersContent.append("name:\n");
        tuningParametersContent.append(CSSaveParameters[i]->cs_name + "\n");

        if (ui->tet_call_duration->isEnabled()) {
            tuningParametersContent.append(ui->lbl_call_duration->text() + "\n");
            tuningParametersContent.append(CSSaveParameters[i]->call_duration + "\n");
        }
        if (ui->tet_call_intensity->isEnabled()) {
            tuningParametersContent.append(ui->lbl_call_intensity->text() + "\n");
            tuningParametersContent.append(CSSaveParameters[i]->call_intensity + "\n");
        }
        if (ui->tet_recovery_start_interval->isEnabled()) {
            tuningParametersContent.append(ui->lbl_recovery_start_interval->text() + "\n");
            tuningParametersContent.append(CSSaveParameters[i]->recovery_start_interval + "\n");
        }
    }
    tuningParametersContent.append("\nPS_MODELS:\n\n");
    for (int i = 0; i < PSSaveParameters.size(); ++i)
    {
        tuningParametersContent.append("name:\n");
        tuningParametersContent.append(PSSaveParameters[i]->ps_name + "\n");
        if (ui->tet_ps_duration->isEnabled()) {
            tuningParametersContent.append(ui->lbl_ps_duration->text() + "\n");
            tuningParametersContent.append(PSSaveParameters[i]->ps_duration + "\n");
        }
        if (ui->tet_ps_intensity->isEnabled()) {
            tuningParametersContent.append(ui->lbl_ps_intensity->text() + "\n");
            tuningParametersContent.append(PSSaveParameters[i]->ps_intensity + "\n");
        }
    }
    if (ui->area_combobox->count() != 0) {
        tuningParametersContent.append("\nAREAS:\n");
        for (int i = 0; i < areaSaveParameters.size(); ++i) {
            tuningParametersContent.append("name:\n");
            tuningParametersContent.append(areaSaveParameters[i]->area_name + "\n");
            if (ui->tet_speed->isEnabled()) {
                tuningParametersContent.append(ui->lbl_speed->text() + " \n");
                tuningParametersContent.append(areaSaveParameters[i]->speed + "\n");
            }
            if (ui->tet_granularity->isEnabled()) {
                tuningParametersContent.append(ui->lbl_granularity->text() + "\n");
                tuningParametersContent.append(areaSaveParameters[i]->granularity + "\n");
            }
        }
    }
    return tuningParametersContent;
}


void TuningTrafficManager::on_bt_save_clicked()
{
    tuningParametersContentList.clear();
    if (ui->cs_combobox->count() > 0 and ui->ps_combobox->count() > 0) {
        SaveAll();
        tuningParametersContentList.append("TUNING TRAFFIC PARAMETERS:");
        tuningParametersContentList << saveToString().split("\n");
    }
    saveClicked = true;
    close();

}

void TuningTrafficManager::on_bt_cancel_clicked()
{
    if (ui->cs_combobox->count() > 0 and ui->ps_combobox->count() > 0) {
        readTemporaryParameters(tuningTrafficData);
    }
    cancelClicked = true;
    this->close();
}

void TuningTrafficManager::on_bt_restore_clicked()
{
    for (int i = 0; i < CSSaveParameters.size(); ++i) {
        CSSaveParameters[i]->call_duration = "0";
        CSSaveParameters[i]->call_intensity = "0";
        CSSaveParameters[i]->recovery_start_interval = "0";
        tuningTrafficData->setCall_duration("0", i);
        tuningTrafficData->setCall_intensity("0", i);
        tuningTrafficData->setRecovery_start_interval("0", i);
    }

    for (int i = 0; i < PSSaveParameters.size(); ++i) {
        PSSaveParameters[i]->ps_duration = "0";
        PSSaveParameters[i]->ps_intensity = "0";
        tuningTrafficData->setPs_duration("0", i);
        tuningTrafficData->setPs_intensity("0", i);
    }

    for (int i = 0; i < areaSaveParameters.size(); ++i) {
        areaSaveParameters[i]->granularity = "0";
        areaSaveParameters[i]->speed = "0";
        tuningTrafficData->setSpeed("0", i);
        tuningTrafficData->setGranularity("0", i);
    }

    ui->tet_granularity->setText("0");
    ui->tet_speed->setText("0");
    ui->tet_call_duration->setText("0");
    ui->tet_call_intensity->setText("0");
    ui->tet_ps_duration->setText("0");
    ui->tet_ps_intensity->setText("0");
    ui->tet_recovery_start_interval->setText("0");

    ui->cs_combobox->setCurrentIndex(0);
    ui->cs_combobox->activated(0);
    ui->ps_combobox->setCurrentIndex(0);
    ui->ps_combobox->activated(0);
    ui->area_combobox->setCurrentIndex(0);
    ui->area_combobox->activated(0);

    ui->tet_recovery_start_interval->setEnabled(false);
    ui->tet_call_duration->setEnabled(false);
    ui->tet_call_intensity->setEnabled(false);
    ui->tet_granularity->setEnabled(false);
    ui->tet_ps_intensity->setEnabled(false);
    ui->tet_ps_duration->setEnabled(false);
    ui->tet_speed->setEnabled(false);
    ui->area_combobox->setEnabled(true);
    ui->chb_area->setChecked(false);
}

void TuningTrafficManager::on_cs_combobox_activated(const QString &arg1)
{
    if (arg1 == "" or arg1 == "poweron") {
        ui->tet_call_intensity->setEnabled(false);
        ui->tet_call_duration->setEnabled(false);
    }
    else {
        ui->tet_call_intensity->setEnabled(true);
        ui->tet_call_duration->setEnabled(true);

        if(arg1 == "PowerOnOffPsCntRecover"){
            ui->tet_recovery_start_interval->setEnabled(true);
        }
        else {
            ui->tet_recovery_start_interval->setEnabled(false);
        }
    }

    ui->tet_call_duration->setText(CSSaveParameters[ui->cs_combobox->currentIndex()]->call_duration);
    ui->tet_call_intensity->setText(CSSaveParameters[ui->cs_combobox->currentIndex()]->call_intensity);
    ui->tet_recovery_start_interval->setText(CSSaveParameters[ui->cs_combobox->currentIndex()]->recovery_start_interval);
}


void TuningTrafficManager::on_ps_combobox_activated(const QString & arg1)
{
    if (arg1 == "" or arg1 == "NoPS") {
        ui->tet_ps_intensity->setEnabled(false);
        ui->tet_ps_duration->setEnabled(false);
    }
    else {
        ui->tet_ps_intensity->setEnabled(true);
        ui->tet_ps_duration->setEnabled(true);
    }
    ui->tet_ps_duration->setText(PSSaveParameters[ui->ps_combobox->currentIndex()]->ps_duration);
    ui->tet_ps_intensity->setText(PSSaveParameters[ui->ps_combobox->currentIndex()]->ps_intensity);
}

void TuningTrafficManager::on_area_combobox_activated()
{
    ui->tet_speed->setEnabled(true);
    ui->tet_granularity->setEnabled(true);
    ui->tet_granularity->setText(areaSaveParameters[ui->area_combobox->currentIndex()]->granularity);
    ui->tet_speed->setText(areaSaveParameters[ui->area_combobox->currentIndex()]->speed);
}

void TuningTrafficManager::on_chb_area_toggled()
{
    ui->area_combobox->setEnabled(!ui->chb_area->isChecked());
}

bool TuningTrafficManager::isInPsCombobox(QString value)
{
    if(ui->ps_combobox->findText(value) >= 0) {
        return true;
    }
    return false;
}

void TuningTrafficManager::on_btn_csMiniSave_clicked()
{
    if (ui->cs_combobox->count() > 0) {
        if (ui->tet_call_duration->isEnabled()) {
            tuningTrafficData->setCall_duration(ui->tet_call_duration->text(), ui->cs_combobox->currentIndex());
        }
        if (ui->tet_call_intensity->isEnabled()) {
            tuningTrafficData->setCall_intensity(ui->tet_call_intensity->text(), ui->cs_combobox->currentIndex());
        }
        if (ui->tet_recovery_start_interval->isEnabled()){
            tuningTrafficData->setRecovery_start_interval(ui->tet_recovery_start_interval->text(), ui->cs_combobox->currentIndex());
        }
        tuningTrafficData->setCs_Name(ui->cs_combobox->currentText(), ui->cs_combobox->currentIndex());
    }
}

void TuningTrafficManager::on_btn_psMiniSave_clicked()
{
    if (ui->ps_combobox->count() > 0) {
        if (ui->tet_ps_duration->isEnabled()) {
            tuningTrafficData->setPs_duration(ui->tet_ps_duration->text(), ui->ps_combobox->currentIndex());
        }
        if (ui->tet_ps_intensity->isEnabled()){
            tuningTrafficData->setPs_intensity(ui->tet_ps_intensity->text(), ui->ps_combobox->currentIndex());
        }
        tuningTrafficData->setPs_Name(ui->ps_combobox->currentText(), ui->ps_combobox->currentIndex());
    }
}

void TuningTrafficManager::on_btn_areaMiniSave_clicked()
{
    if (ui->area_combobox->count() > 0) {
        if (ui->tet_granularity->isEnabled()) {
            tuningTrafficData->setGranularity(ui->tet_granularity->text(), ui->area_combobox->currentIndex());
        }
        if (ui->chb_area->isChecked()) {
            for (int i = 0; i < tuningTrafficData->getAreaGroup().size(); ++i) {
                tuningTrafficData->setSpeed(ui->tet_speed->text(), i);
            }
        }
        else {
            if (ui->tet_speed->isEnabled()) {
                tuningTrafficData->setSpeed(ui->tet_speed->text(), ui->area_combobox->currentIndex());
            }
        }
        tuningTrafficData->setArea_Name(ui->area_combobox->currentText(), ui->area_combobox->currentIndex());
    }
}


void TuningTrafficManager::clearCSCombobox() { ui->cs_combobox->clear(); }

void TuningTrafficManager::clearPSCombobox() { ui->ps_combobox->clear(); }

void TuningTrafficManager::clearAreaCombobox() { ui->area_combobox->clear(); }

bool TuningTrafficManager::isinCsCombobox(QString value)
{
    if(ui->cs_combobox->findText(value) >= 0){
        return true;
    }
    return false;

}

bool TuningTrafficManager::isInAreaCombobox(QString value)
{
    if (ui->area_combobox->findText(value) >= 0) {
        return true;
    }
    return false;
}

void TuningTrafficManager::setUEGroup(Form* form)
{
    UEGroup.cs = form->get_currentCSBehavior();
    UEGroup.ps = form->get_currentPSBehavior();
    UEGroup.area = form->get_currentArea();
}

void TuningTrafficManager::setCSCombobox()
{
    if (!isinCsCombobox(UEGroup.cs)) {
        ui->cs_combobox->addItem(UEGroup.cs);
    }
}

void TuningTrafficManager::setPSCombobox()
{
    if (!isInPsCombobox(UEGroup.ps)) {
        ui->ps_combobox->addItem(UEGroup.ps);
    }
}

void TuningTrafficManager::setAreaCombobox()
{
    if (UEGroup.area != "" && (!isInAreaCombobox(UEGroup.area))) {
        ui->area_combobox->addItem(UEGroup.area);
    }
}


void TuningTrafficManager::initialize(TuningTrafficData *tuningTrafficData)
{
    this->tuningTrafficData = tuningTrafficData;

    CSSaveParameters.resize(0);
    for (int i = 0; i < ui->cs_combobox->count(); ++i) {
        CSSaveParameters.push_back(new TuningTrafficData::CSParameters());
        CSSaveParameters[i]->cs_name = ui->cs_combobox->itemText(i);
    }

    PSSaveParameters.resize(0);
    for (int i = 0; i < ui->ps_combobox->count(); ++i) {
        PSSaveParameters.push_back(new TuningTrafficData::PSParameters());
        PSSaveParameters[i]->ps_name = ui->ps_combobox->itemText(i);
    }

    areaSaveParameters.resize(0);
    for (int i = 0; i < ui->area_combobox->count(); ++i) {
        areaSaveParameters.push_back(new TuningTrafficData::Areas());
        areaSaveParameters[i]->area_name = ui->area_combobox->itemText(i);
    }


    tuningTrafficData->csInitialize(ui->cs_combobox->count());
    for (int i = 0; i < ui->cs_combobox->count(); ++i) {
        tuningTrafficData->setCs_Name(ui->cs_combobox->itemText(i), i);
    }
    tuningTrafficData->psInitialize(ui->ps_combobox->count());
    for (int i = 0; i < ui->ps_combobox->count(); ++i) {
        tuningTrafficData->setPs_Name(ui->ps_combobox->itemText(i), i);
    }
    tuningTrafficData->areaInitialize(ui->area_combobox->count());
    for (int i = 0; i < ui->area_combobox->count(); ++i) {
        tuningTrafficData->setArea_Name(ui->area_combobox->itemText(i), i);
    }
}

void TuningTrafficManager::pushModel(TuningTrafficData *tuningTrafficData)
{
    this->tuningTrafficData = tuningTrafficData;

    //Adding new set of Parameters to the global Vector
    if (CSSaveParameters.size() < ui->cs_combobox->count()) {
        CSSaveParameters.push_back(new TuningTrafficData::CSParameters());
    }
    for (int i = CSSaveParameters.size()-1; i < ui->cs_combobox->count(); ++i) {
        CSSaveParameters[i]->cs_name = ui->cs_combobox->itemText(i);
    }

    if (PSSaveParameters.size() < ui->ps_combobox->count()) {
        PSSaveParameters.push_back(new TuningTrafficData::PSParameters());
    }
    for (int i = PSSaveParameters.size()-1; i < ui->ps_combobox->count(); ++i) {
        PSSaveParameters[i]->ps_name = ui->ps_combobox->itemText(i);
    }

    if (areaSaveParameters.size() < ui->area_combobox->count()) {
        areaSaveParameters.push_back(new TuningTrafficData::Areas());
    }
    for (int i = areaSaveParameters.size()-1;i < ui->area_combobox->count(); ++i) {
        areaSaveParameters[i]->area_name = ui->area_combobox->itemText(i);
    }


    //Adding the same set of Parameters to temporary Vector
    if (tuningTrafficData->getCSParamGroup().size() < ui->cs_combobox->count()) {
        tuningTrafficData->pushCSModel();
    }
    for (int i = tuningTrafficData->getCSParamGroup().size()-1; i < ui->cs_combobox->count(); ++i) {
        tuningTrafficData->setCs_Name(ui->cs_combobox->itemText(i), i);
    }

    if (tuningTrafficData->getPSParamGroup().size() < ui->ps_combobox->count()) {
        tuningTrafficData->pushPSModel();
    }
    for (int i = tuningTrafficData->getPSParamGroup().size()-1; i < ui->ps_combobox->count(); ++i) {
        tuningTrafficData->setPs_Name(ui->ps_combobox->itemText(i), i);
    }

    if (tuningTrafficData->getAreaGroup().size() < ui->area_combobox->count()) {
        tuningTrafficData->pushAreaModel();
    }
    for (int i = tuningTrafficData->getAreaGroup().size()-1; i < ui->area_combobox->count(); ++i) {
        tuningTrafficData->setArea_Name(ui->area_combobox->itemText(i), i);
    }
}

void TuningTrafficManager::popCSModel(TuningTrafficData *tuningTrafficData)
{
    this->tuningTrafficData = tuningTrafficData;
    CSSaveParameters.pop_back();
    tuningTrafficData->popCSModel();
    ui->cs_combobox->removeItem(ui->cs_combobox->count()-1);
}

void TuningTrafficManager::popPSModel(TuningTrafficData *tuningTrafficData)
{
    this->tuningTrafficData = tuningTrafficData;
    PSSaveParameters.pop_back();
    tuningTrafficData->popPSModel();
    ui->ps_combobox->removeItem(ui->ps_combobox->count()-1);
}

void TuningTrafficManager::popArea(TuningTrafficData *tuningTrafficData)
{
    this->tuningTrafficData = tuningTrafficData;
    areaSaveParameters.pop_back();
    tuningTrafficData->popAreaModel();
    ui->area_combobox->removeItem(ui->area_combobox->count()-1);
}

int TuningTrafficManager::get_csComboboxCount() { return ui->cs_combobox->count(); }

int TuningTrafficManager::get_psComboboxCount() { return ui->ps_combobox->count(); }
