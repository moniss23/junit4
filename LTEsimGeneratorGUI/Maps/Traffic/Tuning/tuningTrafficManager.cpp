#include <QDoubleValidator>
#include <QDebug>

#include "tuningTrafficManager.h"
#include "ui_tuningtrafficform.h"

bool tmp_areaChecked;

//Saved structure of chosen tuning parameters
QStringList tuningParametersContentList;

TuningTrafficManager::TuningTrafficManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TuningTrafficForm)
{
    ui->setupUi(this);
    this->setWindowTitle("Tuning traffic");
    setFixedSize(sizeHint());

    this->ui->csComboBox->addItems(tuningTrafficData.CSSTRINGLIST);
    this->ui->psComboBox->addItems(tuningTrafficData.PSSTRINGLIST);
    this->ui->mobilityComboBox->addItems(tuningTrafficData.MOBILITYSTRINGLIST);

    cancelClicked = false;
    saveClicked = false;
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

void TuningTrafficManager::loadAndSpawn(const QString &projectName, const QString &trafficFileName, const TuningTrafficData &tuningTrafficData)
{
    this->show();
}
