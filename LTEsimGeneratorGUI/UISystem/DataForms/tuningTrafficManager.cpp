#include <QDoubleValidator>
#include "tuningTrafficManager.h"
#include "ui_tuningtrafficform.h"

TuningTrafficManager::TuningTrafficManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TuningTrafficForm)
{
    ui->setupUi(this);
    setFixedSize(sizeHint());

    ui->mobilityCheckBox->setVisible(false);

    ui->csIntensityLineEdit->setValidator(new QDoubleValidator(1.00,100.00,2,this));
    ui->csDurationLineEdit->setValidator(new QDoubleValidator(1.00,100.00,2,this));
    ui->recoveryStartIntervalLineEdit->setValidator(new QDoubleValidator(1.00,100.00,2,this));
    ui->psIntensityLineEdit->setValidator(new QDoubleValidator(1.00,100.00,2,this));
    ui->psDurationLineEdit->setValidator(new QDoubleValidator(1.00,100.00,2,this));
    ui->granularityLineEdit->setValidator(new QDoubleValidator(1.00,100.00,2,this));
    ui->speedLineEdit->setValidator(new QDoubleValidator(1.00,100.00,2,this));
}

TuningTrafficManager::~TuningTrafficManager()
{
    delete ui;
}

void TuningTrafficManager::loadAndSpawn(const QString &projectName, const QString &trafficFileName, const std::tuple<QStringList,QStringList,QStringList> &comboBoxesLists, const TuningTrafficData tuningTrafficData)
{
    this->projectName = projectName;
    this->trafficFileName = trafficFileName;
    this->tuningTrafficData = tuningTrafficData;

    fillComboBoxes(comboBoxesLists);

    ui->csComboBox->setCurrentIndex(0);
    ui->psComboBox->setCurrentIndex(0);
    ui->mobilityComboBox->setCurrentIndex(0);

    this->show();
}

void TuningTrafficManager::restoreTuningTrafficData(const TuningTrafficData &tuningTrafficData)
{
    this->tuningTrafficData = tuningTrafficData;
}

void TuningTrafficManager::on_csSaveButton_clicked()
{
    if(this->ui->csComboBox->currentText()=="None item") {
        return;
    }
    for (TuningTrafficData::CSParameters &it:this->tuningTrafficData.csParamGroup) {
        if (it.csName == this->ui->csComboBox->currentText()) {
            if (it.csName == "PowerOnOffPsCntRecover") {
                it.recoveryStartInterval = ui->csIntensityLineEdit->text().toDouble();
            }
            it.callDuration=ui->csDurationLineEdit->text().toDouble();
            it.callIntensity=ui->csIntensityLineEdit->text().toDouble();
            return;
        }
    }
}

void TuningTrafficManager::on_psSaveButton_clicked()
{
    if(this->ui->psComboBox->currentText()=="None item") {
        return;
    }
    for (TuningTrafficData::PSParameters &it:this->tuningTrafficData.psParamGroup) {
        if (it.psName == this->ui->psComboBox->currentText()) {
            it.psDuration=ui->psDurationLineEdit->text().toDouble();
            it.psIntensity=ui->psIntensityLineEdit->text().toDouble();
            return;
        }
    }
}

void TuningTrafficManager::on_mobilitySaveButton_clicked()
{
    if(this->ui->mobilityComboBox->currentText()=="None item") {
        return;
    }
    for (TuningTrafficData::Mobility &it:this->tuningTrafficData.mobilityGroup) {
        if (it.mobilityName == this->ui->mobilityComboBox->currentText()) {
            it.speed=ui->speedLineEdit->text().toDouble();
            it.granularity=ui->granularityLineEdit->text().toDouble();
            return;
        }
    }
}

void TuningTrafficManager::on_saveButton_clicked()
{
    ui->csSaveButton->clicked();
    ui->psSaveButton->clicked();
    ui->mobilitySaveButton->clicked();
    emit saveTuningTrafficData(projectName, trafficFileName, tuningTrafficData);
    this->close();
}

void TuningTrafficManager::on_cancelButton_clicked()
{
    this->close();
}

void TuningTrafficManager::on_csComboBox_currentIndexChanged(int index)
{

    if (index <= 0){
        ui->csDurationLineEdit->setEnabled(false);
        ui->csIntensityLineEdit->setEnabled(false);
        ui->recoveryStartIntervalLineEdit->setEnabled(false);
        ui->csDurationLineEdit->setText("");
        ui->csIntensityLineEdit->setText("");
        ui->recoveryStartIntervalLineEdit->setText("");
        return;
    }

    ui->csDurationLineEdit->setEnabled(true);
    ui->csIntensityLineEdit->setEnabled(true);

    if(ui->csComboBox->currentText() == "PowerOnOffPsCntRecover") {
        ui->recoveryStartIntervalLineEdit->setEnabled(true);
        ui->recoveryStartIntervalLineEdit->setText(QString::number(tuningTrafficData.csParamGroup.at(index).recoveryStartInterval));
    }else {
        ui->recoveryStartIntervalLineEdit->setEnabled(false);
        ui->recoveryStartIntervalLineEdit->setText("");
    }
    for (TuningTrafficData::CSParameters &it:this->tuningTrafficData.csParamGroup) {
        if (it.csName == this->ui->csComboBox->currentText()) {
            ui->csDurationLineEdit->setText(QString::number(it.callDuration));
            ui->csIntensityLineEdit->setText(QString::number(it.callIntensity));
        }
    }
}

void TuningTrafficManager::on_psComboBox_currentIndexChanged(int index)
{
    if (index<=0) {
        ui->psDurationLineEdit->setEnabled(false);
        ui->psIntensityLineEdit->setEnabled(false);
        ui->psDurationLineEdit->setText("");
        ui->psIntensityLineEdit->setText("");
        return;
    }
    ui->psDurationLineEdit->setEnabled(true);
    ui->psIntensityLineEdit->setEnabled(true);
    for (TuningTrafficData::PSParameters &it:this->tuningTrafficData.psParamGroup) {
        if (it.psName == this->ui->psComboBox->currentText()) {
            ui->psDurationLineEdit->setText(QString::number(it.psDuration));
            ui->psIntensityLineEdit->setText(QString::number(it.psIntensity));
        }
    }
}

void TuningTrafficManager::on_mobilityComboBox_currentIndexChanged(int index)
{
    if (index<=0) {
        ui->speedLineEdit->setEnabled(false);
        ui->granularityLineEdit->setEnabled(false);
        ui->speedLineEdit->setText("");
        ui->granularityLineEdit->setText("");
        return;
    }
    ui->speedLineEdit->setEnabled(true);
    ui->granularityLineEdit->setEnabled(true);
    for (TuningTrafficData::Mobility &it:this->tuningTrafficData.mobilityGroup) {
        if (it.mobilityName == this->ui->mobilityComboBox->currentText()) {
            ui->speedLineEdit->setText(QString::number(it.speed));
            ui->granularityLineEdit->setText(QString::number(it.granularity));
        }
    }
}

void TuningTrafficManager::on_restoreButton_clicked()
{
    emit restoreTuningTrafficData(projectName,trafficFileName);
    ui->csComboBox->setCurrentIndex(0);
    ui->psComboBox->setCurrentIndex(0);
    ui->mobilityComboBox->setCurrentIndex(0);
}

void TuningTrafficManager::fillComboBoxes(const std::tuple<QStringList, QStringList, QStringList> &comboBoxesLists)
{
    ui->csComboBox->clear();
    ui->psComboBox->clear();
    ui->mobilityComboBox->clear();

    ui->csComboBox->addItem("None item");
    ui->psComboBox->addItem("None item");
    ui->mobilityComboBox->addItem("None item");

    ui->csComboBox->addItems(std::get<0> (comboBoxesLists));
    ui->psComboBox->addItems(std::get<1> (comboBoxesLists));
    ui->mobilityComboBox->addItems(std::get<2> (comboBoxesLists));
}
