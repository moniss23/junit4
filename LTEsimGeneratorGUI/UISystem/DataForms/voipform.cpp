#include "voipform.h"
#include "ui_voipform.h"

VoipForm::VoipForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VoipForm)
{
    ui->setupUi(this);
}

VoipForm::~VoipForm()
{
    delete ui;
}
