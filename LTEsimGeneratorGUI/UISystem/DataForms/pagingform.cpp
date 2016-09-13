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
}



PagingForm::~PagingForm()
{
    delete ui;
}

void PagingForm::loadAndSpawn(const PagingSettings &pagingSettings, const QString &projectName)
{
    this->pagingSettings = pagingSettings;
    this->projectName = projectName;
    this->setDefaultParameters();
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

}

void PagingForm::setChanges()
{
        pagingSettings.generators = this->ui->tet_generators->text().toInt();
        pagingSettings.names = this->ui->tet_paging_generator_names->text().split(",");
        pagingSettings.imsiRanges = this->ui->tet_imsi_ranges->text().split(",");
        if (this->ui->tet_ue_paging_identity->text() == "IMSI") {
            pagingSettings.uePagingIdentity = "IMSI";
        }
        else if (this->ui->tet_ue_paging_identity->text() == "STMSI") {
            pagingSettings.uePagingIdentity = "STMSI";
        }
        pagingSettings.pagingSlapUris = this->ui->tet_paging_s1ap_uris->text().split(",");
        emit updatePaging(pagingSettings,projectName);
}


void PagingForm::on_RestoreButton_clicked()
{
    setDefaultParameters();
}

void PagingForm::on_OkButton_clicked()
{
    setChanges();
    msg.setText("Changes has been succesfully approved ");
    msg.exec();
    this->close();
}

void PagingForm::on_CancelButton_clicked()
{
    this->close();
}
