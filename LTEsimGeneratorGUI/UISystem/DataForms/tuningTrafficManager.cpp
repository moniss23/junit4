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
    int currentIndex = ui->csComboBox->currentIndex();
    if(currentIndex != 0) {
        tuningTrafficData.csParamGroup[currentIndex-1].callDuration = ui->csDurationLineEdit->text().toDouble();
        tuningTrafficData.csParamGroup[currentIndex-1].callIntensity = ui->csIntensityLineEdit->text().toDouble();
        if(currentIndex == 4){
            tuningTrafficData.csParamGroup[currentIndex-1].recoveryStartInterval = ui->recoveryStartIntervalLineEdit->text().toDouble();
        }
    }
}

void TuningTrafficManager::on_psSaveButton_clicked()
{
    int currentIndex = ui->psComboBox->currentIndex();
    if(currentIndex != 0) {
        TuningTrafficData::PSParameters tmpPS = tuningTrafficData.psParamGroup.at(currentIndex-1);
        tmpPS.psDuration = ui->psDurationLineEdit->text().toDouble();
        tmpPS.psIntensity = ui->psIntensityLineEdit->text().toDouble();
    }
}

void TuningTrafficManager::on_mobilitySaveButton_clicked()
{
    int currentIndex = ui->mobilityComboBox->currentIndex();
    if(currentIndex != 0) {
        TuningTrafficData::Mobility tmpMobility = tuningTrafficData.mobilityGroup.at(currentIndex-1);
        tmpMobility.granularity = ui->granularityLineEdit->text().toDouble();
        tmpMobility.speed = ui->speedLineEdit->text().toDouble();
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
    if(index > 0) {
        ui->csDurationLineEdit->setEnabled(true);
        ui->csIntensityLineEdit->setEnabled(true);
        ui->csDurationLineEdit->setText(QString::number(tuningTrafficData.csParamGroup.at(index).callDuration));
        ui->csIntensityLineEdit->setText(QString::number(tuningTrafficData.csParamGroup.at(index).callIntensity));
        if(ui->csComboBox->currentText() == "PowerOnOffPsCntRecover") {
            ui->recoveryStartIntervalLineEdit->setEnabled(true);
            ui->recoveryStartIntervalLineEdit->setText(QString::number(tuningTrafficData.csParamGroup.at(index).recoveryStartInterval));
        }else {
            ui->recoveryStartIntervalLineEdit->setEnabled(false);
            ui->recoveryStartIntervalLineEdit->setText("");
        }
    }else {
        ui->csDurationLineEdit->setEnabled(false);
        ui->csIntensityLineEdit->setEnabled(false);
        ui->recoveryStartIntervalLineEdit->setEnabled(false);
        ui->csDurationLineEdit->setText("");
        ui->csIntensityLineEdit->setText("");
        ui->recoveryStartIntervalLineEdit->setText("");
    }
}

void TuningTrafficManager::on_psComboBox_currentIndexChanged(int index)
{
    if(index > 0 && ui->psComboBox->itemText(index) != "NoPs") {
        ui->psDurationLineEdit->setEnabled(true);
        ui->psIntensityLineEdit->setEnabled(true);
        ui->psDurationLineEdit->setText(QString::number(tuningTrafficData.psParamGroup.at(index).psDuration));
        ui->psIntensityLineEdit->setText(QString::number(tuningTrafficData.psParamGroup.at(index).psIntensity));
    }else {
        ui->psDurationLineEdit->setEnabled(false);
        ui->psIntensityLineEdit->setEnabled(false);
        ui->psDurationLineEdit->setText("");
        ui->psIntensityLineEdit->setText("");
    }
}

void TuningTrafficManager::on_mobilityComboBox_currentIndexChanged(int index)
{
    if(index > 0) {
        ui->granularityLineEdit->setEnabled(true);
        ui->speedLineEdit->setEnabled(true);
        ui->granularityLineEdit->setText(QString::number(tuningTrafficData.mobilityGroup.at(index).granularity));
        ui->speedLineEdit->setText(QString::number(tuningTrafficData.mobilityGroup.at(index).speed));
    }else {
        ui->granularityLineEdit->setEnabled(false);
        ui->speedLineEdit->setEnabled(false);
        ui->granularityLineEdit->setText("");
        ui->speedLineEdit->setText("");
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
