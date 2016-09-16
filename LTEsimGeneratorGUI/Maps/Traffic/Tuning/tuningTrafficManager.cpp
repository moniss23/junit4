#include <QDoubleValidator>

#include "tuningTrafficManager.h"
#include "ui_tuningtrafficform.h"

TuningTrafficManager::TuningTrafficManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TuningTrafficForm)
{
    ui->setupUi(this);
    this->setWindowTitle("Tuning traffic");
    setFixedSize(sizeHint());

    ui->csComboBox->addItems(tuningTrafficData.CSSTRINGLIST);
    ui->psComboBox->addItems(tuningTrafficData.PSSTRINGLIST);
    ui->mobilityComboBox->addItems(tuningTrafficData.MOBILITYSTRINGLIST);

    ui->mobilityCheckBox->setVisible(false);
}

TuningTrafficManager::~TuningTrafficManager()
{
    delete ui;
}

void TuningTrafficManager::setUEGroup(Form* form)
{
    UEGroup.cs = form->get_currentCSBehavior();
    UEGroup.ps = form->get_currentPSBehavior();
    UEGroup.area = form->get_currentArea();
}

void TuningTrafficManager::loadAndSpawn(const QString &projectName, const QString &trafficFileName, const TuningTrafficData tuningTrafficData)
{
    this->projectName = projectName;
    this->trafficFileName = trafficFileName;
    this->tuningTrafficData = tuningTrafficData;

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
        TuningTrafficData::CSParameters *tmpCS = tuningTrafficData.csParamGroup.at(currentIndex-1);
        tmpCS->callDuration = ui->csDurationLineEdit->text().toDouble();
        tmpCS->callIntensity = ui->csIntensityLineEdit->text().toDouble();
        if(currentIndex == 4)
            tmpCS->recoveryStartInterval = ui->recoveryStartIntervalLineEdit->text().toDouble();
    }
}

void TuningTrafficManager::on_psSaveButton_clicked()
{
    int currentIndex = ui->psComboBox->currentIndex();
    if(currentIndex != 0) {
        TuningTrafficData::PSParameters *tmpPS = tuningTrafficData.psParamGroup.at(currentIndex-1);
        tmpPS->psDuration = ui->psDurationLineEdit->text().toDouble();
        tmpPS->psIntensity = ui->psIntensityLineEdit->text().toDouble();
    }
}

void TuningTrafficManager::on_mobilitySaveButton_clicked()
{
    int currentIndex = ui->mobilityComboBox->currentIndex();
    if(currentIndex != 0) {
        TuningTrafficData::Mobility *tmpMobility = tuningTrafficData.mobilityGroup.at(currentIndex-1);
        tmpMobility->granularity = ui->granularityLineEdit->text().toDouble();
        tmpMobility->speed = ui->speedLineEdit->text().toDouble();
    }
}

void TuningTrafficManager::on_saveButton_clicked()
{
//    if(QMessageBox::Yes == QMessageBox(QMessageBox::Warning, "Do you want to save?",
//                                       "Any unsaved changes to Tuning Traffic will be lost.\nDo you want to save them?",
//                                       QMessageBox::Yes|QMessageBox::No).exec()) {
//        ui->csSaveButton->clicked();
//        ui->psSaveButton->clicked();
//        ui->mobilitySaveButton->clicked();
//    }
    emit saveTuningTrafficData(projectName, trafficFileName, tuningTrafficData);
    this->close();
}

void TuningTrafficManager::on_cancelButton_clicked()
{
    this->close();
}

void TuningTrafficManager::on_csComboBox_currentIndexChanged(int index)
{
    if(index != 0) {
        ui->csDurationLineEdit->setEnabled(true);
        ui->csIntensityLineEdit->setEnabled(true);
        ui->csDurationLineEdit->setText(QString::number(tuningTrafficData.csParamGroup.at(index-1)->callDuration));
        ui->csIntensityLineEdit->setText(QString::number(tuningTrafficData.csParamGroup.at(index-1)->callIntensity));
        if(index == 4) {
            ui->recoveryStartIntervalLineEdit->setEnabled(true);
            ui->recoveryStartIntervalLineEdit->setText(QString::number(tuningTrafficData.csParamGroup.at(index-1)->recoveryStartInterval));
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
    if(index != 0) {
        ui->psDurationLineEdit->setEnabled(true);
        ui->psIntensityLineEdit->setEnabled(true);
        ui->psDurationLineEdit->setText(QString::number(tuningTrafficData.psParamGroup.at(index-1)->psDuration));
        ui->psIntensityLineEdit->setText(QString::number(tuningTrafficData.psParamGroup.at(index-1)->psIntensity));
    }else {
        ui->psDurationLineEdit->setEnabled(false);
        ui->psIntensityLineEdit->setEnabled(false);
        ui->psDurationLineEdit->setText("");
        ui->psIntensityLineEdit->setText("");
    }
}

void TuningTrafficManager::on_mobilityComboBox_currentIndexChanged(int index)
{
    if(index != 0) {
        ui->granularityLineEdit->setEnabled(true);
        ui->speedLineEdit->setEnabled(true);
        ui->granularityLineEdit->setText(QString::number(tuningTrafficData.mobilityGroup.at(index-1)->granularity));
        ui->speedLineEdit->setText(QString::number(tuningTrafficData.mobilityGroup.at(index-1)->speed));
    }else {
        ui->granularityLineEdit->setEnabled(false);
        ui->speedLineEdit->setEnabled(false);
        ui->granularityLineEdit->setText("");
        ui->speedLineEdit->setText("");
    }
}

void TuningTrafficManager::on_restoreButton_clicked()
{
//    emit restoreTuningTrafficData(projectName,trafficFileName);
//    ui->csComboBox->setCurrentIndex(0);
//    ui->psComboBox->setCurrentIndex(0);
//    ui->mobilityComboBox->setCurrentIndex(0);
}
