#include "ubsimform.h"
#include "ui_ubsimform.h"
#include <Maps/Parameters/MapWindow/mapwindow.h>

extern MapWindow *map_w;
UBsimForm::UBsimForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UBsimForm)
{
    ui->setupUi(this);
    this->ui->lbl_2->setToolTip("Name of the UE component e.g. \"ue1\"");
    this->ui->lbl_3->setToolTip("Space separated string with TYPE;instance tuples where allowed values of TYPE is UCTOOL e.g \"UCTOOL;uctool1\"  ");
    this->ui->lbl_5->setToolTip("Path e.g. \"/etc/alternatives/ltesim-root/ltesim/internal/ltesim-plugin-filters/com/ericsson/sps/ltesim/ue/rrc/filter\"");
    this->ui->lbl_7->setToolTip("Used to control which integrity protection and ciphering algorithms a UE supports");
    this->ui->lbl_6->setToolTip("The algorithm used during EPS AKA procedure.");
    this->ui->lbl_4->setToolTip("Used for MILENAGE");
    this->ui->lbl_8->setToolTip("The OP used in the MILENAGE algorithm. Also used in simulated MME.");
    this->ui->lbl_9->setToolTip("IMSI range used by traffic models specified by (space separated string): \"<first_range> <second_range>\" e.g. \"262800100326000+1499 262800100329000+1499\" ");
    this->ui->lbl_10->setToolTip("Directory containing users UE type definitions");
    this->ui->lbl_11->setToolTip("Directory containing users CS traffic Models");
    this->ui->lbl_12->setToolTip("Directory containing users PS traffic Models");
    this->ui->lbl_13->setToolTip("Directory containing users Mobility Models");
    this->ui->lbl_14->setToolTip("UBsim code in UBsim project (ubsim.jar)");
}

UBsimForm::~UBsimForm()
{
    delete ui;
}

void UBsimForm::loadAndOpen(const UBSimSettings &ubSimSettings, const QString &projectName) {
    this->ubSimSettings = ubSimSettings;
    this->projectName = projectName;
    this->setParameters();
    this->show();
}

void UBsimForm::on_buttonBox_accepted()
{
    this->getParameters();
    if(QMessageBox::Yes == QMessageBox(QMessageBox::Information, "UBSimSettings", "Are you sure?", QMessageBox::Yes|QMessageBox::No).exec()){
        emit updateUBSimSettings(ubSimSettings, projectName);
        this->close();
    }
}

void UBsimForm::on_buttonBox_rejected()
{
    this->close();
}

void UBsimForm::on_pbReset_clicked()
{
    this->setParameters();
}

void UBsimForm::getParameters()
{
    this->ubSimSettings.name = this->ui->tet_name->text();
    this->ubSimSettings.l1l2_managers = this->ui->tet_l1l2_managers->text();
    this->ubSimSettings.rrc_pluginFilterPath = this->ui->tet_rrc_pluginFilterPath->text();
    this->ubSimSettings.ue_network_capability = this->ui->tet_ue_network_capability->text();
    this->ubSimSettings.ue_keyDerivationAlgorithm = this->ui->tet_ue_keyDerivationAlgorithm->text();
    this->ubSimSettings.ue_key = this->ui->tet_ue_key->text();
    this->ubSimSettings.ue_op = this->ui->tet_ue_op->text();
    this->ubSimSettings.imsiMapRange = this->ui->tet_imsiMapRange->text();
    this->ubSimSettings.ueTypesDir = this->ui->tet_ueTypesDir->text();
    this->ubSimSettings.csTrafficModelsDir = this->ui->tet_csTrafficModelsDir->text();
    this->ubSimSettings.psTrafficModelsDir = this->ui->tet_psTrafficModelsDir->text();
    this->ubSimSettings.mobilityModelsDir = this->ui->tet_mobilityModelsDir->text();
    this->ubSimSettings.UBSimGui = this->ui->ubSimGuiCheckbox->isChecked();
    this->ubSimSettings.ubsim_patches = this->ui->tet_ubsim_patches->text();
}

void UBsimForm::setParameters()
{
    this->ui->tet_name->setText(this->ubSimSettings.name);
    this->ui->tet_l1l2_managers->setText(this->ubSimSettings.l1l2_managers);
    this->ui->tet_rrc_pluginFilterPath->setText(this->ubSimSettings.rrc_pluginFilterPath);
    this->ui->tet_ue_network_capability->setText(this->ubSimSettings.ue_network_capability);
    this->ui->tet_ue_keyDerivationAlgorithm->setText(this->ubSimSettings.ue_keyDerivationAlgorithm);
    this->ui->tet_ue_key->setText(this->ubSimSettings.ue_key);
    this->ui->tet_ue_op->setText(this->ubSimSettings.ue_op);
    this->ui->tet_imsiMapRange->setText(this->ubSimSettings.imsiMapRange);
    this->ui->tet_ueTypesDir->setText(this->ubSimSettings.ueTypesDir);
    this->ui->tet_csTrafficModelsDir->setText(this->ubSimSettings.csTrafficModelsDir);
    this->ui->tet_psTrafficModelsDir->setText(this->ubSimSettings.psTrafficModelsDir);
    this->ui->tet_mobilityModelsDir->setText(this->ubSimSettings.mobilityModelsDir);
    this->ui->ubSimGuiCheckbox->setChecked(this->ubSimSettings.UBSimGui);
    this->ui->tet_ubsim_patches->setText(this->ubSimSettings.ubsim_patches);
}
