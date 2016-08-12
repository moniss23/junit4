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

void StatisticsManager::setParameters(StatisticsData *statistics, DataSystem* appsettings) {
    this->statisticsPtr = statistics;

    QString mapIndex = statistics->getMapIndex();
    localStatistics = new StatisticsData(mapIndex, appsettings);

    //Check boxes in a vector.
    if(this->checkBoxes->empty()) {
        for(int i=0;i<=20;i++) {
        QCheckBox* checkBox = new QCheckBox();
        checkBox->setObjectName(statisticsPtr->getStringFromEnum(i));
        Stats_settings setting = static_cast<Stats_settings>(i);
        checkBox->setChecked(statisticsPtr->getStatMap(setting));
        connect(checkBox,&QCheckBox::clicked,[=]() {
            QString* name = new QString(checkBox->objectName());
            Stats_settings* setting = new Stats_settings(statisticsPtr->getEnumFromString(*name));
            localStatistics->setStatMap(*setting);
            wereChangesMade = true;
        });
        checkBoxes->push_back(checkBox);
        }
        checkBoxes->at(0)->setText("Listing Static Information for Each UE");
        checkBoxes->at(1)->setText("Resetting All Statistics Counters");
        checkBoxes->at(2)->setText("Listing Statistics on NAS");
        checkBoxes->at(3)->setText("Listing Statistics on RRC");
        checkBoxes->at(4)->setText("Listing Mobility Statistics per Model and Area");
        checkBoxes->at(5)->setText("Listing Throughput Statistics per Area and Model");
        checkBoxes->at(6)->setText("Listing Throughput Statistics per UE and Model");
        checkBoxes->at(7)->setText("Listing Mobility Statistics per UE");
        checkBoxes->at(8)->setText("Listing PS Statistics per Model");
        checkBoxes->at(9)->setText("Listing PS Statistics per UE");
        checkBoxes->at(10)->setText("Listing CS Statistics per Model");
        checkBoxes->at(11)->setText("Listing CS Statistics per UE");
        checkBoxes->at(12)->setText("Protocol Statistics");
        checkBoxes->at(13)->setText("TGU Statistics");
        checkBoxes->at(14)->setText("Countinuous Statistics");
        checkBoxes->at(15)->setText("Protocol Statistics");
        checkBoxes->at(16)->setText("ROHC Protocol Statistics");
        checkBoxes->at(17)->setText("General Bearer information");
        checkBoxes->at(18)->setText("Bearer ROHC information");
        checkBoxes->at(19)->setText("Bearer Error Statistics");
        checkBoxes->at(20)->setText("Continuous Statistics");
    }

    int iter=0;

    if(!isUiSetUp) {
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
            Stats_settings setting = static_cast<Stats_settings>(iter);
            checkBox->setChecked(statistics->getStatMap(setting));
            iter++;
        }
    }
    ui->statisticsTabs->setCurrentIndex(0);
}

void StatisticsManager::on_saveButton_clicked()
{
    if(wereChangesMade) {
        *statisticsPtr = *localStatistics;
        wereChangesMade = false;
    }else {
        QMessageBox(QMessageBox::Warning,"Cannot save.","No changes were made.",QMessageBox::Ok);
    }
}

void StatisticsManager::on_restoreButton_clicked()
{
    int iter = 0;
    for(auto checkBox : *checkBoxes) {
        Stats_settings setting = static_cast<Stats_settings>(iter);
        bool defaultValue = false;
        localStatistics->setStatMap(setting, defaultValue);
        checkBox->setChecked(false);
        iter++;
    }
    *statisticsPtr = *localStatistics;
}
