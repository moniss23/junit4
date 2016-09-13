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

void UBsimForm::loadAndOpen(const UBSimSettings &ubSimSettings, const QString &projectName) {
    this->ubSimSettings = ubSimSettings;
    this->projectName = projectName;
    this->setParameters();
    this->show();
}

void UBsimForm::on_buttonBox_accepted()
{
    this->getParameters();
    emit updateUBSimSettings(ubSimSettings, projectName);
    this->close();
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

    this->ubSimSettings.imsiMapRange = this->ui->tet_imsiMapRange->text();
    this->ubSimSettings.ueTypesDir = this->ui->tet_ueTypesDir->text();
    this->ubSimSettings.csTrafficModelsDir = this->ui->tet_csTrafficModelsDir->text();
    this->ubSimSettings.psTrafficModelsDir = this->ui->tet_psTrafficModelsDir->text();
    this->ubSimSettings.mobilityModelsDir = this->ui->tet_mobilityModelsDir->text();
    this->ubSimSettings.UBSimGui = this->ui->ubSimGuiCheckbox->isChecked();
    this->ubSimSettings.ubsim_patches = this->ui->tet_ubsim_patches->text().split(":");
}

void UBsimForm::setParameters()
{
    this->ui->tet_imsiMapRange->setText(this->ubSimSettings.imsiMapRange);
    this->ui->tet_ueTypesDir->setText(this->ubSimSettings.ueTypesDir);
    this->ui->tet_csTrafficModelsDir->setText(this->ubSimSettings.csTrafficModelsDir);
    this->ui->tet_psTrafficModelsDir->setText(this->ubSimSettings.psTrafficModelsDir);
    this->ui->tet_mobilityModelsDir->setText(this->ubSimSettings.mobilityModelsDir);
    this->ui->ubSimGuiCheckbox->setChecked(this->ubSimSettings.UBSimGui);
    QString ubSimPatches;
    for (int i=0;i<ubSimSettings.ubsim_patches.size();i++){
        ubSimPatches.append(ubSimSettings.ubsim_patches[i]+":");
    }
    this->ui->tet_ubsim_patches->setText(ubSimPatches);
}
