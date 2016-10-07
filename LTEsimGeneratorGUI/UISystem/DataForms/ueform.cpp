#include "ueform.h"
#include "ui_ueform.h"
#include <QMessageBox>
UeForm::UeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UeForm)
{
    ui->setupUi(this);
    this->ui->lbl_2->setToolTip("Name of the UE component e.g. \"ue1\"");
    this->ui->lbl_3->setToolTip("Space separated string with TYPE;instance tuples where allowed values of TYPE is UCTOOL e.g \"UCTOOL;uctool1\"  ");
    this->ui->lbl_5->setToolTip("Path e.g. \"/etc/alternatives/ltesim-root/ltesim/internal/ltesim-plugin-filters/com/ericsson/sps/ltesim/ue/rrc/filter\"");
    this->ui->lbl_7->setToolTip("Used to control which integrity protection and ciphering algorithms a UE supports");
    this->ui->lbl_6->setToolTip("The algorithm used during EPS AKA procedure.");
    this->ui->lbl_4->setToolTip("Used for MILENAGE");
    this->ui->lbl_8->setToolTip("The OP used in the MILENAGE algorithm. Also used in simulated MME.");
    emit enableUBSim(ueParameters.startUeComponent);
}

UeForm::~UeForm()
{
    delete ui;
}

void UeForm::loadAndOpen(const UeParameters &ueParameters, const QString &projectName,bool enable) {
    this->ueParameters=ueParameters;
    this->projectName = projectName;
    this->updateUi();
    if(ueParameters.startUeComponent) {
        this->enableWindow(ueParameters.startUeComponent);
        this->setReadOnly(!enable);
    } else {
        this->setReadOnly(!enable);
        this->enableWindow(ueParameters.startUeComponent);
    }
        this->setWindowFlags( Qt::Dialog | Qt::WindowStaysOnTopHint);
    this->show();
}

void UeForm::getParameters()
{
    this->ueParameters.name = this->ui->tet_name->text();
    this->ueParameters.managers = this->ui->tet_l1l2_managers->text();
    this->ueParameters.pluginFilterPath = this->ui->tet_rrc_pluginFilterPath->text();
    this->ueParameters.ueNetworkCapability = this->ui->tet_ue_network_capability->text();
    this->ueParameters.ueKeyDerivationAlgorithm = this->ui->tet_ue_keyDerivationAlgorithm->text();
    this->ueParameters.ueKey = this->ui->tet_ue_key->text();
    this->ueParameters.ueOp = this->ui->tet_ue_op->text();
    this->ueParameters.startUeComponent = this->ui->checkBox->isChecked();
}

void UeForm::updateUi()
{
    this->ui->tet_name->setText(this->ueParameters.name);
    this->ui->tet_l1l2_managers->setText(this->ueParameters.managers);
    this->ui->tet_rrc_pluginFilterPath->setText(this->ueParameters.pluginFilterPath);
    this->ui->tet_ue_network_capability->setText(this->ueParameters.ueNetworkCapability);
    this->ui->tet_ue_keyDerivationAlgorithm->setText(this->ueParameters.ueKeyDerivationAlgorithm);
    this->ui->tet_ue_key->setText(this->ueParameters.ueKey);
    this->ui->tet_ue_op->setText(this->ueParameters.ueOp);
    this->ui->checkBox->setChecked(this->ueParameters.startUeComponent);
}

void UeForm::on_restoreDefault_clicked()
{
    this->updateUi();
}

void UeForm::on_OkButton_clicked()
{
    this->getParameters();
    emit updateUeSettings(ueParameters,projectName);
    this->close();
}

void UeForm::on_CancelButton_clicked()
{
    this->close();
}

void UeForm::setReadOnly(bool value)
{
    this->ui->tet_l1l2_managers->setEnabled(value);
    this->ui->tet_name->setEnabled(value);
    this->ui->tet_rrc_pluginFilterPath->setEnabled(value);
    this->ui->tet_ue_key->setEnabled(value);
    this->ui->tet_ue_keyDerivationAlgorithm->setEnabled(value);
    this->ui->tet_ue_network_capability->setEnabled(value);
    this->ui->tet_ue_op->setEnabled(value);
    this->ui->checkBox->setEnabled(value);
    this->ui->restoreDefault->setEnabled(value);
    this->ui->OkButton->setEnabled(value);
}

void UeForm::enableWindow(bool start)
{
    this->ui->tet_l1l2_managers->setEnabled(start);
    this->ui->tet_name->setEnabled(start);
    this->ui->tet_rrc_pluginFilterPath->setEnabled(start);
    this->ui->tet_ue_key->setEnabled(start);
    this->ui->tet_ue_keyDerivationAlgorithm->setEnabled(start);
    this->ui->tet_ue_network_capability->setEnabled(start);
    this->ui->tet_ue_op->setEnabled(start);
}

void UeForm::on_checkBox_stateChanged(int arg1)
{
    ueParameters.startUeComponent=arg1;
    this->enableWindow(arg1);
    emit enableUBSim(arg1);
}
