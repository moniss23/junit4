#include "timeManager.h"
#include "ui_timeForm.h"
#include "maps/traffic_map/ue_param/UE_param_form.h"
#include <QMessageBox>
#include <QDebug>

QStringList timeParametersContentList;

TimeManager::TimeManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrafficTimeForm)
{
    ui->setupUi(this);
    setFixedSize(sizeHint());
    parametersValidation();
    Form::resetUEPairsCount();
    ui->tab_timeTraffic->setCurrentIndex(0);
}

TimeManager::~TimeManager()
{
    delete ui;
}

void TimeManager::setParameters(TimeData *timeTraffic)
{
    this->timeTraffic = timeTraffic;

    ui->txt_attachRate1->setText(timeTraffic->get_tab1_AttachRate());
    ui->txt_attachRate2->setText(timeTraffic->get_tab2_AttachRate());
    ui->txt_detachRate1->setText(timeTraffic->get_tab1_DetachRate());
    ui->txt_detachRate2->setText(timeTraffic->get_tab2_DetachRate());
    ui->txt_statsRate1->setText(timeTraffic->get_tab1_StatsRate());
    ui->txt_statsRate2->setText(timeTraffic->get_tab2_StatsRate());
    ui->txt_crdelUEPeriod->setText(timeTraffic->get_tab2_CrDrUEPeriod());

    ui->spn_hours1->setValue(timeTraffic->getSpn_time1().hour());
    ui->spn_minutes1->setValue(timeTraffic->getSpn_time1().minute());
    ui->spn_seconds2->setValue(timeTraffic->getSpn_time1().second());

    ui->spn_hours2->setValue(timeTraffic->getSpn_time2().hour());
    ui->spn_minutes2->setValue(timeTraffic->getSpn_time2().minute());
    ui->spn_seconds2->setValue(timeTraffic->getSpn_time2().second());

    ui->lbl_warning1->setVisible(Form::getUEPairs() > 1000);
    ui->lbl_warning2->setVisible(Form::getUEPairs() > 1000);
}

void TimeManager::on_txt_attachRate1_textChanged(QString value)
{
    ui->txt_detachRate1->setText(value);
}

void TimeManager::on_txt_attachRate2_textChanged(QString value)
{
    ui->txt_detachRate2->setText(value);
}

void TimeManager::on_buttonBox_accepted()
{
    timeParametersContentList.clear();
    if (ui->txt_crdelUEPeriod->text().toInt() > convert_tab2_trafficDuration())
        QMessageBox::warning(this, "Warning", "Create/delete UE period cannot be longer than traffic duration", QMessageBox::Ok);
    else
    {
        this->close();
        SaveAll();
        timeParametersContentList.append("TRAFFIC DURATION PARAMETERS:");
        timeParametersContentList << saveToString().split("\n");
    }
}

void TimeManager::on_btn_restore_clicked()
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

void TimeManager::on_buttonBox_rejected()
{
    this->close();
}

void TimeManager::on_rd_statsRate1_toggled()
{
    ui->txt_statsRate1->setEnabled(ui->rd_statsRate1->isChecked());
}

void TimeManager::on_rd_statsRate2_toggled()
{
    ui->txt_statsRate2->setEnabled(ui->rd_statsRate2->isChecked());
}

void TimeManager::on_gb_attdetRate1_toggled()
{
    if (Form::getUEPairs() > 1000)
        ui->lbl_warning1->setVisible(!ui->gb_attdetRate1->isChecked());
}

void TimeManager::on_gb_attdetRate2_toggled()
{
    if (Form::getUEPairs() > 1000)
        ui->lbl_warning2->setVisible(!ui->gb_attdetRate2->isChecked());
}

void TimeManager::parametersValidation()
{
    ui->txt_attachRate1->setValidator(new QIntValidator(0, 712860, this));
    ui->txt_attachRate2->setValidator(new QIntValidator(0, 712860, this));
    ui->txt_detachRate1->setValidator(new QIntValidator(0, 712860, this));
    ui->txt_detachRate2->setValidator(new QIntValidator(0, 712860, this));
    ui->txt_statsRate1->setValidator(new QIntValidator(0, 712860, this));
    ui->txt_statsRate2->setValidator(new QIntValidator(0, 712860, this));
    ui->txt_crdelUEPeriod->setValidator(new QIntValidator(0, 720000, this));

    ui->spn_hours1->setRange(0, 23);
    ui->spn_hours2->setRange(0, 23);
    ui->spn_minutes1->setRange(0, 59);
    ui->spn_minutes2->setRange(0, 59);
    ui->spn_seconds1->setRange(0, 59);
    ui->spn_seconds2->setRange(0, 59);
}

int TimeManager::convert_tab1_trafficDuration()
{
    return ui->spn_hours1->value()*3600 + ui->spn_minutes1->value()*60 + ui->spn_seconds1->value();
}

int TimeManager::convert_tab2_trafficDuration()
{
    return ui->spn_hours2->value()*3600 + ui->spn_minutes2->value()*60 + ui->spn_seconds2->value();
}

void TimeManager::SaveAll()
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

    timeTraffic->setSpn_time1(ui->spn_hours1->value(), ui->spn_minutes1->value(), ui->spn_seconds1->value());
    timeTraffic->setSpn_time2(ui->spn_hours2->value(), ui->spn_minutes2->value(), ui->spn_seconds2->value());
}

QString TimeManager::saveToString()
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
