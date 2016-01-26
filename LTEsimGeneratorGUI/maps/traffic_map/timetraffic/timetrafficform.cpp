#include "timetrafficform.h"
#include "ui_timetrafficform.h"
#include "maps/traffic_map/ue_param/UE_param_form.h"
#include <QMessageBox>
#include <QDebug>


// --temporary variables to save previous settings
QString tmp_attachRate1;
QString tmp_detachRate1;
QString tmp_statsRate1;
QString tmp_attachRate2;
QString tmp_detachRate2;
QString tmp_statsRate2;

int tmp_hours1;
int tmp_minutes1;
int tmp_seconds1;
int tmp_hours2;
int tmp_minutes2;
int tmp_seconds2;

QString tmp_crdelUEPeriod;

bool tmp_statschecked1;
bool tmp_statsAfter1;
bool tmp_statsAfter2;
bool tmp_statschecked2;

bool tmp_gbAttDetRate1;
bool tmp_gbAttDetRate2;
// --

QStringList timeParametersContentList;

TimeTrafficForm::TimeTrafficForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeTrafficForm)
{
    ui->setupUi(this);
    setFixedSize(sizeHint());
    parametersValidation();
    Form::resetUEPairsCount();
    ui->tab_timeTraffic->setCurrentIndex(0);
    cancelClicked = false;
    saveClicked = false;

}

TimeTrafficForm::~TimeTrafficForm()
{
    delete ui;
}

void TimeTrafficForm::setParameters(TimeTraffic *timeTraffic)
{
    this->timeTraffic = timeTraffic;

    ui->txt_attachRate1->setText(timeTraffic->get_tab1_AttachRate());
    ui->txt_attachRate2->setText(timeTraffic->get_tab2_AttachRate());
    ui->txt_detachRate1->setText(timeTraffic->get_tab1_DetachRate());
    ui->txt_detachRate2->setText(timeTraffic->get_tab2_DetachRate());
    ui->txt_statsRate1->setText(timeTraffic->get_tab1_StatsRate());
    ui->txt_statsRate2->setText(timeTraffic->get_tab2_StatsRate());
    ui->txt_crdelUEPeriod->setText(timeTraffic->get_tab2_CrDrUEPeriod());
    ui->spn_hours1->setValue(timeTraffic->getSpn_hours1());
    ui->spn_minutes1->setValue(timeTraffic->getSpn_minutes1());
    ui->spn_seconds1->setValue(timeTraffic->getSpn_seconds1());
    ui->spn_hours2->setValue(timeTraffic->getSpn_hours2());
    ui->spn_minutes2->setValue(timeTraffic->getSpn_minutes2());
    ui->spn_seconds2->setValue(timeTraffic->getSpn_seconds2());

    if (Form::getUEPairs() > 1000)
    {
        ui->lbl_warning1->setVisible(true);
        ui->lbl_warning2->setVisible(true);
    }
    else
    {
        ui->lbl_warning1->setVisible(false);
        ui->lbl_warning2->setVisible(false);
    }
}


void TimeTrafficForm::on_txt_attachRate1_textChanged(QString value)
{
    ui->txt_detachRate1->setText(value);
}

void TimeTrafficForm::on_txt_attachRate2_textChanged(QString value)
{
    ui->txt_detachRate2->setText(value);
}

void TimeTrafficForm::on_buttonBox_accepted()
{
    timeParametersContentList.clear();
    if (ui->txt_crdelUEPeriod->text().toInt() > convert_tab2_trafficDuration())
        QMessageBox::warning(this, "Warning", "Create/delete UE period cannot be longer than traffic duration", QMessageBox::Ok);
    else
    { 
        this->close();
        saveTemporarySettings();
        SaveAll();
        saveClicked = true;
        timeParametersContentList.append("TRAFFIC DURATION PARAMETERS:");
        timeParametersContentList << saveToString().split("\n");
    }

}

void TimeTrafficForm::on_btn_restore_clicked()
{
    ui->spn_hours1->setValue(0);
    ui->spn_minutes1->setValue(0);
    ui->spn_seconds1->setValue(0);
    ui->spn_hours2->setValue(0);
    ui->spn_minutes2->setValue(0);
    ui->spn_seconds2->setValue(0);

    ui->txt_crdelUEPeriod->setText("0");
    ui->txt_attachRate1->setText("0");
    ui->txt_detachRate1->setText("0");
    ui->txt_attachRate2->setText("0");
    ui->txt_detachRate2->setText("0");
    ui->txt_statsRate1->setText("0");
    ui->txt_statsRate2->setText("0");

}

void TimeTrafficForm::on_buttonBox_rejected()
{
    if (saveClicked == false)
    {
        tmp_statschecked1 = false;
        tmp_statschecked2 = false;
        readTemporarySettings();
    }
    else if (saveClicked == true)
    {
        readTemporarySettings();
    }
    this->close();
    cancelClicked = true;
}


void TimeTrafficForm::on_rd_statsRate1_toggled()
{
    ui->txt_statsRate1->setEnabled(ui->rd_statsRate1->isChecked());
}

void TimeTrafficForm::on_rd_statsRate2_toggled()
{
    if (Form::getUEPairs() > 1000)
        ui->txt_statsRate2->setEnabled(ui->rd_statsRate2->isChecked());
}

void TimeTrafficForm::on_gb_attdetRate1_toggled()
{
    if (Form::getUEPairs() > 1000)
        ui->lbl_warning1->setVisible(!ui->gb_attdetRate1->isChecked());
}

void TimeTrafficForm::on_gb_attdetRate2_toggled()
{
    ui->lbl_warning2->setVisible(!ui->gb_attdetRate2->isChecked());
}

bool TimeTrafficForm::getCancelClicked() const
{
    return cancelClicked;
}

void TimeTrafficForm::setCancelClicked(bool value)
{
    cancelClicked = value;
}

void TimeTrafficForm::parametersValidation()
{
    ui->txt_attachRate1->setValidator(new QIntValidator(0, 712860, this));
    ui->txt_attachRate2->setValidator(new QIntValidator(0, 712860, this));
    ui->txt_detachRate1->setValidator(new QIntValidator(0, 712860, this));
    ui->txt_detachRate2->setValidator(new QIntValidator(0, 712860, this));
    ui->txt_statsRate1->setValidator(new QIntValidator(0, 712860, this));
    ui->txt_statsRate2->setValidator(new QIntValidator(0, 712860, this));
    ui->txt_crdelUEPeriod->setValidator(new QIntValidator(0, 720000, this));
    ui->spn_hours1->setRange(0, 200);
    ui->spn_hours2->setRange(0,200);
    ui->spn_minutes1->setRange(0, 59);
    ui->spn_minutes2->setRange(0, 59);
    ui->spn_seconds1->setRange(0, 59);
    ui->spn_seconds2->setRange(0, 59);
}

int TimeTrafficForm::convert_tab1_trafficDuration()
{
    return ui->spn_hours1->value()*3600 + ui->spn_minutes1->value()*60 + ui->spn_seconds1->value();
}

int TimeTrafficForm::convert_tab2_trafficDuration()
{
    return ui->spn_hours2->value()*3600 + ui->spn_minutes2->value()*60 + ui->spn_seconds2->value();
}

void TimeTrafficForm::saveTemporarySettings()
{
    tmp_attachRate1 = ui->txt_attachRate1->text();
    tmp_attachRate2 = ui->txt_attachRate2->text();
    tmp_crdelUEPeriod = ui->txt_crdelUEPeriod->text();
    tmp_detachRate1 = ui->txt_detachRate1->text();
    tmp_detachRate2 = ui->txt_detachRate2->text();

    tmp_hours1 = ui->spn_hours1->value();
    tmp_hours2 = ui->spn_hours2->value();
    tmp_minutes1 = ui->spn_minutes1->value();
    tmp_minutes2 = ui->spn_minutes2->value();
    tmp_seconds1 = ui->spn_seconds1->value();
    tmp_seconds2 = ui->spn_seconds2->value();

    tmp_statschecked1 = ui->rd_statsRate1->isChecked();
    tmp_statschecked2 = ui->rd_statsRate2->isChecked();
    tmp_statsAfter1 = ui->rd_statsAfter1->isChecked();
    tmp_statsAfter2 = ui->rd_statsAfter2->isChecked();
    tmp_gbAttDetRate1 = ui->gb_attdetRate1->isChecked();
    tmp_gbAttDetRate2 = ui->gb_attdetRate2->isChecked();

    tmp_statsRate1 = ui->txt_statsRate1->text();
    tmp_statsRate2 = ui->txt_statsRate2->text();
}

void TimeTrafficForm::readTemporarySettings()
{
    ui->txt_attachRate1->setText(tmp_attachRate1);
    ui->txt_attachRate2->setText(tmp_attachRate2);
    ui->txt_crdelUEPeriod->setText(tmp_crdelUEPeriod);
    ui->txt_detachRate1->setText(tmp_detachRate1);
    ui->txt_detachRate2->setText(tmp_detachRate2);
    ui->txt_statsRate1->setText(tmp_statsRate1);
    ui->txt_statsRate2->setText(tmp_statsRate2);

    ui->spn_hours1->setValue(tmp_hours1);
    ui->spn_minutes1->setValue(tmp_minutes1);
    ui->spn_seconds1->setValue(tmp_seconds1);
    ui->spn_hours1->setValue(tmp_hours2);
    ui->spn_minutes1->setValue(tmp_minutes2);
    ui->spn_seconds1->setValue(tmp_seconds2);
    ui->rd_statsAfter1->setChecked(tmp_statsAfter1);
    ui->rd_statsAfter2->setChecked(tmp_statsAfter2);
    ui->rd_statsRate1->setChecked(tmp_statschecked1);
    ui->rd_statsRate2->setChecked(tmp_statschecked2);;
    ui->gb_attdetRate1->setChecked(tmp_gbAttDetRate1);
    ui->gb_attdetRate2->setChecked(tmp_gbAttDetRate2);
}

void TimeTrafficForm::SaveAll()
{
    timeTraffic->set_tab1_AttachRate(ui->txt_attachRate1->text());
    timeTraffic->set_tab1_DetachRate(ui->txt_detachRate1->text());
    timeTraffic->set_tab1_StatsRate(ui->txt_statsRate1->text());
    timeTraffic->set_tab1_TimeTrafficDuration(convert_tab1_trafficDuration());
    timeTraffic->set_tab2_AttachRate(ui->txt_attachRate2->text());
    timeTraffic->set_tab2_CrDrUEPeriod(ui->txt_crdelUEPeriod->text());
    timeTraffic->set_tab2_DetachRate(ui->txt_detachRate2->text());
    timeTraffic->set_tab2_StatsRate(ui->txt_statsRate2->text());
    timeTraffic->set_tab2_TimeTrafficDuration(convert_tab2_trafficDuration());
    timeTraffic->setSpn_hours1(ui->spn_hours1->value());
    timeTraffic->setSpn_minutes1(ui->spn_minutes1->value());
    timeTraffic->setSpn_seconds1(ui->spn_seconds1->value());
    timeTraffic->setSpn_hours2(ui->spn_hours2->value());
    timeTraffic->setSpn_minutes2(ui->spn_minutes2->value());
    timeTraffic->setSpn_seconds2(ui->spn_seconds2->value());
}

QString TimeTrafficForm::saveToString()
{
    QString timeParametersContent;
    if (ui->tab_timeTraffic->currentIndex() == 0)
    {
        timeParametersContent.append(ui->lbl_trafficDuration->text() + " ");
        timeParametersContent.append(QString::number(convert_tab1_trafficDuration()) + "\n");
        if (ui->gb_attdetRate1->isChecked())
        {
            timeParametersContent.append(ui->lbl_attachRate->text() + " ");
            timeParametersContent.append(ui->txt_attachRate1->text() + "\n");
            timeParametersContent.append(ui->lbl_detachRate->text() + " ");
            timeParametersContent.append(ui->txt_detachRate1->text() + "\n");
        }
        if (ui->rd_statsRate1->isChecked())
        {
            timeParametersContent.append(ui->rd_statsRate1->text() + " ");
            timeParametersContent.append(ui->txt_statsRate1->text() + "\n");
        }
    }
    else if( ui->tab_timeTraffic->currentIndex() == 1)
    {
        timeParametersContent.append(ui->lbl_trafficDuration_2->text() + " ");
        timeParametersContent.append(QString::number(convert_tab2_trafficDuration()) + "\n");
        timeParametersContent.append(ui->lbl_crdelUEPeriod->text() + " ");
        timeParametersContent.append(ui->txt_crdelUEPeriod->text() + "\n");
        if (ui->gb_attdetRate2->isChecked())
        {
            timeParametersContent.append(ui->lbl_attachRate_2->text() + " ");
            timeParametersContent.append(ui->txt_attachRate2->text() + "\n");
            timeParametersContent.append(ui->lbl_detachRate_2->text() + " ");
            timeParametersContent.append(ui->txt_detachRate2->text() + "\n");
        }
        if (ui->rd_statsRate2->isChecked())
        {
            timeParametersContent.append(ui->rd_statsRate2->text() + " ");
            timeParametersContent.append(ui->txt_statsRate2->text());
        }
    }
    return timeParametersContent;
}



