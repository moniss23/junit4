#include "timeForm.h"
#include "ui_timeForm.h"
#include <UISystem/DataForms/UE_param_form.h>
#include <QMessageBox>

TimeForm::TimeForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeForm)
{
    this->ui->setupUi(this);
    this->setFixedSize(sizeHint());
    this->setParametersValidation();
    this->ui->tab_timeTraffic->setCurrentIndex(0);
}

TimeForm::~TimeForm()
{
    delete ui;
}

void TimeForm::loadAndOpen(const QString &projectName, const QString &trafficName, const TimeData &timeData)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->timeData=timeData;
    this->refreshUi();
        this->setWindowFlags( Qt::Dialog | Qt::WindowStaysOnTopHint);
    this->show();
}

void TimeForm::on_txt_attachRate1_textChanged(QString value)
{
    ui->txt_detachRate1->setText(value);
}

void TimeForm::on_txt_attachRate2_textChanged(QString value)
{
    ui->txt_detachRate2->setText(value);
}

void TimeForm::refreshUi()
{
    ui->txt_attachRate1->setText(QString::number(timeData.tab1_attachRate));
    ui->txt_attachRate2->setText(QString::number(timeData.tab2_attachRate));
    ui->txt_detachRate1->setText(QString::number(timeData.tab1_detachRate));
    ui->txt_detachRate2->setText(QString::number(timeData.tab2_detachRate));
    ui->tab1_statisticsLineEdit->setText(QString::number(timeData.tab1_statsRate));
    ui->tab2_statisticsLineEdit->setText(QString::number(timeData.tab2_statsRate));
    ui->txt_crdelUEPeriod->setText(QString::number(timeData.tab2_crdelUEPeriod));
    ui->gb_attdetRate1->setChecked(!timeData.tab1_ueAttachDettach);
    ui->gb_attdetRate1->setChecked(timeData.tab1_ueAttachDettach);
    ui->gb_attdetRate2->setChecked(!timeData.tab2_ueAttachDettach);
    ui->gb_attdetRate2->setChecked(timeData.tab2_ueAttachDettach);
    ui->tab1_printStatisticsWithRate->setChecked(!timeData.tab1_statisticsWithRate);
    ui->tab1_printStatisticsWithRate->setChecked(timeData.tab1_statisticsWithRate);
    ui->tab2_statisticsWithRate->setChecked(!timeData.tab2_statisticsWithRate);
    ui->tab2_statisticsWithRate->setChecked(timeData.tab2_statisticsWithRate);
    ui->tab1_printStatisticsAfterTheEnd->setChecked(timeData.tab1_statisticsAfterEnd);
    ui->tab2_statisticsAfterTheEnd->setChecked(timeData.tab2_statisticsAfterEnd);
    ui->resetAllStat1->setChecked(timeData.resetAllStat1);
    ui->resetAllStat2->setChecked(timeData.resetAllStat2);

    ui->spn_hours1->setValue(timeData.spn_time1.hour());
    ui->spn_minutes1->setValue(timeData.spn_time1.minute());
    ui->spn_seconds2->setValue(timeData.spn_time1.second());

    ui->spn_hours2->setValue(timeData.spn_time2.hour());
    ui->spn_minutes2->setValue(timeData.spn_time2.minute());
    ui->spn_seconds2->setValue(timeData.spn_time2.second());

    ui->lbl_warning1->setVisible(Form::getUEPairs() > 1000);
    ui->lbl_warning2->setVisible(Form::getUEPairs() > 1000);
}

void TimeForm::on_btn_restore_clicked()
{
    this->refreshUi();
}

void TimeForm::on_gb_attdetRate1_toggled()
{
    if (Form::getUEPairs() > 1000)
        ui->lbl_warning1->setVisible(!ui->gb_attdetRate1->isChecked());
}

void TimeForm::on_gb_attdetRate2_toggled()
{
    if (Form::getUEPairs() > 1000)
        ui->lbl_warning2->setVisible(!ui->gb_attdetRate2->isChecked());
}

void TimeForm::setParametersValidation()
{
    ui->txt_attachRate1->setValidator(new QIntValidator(0, 712860, this));
    ui->txt_attachRate2->setValidator(new QIntValidator(0, 712860, this));
    ui->txt_detachRate1->setValidator(new QIntValidator(0, 712860, this));
    ui->txt_detachRate2->setValidator(new QIntValidator(0, 712860, this));
    ui->tab1_statisticsLineEdit->setValidator(new QIntValidator(0, 712860, this));
    ui->tab2_statisticsLineEdit->setValidator(new QIntValidator(0, 712860, this));
    ui->txt_crdelUEPeriod->setValidator(new QIntValidator(0, 720000, this));

    ui->spn_hours1->setRange(0, 23);
    ui->spn_hours2->setRange(0, 23);
    ui->spn_minutes1->setRange(0, 59);
    ui->spn_minutes2->setRange(0, 59);
    ui->spn_seconds1->setRange(0, 59);
    ui->spn_seconds2->setRange(0, 59);
}

void TimeForm::getParameters()
{
    timeData.tab1_attachRate = ui->txt_attachRate1->text().toInt();
    timeData.tab1_detachRate = ui->txt_detachRate1->text().toInt();
    timeData.tab1_statsRate = ui->tab1_statisticsLineEdit->text().toInt();
    timeData.tab2_attachRate = ui->txt_attachRate2->text().toInt();
    timeData.tab2_crdelUEPeriod = ui->txt_crdelUEPeriod->text().toInt();
    timeData.tab2_detachRate = ui->txt_detachRate2->text().toInt();
    timeData.tab2_statsRate = ui->tab2_statisticsLineEdit->text().toInt();
    timeData.spn_time1.setHMS(ui->spn_hours1->value(), ui->spn_minutes1->value(), ui->spn_seconds1->value());
    timeData.spn_time2 .setHMS(ui->spn_hours2->value(), ui->spn_minutes2->value(), ui->spn_seconds2->value());
    timeData.tab1_statisticsAfterEnd = ui->tab1_printStatisticsAfterTheEnd->isChecked();
    timeData.tab2_statisticsAfterEnd = ui->tab2_statisticsAfterTheEnd->isChecked();
    timeData.tab1_statisticsWithRate = ui->tab1_printStatisticsWithRate->isChecked();
    timeData.tab2_statisticsWithRate = ui->tab2_statisticsWithRate->isChecked();
    timeData.tab1_ueAttachDettach = ui->gb_attdetRate1->isChecked();
    timeData.tab2_ueAttachDettach = ui->gb_attdetRate2->isChecked();
    timeData.resetAllStat1 = ui->resetAllStat1->isChecked();
    timeData.resetAllStat2 = ui->resetAllStat2->isChecked();
}

void TimeForm::on_tab1_printStatisticsWithRate_toggled(bool checked)
{
    this->ui->tab1_statisticsLineEdit->setEnabled(checked);
}

void TimeForm::on_tab2_statisticsWithRate_toggled(bool checked)
{
    this->ui->tab2_statisticsLineEdit->setEnabled(checked);
}

void TimeForm::on_okButton_clicked()
{
    this->getParameters();
    emit saveTimeData(projectName, trafficName, timeData);
    this->close();
}

void TimeForm::on_cancelButton_clicked()
{
    this->close();
}
