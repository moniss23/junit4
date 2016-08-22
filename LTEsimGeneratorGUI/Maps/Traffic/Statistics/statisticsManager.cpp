#include "statisticsManager.h"
#include "ui_statisticsForm.h"
#include <QLabel>
#include <QMessageBox>

StatisticsManager::StatisticsManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsForm)
{
    ui->setupUi(this);
    this->setFixedSize(360, 400);
    this->setWindowTitle("Statistics");
    this->checkBoxes = new QVector<QCheckBox*>();
    this->wereChangesMade = false;
    this->isUiSetUp = false;
}

StatisticsManager::~StatisticsManager() {
    delete ui;
}

void StatisticsManager::showStatisticsWindow(const StatisticsData &statisticsData)
{
    localStats = statisticsData;

    if(this->checkBoxes->empty()) {
        for(auto name: statisticsData.namesList) {
            QCheckBox* checkBox = new QCheckBox();
            checkBox->setObjectName(name);
            checkBox->setText(name);
            checkBox->setChecked(localStats.getStatMapFor(name));
            connect(checkBox,&QCheckBox::clicked,[=]() {
                localStats.setStatMapFor(checkBox->objectName());
                this->wereChangesMade = true;
            });
            checkBoxes->push_back(checkBox);
        }
    }

    if(!isUiSetUp) {
        int iter=0;

        QWidget* generalSettingsTab = new QWidget();
        QWidget* IPGWTGSettingsTab = new QWidget();
        QWidget* PDCP_USettingsTab = new QWidget();
        QVBoxLayout* generalTabLayout = new QVBoxLayout();
        QVBoxLayout* IPGWTGTabLayout = new QVBoxLayout();
        QVBoxLayout* PDCP_UTabLayout = new QVBoxLayout();

        for(auto checkBox : *checkBoxes){
            if(iter<12) {
                generalTabLayout->addWidget(checkBox);
            }else if(iter<15) {
                IPGWTGTabLayout->addWidget(checkBox);
            }else {
                PDCP_UTabLayout->addWidget(checkBox);
            }
            iter++;
        }

        QSpacerItem* vSpacer = new QSpacerItem(360,400);

        generalTabLayout->addSpacerItem(vSpacer);
        IPGWTGTabLayout->addSpacerItem(vSpacer);
        PDCP_UTabLayout->addSpacerItem(vSpacer);

        generalSettingsTab->setLayout(generalTabLayout);
        IPGWTGSettingsTab->setLayout(IPGWTGTabLayout);
        PDCP_USettingsTab->setLayout(PDCP_UTabLayout);

        ui->statisticsTabs->addTab(generalSettingsTab,"General");
        ui->statisticsTabs->addTab(IPGWTGSettingsTab,"IPGWTG");
        ui->statisticsTabs->addTab(PDCP_USettingsTab,"IPGWTG and PDCP-U");

        this->isUiSetUp = true;
    }else {
        for(auto checkBox : *checkBoxes) {
            checkBox->setChecked(localStats.getStatMapFor(checkBox->objectName()));
        }
    }
    ui->statisticsTabs->setCurrentIndex(0);
}

void StatisticsManager::on_saveButton_clicked()
{
    if(this->wereChangesMade) {
        emit updateStatisticsData(localStats); // {TrafficWindow.TrafficFile.StatisticsData = localStats;}
        this->wereChangesMade = false;
    }else {
        QMessageBox(QMessageBox::Warning,"Cannot save.","No changes were made.",QMessageBox::Ok);
    }
}

void StatisticsManager::on_restoreButton_clicked()
{
    emit restoreDefaultValues(); //{localStats = TraficWindow.TrafficFileData.StatisticsData;}
    for(auto checkBox : *checkBoxes) {
        checkBox->setChecked(localStats.getStatMapFor(checkBox->objectName()));
    }
}
