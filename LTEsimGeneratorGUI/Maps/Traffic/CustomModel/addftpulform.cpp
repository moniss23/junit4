#include "addftpulform.h"
#include "ui_addftpulform.h"
#include <QMessageBox>

QList<QString> FtpUlList;

AddFtpUlForm::AddFtpUlForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFtpUlForm)
{
    ui->setupUi(this);
    this->setWindowTitle("addFtpUl");
    qciAddFtpUlPointer = ui->qciComboFtpUl;

    ui->tet_filesize->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->tet_minThroughput->setValidator(new QIntValidator(0, INT_MAX, this));

    ui->qciComboFtpUl->addItem("");
    for(int i=1; i<10; i++){
        QString index = QString::number(i);
        ui->qciComboFtpUl->addItem(index);
    }
}

AddFtpUlForm::~AddFtpUlForm()
{
    delete ui;
}

void AddFtpUlForm::on_tet_filesize_returnPressed()
{
    addftpul->setFilesize(ui->tet_filesize->text());
}

void AddFtpUlForm::on_tet_minThroughput_returnPressed()
{
    addftpul->setMinthroughput(ui->tet_minThroughput->text());
}

void AddFtpUlForm::on_bt_save_clicked()
{
    SaveAll();
    this->close();
}

void AddFtpUlForm::on_bt_cancel_clicked()
{
    this->close();
}

void AddFtpUlForm::SaveAll()
{
    addftpul->setQci(ui->qciComboFtpUl->currentText());
    addftpul->setFilesize(ui->tet_filesize->text());
    addftpul->setMinthroughput(ui->tet_minThroughput->text());
}

void AddFtpUlForm::setParameters(Addftpul *addftpul)
{
    this->addftpul = addftpul;
    ui->qciComboFtpUl->setCurrentText(addftpul->getQci());
    ui->tet_filesize->setText(addftpul->getFilesize());
    ui->tet_minThroughput->setText(addftpul->getMinthroughput());
}

void AddFtpUlForm::addToList(){

    FtpUlList.clear();
    FtpUlList.append("AddFtpUl\nQCI:");
    FtpUlList.append(ui->qciComboFtpUl->currentText());
    FtpUlList.append("File Size:");
    FtpUlList.append(ui->tet_filesize->text());
    FtpUlList.append("Min Throughput:");
    FtpUlList.append(ui->tet_minThroughput->text());
}
