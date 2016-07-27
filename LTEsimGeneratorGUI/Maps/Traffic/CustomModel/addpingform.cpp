#include "addpingform.h"
#include "ui_addpingform.h"

    QList<QString> PingList;

AddPingForm::AddPingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPingForm)
{
    ui->setupUi(this);
    this->setWindowTitle("addPing");\

    qciAddpingPointer = ui->qciComboPing;

    QRegExp rx("[0-9]{0,20}");

    ui->tet_interval->setValidator(new QRegExpValidator(rx, this));
    ui->tet_minRecievedPings->setValidator(new QRegExpValidator(rx, this));
    ui->tet_numberOfPagins->setValidator(new QRegExpValidator(rx, this));

            ui->qciComboPing->addItem("");

    for(int i=1; i<10; i++){

        QString index = QString::number(i);
        ui->qciComboPing->addItem(index);

    }

}

AddPingForm::~AddPingForm()
{
    delete ui;
}

void AddPingForm::on_tet_numberOfPagins_returnPressed()
{
    addping->setNumberOfPings(ui->tet_numberOfPagins->text());
}

void AddPingForm::on_tet_interval_returnPressed()
{
    addping->setInterval(ui->tet_interval->text());
}

void AddPingForm::on_tet_minRecievedPings_returnPressed()
{
    addping->setMinRecievedPings(ui->tet_minRecievedPings->text());
}

void AddPingForm::SaveAll()
{
    addping->setQci(ui->qciComboPing->currentText());
    addping->setNumberOfPings(ui->tet_numberOfPagins->text());
    addping->setInterval(ui->tet_interval->text());
    addping->setMinRecievedPings(ui->tet_minRecievedPings->text());
}

void AddPingForm::on_bt_save_clicked()
{
    SaveAll();
    addToPingList();
    this->close();

}

void AddPingForm::on_bt_cancel_clicked()
{
    this->close();
}

void AddPingForm::setParameters(Addping *addping)
{
    this->addping = addping;

    ui->qciComboPing->setCurrentText(addping->getQci());
    ui->tet_interval->setText(addping->getInterval());
    ui->tet_minRecievedPings->setText(addping->getMinRecievedPings());
    ui->tet_numberOfPagins->setText(addping->getNumberOfPings());
}

void AddPingForm::addToPingList(){

    PingList.clear();
    PingList.insert(0, "AddPing\nQCI:");
    PingList.insert(1, ui->qciComboPing->currentText());
    PingList.insert(2, "NumberOfPagins:");
    PingList.insert(3, ui->tet_numberOfPagins->text());
    PingList.insert(4, "Interval:");
    PingList.insert(5, ui->tet_interval->text());
    PingList.insert(6, "MinRecievedPings:");
    PingList.insert(7, ui->tet_minRecievedPings->text());


}