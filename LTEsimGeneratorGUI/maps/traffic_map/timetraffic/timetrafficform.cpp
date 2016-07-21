#include "timetrafficform.h"
#include "ui_timetrafficform.h"
#include "maps/traffic_map/ue_param/UE_param_form.h"
#include <QMessageBox>
#include <QDebug>

QStringList timeParametersContentList;

TimeTrafficForm::TimeTrafficForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeTrafficForm)
{
    ui->setupUi(this);
    setFixedSize(sizeHint() );
    parametersValidation();
    Form::resetUEPairsCount();
    ui->tab_timeTraffic->setCurrentIndex(0);
}

TimeTrafficForm::~TimeTrafficForm()
{
    delete ui;
}

void TimeTrafficForm::setParameters(TimeTraffic *timeTraffic)
{
    this->timeTraffic = timeTraffic;

    ui->txt_attachRate1->setText(timeTraffic->get_tab1_AttachRate() );
    ui->txt_attachRate2->setText(timeTraffic->get_tab2_AttachRate() );
    ui->txt_detachRate1->setText(timeTraffic->get_tab1_DetachRate() );
    ui->txt_detachRate2->setText(timeTraffic->get_tab2_DetachRate() );
    ui->txt_statsRate1->setText(timeTraffic->get_tab1_StatsRate() );
    ui->txt_statsRate2->setText(timeTraffic->get_tab2_StatsRate() );
    ui->txt_crdelUEPeriod->setText(timeTraffic->get_tab2_CrDrUEPeriod() );
    ui->spn_hours1->setValue(timeTraffic->getSpn_hours1() );
    ui->spn_minutes1->setValue(timeTraffic->getSpn_minutes1() );
    ui->spn_seconds1->setValue(timeTraffic->getSpn_seconds1() );
    ui->spn_hours2->setValue(timeTraffic->getSpn_hours2() );
    ui->spn_minutes2->setValue(timeTraffic->getSpn_minutes2() );
    ui->spn_seconds2->setValue(timeTraffic->getSpn_seconds2() );

    ui->lbl_warning1->setVisible(Form::getUEPairs() > 1000);
    ui->lbl_warning2->setVisible(Form::getUEPairs() > 1000);
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
    if (ui->txt_crdelUEPeriod->text().toInt() > convert_tab2_trafficDuration() )
        QMessageBox::warning(this, "Warning", "Create/delete UE period cannot be longer than traffic duration", QMessageBox::Ok);
    else
    {
        this->close();
        SaveAll();
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
    this->close();
}

void TimeTrafficForm::on_rd_statsRate1_toggled()
{
    ui->txt_statsRate1->setEnabled(ui->rd_statsRate1->isChecked() );
}

void TimeTrafficForm::on_rd_statsRate2_toggled()
{
    ui->txt_statsRate2->setEnabled(ui->rd_statsRate2->isChecked() );
}

void TimeTrafficForm::on_gb_attdetRate1_toggled()
{
    if (Form::getUEPairs() > 1000)
        ui->lbl_warning1->setVisible(!ui->gb_attdetRate1->isChecked() );
}

void TimeTrafficForm::on_gb_attdetRate2_toggled()
{
    if (Form::getUEPairs() > 1000)
        ui->lbl_warning2->setVisible(!ui->gb_attdetRate2->isChecked() );
}

void TimeTrafficForm::parametersValidation()
{
    ui->txt_attachRate1->setValidator(new QIntValidator(0, 712860, this) );
    ui->txt_attachRate2->setValidator(new QIntValidator(0, 712860, this) );
    ui->txt_detachRate1->setValidator(new QIntValidator(0, 712860, this) );
    ui->txt_detachRate2->setValidator(new QIntValidator(0, 712860, this) );
    ui->txt_statsRate1->setValidator(new QIntValidator(0, 712860, this) );
    ui->txt_statsRate2->setValidator(new QIntValidator(0, 712860, this) );
    ui->txt_crdelUEPeriod->setValidator(new QIntValidator(0, 720000, this) );
    ui->spn_hours1->setRange(0, 200);
    ui->spn_hours2->setRange(0,200);
    ui->spn_minutes1->setRange(0, 59);
    ui->spn_minutes2->setRange(0, 59);
    ui->spn_seconds1->setRange(0, 59);
    ui->spn_seconds2->setRange(0, 59);
}

int TimeTrafficForm::convert_tab1_trafficDuration()
{
    return ui->spn_hours1->value() * 3600 + ui->spn_minutes1->value() * 60 + ui->spn_seconds1->value();
}

int TimeTrafficForm::convert_tab2_trafficDuration()
{
    return ui->spn_hours2->value() * 3600 + ui->spn_minutes2->value() * 60 + ui->spn_seconds2->value();
}

void TimeTrafficForm::SaveAll()
{
    timeTraffic->set_tab1_AttachRate(ui->txt_attachRate1->text() );
    timeTraffic->set_tab1_DetachRate(ui->txt_detachRate1->text() );
    timeTraffic->set_tab1_StatsRate(ui->txt_statsRate1->text() );
    timeTraffic->set_tab1_TimeTrafficDuration(convert_tab1_trafficDuration() );
    timeTraffic->set_tab2_AttachRate(ui->txt_attachRate2->text() );
    timeTraffic->set_tab2_CrDrUEPeriod(ui->txt_crdelUEPeriod->text() );
    timeTraffic->set_tab2_DetachRate(ui->txt_detachRate2->text() );
    timeTraffic->set_tab2_StatsRate(ui->txt_statsRate2->text() );
    timeTraffic->set_tab2_TimeTrafficDuration(convert_tab2_trafficDuration() );
    timeTraffic->setSpn_hours1(ui->spn_hours1->value() );
    timeTraffic->setSpn_minutes1(ui->spn_minutes1->value() );
    timeTraffic->setSpn_seconds1(ui->spn_seconds1->value() );
    timeTraffic->setSpn_hours2(ui->spn_hours2->value() );
    timeTraffic->setSpn_minutes2(ui->spn_minutes2->value() );
    timeTraffic->setSpn_seconds2(ui->spn_seconds2->value() );
}

QString TimeTrafficForm::saveToString()
{
    QString timeParametersContent;
    if (ui->tab_timeTraffic->currentIndex() == 0)
    {
        timeParametersContent.append(ui->lbl_trafficDuration->text() + " ");
        timeParametersContent.append(QString::number(convert_tab1_trafficDuration() ) + "\n");
        if (ui->gb_attdetRate1->isChecked() )
        {
            timeParametersContent.append(ui->lbl_attachRate->text() + " ");
            timeParametersContent.append(ui->txt_attachRate1->text() + "\n");
            timeParametersContent.append(ui->lbl_detachRate->text() + " ");
            timeParametersContent.append(ui->txt_detachRate1->text() + "\n");
        }
        if (ui->rd_statsRate1->isChecked() )
        {
            timeParametersContent.append(ui->rd_statsRate1->text() + " ");
            timeParametersContent.append(ui->txt_statsRate1->text() + "\n");
        }
    }
    else if( ui->tab_timeTraffic->currentIndex() == 1)
    {
        timeParametersContent.append(ui->lbl_trafficDuration_2->text() + " ");
        timeParametersContent.append(QString::number(convert_tab2_trafficDuration() ) + "\n");
        timeParametersContent.append(ui->lbl_crdelUEPeriod->text() + " ");
        timeParametersContent.append(ui->txt_crdelUEPeriod->text() + "\n");
        if (ui->gb_attdetRate2->isChecked() )
        {
            timeParametersContent.append(ui->lbl_attachRate_2->text() + " ");
            timeParametersContent.append(ui->txt_attachRate2->text() + "\n");
            timeParametersContent.append(ui->lbl_detachRate_2->text() + " ");
            timeParametersContent.append(ui->txt_detachRate2->text() + "\n");
        }
        if (ui->rd_statsRate2->isChecked() )
        {
            timeParametersContent.append(ui->rd_statsRate2->text() + " ");
            timeParametersContent.append(ui->txt_statsRate2->text() );
        }
    }
    return timeParametersContent;
}
