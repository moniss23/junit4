#include "syncedpingform.h"
#include "ui_syncedpingform.h"

SyncedPingForm::SyncedPingForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SyncedPingForm)
{
    ui->setupUi(this);
}

SyncedPingForm::~SyncedPingForm()
{
    delete ui;
}
