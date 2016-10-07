#include "ubsimform.h"
#include "ui_ubsimform.h"

#include <QStringList>
#include <QMessageBox>

UBsimForm::UBsimForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UBsimForm)
{
    ui->setupUi(this);

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

void UBsimForm::loadAndOpen(const UBSimSettings &ubSimSettings,const UeParameters &ueParameters, const QString &projectName,bool enable) {
    (void) ueParameters;

    this->ubSimSettings = ubSimSettings;
    this->projectName = projectName;
    this->updateUi();
    if(ueParameters.startUeComponent) {
        this->disableWindow(!ueParameters.startUeComponent);
        this->setReadOnly(!enable);
    }else {
        this->setReadOnly(!enable);
        this->disableWindow(!ueParameters.startUeComponent);
    }
    this->show();
}

void UBsimForm::on_pbReset_clicked()
{
    this->updateUi();
}

void UBsimForm::getParameters()
{

    this->ubSimSettings.imsiMapRange = this->ui->tet_imsiMapRange->text();
    this->ubSimSettings.ueTypesDir = this->ui->tet_ueTypesDir->text();
    this->ubSimSettings.csTrafficModelsDir = this->ui->tet_csTrafficModelsDir->text();
    this->ubSimSettings.psTrafficModelsDir = this->ui->tet_psTrafficModelsDir->text();
    this->ubSimSettings.mobilityModelsDir = this->ui->tet_mobilityModelsDir->text();
    this->ubSimSettings.UBSimGui = this->ui->ubSimGuiCheckbox->isChecked();
    this->ubSimSettings.ubsim_patches = this->ui->tet_ubsim_patches->text().split(":",QString::SkipEmptyParts);
}

void UBsimForm::updateUi()
{
    this->ui->tet_imsiMapRange->setText(this->ubSimSettings.imsiMapRange);
    this->ui->tet_ueTypesDir->setText(this->ubSimSettings.ueTypesDir);
    this->ui->tet_csTrafficModelsDir->setText(this->ubSimSettings.csTrafficModelsDir);
    this->ui->tet_psTrafficModelsDir->setText(this->ubSimSettings.psTrafficModelsDir);
    this->ui->tet_mobilityModelsDir->setText(this->ubSimSettings.mobilityModelsDir);
    this->ui->ubSimGuiCheckbox->setChecked(this->ubSimSettings.UBSimGui);
    QString ubSimPatches;
    for (int i=0;i<ubSimSettings.ubsim_patches.size();i++){
        ubSimPatches.append(ubSimSettings.ubsim_patches[i].remove("\""));
        if (i!=ubSimSettings.ubsim_patches.size()-1){
            ubSimPatches.append(":");
        }
    }
    this->ui->tet_ubsim_patches->setText(ubSimPatches);
}
void UBsimForm::setReadOnly(bool value)
{
    this->ui->tet_csTrafficModelsDir->setEnabled(value);
    this->ui->tet_imsiMapRange->setEnabled(value);
    this->ui->tet_mobilityModelsDir->setEnabled(value);
    this->ui->tet_psTrafficModelsDir->setEnabled(value);
    this->ui->tet_ubsim_patches->setEnabled(value);
    this->ui->tet_ueTypesDir->setEnabled(value);
    this->ui->ubSimGuiCheckbox->setEnabled(value);
    this->ui->pbReset->setEnabled(value);
    this->ui->okButton->setEnabled(value);
}

void UBsimForm::on_ubSimGuiCheckbox_stateChanged(int arg1)
{
    ubSimSettings.UBSimGui = arg1;
}
void UBsimForm::disableWindow(bool state)
{
    this->ui->tet_csTrafficModelsDir->setEnabled(!state);
    this->ui->tet_imsiMapRange->setEnabled(!state);
    this->ui->tet_mobilityModelsDir->setEnabled(!state);
    this->ui->tet_psTrafficModelsDir->setEnabled(!state);
    this->ui->tet_ubsim_patches->setEnabled(!state);
    this->ui->tet_ueTypesDir->setEnabled(!state);
    this->ui->ubSimGuiCheckbox->setEnabled(!state);
}

void UBsimForm::on_okButton_clicked()
{
    this->getParameters();
    emit updateUBSimSettings(ubSimSettings, projectName);
    this->close();
}

void UBsimForm::on_cancelButton_clicked()
{
    this->close();
}
