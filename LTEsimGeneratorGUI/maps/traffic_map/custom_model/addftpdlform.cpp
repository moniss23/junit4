#include "addftpdlform.h"
#include "ui_addftpdlform.h"
#include <QMessageBox>
#include <QDebug>

   QList<QString> FtpDlList;

AddFtpDlForm::AddFtpDlForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFtpDlForm)
{
    ui->setupUi(this);
    this->setWindowTitle("addFtpDl");

    QRegExp rx("[0-9]{0,10}");
    QRegExp rx1("[0-9]{0,20}");


   ui->tet_filesize->setValidator(new QRegExpValidator (rx, this));
   ui->tet_minThroughput->setValidator(new QRegExpValidator(rx1, this));

    qciAddFtpDlPointer = ui->qciComboFtpDl;
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
    checkFileSize();

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
    FtpDlList.insert(0, "AddFtpDl\nQCI:");
    FtpDlList.insert(1,ui->qciComboFtpDl->currentText());
    FtpDlList.insert(2, "FileSize:");
    FtpDlList.insert(3, ui->tet_filesize->text());
    FtpDlList.insert(4, "Min Throughtput:");
    FtpDlList.insert(5, ui->tet_minThroughput->text());
}

void AddFtpDlForm::checkFileSize(){

    QString input = ui->tet_filesize->text();

    uint value = input.toUInt(0, 10);

    if(value < 2147483647){
        addToList();
        this->close();
        qDebug() <<FtpDlList;
    }
    else{
        QMessageBox::information(this, "Warning", "You can NOT use File Size bigger than 2147483647");
        ui->tet_filesize->clear();

    }
}

