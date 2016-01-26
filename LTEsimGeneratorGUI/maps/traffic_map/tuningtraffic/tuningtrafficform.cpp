#include "tuningtrafficform.h"
#include "ui_tuningtrafficform.h"
#include "doubleinputvalidator.h"
#include <QDebug>


//temporary variables for dialog's window settings

bool tmp_areaChecked;

//--

//Saved structure of chosen tuning parameters
QStringList tuningParametersContentList;

TuningTrafficForm::TuningTrafficForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TuningTrafficForm)
{
    ui->setupUi(this);
    this->setWindowTitle("Tuning traffic");
    setFixedSize(sizeHint());
    setParametersValidation();
    CSSaveParameters = QVector<Tuningtraffic::CSParameters* >();
    PSSaveParameters = QVector<Tuningtraffic::PSParameters* >();
    areaSaveParameters = QVector<Tuningtraffic::Areas* >();

    CSSaveParameters.push_back(new Tuningtraffic::CSParameters());
    PSSaveParameters.push_back(new Tuningtraffic::PSParameters());
    areaSaveParameters.push_back(new Tuningtraffic::Areas());

    cancelClicked = false;
    saveClicked = false;
}

TuningTrafficForm::~TuningTrafficForm()
{
    delete ui;
    for (int i = 0; i < CSSaveParameters.size(); ++i)
        delete CSSaveParameters[i];
    CSSaveParameters.clear();

    for (int i = 0; i < PSSaveParameters.size(); ++i)
        delete PSSaveParameters[i];
    PSSaveParameters.clear();

    for (int i = 0; i < areaSaveParameters.size(); ++i)
        delete areaSaveParameters[i];
    areaSaveParameters.clear();
}

void TuningTrafficForm::setParameters()
{
    for (int i = 0; i < CSSaveParameters.size(); ++i)
    {
        if (!isinCsCombobox(CSSaveParameters[i]->cs_name))
            ui->cs_combobox->addItem(CSSaveParameters[i]->cs_name);
        ui->tet_call_intensity->setText(CSSaveParameters[i]->call_intensity);
        ui->tet_call_duration->setText(CSSaveParameters[i]->call_duration);
        ui->tet_recovery_start_interval->setText(CSSaveParameters[i]->recovery_start_interval);
    }
    for (int i = 0; i < PSSaveParameters.size(); ++i)
    {
        if (!isInPsCombobox(PSSaveParameters[i]->ps_name))
            ui->ps_combobox->addItem(PSSaveParameters[i]->ps_name);
        ui->tet_ps_duration->setText(PSSaveParameters[i]->ps_duration);
        ui->tet_ps_intensity->setText(PSSaveParameters[i]->ps_intensity);
    }
    for (int i = 0; i < areaSaveParameters.size(); ++i)
    {
        if (!isInAreaCombobox(areaSaveParameters[i]->area_name) && areaSaveParameters[i]->area_name != "")
            ui->area_combobox->addItem(areaSaveParameters[i]->area_name);
        ui->tet_speed->setText(areaSaveParameters[i]->speed);
        ui->tet_granularity->setText(areaSaveParameters[i]->granularity);
    }
    ui->cs_combobox->setCurrentIndex(tuningtraffic->get_csBehaviorIndex());
    ui->ps_combobox->setCurrentIndex(tuningtraffic->get_psBehaviorIndex());
    ui->area_combobox->setCurrentIndex(tuningtraffic->get_AreaIndex());

    ui->chb_area->setChecked(tmp_areaChecked);
}


void TuningTrafficForm::SaveAll()
{

    tuningtraffic->set_csBehaviorIndex(0);
    tuningtraffic->set_psBehaviorIndex(0);
    tuningtraffic->set_AreaIndex(0);
    tmp_areaChecked = ui->chb_area->isChecked();

    copyCSParams(tuningtraffic->getCSParamGroup());
    copyPSParams(tuningtraffic->getPSParamGroup());
    copyAreaParams(tuningtraffic->getAreaGroup());
}

void TuningTrafficForm::setParametersValidation()
{
    ui->tet_ps_intensity->setValidator(new DoubleInputValidator(0, 100, 3, this));
    ui->tet_recovery_start_interval->setValidator(new DoubleInputValidator(0, 100, 3, this));
    ui->tet_ps_duration->setValidator(new DoubleInputValidator(0, 100, 3, this));
    ui->tet_call_duration->setValidator(new DoubleInputValidator(0,100,3, this));
    ui->tet_call_intensity->setValidator(new DoubleInputValidator(0,100,3, this));
    ui->tet_granularity->setValidator(new QIntValidator(0,100,this));
    ui->tet_speed->setValidator(new QIntValidator(0, 100, this));
}

void TuningTrafficForm::copyCSParams(const QVector<Tuningtraffic::CSParameters *> &value)
{
    for (int i = 0; i < value.size(); ++i)
    {
        CSSaveParameters[i]->call_duration = value[i]->call_duration;
        CSSaveParameters[i]->call_intensity = value[i]->call_intensity;
        CSSaveParameters[i]->cs_name = value[i]->cs_name;
        CSSaveParameters[i]->recovery_start_interval = value[i]->recovery_start_interval;
    }
}

void TuningTrafficForm::copyPSParams(const QVector<Tuningtraffic::PSParameters *> &value)
{
    for (int i = 0; i < value.size(); ++i)
    {
        PSSaveParameters[i]->ps_duration = value[i]->ps_duration;
        PSSaveParameters[i]->ps_intensity = value[i]->ps_intensity;
        PSSaveParameters[i]->ps_name = value[i]->ps_name;
    }
}

void TuningTrafficForm::copyAreaParams(const QVector<Tuningtraffic::Areas *> &value)
{
    for (int i = 0; i < value.size(); ++i)
    {
        areaSaveParameters[i]->speed = value[i]->speed;
        areaSaveParameters[i]->granularity = value[i]->granularity;
        areaSaveParameters[i]->area_name = value[i]->area_name;
    }
}

void TuningTrafficForm::readTemporaryParameters(Tuningtraffic* tuningtraffic)
{
    this->tuningtraffic = tuningtraffic;
    for (int i = 0; i < this->tuningtraffic->getCSParamGroup().size(); ++i)
    {
        if (!isinCsCombobox(tuningtraffic->getCs_Name(i)))
            ui->cs_combobox->addItem(this->tuningtraffic->getCs_Name(i));
        ui->tet_call_intensity->setText(tuningtraffic->getCall_intensity(i));
        ui->tet_call_duration->setText(tuningtraffic->getCall_duration(i));
        ui->tet_recovery_start_interval->setText(tuningtraffic->getRecovery_start_interval(i));
    }
    for (int i = 0; i < this->tuningtraffic->getPSParamGroup().size(); ++i)
    {
        if (!isInPsCombobox(tuningtraffic->getPs_Name(i)))
            ui->ps_combobox->addItem(this->tuningtraffic->getPs_Name(i));
        ui->tet_ps_duration->setText(tuningtraffic->getPs_duration(i));
        ui->tet_ps_intensity->setText(tuningtraffic->getPS_intensity(i));
    }
    for (int i = 0; i < this->tuningtraffic->getAreaGroup().size(); ++i)
    {
        if (!isInAreaCombobox(tuningtraffic->getArea_name(i)) && tuningtraffic->getArea_name(i) != "")
            ui->area_combobox->addItem(this->tuningtraffic->getArea_name(i));
        ui->tet_speed->setText(tuningtraffic->getSpeed(i));
        ui->tet_granularity->setText(tuningtraffic->getGranularity(i));
    }
    ui->cs_combobox->setCurrentIndex(tuningtraffic->get_csBehaviorIndex());
    ui->ps_combobox->setCurrentIndex(tuningtraffic->get_psBehaviorIndex());
    ui->area_combobox->setCurrentIndex(tuningtraffic->get_AreaIndex());

    ui->chb_area->setChecked(tmp_areaChecked);
}

QString TuningTrafficForm::saveToString()
{
    QString tuningParametersContent;
    if (ui->cs_combobox->count() != 0 and ui->ps_combobox->count() != 0)
    {
        tuningParametersContent.append("CS_MODELS:\n\n");
        for (int i = 0; i < CSSaveParameters.size(); ++i)
        {
            tuningParametersContent.append("name:\n");
            tuningParametersContent.append(CSSaveParameters[i]->cs_name + "\n");
            if (ui->tet_call_duration->isEnabled())
            {
                tuningParametersContent.append(ui->lbl_call_duration->text() + "\n");
                tuningParametersContent.append(CSSaveParameters[i]->call_duration + "\n");
            }
            if (ui->tet_call_intensity->isEnabled())
            {
                tuningParametersContent.append(ui->lbl_call_intensity->text() + "\n");
                tuningParametersContent.append(CSSaveParameters[i]->call_intensity + "\n");
            }
            if (ui->tet_recovery_start_interval->isEnabled())
            {
                tuningParametersContent.append(ui->lbl_recovery_start_interval->text() + "\n");
                tuningParametersContent.append(CSSaveParameters[i]->recovery_start_interval + "\n");
            }
        }
        tuningParametersContent.append("\nPS_MODELS:\n\n");
        for (int i = 0; i < PSSaveParameters.size(); ++i)
        {
            tuningParametersContent.append("name:\n");
            tuningParametersContent.append(PSSaveParameters[i]->ps_name + "\n");
            if (ui->tet_ps_duration->isEnabled())
            {
                tuningParametersContent.append(ui->lbl_ps_duration->text() + "\n");
                tuningParametersContent.append(PSSaveParameters[i]->ps_duration + "\n");
            }
            if (ui->tet_ps_intensity->isEnabled())
            {
                tuningParametersContent.append(ui->lbl_ps_intensity->text() + "\n");
                tuningParametersContent.append(PSSaveParameters[i]->ps_intensity + "\n");
            }
        }
        if (ui->area_combobox->count() != 0)
        {
            tuningParametersContent.append("\nAREAS:\n");
            for (int i = 0; i < areaSaveParameters.size(); ++i)
            {
                tuningParametersContent.append("name:\n");
                tuningParametersContent.append(areaSaveParameters[i]->area_name + "\n");
                if (ui->tet_speed->isEnabled())
                {
                    tuningParametersContent.append(ui->lbl_speed->text() + " \n");
                    tuningParametersContent.append(areaSaveParameters[i]->speed + "\n");
                }
                if (ui->tet_granularity->isEnabled())
                {
                    tuningParametersContent.append(ui->lbl_granularity->text() + "\n");
                    tuningParametersContent.append(areaSaveParameters[i]->granularity + "\n");
                }
            }
        }

    }
    return tuningParametersContent;
}


void TuningTrafficForm::on_bt_save_clicked()
{
    tuningParametersContentList.clear();
    if (ui->cs_combobox->count() > 0 and ui->ps_combobox->count() > 0)
    {
        SaveAll();
        tuningParametersContentList.append("TUNING TRAFFIC PARAMETERS:");
        tuningParametersContentList << saveToString().split("\n");
    }
    saveClicked = true;
    close();

}

void TuningTrafficForm::on_bt_cancel_clicked()
{
    if (ui->cs_combobox->count() > 0 and ui->ps_combobox->count() > 0)
        readTemporaryParameters(tuningtraffic);
    cancelClicked = true;
    this->close();
}

void TuningTrafficForm::on_bt_restore_clicked()
{
    for (int i = 0; i < CSSaveParameters.size(); ++i)
    {
        CSSaveParameters[i]->call_duration = "0";
        CSSaveParameters[i]->call_intensity = "0";
        CSSaveParameters[i]->recovery_start_interval = "0";
        tuningtraffic->setCall_duration("0", i);
        tuningtraffic->setCall_intensity("0", i);
        tuningtraffic->setRecovery_start_interval("0", i);
    }

    for (int i = 0; i < PSSaveParameters.size(); ++i)
    {
        PSSaveParameters[i]->ps_duration = "0";
        PSSaveParameters[i]->ps_intensity = "0";
        tuningtraffic->setPs_duration("0", i);
        tuningtraffic->setPs_intensity("0", i);
    }

    for (int i = 0; i < areaSaveParameters.size(); ++i)
    {
        areaSaveParameters[i]->granularity = "0";
        areaSaveParameters[i]->speed = "0";
        tuningtraffic->setSpeed("0", i);
        tuningtraffic->setGranularity("0", i);
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

void TuningTrafficForm::on_cs_combobox_activated(const QString &arg1)
{
    if (arg1 == "" or arg1 == "poweron")
    {
        ui->tet_call_intensity->setEnabled(false);
        ui->tet_call_duration->setEnabled(false);
    }
    else
    {
        ui->tet_call_intensity->setEnabled(true);
        ui->tet_call_duration->setEnabled(true);

        if(arg1 == "PowerOnOffPsCntRecover")
            ui->tet_recovery_start_interval->setEnabled(true);
        else
            ui->tet_recovery_start_interval->setEnabled(false);
    }

    ui->tet_call_duration->setText(CSSaveParameters[ui->cs_combobox->currentIndex()]->call_duration);
    ui->tet_call_intensity->setText(CSSaveParameters[ui->cs_combobox->currentIndex()]->call_intensity);
    ui->tet_recovery_start_interval->setText(CSSaveParameters[ui->cs_combobox->currentIndex()]->recovery_start_interval);
}


void TuningTrafficForm::on_ps_combobox_activated(const QString & arg1)
{
    if (arg1 == "" or arg1 == "NoPS")
    {
        ui->tet_ps_intensity->setEnabled(false);
        ui->tet_ps_duration->setEnabled(false);
    }
    else
    {
        ui->tet_ps_intensity->setEnabled(true);
        ui->tet_ps_duration->setEnabled(true);
    }
    ui->tet_ps_duration->setText(PSSaveParameters[ui->ps_combobox->currentIndex()]->ps_duration);
    ui->tet_ps_intensity->setText(PSSaveParameters[ui->ps_combobox->currentIndex()]->ps_intensity);
}

void TuningTrafficForm::on_area_combobox_activated()
{
    ui->tet_speed->setEnabled(true);
    ui->tet_granularity->setEnabled(true);
    ui->tet_granularity->setText(areaSaveParameters[ui->area_combobox->currentIndex()]->granularity);
    ui->tet_speed->setText(areaSaveParameters[ui->area_combobox->currentIndex()]->speed);
}

void TuningTrafficForm::on_chb_area_toggled()
{
    ui->area_combobox->setEnabled(!ui->chb_area->isChecked());
}

bool TuningTrafficForm::isInPsCombobox(QString value)
{
    if(ui->ps_combobox->findText(value) >= 0)
        return true;
    else
        return false;
}

void TuningTrafficForm::on_btn_csMiniSave_clicked()
{
    if (ui->cs_combobox->count() > 0)
    {
        if (ui->tet_call_duration->isEnabled())
            tuningtraffic->setCall_duration(ui->tet_call_duration->text(), ui->cs_combobox->currentIndex());
        if (ui->tet_call_intensity->isEnabled())
            tuningtraffic->setCall_intensity(ui->tet_call_intensity->text(), ui->cs_combobox->currentIndex());
        if (ui->tet_recovery_start_interval->isEnabled())
            tuningtraffic->setRecovery_start_interval(ui->tet_recovery_start_interval->text(), ui->cs_combobox->currentIndex());
        tuningtraffic->setCs_Name(ui->cs_combobox->currentText(), ui->cs_combobox->currentIndex());
    }
}

void TuningTrafficForm::on_btn_psMiniSave_clicked()
{
    if (ui->ps_combobox->count() > 0)
    {
        if (ui->tet_ps_duration->isEnabled())
            tuningtraffic->setPs_duration(ui->tet_ps_duration->text(), ui->ps_combobox->currentIndex());
        if (ui->tet_ps_intensity->isEnabled())
            tuningtraffic->setPs_intensity(ui->tet_ps_intensity->text(), ui->ps_combobox->currentIndex());
        tuningtraffic->setPs_Name(ui->ps_combobox->currentText(), ui->ps_combobox->currentIndex());
    }
}

void TuningTrafficForm::on_btn_areaMiniSave_clicked()
{
    if (ui->area_combobox->count() > 0)
    {
        if (ui->tet_granularity->isEnabled())
            tuningtraffic->setGranularity(ui->tet_granularity->text(), ui->area_combobox->currentIndex());
        if (ui->chb_area->isChecked())
        {
            for (int i = 0; i < tuningtraffic->getAreaGroup().size(); ++i)
                tuningtraffic->setSpeed(ui->tet_speed->text(), i);
        }
        else
        {
            if (ui->tet_speed->isEnabled())
                tuningtraffic->setSpeed(ui->tet_speed->text(), ui->area_combobox->currentIndex());
        }
        tuningtraffic->setArea_Name(ui->area_combobox->currentText(), ui->area_combobox->currentIndex());
    }
}


void TuningTrafficForm::clearCSCombobox()
{
    ui->cs_combobox->clear();
}

void TuningTrafficForm::clearPSCombobox()
{
    ui->ps_combobox->clear();
}

void TuningTrafficForm::clearAreaCombobox()
{
    ui->area_combobox->clear();
}

bool TuningTrafficForm::isinCsCombobox(QString value)
{
    if(ui->cs_combobox->findText(value) >= 0)
        return true;
    else
        return false;
}

bool TuningTrafficForm::isInAreaCombobox(QString value)
{
    if (ui->area_combobox->findText(value) >= 0)
        return true;
    else
        return false;
}

void TuningTrafficForm::setUEGroup(Form* form)
{
    UEGroup.cs = form->get_currentCSBehavior();
    UEGroup.ps = form->get_currentPSBehavior();
    UEGroup.area = form->get_currentArea();
}

void TuningTrafficForm::setCSCombobox()
{
    if (!isinCsCombobox(UEGroup.cs))
        ui->cs_combobox->addItem(UEGroup.cs);
}

void TuningTrafficForm::setPSCombobox()
{
    if (!isInPsCombobox(UEGroup.ps))
        ui->ps_combobox->addItem(UEGroup.ps);
}

void TuningTrafficForm::setAreaCombobox()
{
    if (UEGroup.area != "")
    {
        if (!isInAreaCombobox(UEGroup.area))
            ui->area_combobox->addItem(UEGroup.area);
    }
}

void TuningTrafficForm::initialize(Tuningtraffic *tuningtraffic)
{
    this->tuningtraffic = tuningtraffic;
    CSSaveParameters.resize(0);
    for (int i = 0; i < ui->cs_combobox->count(); ++i)
        CSSaveParameters.push_back(new Tuningtraffic::CSParameters());
    for (int i = 0; i < ui->cs_combobox->count(); ++i)
        CSSaveParameters[i]->cs_name = ui->cs_combobox->itemText(i);

    PSSaveParameters.resize(0);
    for (int i = 0; i < ui->ps_combobox->count(); ++i)
        PSSaveParameters.push_back(new Tuningtraffic::PSParameters());
    for (int i = 0; i < ui->ps_combobox->count(); ++i)
        PSSaveParameters[i]->ps_name = ui->ps_combobox->itemText(i);

    areaSaveParameters.resize(0);
    for (int i = 0; i < ui->area_combobox->count(); ++i)
        areaSaveParameters.push_back(new Tuningtraffic::Areas());
    for (int i = 0; i < ui->area_combobox->count(); ++i)
        areaSaveParameters[i]->area_name = ui->area_combobox->itemText(i);


    tuningtraffic->csInitialize(ui->cs_combobox->count());
    for (int i = 0; i < ui->cs_combobox->count(); ++i)
        tuningtraffic->setCs_Name(ui->cs_combobox->itemText(i), i);
    tuningtraffic->psInitialize(ui->ps_combobox->count());
    for (int i = 0; i < ui->ps_combobox->count(); ++i)
        tuningtraffic->setPs_Name(ui->ps_combobox->itemText(i), i);
    tuningtraffic->areaInitialize(ui->area_combobox->count());
    for (int i = 0; i < ui->area_combobox->count(); ++i)
        tuningtraffic->setArea_Name(ui->area_combobox->itemText(i), i);
}

void TuningTrafficForm::pushModel(Tuningtraffic *tuningtraffic)
{
    this->tuningtraffic = tuningtraffic;

    //Adding new set of Parameters to the global Vector
    if (CSSaveParameters.size() < ui->cs_combobox->count())
        CSSaveParameters.push_back(new Tuningtraffic::CSParameters());
    for (int i = CSSaveParameters.size()-1; i < ui->cs_combobox->count(); ++i)
        CSSaveParameters[i]->cs_name = ui->cs_combobox->itemText(i);

    if (PSSaveParameters.size() < ui->ps_combobox->count())
        PSSaveParameters.push_back(new Tuningtraffic::PSParameters());
    for (int i = PSSaveParameters.size()-1; i < ui->ps_combobox->count(); ++i)
        PSSaveParameters[i]->ps_name = ui->ps_combobox->itemText(i);

    if (areaSaveParameters.size() < ui->area_combobox->count())
        areaSaveParameters.push_back(new Tuningtraffic::Areas());
    for (int i = areaSaveParameters.size()-1;i < ui->area_combobox->count(); ++i)
        areaSaveParameters[i]->area_name = ui->area_combobox->itemText(i);


    //Adding the same set of Parameters to temporary Vector
    if (tuningtraffic->getCSParamGroup().size() < ui->cs_combobox->count())
        tuningtraffic->pushCSModel();
    for (int i = tuningtraffic->getCSParamGroup().size()-1; i < ui->cs_combobox->count(); ++i)
        tuningtraffic->setCs_Name(ui->cs_combobox->itemText(i), i);

    if (tuningtraffic->getPSParamGroup().size() < ui->ps_combobox->count())
        tuningtraffic->pushPSModel();
    for (int i = tuningtraffic->getPSParamGroup().size()-1; i < ui->ps_combobox->count(); ++i)
        tuningtraffic->setPs_Name(ui->ps_combobox->itemText(i), i);

    if (tuningtraffic->getAreaGroup().size() < ui->area_combobox->count())
        tuningtraffic->pushAreaModel();
    for (int i = tuningtraffic->getAreaGroup().size()-1; i < ui->area_combobox->count(); ++i)
        tuningtraffic->setArea_Name(ui->area_combobox->itemText(i), i);
}

void TuningTrafficForm::popCSModel(Tuningtraffic *tuningtraffic)
{
    this->tuningtraffic = tuningtraffic;
    CSSaveParameters.pop_back();
    tuningtraffic->popCSModel();
    ui->cs_combobox->removeItem(ui->cs_combobox->count()-1);
}

void TuningTrafficForm::popPSModel(Tuningtraffic *tuningtraffic)
{
    this->tuningtraffic = tuningtraffic;
    PSSaveParameters.pop_back();
    tuningtraffic->popPSModel();
    ui->ps_combobox->removeItem(ui->ps_combobox->count()-1);
}

void TuningTrafficForm::popArea(Tuningtraffic *tuningtraffic)
{
    this->tuningtraffic = tuningtraffic;
    areaSaveParameters.pop_back();
    tuningtraffic->popAreaModel();
    ui->area_combobox->removeItem(ui->area_combobox->count()-1);
}

int TuningTrafficForm::get_csComboboxCount()
{
    return ui->cs_combobox->count();
}

int TuningTrafficForm::get_psComboboxCount()
{
    return ui->ps_combobox->count();
}
