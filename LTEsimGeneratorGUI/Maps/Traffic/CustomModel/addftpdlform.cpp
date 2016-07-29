#include "addftpdlform.h"
#include "ui_addftpdlform.h"
#include <QMessageBox>

QList<QString> FtpDlList;

AddFtpDlForm::AddFtpDlForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFtpDlForm)
{
    ui->setupUi(this);
    this->setWindowTitle("FTP Dl");
    qciAddFtpDlPointer = ui->qciComboFtpDl;

    ui->tet_filesize->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->tet_minThroughput->setValidator(new QIntValidator(0, INT_MAX, this));

    ui->qciComboFtpDl->addItem("");
    for(int i=1; i<10; i++){
        QString index = QString::number(i);
        ui->qciComboFtpDl->addItem(index);
    }
}

AddFtpDlForm::~AddFtpDlForm()
{
    delete ui;
}

void AddFtpDlForm::on_tet_filesize_returnPressed()
{
    addftpdl->setFilesize(ui->tet_filesize->text());
}

void AddFtpDlForm::on_tet_minThroughput_returnPressed()
{
    addftpdl->setMinthroughput(ui->tet_minThroughput->text());
}

void AddFtpDlForm::on_bt_save_clicked()
{
    SaveAll();
    this->close();
}

void AddFtpDlForm::on_bt_cancel_clicked()
{
    this->close();
}

void AddFtpDlForm::SaveAll()
{
    addftpdl->setQci(ui->qciComboFtpDl->currentText());
    addftpdl->setFilesize(ui->tet_filesize->text());
    addftpdl->setMinthroughput(ui->tet_minThroughput->text());
}

void AddFtpDlForm::setParameters(Addftpdl *addftpdl)
{
    this->addftpdl = addftpdl;
    ui->qciComboFtpDl->setCurrentText(addftpdl->getQci());
    ui->tet_filesize->setText(addftpdl->getFilesize());
    ui->tet_minThroughput->setText(addftpdl->getMinthroughput());
}

void AddFtpDlForm::addToList(){
    FtpDlList.clear();
    FtpDlList.append("AddFtpDl\nQCI:");
    FtpDlList.append(ui->qciComboFtpDl->currentText());
    FtpDlList.append("FileSize:");
    FtpDlList.append(ui->tet_filesize->text());
    FtpDlList.append("Min Throughtput:");
    FtpDlList.append(ui->tet_minThroughput->text());
}
