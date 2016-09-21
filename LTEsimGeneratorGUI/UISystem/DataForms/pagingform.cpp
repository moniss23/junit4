#include "pagingform.h"
#include "ui_pagingform.h"

PagingForm::PagingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PagingForm)
{
    ui->setupUi(this);
    this->ui->lbl_2->setToolTip("Number of paging generators");
    this->ui->lbl_3->setToolTip("Name of the paging generators e.g. \"pagings1\",\"pagings2\",\"pagings3\" ");
    this->ui->lbl_5->setToolTip("The IMSI range which pagings are generated by each generator e.g. \"100000+100\",\"200000+100\",\"300000+100\"");
    this->ui->lbl_7->setToolTip("Used to generate GUMMEI e.g. \"AA\", \"AB\", \"AC\"");
    this->ui->lbl_6->setToolTip("Can be IMSI or STMSI e.g. \"IMSI\"");
    this->ui->lbl_4->setToolTip("The IP addresses must be available on the LTEsim server and reachable from the eNB CP interface, e.g. \"sctp://127.0.1.1:36412\"");
    emit enablePagingRate(pagingSettings.isUsedInConfiguration);
}



PagingForm::~PagingForm()
{
    delete ui;
}

void PagingForm::loadAndSpawn(const PagingSettings &pagingSettings, const QString &projectName, bool enable)
{
    this->pagingSettings = pagingSettings;
    this->projectName = projectName;
    this->setDefaultParameters();
    this->setEnabled(!enable);
    this->enableWindow(pagingSettings.isUsedInConfiguration);
    this->show();
}

void PagingForm::setDefaultParameters()
{
    this->ui->tet_generators->setText(QString::number(pagingSettings.generators));
    QString pagingNames;
    for (QString name:pagingSettings.names) {
        pagingNames+=(name+",");
    }
    this->ui->tet_paging_generator_names->setText(pagingNames);
    QString pagingRanges;
    for (QString range:pagingSettings.imsiRanges) {
        pagingRanges+=(range+",");
    }
    this->ui->tet_imsi_ranges->setText(pagingRanges);
    this->ui->tet_ue_paging_identity->setText(pagingSettings.uePagingIdentity);
    QString pagingUris;
    for (QString ur:pagingSettings.pagingSlapUris) {
        pagingUris+=(ur+",");
    }
    this->ui->tet_paging_s1ap_uris->setText(pagingUris);
    this->ui->checkBox_generate_pagings->setChecked(pagingSettings.isUsedInConfiguration);

}

void PagingForm::setChanges()
{
        pagingSettings.generators = this->ui->tet_generators->text().toInt();
        pagingSettings.names = this->ui->tet_paging_generator_names->text().split(",",QString::SkipEmptyParts);
        pagingSettings.imsiRanges = this->ui->tet_imsi_ranges->text().split(",");
        if (this->ui->tet_ue_paging_identity->text() == "IMSI") {
            pagingSettings.uePagingIdentity = "IMSI";
        }
        else if (this->ui->tet_ue_paging_identity->text() == "STMSI") {
            pagingSettings.uePagingIdentity = "STMSI";
        }
        pagingSettings.pagingSlapUris = this->ui->tet_paging_s1ap_uris->text().split(",");
        pagingSettings.isUsedInConfiguration=this->ui->checkBox_generate_pagings->isChecked();
        emit updatePaging(pagingSettings,projectName);
}


void PagingForm::on_RestoreButton_clicked()
{
    setDefaultParameters();
}

void PagingForm::on_OkButton_clicked()
{
    setChanges();
    emit updatePaging(pagingSettings,projectName);
    this->close();
}

void PagingForm::on_CancelButton_clicked()
{
    this->close();
}
void PagingForm::setReadOnly(bool value)
{
    this->ui->tet_generators->setReadOnly(value);
    this->ui->tet_imsi_ranges->setReadOnly(value);
    this->ui->tet_mme_codes->setReadOnly(value);
    this->ui->tet_paging_generator_names->setReadOnly(value);
    this->ui->tet_paging_s1ap_uris->setReadOnly(value);
    this->ui->tet_ue_paging_identity->setReadOnly(value);
    this->ui->checkBox_bundle_paging->setEnabled(!value);
    this->ui->checkBox_generate_pagings->setEnabled(!value);
    this->ui->checkBox_s1ap_checkASN1_constraints->setEnabled(!value);
}


void PagingForm::on_checkBox_generate_pagings_stateChanged(int arg1)
{
    pagingSettings.isUsedInConfiguration=arg1;
    enableWindow(arg1);
    emit enablePagingRate(arg1);
}
void PagingForm::enableWindow(bool value)
{
    this->ui->tet_generators->setEnabled(value);
    this->ui->tet_imsi_ranges->setEnabled(value);
    this->ui->tet_mme_codes->setEnabled(value);
    this->ui->tet_paging_generator_names->setEnabled(value);
    this->ui->tet_paging_s1ap_uris->setEnabled(value);
    this->ui->tet_ue_paging_identity->setEnabled(value);
    this->ui->checkBox_bundle_paging->setEnabled(value);
    this->ui->checkBox_s1ap_checkASN1_constraints->setEnabled(value);
}
