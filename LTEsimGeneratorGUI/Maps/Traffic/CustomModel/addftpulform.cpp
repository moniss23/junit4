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

    QRegExp rx("[0-9]{0,10}");
    QRegExp rx1("[0-9]{0,20}");


   ui->tet_filesize->setValidator(new QRegExpValidator (rx, this));
   ui->tet_minThroughput->setValidator(new QRegExpValidator(rx1, this));

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
    checkFileSize();
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
    FtpUlList.insert(0, "AddFtpUl\nQCI:");
    FtpUlList.insert(1,ui->qciComboFtpUl->currentText());
    FtpUlList.insert(2, "File Size:");
    FtpUlList.insert(3, ui->tet_filesize->text());
    FtpUlList.insert(4, "Min Throughput:");
    FtpUlList.insert(5, ui->tet_minThroughput->text());
}


void AddFtpUlForm::checkFileSize(){

    QString input = ui->tet_filesize->text();

    uint value = input.toUInt(0, 10);

    if(value < 2147483647){
        addToList();
        this->close();

    }
    else{
        QMessageBox::information(this, "Warning", "You can NOT use File Size bigger than 2147483647");
        ui->tet_filesize->clear();

    }
}
