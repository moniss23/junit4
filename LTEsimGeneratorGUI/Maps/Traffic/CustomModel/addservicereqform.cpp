#include "addservicereqform.h"
#include "ui_addservicereqform.h"
#include <QMessageBox>

    QList<QString> ServiceReqList;
    QList<QString> QciListSynced;

AddServiceReqForm::AddServiceReqForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddServiceReqForm)
{
    ui->setupUi(this);
    this->setWindowTitle("addServiceReq");

    QRegExp rx("[0-9]{0,20}");

    ui->tet_intervalBetweenUlData->setValidator(new QRegExpValidator(rx, this));
    ui->tet_timeToWaitFroAttach->setValidator(new QRegExpValidator(rx, this));

qciAddServiceReqQci1 = ui->qci1;
qciAddServiceReqQci2 = ui->qci2;
qciAddServiceReqQci3 = ui->qci3;
qciAddServiceReqQci4 = ui->qci4;
qciAddServiceReqQci5 = ui->qci5;
qciAddServiceReqQci6 = ui->qci6;
qciAddServiceReqQci7 = ui->qci7;
qciAddServiceReqQci8 = ui->qci8;
qciAddServiceReqQci9 = ui->qci9;


ui->qci1->addItem("");
ui->qci2->addItem("");
ui->qci3->addItem("");
ui->qci4->addItem("");
ui->qci5->addItem("");
ui->qci6->addItem("");
ui->qci7->addItem("");
ui->qci8->addItem("");
ui->qci9->addItem("");

for(int i=1; i<10; i++){

    QString index = QString::number(i);
    ui->qci1->addItem(index);
    ui->qci2->addItem(index);
    ui->qci3->addItem(index);
    ui->qci4->addItem(index);
    ui->qci5->addItem(index);
    ui->qci6->addItem(index);
    ui->qci7->addItem(index);
    ui->qci8->addItem(index);
    ui->qci9->addItem(index);

}


}

AddServiceReqForm::~AddServiceReqForm()
{
    delete ui;
}

void AddServiceReqForm::on_tet_timeToWaitFroAttach_returnPressed()
{
    addservicereq->setTimeToWaitForAttach(ui->tet_timeToWaitFroAttach->text());
}

void AddServiceReqForm::on_tet_intervalBetweenUlData_returnPressed()
{
    addservicereq->setIntervalBetweenUlData(ui->tet_intervalBetweenUlData->text());
}

void AddServiceReqForm::on_bt_save_clicked()
{
    if(ui->qci1->currentText() != "" && (ui->qci1->currentText() == ui->qci2->currentText() || ui->qci1->currentText() == ui->qci3->currentText() || ui->qci1->currentText() == ui->qci4->currentText() || ui->qci1->currentText() == ui->qci5->currentText() || ui->qci1->currentText() == ui->qci6->currentText() || ui->qci1->currentText() == ui->qci7->currentText() || ui->qci1->currentText() == ui->qci8->currentText() || ui->qci1->currentText() == ui->qci9->currentText())){

        QMessageBox::information(this, "Warning", "You can NOT add the same values in two or more qciArray");

    }
    if(ui->qci2->currentText() != "" && (ui->qci2->currentText() == ui->qci1->currentText() || ui->qci2->currentText() == ui->qci3->currentText() || ui->qci2->currentText() == ui->qci4->currentText() || ui->qci2->currentText() == ui->qci5->currentText() || ui->qci2->currentText() == ui->qci6->currentText() || ui->qci2->currentText() == ui->qci7->currentText() || ui->qci2->currentText() == ui->qci8->currentText() || ui->qci2->currentText() == ui->qci9->currentText())){

        QMessageBox::information(this, "Warning", "You can NOT add the same values in two or more qciArray");

    }
    if(ui->qci3->currentText() != "" && (ui->qci3->currentText() == ui->qci1->currentText() || ui->qci3->currentText() == ui->qci2->currentText() || ui->qci3->currentText() == ui->qci4->currentText() || ui->qci3->currentText() == ui->qci5->currentText() || ui->qci3->currentText() == ui->qci6->currentText() || ui->qci3->currentText() == ui->qci7->currentText() || ui->qci3->currentText() == ui->qci8->currentText() || ui->qci3->currentText() == ui->qci9->currentText())){

        QMessageBox::information(this, "Warning", "You can NOT add the same values in two or more qciArray");

    }
    if(ui->qci4->currentText() != "" && (ui->qci4->currentText() == ui->qci1->currentText() || ui->qci4->currentText() == ui->qci2->currentText() || ui->qci4->currentText() == ui->qci3->currentText() || ui->qci4->currentText() == ui->qci5->currentText() || ui->qci4->currentText() == ui->qci6->currentText() || ui->qci4->currentText() == ui->qci7->currentText() || ui->qci4->currentText() == ui->qci8->currentText() || ui->qci4->currentText() == ui->qci9->currentText())){

        QMessageBox::information(this, "Warning", "You can NOT add the same values in two or more qciArray");

    }
    if(ui->qci5->currentText() != "" && (ui->qci5->currentText() == ui->qci1->currentText() || ui->qci5->currentText() == ui->qci2->currentText() || ui->qci5->currentText() == ui->qci3->currentText() || ui->qci5->currentText() == ui->qci4->currentText() || ui->qci5->currentText() == ui->qci6->currentText() || ui->qci5->currentText() == ui->qci7->currentText() || ui->qci5->currentText() == ui->qci8->currentText() || ui->qci5->currentText() == ui->qci9->currentText())){

        QMessageBox::information(this, "Warning", "You can NOT add the same values in two or more qciArray");

    }
    if(ui->qci6->currentText() != "" && (ui->qci6->currentText() == ui->qci1->currentText() || ui->qci6->currentText() == ui->qci2->currentText() || ui->qci6->currentText() == ui->qci3->currentText() || ui->qci6->currentText() == ui->qci4->currentText() || ui->qci6->currentText() == ui->qci5->currentText() || ui->qci6->currentText() == ui->qci7->currentText() || ui->qci6->currentText() == ui->qci8->currentText() || ui->qci6->currentText() == ui->qci9->currentText())){

        QMessageBox::information(this, "Warning", "You can NOT add the same values in two or more qciArray");

    }
    if(ui->qci7->currentText() != "" && (ui->qci7->currentText() == ui->qci1->currentText() || ui->qci7->currentText() == ui->qci2->currentText() || ui->qci7->currentText() == ui->qci3->currentText() || ui->qci7->currentText() == ui->qci4->currentText() || ui->qci7->currentText() == ui->qci5->currentText() || ui->qci7->currentText() == ui->qci6->currentText() || ui->qci7->currentText() == ui->qci8->currentText() || ui->qci7->currentText() == ui->qci9->currentText())){

        QMessageBox::information(this, "Warning", "You can NOT add the same values in two or more qciArray");

    }
    if(ui->qci8->currentText() != "" && (ui->qci8->currentText() == ui->qci1->currentText() || ui->qci8->currentText() == ui->qci2->currentText() || ui->qci8->currentText() == ui->qci3->currentText() || ui->qci8->currentText() == ui->qci4->currentText() || ui->qci8->currentText() == ui->qci5->currentText() || ui->qci8->currentText() == ui->qci6->currentText() || ui->qci8->currentText() == ui->qci7->currentText() || ui->qci8->currentText() == ui->qci9->currentText())){

        QMessageBox::information(this, "Warning", "You can NOT add the same values in two or more qciArray");

    }
    if(ui->qci9->currentText() != "" && (ui->qci9->currentText() == ui->qci1->currentText() || ui->qci9->currentText() == ui->qci2->currentText() || ui->qci9->currentText() == ui->qci3->currentText() || ui->qci9->currentText() == ui->qci4->currentText() || ui->qci9->currentText() == ui->qci5->currentText() || ui->qci9->currentText() == ui->qci6->currentText() || ui->qci9->currentText() == ui->qci7->currentText() || ui->qci9->currentText() == ui->qci8->currentText())){

        QMessageBox::information(this, "Warning", "You can NOT add the same values in two or more qciArray");

    }

    else{

    SaveAll();
    this->close();

    }
}
void AddServiceReqForm::on_pt_cancel_clicked()
{
    this->close();
}

void AddServiceReqForm::SaveAll()
{

   addservicereq->setTimeToWaitForAttach(ui->tet_timeToWaitFroAttach->text());
   addservicereq->setIntervalBetweenUlData(ui->tet_intervalBetweenUlData->text());
}

void AddServiceReqForm::setParameters(Addservicereq *addservicereq)
{
    this->addservicereq = addservicereq;


    ui->tet_timeToWaitFroAttach->setText(addservicereq->getTimeToWaitForAttach());
    ui->tet_intervalBetweenUlData->setText(addservicereq->getIntervalBetweenUlData());
}

void AddServiceReqForm::qciAddToList(){

    QciListSynced.clear();
    QciListSynced.insert(0, ui->qci1->currentText());
    QciListSynced.insert(1, ui->qci2->currentText());
    QciListSynced.insert(2, ui->qci3->currentText());
    QciListSynced.insert(3, ui->qci4->currentText());
    QciListSynced.insert(4, ui->qci5->currentText());
    QciListSynced.insert(5, ui->qci6->currentText());
    QciListSynced.insert(6, ui->qci7->currentText());
    QciListSynced.insert(7, ui->qci8->currentText());
    QciListSynced.insert(8, ui->qci9->currentText());

}

void AddServiceReqForm::addToList(){

    qciAddToList();
    ServiceReqList.clear();
    ServiceReqList.append("ServiceReq\nQCI:");
    ServiceReqList.append(QciListSynced);
    ServiceReqList.append("TetIntervalBetweenUlData:");
    ServiceReqList.append(ui->tet_intervalBetweenUlData->text());
    ServiceReqList.append("TimeToWaitForAttach:");
    ServiceReqList.append(ui->tet_timeToWaitFroAttach->text());

}
