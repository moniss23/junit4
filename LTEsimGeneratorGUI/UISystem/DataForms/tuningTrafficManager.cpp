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

    QDoubleValidator* doubleValidator = new QDoubleValidator(0.001,100.000,3,this);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);
    doubleValidator->setBottom(0.001);
    doubleValidator->setTop(100.000);
    doubleValidator->setRange(0.001,100.000,3);

    ui->csIntensityLineEdit->setValidator(doubleValidator);
    ui->csDurationLineEdit->setValidator(doubleValidator);
    ui->recoveryStartIntervalLineEdit->setValidator(doubleValidator);
    ui->psIntensityLineEdit->setValidator(doubleValidator);
    ui->psDurationLineEdit->setValidator(doubleValidator);
    ui->granularityLineEdit->setValidator(doubleValidator);
    ui->speedLineEdit->setValidator(doubleValidator);
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

    this->setWindowFlags( Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
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
                it.recoveryStartInterval = ui->csIntensityLineEdit->text().replace(',','.').toDouble();
            }
            it.callDuration=ui->csDurationLineEdit->text().replace(',','.').toDouble();
            it.callIntensity=ui->csIntensityLineEdit->text().replace(',','.').toDouble();
            return;
        }
    }
}

void TuningTrafficManager::on_psSaveButton_clicked()
{
    QString currentText = this->ui->psComboBox->currentText();
    if(currentText == "None item" || currentText == "NoPs") {
        return;
    }
    for (TuningTrafficData::PSParameters &it:this->tuningTrafficData.psParamGroup) {
        if (it.psName == currentText) {
            it.psDuration=ui->psDurationLineEdit->text().replace(',','.').toDouble();
            it.psIntensity=ui->psIntensityLineEdit->text().replace(',','.').toDouble();
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
            it.speed=ui->speedLineEdit->text().replace(',','.').toDouble();
            it.granularity=ui->granularityLineEdit->text().replace(',','.').toDouble();
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
        ui->recoveryStartIntervalLineEdit->setText(QString::number(tuningTrafficData.csParamGroup.at(index).recoveryStartInterval).replace('.',','));
    }else {
        ui->recoveryStartIntervalLineEdit->setEnabled(false);
        ui->recoveryStartIntervalLineEdit->setText("");
    }
    for (TuningTrafficData::CSParameters &it:this->tuningTrafficData.csParamGroup) {
        if (it.csName == this->ui->csComboBox->currentText()) {
            ui->csDurationLineEdit->setText(QString::number(it.callDuration).replace('.',','));
            ui->csIntensityLineEdit->setText(QString::number(it.callIntensity).replace('.',','));
        }
    }
}

void TuningTrafficManager::on_psComboBox_currentIndexChanged(int index)
{
    if (index<=0 || ui->psComboBox->currentText() == "NoPs") {
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
            ui->psDurationLineEdit->setText(QString::number(it.psDuration).replace('.',','));
            ui->psIntensityLineEdit->setText(QString::number(it.psIntensity).replace('.',','));
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
            ui->speedLineEdit->setText(QString::number(it.speed).replace('.',','));
            ui->granularityLineEdit->setText(QString::number(it.granularity).replace('.',','));
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
