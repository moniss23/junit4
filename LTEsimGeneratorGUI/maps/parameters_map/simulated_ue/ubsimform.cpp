#include "ubsimform.h"
#include "ui_ubsimform.h"
#include "maps/parameters_map/mapwindow.h"
#include "maps/parameters_map/mapwindowlarge.h"
extern MapWindow *map_w;
extern MapWindowLarge *map_wl;
UBsimForm::UBsimForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UBsimForm)
{
    ui->setupUi(this);
    flagConfirmNewValue = true;
    wasThereChanges=false;
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

void UBsimForm::set_checkboxactive(bool check)
{
    checkboxactive=check;
}

bool UBsimForm::get_checkboxactive()
{
    return  checkboxactive;
}

UBsimForm::~UBsimForm()
{
    delete ui;
}

void UBsimForm::setParameters(Ue *ue)
{
    this->ue = ue;
    ui->tet_name->setText(ue->getName());
    ui->tet_l1l2_managers->setText(ue->getL1l2_managers());
    ui->tet_rrc_pluginFilterPath->setText(ue->getRrc_pluginFilterPath());
    ui->tet_ue_network_capability->setText(ue->getUe_network_capability());
    ui->tet_ue_keyDerivationAlgorithm->setText(ue->getUe_keyDerivationAlgorithm());
    ui->tet_ue_key->setText(ue->getUe_key());
    ui->tet_ue_op->setText(ue->getUe_op());

    ui->tet_imsiMapRange->setText(ue->getImsiMapRange());

    ui->tet_ueTypesDir->setText(ue->getUeTypesDir());
    ui->tet_csTrafficModelsDir->setText(ue->getCsTrafficModelsDir());
    ui->tet_psTrafficModelsDir->setText(ue->getPsTrafficModelsDir());
    ui->tet_mobilityModelsDir->setText(ue->getMobilityModelsDir());
    ui->checkBox_Visualization->setChecked(ue->getVisualization());
    ui->tet_ubsim_patches->setText(ue->getUbsim_patches());

    ui->gbUBsim->setEnabled(ue->getStart_ue_component());
}

void UBsimForm::on_buttonBox_accepted()
{
    this->close();
    if(wasChangesBeforeAccept())
        setChanges();
    msg.setText(" Changes has been succesfully approved ");
    if(flagConfirmNewValue && wasThereChanges )
        msg.exec();
    wasThereChanges=false;
}

void UBsimForm::on_buttonBox_rejected()
{
    if(wasChangesBeforeAccept())
    {
        msgBox.setWindowTitle("Warning");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setText(trUtf8(("File was changed")));
        msgBox.setInformativeText(trUtf8("Do you want to save changes?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);

    int ret = msgBox.exec();

    switch (ret) {
      case QMessageBox::Save:
           setChanges();
           this->close();
         break;
      case QMessageBox::Discard:
            this->close();
         break;
      case QMessageBox::Cancel:
           msgBox.close();
         break;
      default:
        // this part should never work
         break;
                }
    }else
    {
        this->close();
    }
    wasThereChanges=false;
}

void UBsimForm::on_tet_name_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_name->text() != ue->getName())){
        ue->setName(ui->tet_name->text());
        wasThereChanges=true;
        msg.setText(" name: "+ ue->getName() );
        msg.exec();
    }else
     ue->setName(ui->tet_name->text());
}

void UBsimForm::on_tet_l1l2_managers_returnPressed()
{
    if(flagConfirmNewValue && ( ui->tet_l1l2_managers->text() != ue->getL1l2_managers())){
    ue->setL1l2_managers(ui->tet_l1l2_managers->text());
    wasThereChanges=true;
    msg.setText("L1l2_managers: "+ ue->getL1l2_managers() );
    msg.exec();
    }else
    ue->setL1l2_managers(ui->tet_l1l2_managers->text());
}

void UBsimForm::on_tet_rrc_pluginFilterPath_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_rrc_pluginFilterPath->text() != ue->getRrc_pluginFilterPath())){
        ue->setRrc_pluginFilterPath(ui->tet_rrc_pluginFilterPath->text());
        wasThereChanges=true;
        msg.setText("Rrc_pluginFilterPath: "+ ue->getRrc_pluginFilterPath() );
        msg.exec();
    }else
    ue->setRrc_pluginFilterPath(ui->tet_rrc_pluginFilterPath->text());
}

void UBsimForm::on_tet_ue_network_capability_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_ue_network_capability->text() != ue->getUe_network_capability())){
        ue->setUe_network_capability(ui->tet_ue_network_capability->text());
        wasThereChanges=true;
        msg.setText("Ue_network_capability: "+ ue->getUe_network_capability());
        msg.exec();
    }else
    ue->setUe_network_capability(ui->tet_ue_network_capability->text());
}

void UBsimForm::on_tet_ue_keyDerivationAlgorithm_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_ue_keyDerivationAlgorithm->text() != ue->getUe_keyDerivationAlgorithm())){
        ue->setUe_keyDerivationAlgorithm(ui->tet_ue_keyDerivationAlgorithm->text());
        wasThereChanges=true;
        msg.setText("Ue_keyDerivationAlgorithm: "+ ue->getUe_keyDerivationAlgorithm());
        msg.exec();
    }else
    ue->setUe_keyDerivationAlgorithm(ui->tet_ue_keyDerivationAlgorithm->text());
}

void UBsimForm::on_tet_ue_key_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_ue_key->text() != ue->getUe_key())){
        ue->setUe_key(ui->tet_ue_key->text());
        wasThereChanges=true;
        msg.setText("Ue_key: "+ ue->getUe_key());
        msg.exec();
    }else
    ue->setUe_key(ui->tet_ue_key->text());
}

void UBsimForm::on_tet_ue_op_returnPressed()
{
     if(flagConfirmNewValue && (ui->tet_ue_op->text() != ue->getUe_op())){
          ue->setUe_op(ui->tet_ue_op->text());
          wasThereChanges=true;
          msg.setText("Ue_op: "+ ue->getUe_op());
          msg.exec();
     }else
    ue->setUe_op(ui->tet_ue_op->text());
}

void UBsimForm::on_tet_imsiMapRange_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_imsiMapRange->text() != ue->getImsiMapRange())){
         ue->setImsiMapRange(ui->tet_imsiMapRange->text());
         wasThereChanges=true;
         msg.setText("ImsiMapRange: "+ue->getImsiMapRange() );
         msg.exec();
    }else
    ue->setImsiMapRange(ui->tet_imsiMapRange->text());
}

void UBsimForm::on_tet_ueTypesDir_returnPressed()
{
     if(flagConfirmNewValue && (ui->tet_ueTypesDir->text() != ue->getUeTypesDir())){
        ue->setUeTypesDir(ui->tet_ueTypesDir->text());
        wasThereChanges=true;
        msg.setText("UeTypesDir: "+ ue->getUeTypesDir());
        msg.exec();
     }else
     ue->setUeTypesDir(ui->tet_ueTypesDir->text());
}

void UBsimForm::on_tet_csTrafficModelsDir_returnPressed()
{
     if(flagConfirmNewValue && (ui->tet_csTrafficModelsDir->text() != ue->getCsTrafficModelsDir())){
         ue->setCsTrafficModelsDir(ui->tet_csTrafficModelsDir->text());
         wasThereChanges=true;
         msg.setText("CsTrafficModelsDir: "+ue->getCsTrafficModelsDir() );
         msg.exec();
     }else
     ue->setCsTrafficModelsDir(ui->tet_csTrafficModelsDir->text());
}

void UBsimForm::on_tet_psTrafficModelsDir_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_psTrafficModelsDir->text() != ue->getPsTrafficModelsDir())){
        ue->setPsTrafficModelsDir(ui->tet_psTrafficModelsDir->text());
        wasThereChanges=true;
        msg.setText("PsTrafficModelsDir: "+ue->getPsTrafficModelsDir() );
        msg.exec();
    }else
    ue->setPsTrafficModelsDir(ui->tet_psTrafficModelsDir->text());
}

void UBsimForm::on_tet_mobilityModelsDir_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_mobilityModelsDir->text() != ue->getMobilityModelsDir())){
          ue->setMobilityModelsDir(ui->tet_mobilityModelsDir->text());
          wasThereChanges=true;
          msg.setText("MobilityModelsDir: "+ ue->getMobilityModelsDir());
          msg.exec();
    }else
    ue->setMobilityModelsDir(ui->tet_mobilityModelsDir->text());
}

void UBsimForm::on_tet_ubsim_patches_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_ubsim_patches->text() != ue->getUbsim_patches())){
        ue->setUbsim_patches(ui->tet_ubsim_patches->text());
        wasThereChanges=true;
        msg.setText("Ubsim_patches: "+ ue->getUbsim_patches());
        msg.exec();
    }else
    ue->setUbsim_patches(ui->tet_ubsim_patches->text());
}


void UBsimForm::on_checkBox_Visualization_clicked()
{
    ue->setVisualization(ui->checkBox_Visualization->isChecked());
}

void UBsimForm::on_pbReset_clicked()
{

    ue->resetParamsUBSIM();
    setParameters(ue);
    if (map_w!=NULL)
        map_w->resetFlags();
    else if (map_wl!=NULL)
        map_wl->resetFlags();

    if(checkboxactive){
        ue->resetParamsUBSIM();
        setParameters(ue);
        map_w->resetFlags();
        wasThereChanges=false;
    }
}

bool UBsimForm::wasChangesBeforeAccept()
{
    if(ui->tet_name->text() != ue->getName())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_l1l2_managers->text() != ue->getL1l2_managers())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_rrc_pluginFilterPath->text() != ue->getRrc_pluginFilterPath())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_ue_network_capability->text() != ue->getUe_network_capability())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_ue_keyDerivationAlgorithm->text() != ue->getUe_keyDerivationAlgorithm())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_ue_key->text() != ue->getUe_key())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_ue_op->text() != ue->getUe_op())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_imsiMapRange->text() != ue->getImsiMapRange())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_ueTypesDir->text() != ue->getUeTypesDir())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_csTrafficModelsDir->text() != ue->getCsTrafficModelsDir())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_psTrafficModelsDir->text() != ue->getPsTrafficModelsDir())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_mobilityModelsDir->text() != ue->getMobilityModelsDir())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_ubsim_patches->text() != ue->getUbsim_patches())
    {
        wasThereChanges=true;
        return true;
    }else
    {
        return false;
    }
}

void UBsimForm::setChanges()
{
    if(ui->tet_name->text() != ue->getName())
    {
        ue->setName(ui->tet_name->text());
    }
    if(ui->tet_l1l2_managers->text() != ue->getL1l2_managers())
    {
        ue->setL1l2_managers(ui->tet_l1l2_managers->text());
    }
    if(ui->tet_rrc_pluginFilterPath->text() != ue->getRrc_pluginFilterPath())
    {
        ue->setRrc_pluginFilterPath(ui->tet_rrc_pluginFilterPath->text());
    }
    if(ui->tet_ue_network_capability->text() != ue->getUe_network_capability())
    {
        ue->setUe_network_capability(ui->tet_ue_network_capability->text());
    }
    if(ui->tet_ue_keyDerivationAlgorithm->text() != ue->getUe_keyDerivationAlgorithm())
    {
        ue->setUe_keyDerivationAlgorithm(ui->tet_ue_keyDerivationAlgorithm->text());
    }
    if(ui->tet_ue_key->text() != ue->getUe_key())
    {
        ue->setUe_key(ui->tet_ue_key->text());
    }
    if(ui->tet_ue_op->text() != ue->getUe_op())
    {
        ue->setUe_op(ui->tet_ue_op->text());
    }
    if(ui->tet_imsiMapRange->text() != ue->getImsiMapRange())
    {
        ue->setImsiMapRange(ui->tet_imsiMapRange->text());
    }
    if(ui->tet_ueTypesDir->text() != ue->getUeTypesDir())
    {
        ue->setUeTypesDir(ui->tet_ueTypesDir->text());
    }
    if(ui->tet_csTrafficModelsDir->text() != ue->getCsTrafficModelsDir())
    {
        ue->setCsTrafficModelsDir(ui->tet_csTrafficModelsDir->text());
    }
    if(ui->tet_psTrafficModelsDir->text() != ue->getPsTrafficModelsDir())
    {
        ue->setPsTrafficModelsDir(ui->tet_psTrafficModelsDir->text());
    }
    if(ui->tet_mobilityModelsDir->text() != ue->getMobilityModelsDir())
    {
        ue->setMobilityModelsDir(ui->tet_mobilityModelsDir->text());
    }
    if(ui->tet_ubsim_patches->text() != ue->getUbsim_patches())
    {
        ue->setUbsim_patches(ui->tet_ubsim_patches->text());
    }

}
