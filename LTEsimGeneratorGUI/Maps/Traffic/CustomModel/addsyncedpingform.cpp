#include "addsyncedpingform.h"
#include "ui_addsyncedpingform.h"
#include <QMessageBox>

    QList<QString> SyncedPingList;
    QList<QString> QciList;

AddSyncedPingForm::AddSyncedPingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddSyncedPingForm)
{
    ui->setupUi(this);
    this->setWindowTitle("addSyncedPing");

    QRegExp rx("[0-9]{0,20}");

    ui->tet_interval->setValidator(new QRegExpValidator(rx, this));
    ui->tet_minReceivedPings->setValidator(new QRegExpValidator(rx, this));
    ui->tet_numberOfPings->setValidator(new QRegExpValidator(rx, this));
    ui->tet_timeBetweenTasks->setValidator(new QRegExpValidator(rx, this));

    qciAddSyncedPingQci1 = ui->qci1;
    qciAddSyncedPingQci2 = ui->qci2;
    qciAddSyncedPingQci3 = ui->qci3;
    qciAddSyncedPingQci4 = ui->qci4;
    qciAddSyncedPingQci5 = ui->qci5;
    qciAddSyncedPingQci6 = ui->qci6;
    qciAddSyncedPingQci7 = ui->qci7;
    qciAddSyncedPingQci8 = ui->qci8;
    qciAddSyncedPingQci9 = ui->qci9;

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

AddSyncedPingForm::~AddSyncedPingForm()
{
    delete ui;
}

void AddSyncedPingForm::on_tet_timeBetweenTasks_returnPressed()
{
    addsyncedping->setTimeBetweenTasks(ui->tet_timeBetweenTasks->text());
}

void AddSyncedPingForm::on_tet_numberOfPings_returnPressed()
{
    addsyncedping->setNumberOfPings(ui->tet_numberOfPings->text());
}

void AddSyncedPingForm::on_tet_interval_returnPressed()
{
    addsyncedping->setInterval(ui->tet_interval->text());
}

void AddSyncedPingForm::on_tet_minReceivedPings_returnPressed()
{
    addsyncedping->setMinReceivedPings(ui->tet_minReceivedPings->text());
}

void AddSyncedPingForm::SaveAll()
{
    addsyncedping->setQciarray(ui->qci1->currentText());
    addsyncedping->setTimeBetweenTasks(ui->tet_timeBetweenTasks->text());
    addsyncedping->setNumberOfPings(ui->tet_numberOfPings->text());
    addsyncedping->setInterval(ui->tet_interval->text());
    addsyncedping->setMinReceivedPings(ui->tet_minReceivedPings->text());
}

void AddSyncedPingForm::on_bt_save_clicked()
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

void AddSyncedPingForm::on_bt_cancel_clicked()
{
    this->close();
}

void AddSyncedPingForm::setParameters(Addsyncedping *addsyncedping)
{
    this->addsyncedping = addsyncedping;

    ui->qci1->setCurrentText(ui->qci1->currentText());
    ui->tet_timeBetweenTasks->setText(addsyncedping->getTimeBetweenTasks());
    ui->tet_numberOfPings->setText(addsyncedping->getNumberOfPings());
    ui->tet_interval->setText(addsyncedping->getInterval());
    ui->tet_minReceivedPings->setText(addsyncedping->getMinReceivedPings());
}

void AddSyncedPingForm::qciAddToList(){

    QciList.clear();
    QciList.insert(0, ui->qci1->currentText());
    QciList.insert(1, ui->qci2->currentText());
    QciList.insert(2, ui->qci3->currentText());
    QciList.insert(3, ui->qci4->currentText());
    QciList.insert(4, ui->qci5->currentText());
    QciList.insert(5, ui->qci6->currentText());
    QciList.insert(6, ui->qci7->currentText());
    QciList.insert(7, ui->qci8->currentText());
    QciList.insert(8, ui->qci9->currentText());

}

void AddSyncedPingForm::addToList(){

    SyncedPingList.clear();
    SyncedPingList.append("SyncedPing\nQCI:");
    SyncedPingList.append(QciList);
    SyncedPingList.append("Interval:");
    SyncedPingList.append(ui->tet_interval->text());
    SyncedPingList.append("MinReceivedPings:");
    SyncedPingList.append(ui->tet_minReceivedPings->text());
    SyncedPingList.append("NumberOfPings:");
    SyncedPingList.append(ui->tet_numberOfPings->text());
    SyncedPingList.append("TimeBetweenTasks:");
    SyncedPingList.append(ui->tet_timeBetweenTasks->text());

}
