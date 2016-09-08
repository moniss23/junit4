#include "map_traffic.h"
#include "ui_map_traffic.h"

#include <QPoint>
#include <QComboBox>
#include <QMimeData>
#include <QDrag>

#include "Maps/Traffic/CustomModel/customModel.h"
#include "Maps/Traffic/MapComponents/draguelabel.h"
#include "UISystem/DataForms/UE_param_form.h"
#include "my_qlabel.h"
#include "Data/Objects/cell.h"


//globals to get rid of
QStringList savedCM1List;
QStringList savedCM2List;
QStringList savedCM3List;
QStringList savedCM4List;
QStringList savedCM5List;
QStringList savedCM6List;
QStringList savedCM7List;
QStringList savedCM8List;
QStringList savedCM9List;
QStringList savedCM10List;
QStringList savedPingList;
QStringList savedVoipList;
QStringList savedSyncedPingList;
QStringList savedServiceReqList;
QStringList savedFtpDlList;
QStringList savedFtpUlList;
QStringList savedStreamDlList;
QStringList savedStreamUlList;
extern QStringList PS_List;
my_qlabel *pointerCM[10];
int offset_x=40;
int offset_x_2=40;
DragUELabel *actualposition;
extern QStringList timeParametersContentList;
extern QStringList tuningParametersContentList;
//globals to get rid of



Map_traffic::Map_traffic(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Map_traffic)
{
        ui->setupUi(this);

        tuningtraffic = new TuningTrafficData();
        timetraffic = new TimeData();
        statistics = new StatisticsData();
        createCell();

        this->counter_UE=1;
        tab_UE = new DragUELabel*[counter_UE];

        ui->tet_UE->setText(QString::number(counter_UE));
        tab_UE[0] = new DragUELabel("e1",ui->scrollAreaWidgetContents);
        tab_UE[0]->setGeometry(750,60,40,40);

        pointerCM[0] = ui->CM_1;
        pointerCM[1] = ui->CM_2;
        pointerCM[2] = ui->CM_3;
        pointerCM[3] = ui->CM_4;
        pointerCM[4] = ui->CM_5;
        pointerCM[5] = ui->CM_6;
        pointerCM[6] = ui->CM_7;
        pointerCM[7] = ui->CM_8;
        pointerCM[8] = ui->CM_9;
        pointerCM[9] = ui->CM_10;

        if(!savedCM1List.empty()) ui->CM_1->setStyleSheet(savedCM1List.at(2));
        if(!savedCM2List.empty()) ui->CM_2->setStyleSheet(savedCM2List.at(2));
        if(!savedCM3List.empty()) ui->CM_3->setStyleSheet(savedCM3List.at(2));
        if(!savedCM4List.empty()) ui->CM_4->setStyleSheet(savedCM4List.at(2));
        if(!savedCM5List.empty()) ui->CM_5->setStyleSheet(savedCM5List.at(2));
        if(!savedCM6List.empty()) ui->CM_6->setStyleSheet(savedCM6List.at(2));
        if(!savedCM7List.empty()) ui->CM_7->setStyleSheet(savedCM7List.at(2));
        if(!savedCM8List.empty()) ui->CM_8->setStyleSheet(savedCM8List.at(2));
        if(!savedCM9List.empty()) ui->CM_9->setStyleSheet(savedCM9List.at(2));
        if(!savedCM10List.empty()) ui->CM_10->setStyleSheet(savedCM10List.at(2));

        pointerUE1=&viewUE1;
        pointerUE2=&viewUE2;
        pointerUE3=&viewUE3;
        pointerUE4=&viewUE4;
        pointerUE5=&viewUE5;
        pointerUE6=&viewUE6;
        pointerUE7=&viewUE7;
        pointerUE8=&viewUE8;
        pointerUE9=&viewUE9;
        pointerUE10=&viewUE10;

        viewcustomModel = new customModel*[10];
        viewcustomModel[0] = new customModel();
        viewcustomModel[1] = new customModel();
        viewcustomModel[2] = new customModel();
        viewcustomModel[3] = new customModel();
        viewcustomModel[4] = new customModel();
        viewcustomModel[5] = new customModel();
        viewcustomModel[6] = new customModel();
        viewcustomModel[7] = new customModel();
        viewcustomModel[8] = new customModel();
        viewcustomModel[9] = new customModel();

        tableview = new Form*[10];
        tableview[0] = &viewUE1;
        tableview[0]->setWindowTitle("UE Params 1");
        tableview[1] = &viewUE2;
        tableview[1]->setWindowTitle("UE Params 2");
        tableview[2] = &viewUE3;
        tableview[2]->setWindowTitle("UE Params 3");
        tableview[3] = &viewUE4;
        tableview[3]->setWindowTitle("UE Params 4");
        tableview[4] = &viewUE5;
        tableview[4]->setWindowTitle("UE Params 5");
        tableview[5] = &viewUE6;
        tableview[5]->setWindowTitle("UE Params 6");
        tableview[6] = &viewUE7;
        tableview[6]->setWindowTitle("UE Params 7");
        tableview[7] = &viewUE8;
        tableview[7]->setWindowTitle("UE Params 8");
        tableview[8] = &viewUE9;
        tableview[8]->setWindowTitle("UE Params 9");
        tableview[9] = &viewUE10;
        tableview[9]->setWindowTitle("UE Params 10");


        for(unsigned i=0;i<10;i++)
        {
            viewcustomModel[i]->set_custom_name("Custom Model "+QString::number(i+1));
            viewcustomModel[i]->setWindowTitle("Custom Model "+QString::number(i+1));
        }

         connect(ui->CM_2, SIGNAL(Mouse_Pressed()), this, SLOT(on_CM2_clicked()));
         connect(ui->CM_3, SIGNAL(Mouse_Pressed()), this, SLOT(on_CM3_clicked()));
         connect(ui->CM_4, SIGNAL(Mouse_Pressed()), this, SLOT(on_CM4_clicked()));
         connect(ui->CM_5, SIGNAL(Mouse_Pressed()), this, SLOT(on_CM5_clicked()));
         connect(ui->CM_6, SIGNAL(Mouse_Pressed()), this, SLOT(on_CM6_clicked()));
         connect(ui->CM_7, SIGNAL(Mouse_Pressed()), this, SLOT(on_CM7_clicked()));
         connect(ui->CM_8, SIGNAL(Mouse_Pressed()), this, SLOT(on_CM8_clicked()));
         connect(ui->CM_9, SIGNAL(Mouse_Pressed()), this, SLOT(on_CM9_clicked()));
         connect(ui->CM_10, SIGNAL(Mouse_Pressed()), this, SLOT(on_CM10_clicked()));

         for(unsigned i=0;i<10;i++)
         {
             connect(pointerCM[i],&my_qlabel::Mouse_Pressed,[=]() {
                 viewcustomModel[i]->close();
                 viewcustomModel[i]->setWindowModality(Qt::ApplicationModal);
                 viewcustomModel[i]->setParameters(&viewcustomModel[i]);
                 viewcustomModel[i]->show();
             });
         }

        setAcceptDrops(true);

        ui->checkBoxCell11->setChecked(true);
        ui->checkBoxCell12->setChecked(true);
        ui->checkBoxCell21->setChecked(true);
        ui->checkBoxCell22->setChecked(true);
        ui->checkBoxCell31->setChecked(true);
        ui->checkBoxCell32->setChecked(true);
        ui->checkBoxCell41->setChecked(true);
        ui->checkBoxCell42->setChecked(true);
        ui->checkBoxCell51->setChecked(true);
        ui->checkBoxCell52->setChecked(true);
        ui->checkBoxCell61->setChecked(true);
        ui->checkBoxCell62->setChecked(true);
}

Map_traffic::~Map_traffic()
{
    delete ui;
}

void Map_traffic::createCell(){
    tabCell = new Cell *[12];

    tabCell[0] = new Cell ("cell11");
    tabCell[0]->chBox = ui->checkBoxCell11;
    tabCell[0]->center = center11;
    tabCell[0]->chBox->setText(tabCell[0]->name);

    tabCell[1] = new Cell ("cell12");
    tabCell[1]->chBox = ui->checkBoxCell12;
    tabCell[1]->center = center12;
    tabCell[1]->chBox->setText(tabCell[1]->name);

    tabCell[2] = new Cell ("cell21");
    tabCell[2]->chBox = ui->checkBoxCell21;
    tabCell[2]->center = center21;
    tabCell[2]->chBox->setText(tabCell[2]->name);

    tabCell[3] = new Cell ("cell22");
    tabCell[3]->chBox = ui->checkBoxCell22;
    tabCell[3]->center = center22;
    tabCell[3]->chBox->setText(tabCell[3]->name);

    tabCell[4] = new Cell ("cell31");
    tabCell[4]->chBox = ui->checkBoxCell31;
    tabCell[4]->center = center31;
    tabCell[4]->chBox->setText(tabCell[4]->name);

    tabCell[5] = new Cell ("cell32");
    tabCell[5]->chBox = ui->checkBoxCell32;
    tabCell[5]->center = center32;
    tabCell[5]->chBox->setText(tabCell[5]->name);

    tabCell[6] = new Cell ("cell41");
    tabCell[6]->chBox = ui->checkBoxCell41;
    tabCell[6]->center = center41;
    tabCell[6]->chBox->setText(tabCell[6]->name);

    tabCell[7] = new Cell ("cell42");
    tabCell[7]->chBox = ui->checkBoxCell42;
    tabCell[7]->center = center42;
    tabCell[7]->chBox->setText(tabCell[7]->name);

    tabCell[8] = new Cell ("cell51");
    tabCell[8]->chBox = ui->checkBoxCell51;
    tabCell[8]->center = center51;
    tabCell[8]->chBox->setText(tabCell[8]->name);

    tabCell[9] = new Cell ("cell52");
    tabCell[9]->chBox = ui->checkBoxCell52;
    tabCell[9]->center = center52;
    tabCell[9]->chBox->setText(tabCell[9]->name);

    tabCell[10] = new Cell ("cell61");
    tabCell[10]->chBox = ui->checkBoxCell61;
    tabCell[10]->center = center61;
    tabCell[10]->chBox->setText(tabCell[10]->name);

    tabCell[11] = new Cell ("cell62");
    tabCell[11]->chBox = ui->checkBoxCell62;
    tabCell[11]->center = center62;
    tabCell[11]->chBox->setText(tabCell[11]->name);
}

//Drag_UE_functions
void Map_traffic::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-UE")) {
        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void Map_traffic::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){

        DragUELabel *child = dynamic_cast<DragUELabel*>(childAt(event->pos()));

        if (!child)
            return;
        if(child==tab_UE[0]){
            actualposition=child;
            QPoint hotSpot = event->pos() - child->pos();

            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);
            dataStream << child->labelText() << QPoint(hotSpot);

            QMimeData *mimeData = new QMimeData;
            mimeData->setData("application/x-UE", itemData);
            mimeData->setText(child->labelText());

            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->setHotSpot(hotSpot);

            if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
                child->close();
            else
                child->show();
        }

        if(child==tab_UE[1]){
            actualposition=child;
            QPoint hotSpot = event->pos() - child->pos();

            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);
            dataStream << child->labelText() << QPoint(hotSpot);

            QMimeData *mimeData = new QMimeData;
            mimeData->setData("application/x-UE", itemData);
            mimeData->setText(child->labelText());

            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->setHotSpot(hotSpot);

            if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
                child->close();
            else
                child->show();
        }
        if(child==tab_UE[2]){
            actualposition=child;
            QPoint hotSpot = event->pos() - child->pos();

            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);
            dataStream << child->labelText() << QPoint(hotSpot);

            QMimeData *mimeData = new QMimeData;
            mimeData->setData("application/x-UE", itemData);
            mimeData->setText(child->labelText());

            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->setHotSpot(hotSpot);

            if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
                child->close();
            else
                child->show();
        }
        if(child==tab_UE[3]){
            actualposition=child;
            QPoint hotSpot = event->pos() - child->pos();

            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);
            dataStream << child->labelText() << QPoint(hotSpot);

            QMimeData *mimeData = new QMimeData;
            mimeData->setData("application/x-UE", itemData);
            mimeData->setText(child->labelText());

            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->setHotSpot(hotSpot);

            if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
                child->close();
            else
                child->show();
        }
        if(child==tab_UE[4]){
            actualposition=child;
            QPoint hotSpot = event->pos() - child->pos();

            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);
            dataStream << child->labelText() << QPoint(hotSpot);

            QMimeData *mimeData = new QMimeData;
            mimeData->setData("application/x-UE", itemData);
            mimeData->setText(child->labelText());

            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->setHotSpot(hotSpot);

            if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
                child->close();
            else
                child->show();
        }
        if(child==tab_UE[5]){
            actualposition=child;
            QPoint hotSpot = event->pos() - child->pos();

            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);
            dataStream << child->labelText() << QPoint(hotSpot);

            QMimeData *mimeData = new QMimeData;
            mimeData->setData("application/x-UE", itemData);
            mimeData->setText(child->labelText());

            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->setHotSpot(hotSpot);

            if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
                child->close();
            else
                child->show();
        }
        if(child==tab_UE[6]){
            actualposition=child;
            QPoint hotSpot = event->pos() - child->pos();

            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);
            dataStream << child->labelText() << QPoint(hotSpot);

            QMimeData *mimeData = new QMimeData;
            mimeData->setData("application/x-UE", itemData);
            mimeData->setText(child->labelText());

            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->setHotSpot(hotSpot);

            if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
                child->close();
            else
                child->show();
        }
        if(child==tab_UE[7]){
            actualposition=child;
            QPoint hotSpot = event->pos() - child->pos();

            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);
            dataStream << child->labelText() << QPoint(hotSpot);


            QMimeData *mimeData = new QMimeData;
            mimeData->setData("application/x-UE", itemData);
            mimeData->setText(child->labelText());


            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->setHotSpot(hotSpot);

            if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
                child->close();
            else
                child->show();
        }
        if(child==tab_UE[8]){
            actualposition=child;
            QPoint hotSpot = event->pos() - child->pos();

            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);
            dataStream << child->labelText() << QPoint(hotSpot);

            QMimeData *mimeData = new QMimeData;
            mimeData->setData("application/x-UE", itemData);
            mimeData->setText(child->labelText());

            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->setHotSpot(hotSpot);

            if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
                child->close();
            else
                child->show();
        }
        if(child==tab_UE[9]){
            actualposition=child;
            QPoint hotSpot = event->pos() - child->pos();

            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);
            dataStream << child->labelText() << QPoint(hotSpot);

            QMimeData *mimeData = new QMimeData;
            mimeData->setData("application/x-UE", itemData);
            mimeData->setText(child->labelText());

            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->setHotSpot(hotSpot);

            if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
                child->close();
            else
                child->show();
        }
    }
}


void Map_traffic::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-UE")) {
        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void Map_traffic::dropEvent(QDropEvent *event)
{
    //UE1
    if (event->mimeData()->hasFormat("application/x-UE")) {
        const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data("application/x-UE");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString text;
        QPoint offset;
        dataStream >> text >> offset;

        DragUELabel *newLabel = new DragUELabel(text, ui->scrollAreaWidgetContents);

        if(actualposition==tab_UE[0]){
            newLabel->move(event->pos() - offset);
            newLabel->show();
            newLabel->setAttribute(Qt::WA_DeleteOnClose);

            if (event->source() == this) {
                event->setDropAction(Qt::MoveAction);
                event->accept();

                //Cell11
                bool ok=false;
                if(newLabel->y()>ui->cell11_UE->y() && newLabel->y()<ui->cell11_UE->y()+120){
                    if(newLabel->x()>ui->cell11_UE->x() && newLabel->x()<ui->cell11_UE->x()+120){
                        ok=true;
                        pointerUE1->area1->setText("Center11");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //Cell12
                if(!ok && newLabel->y()>ui->cell12_UE->y() && newLabel->y()<(ui->cell12_UE->y()+110)){
                    if(newLabel->x()>ui->cell12_UE->x() && newLabel->x()<(ui->cell12_UE->x()+100)){
                        ok=true;
                        pointerUE1->area1->setText("Center12");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //cell21
                if(!ok && newLabel->y()>ui->cell21_UE->y() && newLabel->y()<(ui->cell21_UE->y()+50)){
                    if(newLabel->x()>ui->cell21_UE->x() && newLabel->x()<(ui->cell21_UE->x()+150)){
                        ok=true;
                        pointerUE1->area1->setText("Center21");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //cell22
                if(!ok && newLabel->y()>ui->cell22_UE->y() && newLabel->y()<(ui->cell22_UE->y()+50)){
                    if(newLabel->x()>ui->cell22_UE->x() && newLabel->x()<(ui->cell22_UE->x()+150)){
                        ok=true;
                        pointerUE1->area1->setText("Center22");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //cell31
                if(!ok && newLabel->y()>ui->cell31_UE->y() && newLabel->y()<(ui->cell31_UE->y()+150)){
                    if(newLabel->x()>ui->cell31_UE->x() && newLabel->x()<(ui->cell31_UE->x()+130)){
                        ok=true;
                        pointerUE1->area1->setText("Center31");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //cell32
                if(!ok && newLabel->y()>ui->cell32_UE->y() && newLabel->y()<(ui->cell32_UE->y()+160)){
                    if(newLabel->x()>ui->cell32_UE->x() && newLabel->x()<(ui->cell32_UE->x()+140)){
                        ok=true;
                        pointerUE1->area1->setText("Center32");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //cell41
                if(!ok && newLabel->y()>ui->cell41_UE->y() && newLabel->y()<(ui->cell41_UE->y()+101)){
                    if(newLabel->x()>ui->cell41_UE->x() && newLabel->x()<(ui->cell41_UE->x()+141)){
                        ok=true;
                        pointerUE1->area1->setText("Center41");
                    }
                    else{
                        pointerUE1->area1->setText("cell41");
                    }
                }

                //cell42
                if(!ok && newLabel->y()>ui->cell42_UE->y() && newLabel->y()<(ui->cell42_UE->y()+101)){
                    if(newLabel->x()>ui->cell42_UE->x() && newLabel->x()<(ui->cell42_UE->x()+141)){
                        ok=true;
                        pointerUE1->area1->setText("Center42");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //cell51
                if(!ok && newLabel->y()>ui->cell51_UE->y() && newLabel->y()<(ui->cell51_UE->y()+101)){
                    if(newLabel->x()>ui->cell51_UE->x() && newLabel->x()<(ui->cell51_UE->x()+151)){
                        ok=true;
                        pointerUE1->area1->setText("Center51");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //cell52
                if(!ok && newLabel->y()>ui->cell52_UE->y() && newLabel->y()<(ui->cell52_UE->y()+101)){
                    if(newLabel->x()>ui->cell52_UE->x() && newLabel->x()<(ui->cell52_UE->x()+151)){
                        ok=true;
                        pointerUE1->area1->setText("Center52");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //cell61
                if(!ok && newLabel->y()>ui->cell61_UE->y() && newLabel->y()<(ui->cell61_UE->y()+111)){
                    if(newLabel->x()>ui->cell61_UE->x() && newLabel->x()<(ui->cell61_UE->x()+131)){
                        ok=true;
                        pointerUE1->area1->setText("Center61");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //cell62
                if(!ok && newLabel->y()>ui->cell62_UE->y() && newLabel->y()<(ui->cell62_UE->y()+111)){
                    if(newLabel->x()>ui->cell62_UE->x() && newLabel->x()<(ui->cell62_UE->x()+131)){
                        ok=true;
                        pointerUE1->area1->setText("Center62");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //Handover11_12
                if(!ok && newLabel->y()>ui->Handover11_12_UE->y() && newLabel->y()<(ui->Handover11_12_UE->y()+120)){
                    if(newLabel->x()>ui->Handover11_12_UE->x() && newLabel->x()<(ui->Handover11_12_UE->x()+60)){
                        ok=true;
                        pointerUE1->area1->setText("Handover11_12");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }
                //Handover11_21
                if(!ok && newLabel->y()>ui->Handover11_21_UE->y() && newLabel->y()<(ui->Handover11_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover11_21_UE->x() && newLabel->x()<(ui->Handover11_21_UE->x()+50)){
                        ok=true;
                        pointerUE1->area1->setText("Handover11_21");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //Handover12_21
                if(!ok && newLabel->y()>ui->Handover12_21_UE->y() && newLabel->y()<(ui->Handover12_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_21_UE->x() && newLabel->x()<(ui->Handover12_21_UE->x()+70)){
                        ok=true;
                        pointerUE1->area1->setText("Handover12_21");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //Handover12_22
                if(!ok && newLabel->y()>ui->Handover12_22_UE->y() && newLabel->y()<(ui->Handover12_22_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_22_UE->x() && newLabel->x()<(ui->Handover12_22_UE->x()+70)){
                        ok=true;
                        pointerUE1->area1->setText("Handover12_22");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }
                //Handover21_22
                if(!ok && newLabel->y()>ui->Handover21_22_UE->y() && newLabel->y()<(ui->Handover21_22_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_22_UE->x() && newLabel->x()<(ui->Handover21_22_UE->x()+70)){
                        ok=true;
                        pointerUE1->area1->setText("Handover21_22");
                    }
                    else{
                        pointerUE1->area1->setText("Handover21_22");
                    }
                }

                //Handover21_31
                if(!ok && newLabel->y()>ui->Handover21_31_UE->y() && newLabel->y()<(ui->Handover21_31_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_31_UE->x() && newLabel->x()<(ui->Handover21_31_UE->x()+60)){
                        ok=true;
                        pointerUE1->area1->setText("Handover21_31");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //Handover21_32
                if(!ok && newLabel->y()>ui->Handover21_32_UE->y() && newLabel->y()<(ui->Handover21_32_UE->y()+30)){
                    if(newLabel->x()>ui->Handover21_32_UE->x() && newLabel->x()<(ui->Handover21_32_UE->x()+90)){
                        ok=true;
                        pointerUE1->area1->setText("Handover21_32");
                    }
                    else{
                        pointerUE1->area1->setText("Handover21_32");
                    }
                }

                //Handover22_32
                if(!ok && newLabel->y()>ui->Handover22_32_UE->y() && newLabel->y()<(ui->Handover22_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover22_32_UE->x() && newLabel->x()<(ui->Handover22_32_UE->x()+60)){
                        ok=true;
                        pointerUE1->area1->setText("Handover22_32");
                    }
                    else{
                        pointerUE1->area1->setText("Handover22_32");
                    }
                }

                //Handover31_32
                if(!ok && newLabel->y()>ui->Handover31_32_UE->y() && newLabel->y()<(ui->Handover31_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover31_32_UE->x() && newLabel->x()<(ui->Handover31_32_UE->x()+60)){
                        ok=true;
                        pointerUE1->area1->setText("Handover31_32");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //Handover31_41
                if(!ok && newLabel->y()>ui->Handover31_41_UE->y() && newLabel->y()<(ui->Handover31_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover31_41_UE->x() && newLabel->x()<(ui->Handover31_41_UE->x()+80)){
                        ok=true;
                        pointerUE1->area1->setText("Handover31_41");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //Handover32_41
                if(!ok && newLabel->y()>ui->Handover32_41_UE->y() && newLabel->y()<(ui->Handover32_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_41_UE->x() && newLabel->x()<(ui->Handover32_41_UE->x()+90)){
                        ok=true;
                        pointerUE1->area1->setText("Handover32_41");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //Handover32_42
                if(!ok && newLabel->y()>ui->Handover32_42_UE->y() && newLabel->y()<(ui->Handover32_42_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_42_UE->x() && newLabel->x()<(ui->Handover32_42_UE->x()+90)){
                        ok=true;
                        pointerUE1->area1->setText("Handover32_42");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //Handover41_42
                if(!ok && newLabel->y()>ui->Handover41_42_UE->y() && newLabel->y()<(ui->Handover41_42_UE->y()+110)){
                    if(newLabel->x()>ui->Handover41_42_UE->x() && newLabel->x()<(ui->Handover41_42_UE->x()+40)){
                        ok=true;
                        pointerUE1->area1->setText("Handover41_42");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //Handover41_51
                if(!ok && newLabel->y()>ui->Handover41_51_UE->y() && newLabel->y()<(ui->Handover41_51_UE->y()+66)){
                    if(newLabel->x()>ui->Handover41_51_UE->x() && newLabel->x()<(ui->Handover41_51_UE->x()+81)){
                        ok=true;
                        pointerUE1->area1->setText("Handover41_51");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //Handover42_52
                if(!ok && newLabel->y()>ui->Handover42_52_UE->y() && newLabel->y()<(ui->Handover42_52_UE->y()+66)){
                    if(newLabel->x()>ui->Handover42_52_UE->x() && newLabel->x()<(ui->Handover42_52_UE->x()+96)){
                        ok=true;
                        pointerUE1->area1->setText("Handover42_52");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //Handover51_52
                if(!ok && newLabel->y()>ui->Handover51_52_UE->y() && newLabel->y()<(ui->Handover51_52_UE->y()+91)){
                    if(newLabel->x()>ui->Handover51_52_UE->x() && newLabel->x()<(ui->Handover51_52_UE->x()+56)){
                        ok=true;
                        pointerUE1->area1->setText("Handover51_52");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //Handover51_61
                if(!ok && newLabel->y()>ui->Handover51_61_UE->y() && newLabel->y()<(ui->Handover51_61_UE->y()+41)){
                    if(newLabel->x()>ui->Handover51_61_UE->x() && newLabel->x()<(ui->Handover51_61_UE->x()+76)){
                        ok=true;
                        pointerUE1->area1->setText("Handover51_61");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //Handover52_61
                if(!ok && newLabel->y()>ui->Handover52_61_UE->y() && newLabel->y()<(ui->Handover52_61_UE->y()+56)){
                    if(newLabel->x()>ui->Handover52_61_UE->x() && newLabel->x()<(ui->Handover52_61_UE->x()+66)){
                        ok=true;
                        pointerUE1->area1->setText("Handover52_61");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //Handover52_62
                if(!ok && newLabel->y()>ui->Handover52_62_UE->y() && newLabel->y()<(ui->Handover52_62_UE->y()+66)){
                    if(newLabel->x()>ui->Handover52_62_UE->x() && newLabel->x()<(ui->Handover52_62_UE->x()+86)){
                        ok=true;
                        pointerUE1->area1->setText("Handover52_62");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }

                //Handover61_62
                if(!ok && newLabel->y()>ui->Handover61_62_UE->y() && newLabel->y()<(ui->Handover61_62_UE->y()+96)){
                    if(newLabel->x()>ui->Handover61_62_UE->x() && newLabel->x()<(ui->Handover61_62_UE->x()+116)){
                        ok=true;
                        pointerUE1->area1->setText("Handover61_62");
                    }
                    else{
                        pointerUE1->area1->setText("");
                    }
                }
                actualposition=newLabel;
                tab_UE[0]=newLabel;
            }
            else {
                event->acceptProposedAction();
            }
        }
    }

    //UE2
    if (event->mimeData()->hasFormat("application/x-UE")) {
        const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data("application/x-UE");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString text;
        QPoint offset;
        dataStream >> text >> offset;

        DragUELabel *newLabel = new DragUELabel(text, ui->scrollAreaWidgetContents);

        if(actualposition==tab_UE[1]){
            newLabel->move(event->pos() - offset);
            newLabel->show();
            newLabel->setAttribute(Qt::WA_DeleteOnClose);

            if (event->source() == this) {
                event->setDropAction(Qt::MoveAction);
                event->accept();

                //Cell11
                bool ok=false;
                if(newLabel->y()>ui->cell11_UE->y() && newLabel->y()<ui->cell11_UE->y()+120){
                    if(newLabel->x()>ui->cell11_UE->x() && newLabel->x()<ui->cell11_UE->x()+120){
                        ok=true;
                        pointerUE2->area1->setText("Center11");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Cell12
                if(!ok && newLabel->y()>ui->cell12_UE->y() && newLabel->y()<(ui->cell12_UE->y()+110)){
                    if(newLabel->x()>ui->cell12_UE->x() && newLabel->x()<(ui->cell12_UE->x()+100)){
                        ok=true;
                        pointerUE2->area1->setText("Center12");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //cell21
                if(!ok && newLabel->y()>ui->cell21_UE->y() && newLabel->y()<(ui->cell21_UE->y()+50)){
                    if(newLabel->x()>ui->cell21_UE->x() && newLabel->x()<(ui->cell21_UE->x()+150)){
                        ok=true;
                        pointerUE2->area1->setText("Center21");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //cell22
                if(!ok && newLabel->y()>ui->cell22_UE->y() && newLabel->y()<(ui->cell22_UE->y()+50)){
                    if(newLabel->x()>ui->cell22_UE->x() && newLabel->x()<(ui->cell22_UE->x()+150)){
                        ok=true;
                        pointerUE2->area1->setText("Center22");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //cell31
                if(!ok && newLabel->y()>ui->cell31_UE->y() && newLabel->y()<(ui->cell31_UE->y()+150)){
                    if(newLabel->x()>ui->cell31_UE->x() && newLabel->x()<(ui->cell31_UE->x()+130)){
                        ok=true;
                        pointerUE2->area1->setText("Center31");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //cell32
                if(!ok && newLabel->y()>ui->cell32_UE->y() && newLabel->y()<(ui->cell32_UE->y()+160)){
                    if(newLabel->x()>ui->cell32_UE->x() && newLabel->x()<(ui->cell32_UE->x()+140)){
                        ok=true;
                        pointerUE2->area1->setText("Center32");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //cell41
                if(!ok && newLabel->y()>ui->cell41_UE->y() && newLabel->y()<(ui->cell41_UE->y()+101)){
                    if(newLabel->x()>ui->cell41_UE->x() && newLabel->x()<(ui->cell41_UE->x()+141)){
                        ok=true;
                        pointerUE2->area1->setText("Center41");
                    }
                    else{
                        pointerUE2->area1->setText("cell41");
                    }
                }

                //cell42
                if(!ok && newLabel->y()>ui->cell42_UE->y() && newLabel->y()<(ui->cell42_UE->y()+101)){
                    if(newLabel->x()>ui->cell42_UE->x() && newLabel->x()<(ui->cell42_UE->x()+141)){
                        ok=true;
                        pointerUE2->area1->setText("Center42");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //cell51
                if(!ok && newLabel->y()>ui->cell51_UE->y() && newLabel->y()<(ui->cell51_UE->y()+101)){
                    if(newLabel->x()>ui->cell51_UE->x() && newLabel->x()<(ui->cell51_UE->x()+151)){
                        ok=true;
                        pointerUE2->area1->setText("Center51");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //cell52
                if(!ok && newLabel->y()>ui->cell52_UE->y() && newLabel->y()<(ui->cell52_UE->y()+101)){
                    if(newLabel->x()>ui->cell52_UE->x() && newLabel->x()<(ui->cell52_UE->x()+151)){
                        ok=true;
                        pointerUE2->area1->setText("Center52");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //cell61
                if(!ok && newLabel->y()>ui->cell61_UE->y() && newLabel->y()<(ui->cell61_UE->y()+111)){
                    if(newLabel->x()>ui->cell61_UE->x() && newLabel->x()<(ui->cell61_UE->x()+131)){
                        ok=true;
                        pointerUE2->area1->setText("Center61");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //cell62
                if(!ok && newLabel->y()>ui->cell62_UE->y() && newLabel->y()<(ui->cell62_UE->y()+111)){
                    if(newLabel->x()>ui->cell62_UE->x() && newLabel->x()<(ui->cell62_UE->x()+131)){
                        ok=true;
                        pointerUE2->area1->setText("Center62");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Handover11_12
                if(!ok && newLabel->y()>ui->Handover11_12_UE->y() && newLabel->y()<(ui->Handover11_12_UE->y()+120)){
                    if(newLabel->x()>ui->Handover11_12_UE->x() && newLabel->x()<(ui->Handover11_12_UE->x()+60)){
                        ok=true;
                        pointerUE2->area1->setText("Handover11_12");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Handover11_21
                if(!ok && newLabel->y()>ui->Handover11_21_UE->y() && newLabel->y()<(ui->Handover11_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover11_21_UE->x() && newLabel->x()<(ui->Handover11_21_UE->x()+50)){
                        ok=true;
                        pointerUE2->area1->setText("Handover11_21");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Handover12_21
                if(!ok && newLabel->y()>ui->Handover12_21_UE->y() && newLabel->y()<(ui->Handover12_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_21_UE->x() && newLabel->x()<(ui->Handover12_21_UE->x()+70)){
                        ok=true;
                        pointerUE2->area1->setText("Handover12_21");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Handover12_22
                if(!ok && newLabel->y()>ui->Handover12_22_UE->y() && newLabel->y()<(ui->Handover12_22_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_22_UE->x() && newLabel->x()<(ui->Handover12_22_UE->x()+70)){
                        ok=true;
                        pointerUE2->area1->setText("Handover12_22");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Handover21_22
                if(!ok && newLabel->y()>ui->Handover21_22_UE->y() && newLabel->y()<(ui->Handover21_22_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_22_UE->x() && newLabel->x()<(ui->Handover21_22_UE->x()+70)){
                        ok=true;
                        pointerUE2->area1->setText("Handover21_22");
                    }
                    else{
                        pointerUE2->area1->setText("Handover21_22");
                    }
                }

                //Handover21_31
                if(!ok && newLabel->y()>ui->Handover21_31_UE->y() && newLabel->y()<(ui->Handover21_31_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_31_UE->x() && newLabel->x()<(ui->Handover21_31_UE->x()+60)){
                        ok=true;
                        pointerUE2->area1->setText("Handover21_31");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Handover21_32
                if(!ok && newLabel->y()>ui->Handover21_32_UE->y() && newLabel->y()<(ui->Handover21_32_UE->y()+30)){
                    if(newLabel->x()>ui->Handover21_32_UE->x() && newLabel->x()<(ui->Handover21_32_UE->x()+90)){
                        ok=true;
                        pointerUE2->area1->setText("Handover21_32");
                    }
                    else{
                        pointerUE2->area1->setText("Handover21_32");
                    }
                }

                //Handover22_32
                if(!ok && newLabel->y()>ui->Handover22_32_UE->y() && newLabel->y()<(ui->Handover22_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover22_32_UE->x() && newLabel->x()<(ui->Handover22_32_UE->x()+60)){
                        ok=true;
                        pointerUE2->area1->setText("Handover22_32");
                    }
                    else{
                        pointerUE2->area1->setText("Handover22_32");
                    }
                }

                //Handover31_32
                if(!ok && newLabel->y()>ui->Handover31_32_UE->y() && newLabel->y()<(ui->Handover31_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover31_32_UE->x() && newLabel->x()<(ui->Handover31_32_UE->x()+60)){
                        ok=true;
                        pointerUE2->area1->setText("Handover31_32");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Handover31_41
                if(!ok && newLabel->y()>ui->Handover31_41_UE->y() && newLabel->y()<(ui->Handover31_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover31_41_UE->x() && newLabel->x()<(ui->Handover31_41_UE->x()+80)){
                        ok=true;
                        pointerUE2->area1->setText("Handover31_41");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Handover32_41
                if(!ok && newLabel->y()>ui->Handover32_41_UE->y() && newLabel->y()<(ui->Handover32_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_41_UE->x() && newLabel->x()<(ui->Handover32_41_UE->x()+90)){
                        ok=true;
                        pointerUE2->area1->setText("Handover32_41");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Handover32_42
                if(!ok && newLabel->y()>ui->Handover32_42_UE->y() && newLabel->y()<(ui->Handover32_42_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_42_UE->x() && newLabel->x()<(ui->Handover32_42_UE->x()+90)){
                        ok=true;
                        pointerUE2->area1->setText("Handover32_42");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Handover41_42
                if(!ok && newLabel->y()>ui->Handover41_42_UE->y() && newLabel->y()<(ui->Handover41_42_UE->y()+110)){
                    if(newLabel->x()>ui->Handover41_42_UE->x() && newLabel->x()<(ui->Handover41_42_UE->x()+40)){
                        ok=true;
                        pointerUE2->area1->setText("Handover41_42");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Handover41_51
                if(!ok && newLabel->y()>ui->Handover41_51_UE->y() && newLabel->y()<(ui->Handover41_51_UE->y()+66)){
                    if(newLabel->x()>ui->Handover41_51_UE->x() && newLabel->x()<(ui->Handover41_51_UE->x()+81)){
                        ok=true;
                        pointerUE2->area1->setText("Handover41_51");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Handover42_52
                if(!ok && newLabel->y()>ui->Handover42_52_UE->y() && newLabel->y()<(ui->Handover42_52_UE->y()+66)){
                    if(newLabel->x()>ui->Handover42_52_UE->x() && newLabel->x()<(ui->Handover42_52_UE->x()+96)){
                        ok=true;
                        pointerUE2->area1->setText("Handover42_52");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Handover51_52
                if(!ok && newLabel->y()>ui->Handover51_52_UE->y() && newLabel->y()<(ui->Handover51_52_UE->y()+91)){
                    if(newLabel->x()>ui->Handover51_52_UE->x() && newLabel->x()<(ui->Handover51_52_UE->x()+56)){
                        ok=true;
                        pointerUE2->area1->setText("Handover51_52");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Handover51_61
                if(!ok && newLabel->y()>ui->Handover51_61_UE->y() && newLabel->y()<(ui->Handover51_61_UE->y()+41)){
                    if(newLabel->x()>ui->Handover51_61_UE->x() && newLabel->x()<(ui->Handover51_61_UE->x()+76)){
                        ok=true;
                        pointerUE2->area1->setText("Handover51_61");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Handover52_61
                if(!ok && newLabel->y()>ui->Handover52_61_UE->y() && newLabel->y()<(ui->Handover52_61_UE->y()+56)){
                    if(newLabel->x()>ui->Handover52_61_UE->x() && newLabel->x()<(ui->Handover52_61_UE->x()+66)){
                        ok=true;
                        pointerUE2->area1->setText("Handover52_61");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Handover52_62
                if(!ok && newLabel->y()>ui->Handover52_62_UE->y() && newLabel->y()<(ui->Handover52_62_UE->y()+66)){
                    if(newLabel->x()>ui->Handover52_62_UE->x() && newLabel->x()<(ui->Handover52_62_UE->x()+86)){
                        ok=true;
                        pointerUE2->area1->setText("Handover52_62");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }

                //Handover61_62
                if(!ok && newLabel->y()>ui->Handover61_62_UE->y() && newLabel->y()<(ui->Handover61_62_UE->y()+96)){
                    if(newLabel->x()>ui->Handover61_62_UE->x() && newLabel->x()<(ui->Handover61_62_UE->x()+116)){
                        ok=true;
                        pointerUE2->area1->setText("Handover61_62");
                    }
                    else{
                        pointerUE2->area1->setText("");
                    }
                }
                actualposition=newLabel;
                tab_UE[1]=newLabel;
            }
            else {
                event->acceptProposedAction();
            }
        }
    }

    //UE3
    if (event->mimeData()->hasFormat("application/x-UE")) {
        const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data("application/x-UE");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString text;
        QPoint offset;
        dataStream >> text >> offset;

        DragUELabel *newLabel = new DragUELabel(text, ui->scrollAreaWidgetContents);

        if(actualposition==tab_UE[2]){
            newLabel->move(event->pos() - offset);
            newLabel->show();
            newLabel->setAttribute(Qt::WA_DeleteOnClose);

            if (event->source() == this) {
                event->setDropAction(Qt::MoveAction);
                event->accept();

                //Cell11
                bool ok=false;
                if(newLabel->y()>ui->cell11_UE->y() && newLabel->y()<ui->cell11_UE->y()+120){
                    if(newLabel->x()>ui->cell11_UE->x() && newLabel->x()<ui->cell11_UE->x()+120){
                        ok=true;
                        pointerUE3->area1->setText("Center11");

                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Cell12
                if(!ok && newLabel->y()>ui->cell12_UE->y() && newLabel->y()<(ui->cell12_UE->y()+110)){
                    if(newLabel->x()>ui->cell12_UE->x() && newLabel->x()<(ui->cell12_UE->x()+100)){
                        ok=true;
                        pointerUE3->area1->setText("Center12");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //cell21
                if(!ok && newLabel->y()>ui->cell21_UE->y() && newLabel->y()<(ui->cell21_UE->y()+50)){
                    if(newLabel->x()>ui->cell21_UE->x() && newLabel->x()<(ui->cell21_UE->x()+150)){
                        ok=true;
                        pointerUE3->area1->setText("Center21");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //cell22
                if(!ok && newLabel->y()>ui->cell22_UE->y() && newLabel->y()<(ui->cell22_UE->y()+50)){
                    if(newLabel->x()>ui->cell22_UE->x() && newLabel->x()<(ui->cell22_UE->x()+150)){
                        ok=true;
                        pointerUE3->area1->setText("Center22");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }
                //cell31
                if(!ok && newLabel->y()>ui->cell31_UE->y() && newLabel->y()<(ui->cell31_UE->y()+150)){
                    if(newLabel->x()>ui->cell31_UE->x() && newLabel->x()<(ui->cell31_UE->x()+130)){
                        ok=true;
                        pointerUE3->area1->setText("Center31");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //cell32
                if(!ok && newLabel->y()>ui->cell32_UE->y() && newLabel->y()<(ui->cell32_UE->y()+160)){
                    if(newLabel->x()>ui->cell32_UE->x() && newLabel->x()<(ui->cell32_UE->x()+140)){
                        ok=true;
                        pointerUE3->area1->setText("Center32");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //cell41
                if(!ok && newLabel->y()>ui->cell41_UE->y() && newLabel->y()<(ui->cell41_UE->y()+101)){
                    if(newLabel->x()>ui->cell41_UE->x() && newLabel->x()<(ui->cell41_UE->x()+141)){
                        ok=true;
                        pointerUE3->area1->setText("Center41");
                    }
                    else{
                        pointerUE3->area1->setText("cell41");
                    }
                }

                //cell42
                if(!ok && newLabel->y()>ui->cell42_UE->y() && newLabel->y()<(ui->cell42_UE->y()+101)){
                    if(newLabel->x()>ui->cell42_UE->x() && newLabel->x()<(ui->cell42_UE->x()+141)){
                        ok=true;
                        pointerUE3->area1->setText("Center42");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //cell51
                if(!ok && newLabel->y()>ui->cell51_UE->y() && newLabel->y()<(ui->cell51_UE->y()+101)){
                    if(newLabel->x()>ui->cell51_UE->x() && newLabel->x()<(ui->cell51_UE->x()+151)){
                        ok=true;
                        pointerUE3->area1->setText("Center51");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //cell52
                if(!ok && newLabel->y()>ui->cell52_UE->y() && newLabel->y()<(ui->cell52_UE->y()+101)){
                    if(newLabel->x()>ui->cell52_UE->x() && newLabel->x()<(ui->cell52_UE->x()+151)){
                        ok=true;
                        pointerUE3->area1->setText("Center52");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //cell61
                if(!ok && newLabel->y()>ui->cell61_UE->y() && newLabel->y()<(ui->cell61_UE->y()+111)){
                    if(newLabel->x()>ui->cell61_UE->x() && newLabel->x()<(ui->cell61_UE->x()+131)){
                        ok=true;
                        pointerUE3->area1->setText("Center61");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //cell62
                if(!ok && newLabel->y()>ui->cell62_UE->y() && newLabel->y()<(ui->cell62_UE->y()+111)){
                    if(newLabel->x()>ui->cell62_UE->x() && newLabel->x()<(ui->cell62_UE->x()+131)){
                        ok=true;
                        pointerUE3->area1->setText("Center62");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Handover11_12
                if(!ok && newLabel->y()>ui->Handover11_12_UE->y() && newLabel->y()<(ui->Handover11_12_UE->y()+120)){
                    if(newLabel->x()>ui->Handover11_12_UE->x() && newLabel->x()<(ui->Handover11_12_UE->x()+60)){
                        ok=true;
                        pointerUE3->area1->setText("Handover11_12");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Handover11_21
                if(!ok && newLabel->y()>ui->Handover11_21_UE->y() && newLabel->y()<(ui->Handover11_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover11_21_UE->x() && newLabel->x()<(ui->Handover11_21_UE->x()+50)){
                        ok=true;
                        pointerUE3->area1->setText("Handover11_21");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Handover12_21
                if(!ok && newLabel->y()>ui->Handover12_21_UE->y() && newLabel->y()<(ui->Handover12_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_21_UE->x() && newLabel->x()<(ui->Handover12_21_UE->x()+70)){
                        ok=true;
                        pointerUE3->area1->setText("Handover12_21");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Handover12_22
                if(!ok && newLabel->y()>ui->Handover12_22_UE->y() && newLabel->y()<(ui->Handover12_22_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_22_UE->x() && newLabel->x()<(ui->Handover12_22_UE->x()+70)){
                        ok=true;
                        pointerUE3->area1->setText("Handover12_22");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Handover21_22
                if(!ok && newLabel->y()>ui->Handover21_22_UE->y() && newLabel->y()<(ui->Handover21_22_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_22_UE->x() && newLabel->x()<(ui->Handover21_22_UE->x()+70)){
                        ok=true;
                        pointerUE3->area1->setText("Handover21_22");
                    }
                    else{
                        pointerUE3->area1->setText("Handover21_22");
                    }
                }

                //Handover21_31
                if(!ok && newLabel->y()>ui->Handover21_31_UE->y() && newLabel->y()<(ui->Handover21_31_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_31_UE->x() && newLabel->x()<(ui->Handover21_31_UE->x()+60)){
                        ok=true;
                        pointerUE3->area1->setText("Handover21_31");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Handover21_32
                if(!ok && newLabel->y()>ui->Handover21_32_UE->y() && newLabel->y()<(ui->Handover21_32_UE->y()+30)){
                    if(newLabel->x()>ui->Handover21_32_UE->x() && newLabel->x()<(ui->Handover21_32_UE->x()+90)){
                        ok=true;
                        pointerUE3->area1->setText("Handover21_32");
                    }
                    else{
                        pointerUE3->area1->setText("Handover21_32");
                    }
                }


                //Handover22_32
                if(!ok && newLabel->y()>ui->Handover22_32_UE->y() && newLabel->y()<(ui->Handover22_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover22_32_UE->x() && newLabel->x()<(ui->Handover22_32_UE->x()+60)){
                        ok=true;
                        pointerUE3->area1->setText("Handover22_32");
                    }
                    else{
                        pointerUE3->area1->setText("Handover22_32");
                    }
                }

                //Handover31_32
                if(!ok && newLabel->y()>ui->Handover31_32_UE->y() && newLabel->y()<(ui->Handover31_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover31_32_UE->x() && newLabel->x()<(ui->Handover31_32_UE->x()+60)){
                        ok=true;
                        pointerUE3->area1->setText("Handover31_32");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Handover31_41
                if(!ok && newLabel->y()>ui->Handover31_41_UE->y() && newLabel->y()<(ui->Handover31_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover31_41_UE->x() && newLabel->x()<(ui->Handover31_41_UE->x()+80)){
                        ok=true;
                        pointerUE3->area1->setText("Handover31_41");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Handover32_41
                if(!ok && newLabel->y()>ui->Handover32_41_UE->y() && newLabel->y()<(ui->Handover32_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_41_UE->x() && newLabel->x()<(ui->Handover32_41_UE->x()+90)){
                        ok=true;
                        pointerUE3->area1->setText("Handover32_41");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Handover32_42
                if(!ok && newLabel->y()>ui->Handover32_42_UE->y() && newLabel->y()<(ui->Handover32_42_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_42_UE->x() && newLabel->x()<(ui->Handover32_42_UE->x()+90)){
                        ok=true;
                        pointerUE3->area1->setText("Handover32_42");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Handover41_42
                if(!ok && newLabel->y()>ui->Handover41_42_UE->y() && newLabel->y()<(ui->Handover41_42_UE->y()+110)){
                    if(newLabel->x()>ui->Handover41_42_UE->x() && newLabel->x()<(ui->Handover41_42_UE->x()+40)){
                        ok=true;
                        pointerUE3->area1->setText("Handover41_42");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Handover41_51
                if(!ok && newLabel->y()>ui->Handover41_51_UE->y() && newLabel->y()<(ui->Handover41_51_UE->y()+66)){
                    if(newLabel->x()>ui->Handover41_51_UE->x() && newLabel->x()<(ui->Handover41_51_UE->x()+81)){
                        ok=true;
                        pointerUE3->area1->setText("Handover41_51");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Handover42_52
                if(!ok && newLabel->y()>ui->Handover42_52_UE->y() && newLabel->y()<(ui->Handover42_52_UE->y()+66)){
                    if(newLabel->x()>ui->Handover42_52_UE->x() && newLabel->x()<(ui->Handover42_52_UE->x()+96)){
                        ok=true;
                        pointerUE3->area1->setText("Handover42_52");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Handover51_52
                if(!ok && newLabel->y()>ui->Handover51_52_UE->y() && newLabel->y()<(ui->Handover51_52_UE->y()+91)){
                    if(newLabel->x()>ui->Handover51_52_UE->x() && newLabel->x()<(ui->Handover51_52_UE->x()+56)){
                        ok=true;
                        pointerUE3->area1->setText("Handover51_52");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Handover51_61
                if(!ok && newLabel->y()>ui->Handover51_61_UE->y() && newLabel->y()<(ui->Handover51_61_UE->y()+41)){
                    if(newLabel->x()>ui->Handover51_61_UE->x() && newLabel->x()<(ui->Handover51_61_UE->x()+76)){
                        ok=true;
                        pointerUE3->area1->setText("Handover51_61");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Handover52_61
                if(!ok && newLabel->y()>ui->Handover52_61_UE->y() && newLabel->y()<(ui->Handover52_61_UE->y()+56)){
                    if(newLabel->x()>ui->Handover52_61_UE->x() && newLabel->x()<(ui->Handover52_61_UE->x()+66)){
                        ok=true;
                        pointerUE3->area1->setText("Handover52_61");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Handover52_62
                if(!ok && newLabel->y()>ui->Handover52_62_UE->y() && newLabel->y()<(ui->Handover52_62_UE->y()+66)){
                    if(newLabel->x()>ui->Handover52_62_UE->x() && newLabel->x()<(ui->Handover52_62_UE->x()+86)){
                        ok=true;
                        pointerUE3->area1->setText("Handover52_62");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }

                //Handover61_62
                if(!ok && newLabel->y()>ui->Handover61_62_UE->y() && newLabel->y()<(ui->Handover61_62_UE->y()+96)){
                    if(newLabel->x()>ui->Handover61_62_UE->x() && newLabel->x()<(ui->Handover61_62_UE->x()+116)){
                        ok=true;
                        pointerUE3->area1->setText("Handover61_62");
                    }
                    else{
                        pointerUE3->area1->setText("");
                    }
                }
                actualposition=newLabel;
                tab_UE[2]=newLabel;
            }
            else {
                event->acceptProposedAction();
            }
        }
    }

    //UE4
    if (event->mimeData()->hasFormat("application/x-UE")) {
        const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data("application/x-UE");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString text;
        QPoint offset;
        dataStream >> text >> offset;

        DragUELabel *newLabel = new DragUELabel(text, ui->scrollAreaWidgetContents);

        if(actualposition==tab_UE[3]){
            newLabel->move(event->pos() - offset);
            newLabel->show();
            newLabel->setAttribute(Qt::WA_DeleteOnClose);

            if (event->source() == this) {
                event->setDropAction(Qt::MoveAction);
                event->accept();

                //Cell11
                bool ok=false;
                if(newLabel->y()>ui->cell11_UE->y() && newLabel->y()<ui->cell11_UE->y()+120){
                    if(newLabel->x()>ui->cell11_UE->x() && newLabel->x()<ui->cell11_UE->x()+120){
                        ok=true;
                        pointerUE4->area1->setText("Center11");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Cell12
                if(!ok && newLabel->y()>ui->cell12_UE->y() && newLabel->y()<(ui->cell12_UE->y()+110)){
                    if(newLabel->x()>ui->cell12_UE->x() && newLabel->x()<(ui->cell12_UE->x()+100)){
                        ok=true;
                        pointerUE4->area1->setText("Center12");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //cell21
                if(!ok && newLabel->y()>ui->cell21_UE->y() && newLabel->y()<(ui->cell21_UE->y()+50)){
                    if(newLabel->x()>ui->cell21_UE->x() && newLabel->x()<(ui->cell21_UE->x()+150)){
                        ok=true;
                        pointerUE4->area1->setText("Center21");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //cell22
                if(!ok && newLabel->y()>ui->cell22_UE->y() && newLabel->y()<(ui->cell22_UE->y()+50)){
                    if(newLabel->x()>ui->cell22_UE->x() && newLabel->x()<(ui->cell22_UE->x()+150)){
                        ok=true;
                        pointerUE4->area1->setText("Center22");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //cell31
                if(!ok && newLabel->y()>ui->cell31_UE->y() && newLabel->y()<(ui->cell31_UE->y()+150)){
                    if(newLabel->x()>ui->cell31_UE->x() && newLabel->x()<(ui->cell31_UE->x()+130)){
                        ok=true;
                        pointerUE4->area1->setText("Center31");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //cell32
                if(!ok && newLabel->y()>ui->cell32_UE->y() && newLabel->y()<(ui->cell32_UE->y()+160)){
                    if(newLabel->x()>ui->cell32_UE->x() && newLabel->x()<(ui->cell32_UE->x()+140)){
                        ok=true;
                        pointerUE4->area1->setText("Center32");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //cell41
                if(!ok && newLabel->y()>ui->cell41_UE->y() && newLabel->y()<(ui->cell41_UE->y()+101)){
                    if(newLabel->x()>ui->cell41_UE->x() && newLabel->x()<(ui->cell41_UE->x()+141)){
                        ok=true;
                        pointerUE4->area1->setText("Center41");
                    }
                    else{
                        pointerUE4->area1->setText("cell41");
                    }
                }

                //cell42
                if(!ok && newLabel->y()>ui->cell42_UE->y() && newLabel->y()<(ui->cell42_UE->y()+101)){
                    if(newLabel->x()>ui->cell42_UE->x() && newLabel->x()<(ui->cell42_UE->x()+141)){
                        ok=true;
                        pointerUE4->area1->setText("Center42");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //cell51
                if(!ok && newLabel->y()>ui->cell51_UE->y() && newLabel->y()<(ui->cell51_UE->y()+101)){
                    if(newLabel->x()>ui->cell51_UE->x() && newLabel->x()<(ui->cell51_UE->x()+151)){
                        ok=true;
                        pointerUE4->area1->setText("Center51");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //cell52
                if(!ok && newLabel->y()>ui->cell52_UE->y() && newLabel->y()<(ui->cell52_UE->y()+101)){
                    if(newLabel->x()>ui->cell52_UE->x() && newLabel->x()<(ui->cell52_UE->x()+151)){
                        ok=true;
                        pointerUE4->area1->setText("Center52");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //cell61
                if(!ok && newLabel->y()>ui->cell61_UE->y() && newLabel->y()<(ui->cell61_UE->y()+111)){
                    if(newLabel->x()>ui->cell61_UE->x() && newLabel->x()<(ui->cell61_UE->x()+131)){
                        ok=true;
                        pointerUE4->area1->setText("Center61");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //cell62
                if(!ok && newLabel->y()>ui->cell62_UE->y() && newLabel->y()<(ui->cell62_UE->y()+111)){
                    if(newLabel->x()>ui->cell62_UE->x() && newLabel->x()<(ui->cell62_UE->x()+131)){
                        ok=true;
                        pointerUE4->area1->setText("Center62");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Handover11_12
                if(!ok && newLabel->y()>ui->Handover11_12_UE->y() && newLabel->y()<(ui->Handover11_12_UE->y()+120)){
                    if(newLabel->x()>ui->Handover11_12_UE->x() && newLabel->x()<(ui->Handover11_12_UE->x()+60)){
                        ok=true;
                        pointerUE4->area1->setText("Handover11_12");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Handover11_21
                if(!ok && newLabel->y()>ui->Handover11_21_UE->y() && newLabel->y()<(ui->Handover11_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover11_21_UE->x() && newLabel->x()<(ui->Handover11_21_UE->x()+50)){
                        ok=true;
                        pointerUE4->area1->setText("Handover11_21");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Handover12_21
                if(!ok && newLabel->y()>ui->Handover12_21_UE->y() && newLabel->y()<(ui->Handover12_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_21_UE->x() && newLabel->x()<(ui->Handover12_21_UE->x()+70)){
                        ok=true;
                        pointerUE4->area1->setText("Handover12_21");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Handover12_22
                if(!ok && newLabel->y()>ui->Handover12_22_UE->y() && newLabel->y()<(ui->Handover12_22_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_22_UE->x() && newLabel->x()<(ui->Handover12_22_UE->x()+70)){
                        ok=true;
                        pointerUE4->area1->setText("Handover12_22");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Handover21_22
                if(!ok && newLabel->y()>ui->Handover21_22_UE->y() && newLabel->y()<(ui->Handover21_22_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_22_UE->x() && newLabel->x()<(ui->Handover21_22_UE->x()+70)){
                        ok=true;
                        pointerUE4->area1->setText("Handover21_22");
                    }
                    else{
                        pointerUE4->area1->setText("Handover21_22");
                    }
                }

                //Handover21_31
                if(!ok && newLabel->y()>ui->Handover21_31_UE->y() && newLabel->y()<(ui->Handover21_31_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_31_UE->x() && newLabel->x()<(ui->Handover21_31_UE->x()+60)){
                        ok=true;
                        pointerUE4->area1->setText("Handover21_31");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Handover21_32
                if(!ok && newLabel->y()>ui->Handover21_32_UE->y() && newLabel->y()<(ui->Handover21_32_UE->y()+30)){
                    if(newLabel->x()>ui->Handover21_32_UE->x() && newLabel->x()<(ui->Handover21_32_UE->x()+90)){
                        ok=true;
                        pointerUE4->area1->setText("Handover21_32");
                    }
                    else{
                        pointerUE4->area1->setText("Handover21_32");
                    }
                }

                //Handover22_32
                if(!ok && newLabel->y()>ui->Handover22_32_UE->y() && newLabel->y()<(ui->Handover22_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover22_32_UE->x() && newLabel->x()<(ui->Handover22_32_UE->x()+60)){
                        ok=true;
                        pointerUE4->area1->setText("Handover22_32");
                    }
                    else{
                        pointerUE4->area1->setText("Handover22_32");
                    }
                }

                //Handover31_32
                if(!ok && newLabel->y()>ui->Handover31_32_UE->y() && newLabel->y()<(ui->Handover31_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover31_32_UE->x() && newLabel->x()<(ui->Handover31_32_UE->x()+60)){
                        ok=true;
                        pointerUE4->area1->setText("Handover31_32");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Handover31_41
                if(!ok && newLabel->y()>ui->Handover31_41_UE->y() && newLabel->y()<(ui->Handover31_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover31_41_UE->x() && newLabel->x()<(ui->Handover31_41_UE->x()+80)){
                        ok=true;
                        pointerUE4->area1->setText("Handover31_41");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Handover32_41
                if(!ok && newLabel->y()>ui->Handover32_41_UE->y() && newLabel->y()<(ui->Handover32_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_41_UE->x() && newLabel->x()<(ui->Handover32_41_UE->x()+90)){
                        ok=true;
                        pointerUE4->area1->setText("Handover32_41");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Handover32_42
                if(!ok && newLabel->y()>ui->Handover32_42_UE->y() && newLabel->y()<(ui->Handover32_42_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_42_UE->x() && newLabel->x()<(ui->Handover32_42_UE->x()+90)){
                        ok=true;
                        pointerUE4->area1->setText("Handover32_42");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Handover41_42
                if(!ok && newLabel->y()>ui->Handover41_42_UE->y() && newLabel->y()<(ui->Handover41_42_UE->y()+110)){
                    if(newLabel->x()>ui->Handover41_42_UE->x() && newLabel->x()<(ui->Handover41_42_UE->x()+40)){
                        ok=true;
                        pointerUE4->area1->setText("Handover41_42");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Handover41_51
                if(!ok && newLabel->y()>ui->Handover41_51_UE->y() && newLabel->y()<(ui->Handover41_51_UE->y()+66)){
                    if(newLabel->x()>ui->Handover41_51_UE->x() && newLabel->x()<(ui->Handover41_51_UE->x()+81)){
                        ok=true;
                        pointerUE4->area1->setText("Handover41_51");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Handover42_52
                if(!ok && newLabel->y()>ui->Handover42_52_UE->y() && newLabel->y()<(ui->Handover42_52_UE->y()+66)){
                    if(newLabel->x()>ui->Handover42_52_UE->x() && newLabel->x()<(ui->Handover42_52_UE->x()+96)){
                        ok=true;
                        pointerUE4->area1->setText("Handover42_52");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Handover51_52
                if(!ok && newLabel->y()>ui->Handover51_52_UE->y() && newLabel->y()<(ui->Handover51_52_UE->y()+91)){
                    if(newLabel->x()>ui->Handover51_52_UE->x() && newLabel->x()<(ui->Handover51_52_UE->x()+56)){
                        ok=true;
                        pointerUE4->area1->setText("Handover51_52");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Handover51_61
                if(!ok && newLabel->y()>ui->Handover51_61_UE->y() && newLabel->y()<(ui->Handover51_61_UE->y()+41)){
                    if(newLabel->x()>ui->Handover51_61_UE->x() && newLabel->x()<(ui->Handover51_61_UE->x()+76)){
                        ok=true;
                        pointerUE4->area1->setText("Handover51_61");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Handover52_61
                if(!ok && newLabel->y()>ui->Handover52_61_UE->y() && newLabel->y()<(ui->Handover52_61_UE->y()+56)){
                    if(newLabel->x()>ui->Handover52_61_UE->x() && newLabel->x()<(ui->Handover52_61_UE->x()+66)){
                        ok=true;
                        pointerUE4->area1->setText("Handover52_61");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Handover52_62
                if(!ok && newLabel->y()>ui->Handover52_62_UE->y() && newLabel->y()<(ui->Handover52_62_UE->y()+66)){
                    if(newLabel->x()>ui->Handover52_62_UE->x() && newLabel->x()<(ui->Handover52_62_UE->x()+86)){
                        ok=true;
                        pointerUE4->area1->setText("Handover52_62");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }

                //Handover61_62
                if(!ok && newLabel->y()>ui->Handover61_62_UE->y() && newLabel->y()<(ui->Handover61_62_UE->y()+96)){
                    if(newLabel->x()>ui->Handover61_62_UE->x() && newLabel->x()<(ui->Handover61_62_UE->x()+116)){
                        ok=true;
                        pointerUE4->area1->setText("Handover61_62");
                    }
                    else{
                        pointerUE4->area1->setText("");
                    }
                }
                actualposition=newLabel;
                tab_UE[3]=newLabel;
            }
            else {
                event->acceptProposedAction();
            }
        }
    }

    //UE5
    if (event->mimeData()->hasFormat("application/x-UE")) {
        const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data("application/x-UE");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString text;
        QPoint offset;
        dataStream >> text >> offset;

        DragUELabel *newLabel = new DragUELabel(text, ui->scrollAreaWidgetContents);

        if(actualposition==tab_UE[4]){
            newLabel->move(event->pos() - offset);
            newLabel->show();
            newLabel->setAttribute(Qt::WA_DeleteOnClose);

            if (event->source() == this) {
                event->setDropAction(Qt::MoveAction);
                event->accept();

                //Cell11
                bool ok=false;
                if(newLabel->y()>ui->cell11_UE->y() && newLabel->y()<ui->cell11_UE->y()+120){
                    if(newLabel->x()>ui->cell11_UE->x() && newLabel->x()<ui->cell11_UE->x()+120){
                        ok=true;
                        pointerUE5->area1->setText("Center11");

                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Cell12
                if(!ok && newLabel->y()>ui->cell12_UE->y() && newLabel->y()<(ui->cell12_UE->y()+110)){
                    if(newLabel->x()>ui->cell12_UE->x() && newLabel->x()<(ui->cell12_UE->x()+100)){
                        ok=true;
                        pointerUE5->area1->setText("Center12");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //cell21
                if(!ok && newLabel->y()>ui->cell21_UE->y() && newLabel->y()<(ui->cell21_UE->y()+50)){
                    if(newLabel->x()>ui->cell21_UE->x() && newLabel->x()<(ui->cell21_UE->x()+150)){
                        ok=true;
                        pointerUE5->area1->setText("Center21");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //cell22
                if(!ok && newLabel->y()>ui->cell22_UE->y() && newLabel->y()<(ui->cell22_UE->y()+50)){
                    if(newLabel->x()>ui->cell22_UE->x() && newLabel->x()<(ui->cell22_UE->x()+150)){
                        ok=true;
                        pointerUE5->area1->setText("Center22");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //cell31
                if(!ok && newLabel->y()>ui->cell31_UE->y() && newLabel->y()<(ui->cell31_UE->y()+150)){
                    if(newLabel->x()>ui->cell31_UE->x() && newLabel->x()<(ui->cell31_UE->x()+130)){
                        ok=true;
                        pointerUE5->area1->setText("Center31");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //cell32
                if(!ok && newLabel->y()>ui->cell32_UE->y() && newLabel->y()<(ui->cell32_UE->y()+160)){
                    if(newLabel->x()>ui->cell32_UE->x() && newLabel->x()<(ui->cell32_UE->x()+140)){
                        ok=true;
                        pointerUE5->area1->setText("Center32");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //cell41
                if(!ok && newLabel->y()>ui->cell41_UE->y() && newLabel->y()<(ui->cell41_UE->y()+101)){
                    if(newLabel->x()>ui->cell41_UE->x() && newLabel->x()<(ui->cell41_UE->x()+141)){
                        ok=true;
                        pointerUE5->area1->setText("Center41");
                    }
                    else{
                        pointerUE5->area1->setText("cell41");
                    }
                }

                //cell42
                if(!ok && newLabel->y()>ui->cell42_UE->y() && newLabel->y()<(ui->cell42_UE->y()+101)){
                    if(newLabel->x()>ui->cell42_UE->x() && newLabel->x()<(ui->cell42_UE->x()+141)){
                        ok=true;
                        pointerUE5->area1->setText("Center42");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //cell51
                if(!ok && newLabel->y()>ui->cell51_UE->y() && newLabel->y()<(ui->cell51_UE->y()+101)){
                    if(newLabel->x()>ui->cell51_UE->x() && newLabel->x()<(ui->cell51_UE->x()+151)){
                        ok=true;
                        pointerUE5->area1->setText("Center51");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //cell52
                if(!ok && newLabel->y()>ui->cell52_UE->y() && newLabel->y()<(ui->cell52_UE->y()+101)){
                    if(newLabel->x()>ui->cell52_UE->x() && newLabel->x()<(ui->cell52_UE->x()+151)){
                        ok=true;
                        pointerUE5->area1->setText("Center52");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //cell61
                if(!ok && newLabel->y()>ui->cell61_UE->y() && newLabel->y()<(ui->cell61_UE->y()+111)){
                    if(newLabel->x()>ui->cell61_UE->x() && newLabel->x()<(ui->cell61_UE->x()+131)){
                        ok=true;
                        pointerUE5->area1->setText("Center61");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //cell62
                if(!ok && newLabel->y()>ui->cell62_UE->y() && newLabel->y()<(ui->cell62_UE->y()+111)){
                    if(newLabel->x()>ui->cell62_UE->x() && newLabel->x()<(ui->cell62_UE->x()+131)){
                        ok=true;
                        pointerUE5->area1->setText("Center62");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Handover11_12
                if(!ok && newLabel->y()>ui->Handover11_12_UE->y() && newLabel->y()<(ui->Handover11_12_UE->y()+120)){
                    if(newLabel->x()>ui->Handover11_12_UE->x() && newLabel->x()<(ui->Handover11_12_UE->x()+60)){
                        ok=true;
                        pointerUE5->area1->setText("Handover11_12");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Handover11_21
                if(!ok && newLabel->y()>ui->Handover11_21_UE->y() && newLabel->y()<(ui->Handover11_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover11_21_UE->x() && newLabel->x()<(ui->Handover11_21_UE->x()+50)){
                        ok=true;
                        pointerUE5->area1->setText("Handover11_21");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Handover12_21
                if(!ok && newLabel->y()>ui->Handover12_21_UE->y() && newLabel->y()<(ui->Handover12_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_21_UE->x() && newLabel->x()<(ui->Handover12_21_UE->x()+70)){
                        ok=true;
                        pointerUE5->area1->setText("Handover12_21");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Handover12_22
                if(!ok && newLabel->y()>ui->Handover12_22_UE->y() && newLabel->y()<(ui->Handover12_22_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_22_UE->x() && newLabel->x()<(ui->Handover12_22_UE->x()+70)){
                        ok=true;
                        pointerUE5->area1->setText("Handover12_22");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Handover21_22
                if(!ok && newLabel->y()>ui->Handover21_22_UE->y() && newLabel->y()<(ui->Handover21_22_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_22_UE->x() && newLabel->x()<(ui->Handover21_22_UE->x()+70)){
                        ok=true;
                        pointerUE5->area1->setText("Handover21_22");
                    }
                    else{
                        pointerUE5->area1->setText("Handover21_22");
                    }
                }

                //Handover21_31
                if(!ok && newLabel->y()>ui->Handover21_31_UE->y() && newLabel->y()<(ui->Handover21_31_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_31_UE->x() && newLabel->x()<(ui->Handover21_31_UE->x()+60)){
                        ok=true;
                        pointerUE5->area1->setText("Handover21_31");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Handover21_32
                if(!ok && newLabel->y()>ui->Handover21_32_UE->y() && newLabel->y()<(ui->Handover21_32_UE->y()+30)){
                    if(newLabel->x()>ui->Handover21_32_UE->x() && newLabel->x()<(ui->Handover21_32_UE->x()+90)){
                        ok=true;
                        pointerUE5->area1->setText("Handover21_32");
                    }
                    else{
                        pointerUE5->area1->setText("Handover21_32");
                    }
                }

                //Handover22_32
                if(!ok && newLabel->y()>ui->Handover22_32_UE->y() && newLabel->y()<(ui->Handover22_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover22_32_UE->x() && newLabel->x()<(ui->Handover22_32_UE->x()+60)){
                        ok=true;
                        pointerUE5->area1->setText("Handover22_32");
                    }
                    else{
                        pointerUE5->area1->setText("Handover22_32");
                    }
                }

                //Handover31_32
                if(!ok && newLabel->y()>ui->Handover31_32_UE->y() && newLabel->y()<(ui->Handover31_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover31_32_UE->x() && newLabel->x()<(ui->Handover31_32_UE->x()+60)){
                        ok=true;
                        pointerUE5->area1->setText("Handover31_32");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Handover31_41
                if(!ok && newLabel->y()>ui->Handover31_41_UE->y() && newLabel->y()<(ui->Handover31_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover31_41_UE->x() && newLabel->x()<(ui->Handover31_41_UE->x()+80)){
                        ok=true;
                        pointerUE5->area1->setText("Handover31_41");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Handover32_41
                if(!ok && newLabel->y()>ui->Handover32_41_UE->y() && newLabel->y()<(ui->Handover32_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_41_UE->x() && newLabel->x()<(ui->Handover32_41_UE->x()+90)){
                        ok=true;
                        pointerUE5->area1->setText("Handover32_41");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Handover32_42
                if(!ok && newLabel->y()>ui->Handover32_42_UE->y() && newLabel->y()<(ui->Handover32_42_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_42_UE->x() && newLabel->x()<(ui->Handover32_42_UE->x()+90)){
                        ok=true;
                        pointerUE5->area1->setText("Handover32_42");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Handover41_42
                if(!ok && newLabel->y()>ui->Handover41_42_UE->y() && newLabel->y()<(ui->Handover41_42_UE->y()+110)){
                    if(newLabel->x()>ui->Handover41_42_UE->x() && newLabel->x()<(ui->Handover41_42_UE->x()+40)){
                        ok=true;
                        pointerUE5->area1->setText("Handover41_42");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Handover41_51
                if(!ok && newLabel->y()>ui->Handover41_51_UE->y() && newLabel->y()<(ui->Handover41_51_UE->y()+66)){
                    if(newLabel->x()>ui->Handover41_51_UE->x() && newLabel->x()<(ui->Handover41_51_UE->x()+81)){
                        ok=true;
                        pointerUE5->area1->setText("Handover41_51");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Handover42_52
                if(!ok && newLabel->y()>ui->Handover42_52_UE->y() && newLabel->y()<(ui->Handover42_52_UE->y()+66)){
                    if(newLabel->x()>ui->Handover42_52_UE->x() && newLabel->x()<(ui->Handover42_52_UE->x()+96)){
                        ok=true;
                        pointerUE5->area1->setText("Handover42_52");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Handover51_52
                if(!ok && newLabel->y()>ui->Handover51_52_UE->y() && newLabel->y()<(ui->Handover51_52_UE->y()+91)){
                    if(newLabel->x()>ui->Handover51_52_UE->x() && newLabel->x()<(ui->Handover51_52_UE->x()+56)){
                        ok=true;
                        pointerUE5->area1->setText("Handover51_52");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Handover51_61
                if(!ok && newLabel->y()>ui->Handover51_61_UE->y() && newLabel->y()<(ui->Handover51_61_UE->y()+41)){
                    if(newLabel->x()>ui->Handover51_61_UE->x() && newLabel->x()<(ui->Handover51_61_UE->x()+76)){
                        ok=true;
                        pointerUE5->area1->setText("Handover51_61");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Handover52_61
                if(!ok && newLabel->y()>ui->Handover52_61_UE->y() && newLabel->y()<(ui->Handover52_61_UE->y()+56)){
                    if(newLabel->x()>ui->Handover52_61_UE->x() && newLabel->x()<(ui->Handover52_61_UE->x()+66)){
                        ok=true;
                        pointerUE5->area1->setText("Handover52_61");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Handover52_62
                if(!ok && newLabel->y()>ui->Handover52_62_UE->y() && newLabel->y()<(ui->Handover52_62_UE->y()+66)){
                    if(newLabel->x()>ui->Handover52_62_UE->x() && newLabel->x()<(ui->Handover52_62_UE->x()+86)){
                        ok=true;
                        pointerUE5->area1->setText("Handover52_62");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }

                //Handover61_62
                if(!ok && newLabel->y()>ui->Handover61_62_UE->y() && newLabel->y()<(ui->Handover61_62_UE->y()+96)){
                    if(newLabel->x()>ui->Handover61_62_UE->x() && newLabel->x()<(ui->Handover61_62_UE->x()+116)){
                        ok=true;
                        pointerUE5->area1->setText("Handover61_62");
                    }
                    else{
                        pointerUE5->area1->setText("");
                    }
                }
                actualposition=newLabel;
                tab_UE[4]=newLabel;
            }
            else {
                event->acceptProposedAction();
            }
        }
    }

    //UE6
    if (event->mimeData()->hasFormat("application/x-UE")) {
        const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data("application/x-UE");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString text;
        QPoint offset;
        dataStream >> text >> offset;

        DragUELabel *newLabel = new DragUELabel(text, ui->scrollAreaWidgetContents);

        if(actualposition==tab_UE[5]){
            newLabel->move(event->pos() - offset);
            newLabel->show();
            newLabel->setAttribute(Qt::WA_DeleteOnClose);

            if (event->source() == this) {
                event->setDropAction(Qt::MoveAction);
                event->accept();

                //Cell11
                bool ok=false;
                if(newLabel->y()>ui->cell11_UE->y() && newLabel->y()<ui->cell11_UE->y()+120){
                    if(newLabel->x()>ui->cell11_UE->x() && newLabel->x()<ui->cell11_UE->x()+120){
                        ok=true;
                        pointerUE6->area1->setText("Center11");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //Cell12
                if(!ok && newLabel->y()>ui->cell12_UE->y() && newLabel->y()<(ui->cell12_UE->y()+110)){
                    if(newLabel->x()>ui->cell12_UE->x() && newLabel->x()<(ui->cell12_UE->x()+100)){
                        ok=true;
                        pointerUE6->area1->setText("Center12");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //cell21
                if(!ok && newLabel->y()>ui->cell21_UE->y() && newLabel->y()<(ui->cell21_UE->y()+50)){
                    if(newLabel->x()>ui->cell21_UE->x() && newLabel->x()<(ui->cell21_UE->x()+150)){
                        ok=true;
                        pointerUE6->area1->setText("Center21");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //cell22
                if(!ok && newLabel->y()>ui->cell22_UE->y() && newLabel->y()<(ui->cell22_UE->y()+50)){
                    if(newLabel->x()>ui->cell22_UE->x() && newLabel->x()<(ui->cell22_UE->x()+150)){
                        ok=true;
                        pointerUE6->area1->setText("Center22");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //cell31
                if(!ok && newLabel->y()>ui->cell31_UE->y() && newLabel->y()<(ui->cell31_UE->y()+150)){
                    if(newLabel->x()>ui->cell31_UE->x() && newLabel->x()<(ui->cell31_UE->x()+130)){
                        ok=true;
                        pointerUE6->area1->setText("Center31");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //cell32
                if(!ok && newLabel->y()>ui->cell32_UE->y() && newLabel->y()<(ui->cell32_UE->y()+160)){
                    if(newLabel->x()>ui->cell32_UE->x() && newLabel->x()<(ui->cell32_UE->x()+140)){
                        ok=true;
                        pointerUE6->area1->setText("Center32");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //cell41
                if(!ok && newLabel->y()>ui->cell41_UE->y() && newLabel->y()<(ui->cell41_UE->y()+101)){
                    if(newLabel->x()>ui->cell41_UE->x() && newLabel->x()<(ui->cell41_UE->x()+141)){
                        ok=true;
                        pointerUE6->area1->setText("Center41");
                    }
                    else{
                        pointerUE6->area1->setText("cell41");
                    }
                }

                //cell42
                if(!ok && newLabel->y()>ui->cell42_UE->y() && newLabel->y()<(ui->cell42_UE->y()+101)){
                    if(newLabel->x()>ui->cell42_UE->x() && newLabel->x()<(ui->cell42_UE->x()+141)){
                        ok=true;
                        pointerUE6->area1->setText("Center42");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //cell51
                if(!ok && newLabel->y()>ui->cell51_UE->y() && newLabel->y()<(ui->cell51_UE->y()+101)){
                    if(newLabel->x()>ui->cell51_UE->x() && newLabel->x()<(ui->cell51_UE->x()+151)){
                        ok=true;
                        pointerUE6->area1->setText("Center51");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //cell52
                if(!ok && newLabel->y()>ui->cell52_UE->y() && newLabel->y()<(ui->cell52_UE->y()+101)){
                    if(newLabel->x()>ui->cell52_UE->x() && newLabel->x()<(ui->cell52_UE->x()+151)){
                        ok=true;
                        pointerUE6->area1->setText("Center52");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //cell61
                if(!ok && newLabel->y()>ui->cell61_UE->y() && newLabel->y()<(ui->cell61_UE->y()+111)){
                    if(newLabel->x()>ui->cell61_UE->x() && newLabel->x()<(ui->cell61_UE->x()+131)){
                        ok=true;
                        pointerUE6->area1->setText("Center61");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //cell62
                if(!ok && newLabel->y()>ui->cell62_UE->y() && newLabel->y()<(ui->cell62_UE->y()+111)){
                    if(newLabel->x()>ui->cell62_UE->x() && newLabel->x()<(ui->cell62_UE->x()+131)){
                        ok=true;
                        pointerUE6->area1->setText("Center62");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //Handover11_12
                if(!ok && newLabel->y()>ui->Handover11_12_UE->y() && newLabel->y()<(ui->Handover11_12_UE->y()+120)){
                    if(newLabel->x()>ui->Handover11_12_UE->x() && newLabel->x()<(ui->Handover11_12_UE->x()+60)){
                        ok=true;
                        pointerUE6->area1->setText("Handover11_12");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //Handover11_21
                if(!ok && newLabel->y()>ui->Handover11_21_UE->y() && newLabel->y()<(ui->Handover11_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover11_21_UE->x() && newLabel->x()<(ui->Handover11_21_UE->x()+50)){
                        ok=true;
                        pointerUE6->area1->setText("Handover11_21");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //Handover12_21
                if(!ok && newLabel->y()>ui->Handover12_21_UE->y() && newLabel->y()<(ui->Handover12_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_21_UE->x() && newLabel->x()<(ui->Handover12_21_UE->x()+70)){
                        ok=true;
                        pointerUE6->area1->setText("Handover12_21");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //Handover12_22
                if(!ok && newLabel->y()>ui->Handover12_22_UE->y() && newLabel->y()<(ui->Handover12_22_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_22_UE->x() && newLabel->x()<(ui->Handover12_22_UE->x()+70)){
                        ok=true;
                        pointerUE6->area1->setText("Handover12_22");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //Handover21_22
                if(!ok && newLabel->y()>ui->Handover21_22_UE->y() && newLabel->y()<(ui->Handover21_22_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_22_UE->x() && newLabel->x()<(ui->Handover21_22_UE->x()+70)){
                        ok=true;
                        pointerUE6->area1->setText("Handover21_22");
                    }
                    else{
                        pointerUE6->area1->setText("Handover21_22");
                    }
                }

                //Handover21_31
                if(!ok && newLabel->y()>ui->Handover21_31_UE->y() && newLabel->y()<(ui->Handover21_31_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_31_UE->x() && newLabel->x()<(ui->Handover21_31_UE->x()+60)){
                        ok=true;
                        pointerUE6->area1->setText("Handover21_31");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //Handover21_32
                if(!ok && newLabel->y()>ui->Handover21_32_UE->y() && newLabel->y()<(ui->Handover21_32_UE->y()+30)){
                    if(newLabel->x()>ui->Handover21_32_UE->x() && newLabel->x()<(ui->Handover21_32_UE->x()+90)){
                        ok=true;
                        pointerUE6->area1->setText("Handover21_32");
                    }
                    else{
                        pointerUE6->area1->setText("Handover21_32");
                    }
                }

                //Handover22_32
                if(!ok && newLabel->y()>ui->Handover22_32_UE->y() && newLabel->y()<(ui->Handover22_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover22_32_UE->x() && newLabel->x()<(ui->Handover22_32_UE->x()+60)){
                        ok=true;
                        pointerUE6->area1->setText("Handover22_32");
                    }
                    else{
                        pointerUE6->area1->setText("Handover22_32");
                    }
                }

                //Handover31_32
                if(!ok && newLabel->y()>ui->Handover31_32_UE->y() && newLabel->y()<(ui->Handover31_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover31_32_UE->x() && newLabel->x()<(ui->Handover31_32_UE->x()+60)){
                        ok=true;
                        pointerUE6->area1->setText("Handover31_32");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //Handover31_41
                if(!ok && newLabel->y()>ui->Handover31_41_UE->y() && newLabel->y()<(ui->Handover31_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover31_41_UE->x() && newLabel->x()<(ui->Handover31_41_UE->x()+80)){
                        ok=true;
                        pointerUE6->area1->setText("Handover31_41");
                    }
                    else{
                        //tab_position_names[UEindex]="";
                    }
                }

                //Handover32_41
                if(!ok && newLabel->y()>ui->Handover32_41_UE->y() && newLabel->y()<(ui->Handover32_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_41_UE->x() && newLabel->x()<(ui->Handover32_41_UE->x()+90)){
                        ok=true;
                        pointerUE6->area1->setText("Handover32_41");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //Handover32_42
                if(!ok && newLabel->y()>ui->Handover32_42_UE->y() && newLabel->y()<(ui->Handover32_42_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_42_UE->x() && newLabel->x()<(ui->Handover32_42_UE->x()+90)){
                        ok=true;
                        pointerUE6->area1->setText("Handover32_42");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //Handover41_42
                if(!ok && newLabel->y()>ui->Handover41_42_UE->y() && newLabel->y()<(ui->Handover41_42_UE->y()+110)){
                    if(newLabel->x()>ui->Handover41_42_UE->x() && newLabel->x()<(ui->Handover41_42_UE->x()+40)){
                        ok=true;
                        pointerUE6->area1->setText("Handover41_42");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //Handover41_51
                if(!ok && newLabel->y()>ui->Handover41_51_UE->y() && newLabel->y()<(ui->Handover41_51_UE->y()+66)){
                    if(newLabel->x()>ui->Handover41_51_UE->x() && newLabel->x()<(ui->Handover41_51_UE->x()+81)){
                        ok=true;
                        pointerUE6->area1->setText("Handover41_51");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //Handover42_52
                if(!ok && newLabel->y()>ui->Handover42_52_UE->y() && newLabel->y()<(ui->Handover42_52_UE->y()+66)){
                    if(newLabel->x()>ui->Handover42_52_UE->x() && newLabel->x()<(ui->Handover42_52_UE->x()+96)){
                        ok=true;
                        pointerUE6->area1->setText("Handover42_52");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //Handover51_52
                if(!ok && newLabel->y()>ui->Handover51_52_UE->y() && newLabel->y()<(ui->Handover51_52_UE->y()+91)){
                    if(newLabel->x()>ui->Handover51_52_UE->x() && newLabel->x()<(ui->Handover51_52_UE->x()+56)){
                        ok=true;
                        pointerUE6->area1->setText("Handover51_52");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //Handover51_61
                if(!ok && newLabel->y()>ui->Handover51_61_UE->y() && newLabel->y()<(ui->Handover51_61_UE->y()+41)){
                    if(newLabel->x()>ui->Handover51_61_UE->x() && newLabel->x()<(ui->Handover51_61_UE->x()+76)){
                        ok=true;
                        pointerUE6->area1->setText("Handover51_61");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //Handover52_61
                if(!ok && newLabel->y()>ui->Handover52_61_UE->y() && newLabel->y()<(ui->Handover52_61_UE->y()+56)){
                    if(newLabel->x()>ui->Handover52_61_UE->x() && newLabel->x()<(ui->Handover52_61_UE->x()+66)){
                        ok=true;
                        pointerUE6->area1->setText("Handover52_61");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //Handover52_62
                if(!ok && newLabel->y()>ui->Handover52_62_UE->y() && newLabel->y()<(ui->Handover52_62_UE->y()+66)){
                    if(newLabel->x()>ui->Handover52_62_UE->x() && newLabel->x()<(ui->Handover52_62_UE->x()+86)){
                        ok=true;
                        pointerUE6->area1->setText("Handover52_62");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }

                //Handover61_62
                if(!ok && newLabel->y()>ui->Handover61_62_UE->y() && newLabel->y()<(ui->Handover61_62_UE->y()+96)){
                    if(newLabel->x()>ui->Handover61_62_UE->x() && newLabel->x()<(ui->Handover61_62_UE->x()+116)){
                        ok=true;
                        pointerUE6->area1->setText("Handover61_62");
                    }
                    else{
                        pointerUE6->area1->setText("");
                    }
                }
                actualposition=newLabel;
                tab_UE[5]=newLabel;
            }

            else {
                event->acceptProposedAction();
            }
        }
    }

    //UE7
    if (event->mimeData()->hasFormat("application/x-UE")) {
        const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data("application/x-UE");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString text;
        QPoint offset;
        dataStream >> text >> offset;

        DragUELabel *newLabel = new DragUELabel(text, ui->scrollAreaWidgetContents);

        if(actualposition==tab_UE[6]){
            newLabel->move(event->pos() - offset);
            newLabel->show();
            newLabel->setAttribute(Qt::WA_DeleteOnClose);

            if (event->source() == this) {
                event->setDropAction(Qt::MoveAction);
                event->accept();

                //Cell11
                bool ok=false;
                if(newLabel->y()>ui->cell11_UE->y() && newLabel->y()<ui->cell11_UE->y()+120){
                    if(newLabel->x()>ui->cell11_UE->x() && newLabel->x()<ui->cell11_UE->x()+120){
                        ok=true;
                        pointerUE7->area1->setText("Center11");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //Cell12
                if(!ok && newLabel->y()>ui->cell12_UE->y() && newLabel->y()<(ui->cell12_UE->y()+110)){
                    if(newLabel->x()>ui->cell12_UE->x() && newLabel->x()<(ui->cell12_UE->x()+100)){
                        ok=true;
                        pointerUE7->area1->setText("Center12");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //cell21
                if(!ok && newLabel->y()>ui->cell21_UE->y() && newLabel->y()<(ui->cell21_UE->y()+50)){
                    if(newLabel->x()>ui->cell21_UE->x() && newLabel->x()<(ui->cell21_UE->x()+150)){
                        ok=true;
                        pointerUE7->area1->setText("Center21");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //cell22
                if(!ok && newLabel->y()>ui->cell22_UE->y() && newLabel->y()<(ui->cell22_UE->y()+50)){
                    if(newLabel->x()>ui->cell22_UE->x() && newLabel->x()<(ui->cell22_UE->x()+150)){
                        ok=true;
                        pointerUE7->area1->setText("Center22");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //cell31
                if(!ok && newLabel->y()>ui->cell31_UE->y() && newLabel->y()<(ui->cell31_UE->y()+150)){
                    if(newLabel->x()>ui->cell31_UE->x() && newLabel->x()<(ui->cell31_UE->x()+130)){
                        ok=true;
                        pointerUE7->area1->setText("Center31");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //cell32
                if(!ok && newLabel->y()>ui->cell32_UE->y() && newLabel->y()<(ui->cell32_UE->y()+160)){
                    if(newLabel->x()>ui->cell32_UE->x() && newLabel->x()<(ui->cell32_UE->x()+140)){
                        ok=true;
                        pointerUE7->area1->setText("Center32");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //cell41
                if(!ok && newLabel->y()>ui->cell41_UE->y() && newLabel->y()<(ui->cell41_UE->y()+101)){
                    if(newLabel->x()>ui->cell41_UE->x() && newLabel->x()<(ui->cell41_UE->x()+141)){
                        ok=true;
                        pointerUE7->area1->setText("Center41");
                    }
                    else{
                        pointerUE7->area1->setText("cell41");
                    }
                }

                //cell42
                if(!ok && newLabel->y()>ui->cell42_UE->y() && newLabel->y()<(ui->cell42_UE->y()+101)){
                    if(newLabel->x()>ui->cell42_UE->x() && newLabel->x()<(ui->cell42_UE->x()+141)){
                        ok=true;
                        pointerUE7->area1->setText("Center42");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //cell51
                if(!ok && newLabel->y()>ui->cell51_UE->y() && newLabel->y()<(ui->cell51_UE->y()+101)){
                    if(newLabel->x()>ui->cell51_UE->x() && newLabel->x()<(ui->cell51_UE->x()+151)){
                        ok=true;
                        pointerUE7->area1->setText("Center51");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //cell52
                if(!ok && newLabel->y()>ui->cell52_UE->y() && newLabel->y()<(ui->cell52_UE->y()+101)){
                    if(newLabel->x()>ui->cell52_UE->x() && newLabel->x()<(ui->cell52_UE->x()+151)){
                        ok=true;
                        pointerUE7->area1->setText("Center52");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //cell61
                if(!ok && newLabel->y()>ui->cell61_UE->y() && newLabel->y()<(ui->cell61_UE->y()+111)){
                    if(newLabel->x()>ui->cell61_UE->x() && newLabel->x()<(ui->cell61_UE->x()+131)){
                        ok=true;
                        pointerUE7->area1->setText("Center61");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }


                //cell62
                if(!ok && newLabel->y()>ui->cell62_UE->y() && newLabel->y()<(ui->cell62_UE->y()+111)){
                    if(newLabel->x()>ui->cell62_UE->x() && newLabel->x()<(ui->cell62_UE->x()+131)){
                        ok=true;
                        pointerUE7->area1->setText("Center62");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //Handover11_12
                if(!ok && newLabel->y()>ui->Handover11_12_UE->y() && newLabel->y()<(ui->Handover11_12_UE->y()+120)){
                    if(newLabel->x()>ui->Handover11_12_UE->x() && newLabel->x()<(ui->Handover11_12_UE->x()+60)){
                        ok=true;
                        pointerUE7->area1->setText("Handover11_12");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //Handover11_21
                if(!ok && newLabel->y()>ui->Handover11_21_UE->y() && newLabel->y()<(ui->Handover11_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover11_21_UE->x() && newLabel->x()<(ui->Handover11_21_UE->x()+50)){
                        ok=true;
                        pointerUE7->area1->setText("Handover11_21");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //Handover12_21
                if(!ok && newLabel->y()>ui->Handover12_21_UE->y() && newLabel->y()<(ui->Handover12_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_21_UE->x() && newLabel->x()<(ui->Handover12_21_UE->x()+70)){
                        ok=true;
                        pointerUE7->area1->setText("Handover12_21");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //Handover12_22
                if(!ok && newLabel->y()>ui->Handover12_22_UE->y() && newLabel->y()<(ui->Handover12_22_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_22_UE->x() && newLabel->x()<(ui->Handover12_22_UE->x()+70)){
                        ok=true;
                        pointerUE7->area1->setText("Handover12_22");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }
                //Handover21_22
                if(!ok && newLabel->y()>ui->Handover21_22_UE->y() && newLabel->y()<(ui->Handover21_22_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_22_UE->x() && newLabel->x()<(ui->Handover21_22_UE->x()+70)){
                        ok=true;
                        pointerUE7->area1->setText("Handover21_22");
                    }
                    else{
                        pointerUE7->area1->setText("Handover21_22");
                    }
                }

                //Handover21_31
                if(!ok && newLabel->y()>ui->Handover21_31_UE->y() && newLabel->y()<(ui->Handover21_31_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_31_UE->x() && newLabel->x()<(ui->Handover21_31_UE->x()+60)){
                        ok=true;
                        pointerUE7->area1->setText("Handover21_31");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //Handover21_32
                if(!ok && newLabel->y()>ui->Handover21_32_UE->y() && newLabel->y()<(ui->Handover21_32_UE->y()+30)){
                    if(newLabel->x()>ui->Handover21_32_UE->x() && newLabel->x()<(ui->Handover21_32_UE->x()+90)){
                        ok=true;
                        pointerUE7->area1->setText("Handover21_32");
                    }
                    else{
                        pointerUE7->area1->setText("Handover21_32");
                    }
                }

                //Handover22_32
                if(!ok && newLabel->y()>ui->Handover22_32_UE->y() && newLabel->y()<(ui->Handover22_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover22_32_UE->x() && newLabel->x()<(ui->Handover22_32_UE->x()+60)){
                        ok=true;
                        pointerUE7->area1->setText("Handover22_32");
                    }
                    else{
                        pointerUE7->area1->setText("Handover22_32");
                    }
                }

                //Handover31_32
                if(!ok && newLabel->y()>ui->Handover31_32_UE->y() && newLabel->y()<(ui->Handover31_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover31_32_UE->x() && newLabel->x()<(ui->Handover31_32_UE->x()+60)){
                        ok=true;
                        pointerUE7->area1->setText("Handover31_32");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //Handover31_41
                if(!ok && newLabel->y()>ui->Handover31_41_UE->y() && newLabel->y()<(ui->Handover31_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover31_41_UE->x() && newLabel->x()<(ui->Handover31_41_UE->x()+80)){
                        ok=true;
                        pointerUE7->area1->setText("Handover31_41");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //Handover32_41
                if(!ok && newLabel->y()>ui->Handover32_41_UE->y() && newLabel->y()<(ui->Handover32_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_41_UE->x() && newLabel->x()<(ui->Handover32_41_UE->x()+90)){
                        ok=true;
                        pointerUE7->area1->setText("Handover32_41");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //Handover32_42
                if(!ok && newLabel->y()>ui->Handover32_42_UE->y() && newLabel->y()<(ui->Handover32_42_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_42_UE->x() && newLabel->x()<(ui->Handover32_42_UE->x()+90)){
                        ok=true;
                        pointerUE7->area1->setText("Handover32_42");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //Handover41_42
                if(!ok && newLabel->y()>ui->Handover41_42_UE->y() && newLabel->y()<(ui->Handover41_42_UE->y()+110)){
                    if(newLabel->x()>ui->Handover41_42_UE->x() && newLabel->x()<(ui->Handover41_42_UE->x()+40)){
                        ok=true;
                        pointerUE7->area1->setText("Handover41_42");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //Handover41_51
                if(!ok && newLabel->y()>ui->Handover41_51_UE->y() && newLabel->y()<(ui->Handover41_51_UE->y()+66)){
                    if(newLabel->x()>ui->Handover41_51_UE->x() && newLabel->x()<(ui->Handover41_51_UE->x()+81)){
                        ok=true;
                        pointerUE7->area1->setText("Handover41_51");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //Handover42_52
                if(!ok && newLabel->y()>ui->Handover42_52_UE->y() && newLabel->y()<(ui->Handover42_52_UE->y()+66)){
                    if(newLabel->x()>ui->Handover42_52_UE->x() && newLabel->x()<(ui->Handover42_52_UE->x()+96)){
                        ok=true;
                        pointerUE7->area1->setText("Handover42_52");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //Handover51_52
                if(!ok && newLabel->y()>ui->Handover51_52_UE->y() && newLabel->y()<(ui->Handover51_52_UE->y()+91)){
                    if(newLabel->x()>ui->Handover51_52_UE->x() && newLabel->x()<(ui->Handover51_52_UE->x()+56)){
                        ok=true;
                        pointerUE7->area1->setText("Handover51_52");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //Handover51_61
                if(!ok && newLabel->y()>ui->Handover51_61_UE->y() && newLabel->y()<(ui->Handover51_61_UE->y()+41)){
                    if(newLabel->x()>ui->Handover51_61_UE->x() && newLabel->x()<(ui->Handover51_61_UE->x()+76)){
                        ok=true;
                        pointerUE7->area1->setText("Handover51_61");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //Handover52_61
                if(!ok && newLabel->y()>ui->Handover52_61_UE->y() && newLabel->y()<(ui->Handover52_61_UE->y()+56)){
                    if(newLabel->x()>ui->Handover52_61_UE->x() && newLabel->x()<(ui->Handover52_61_UE->x()+66)){
                        ok=true;
                        pointerUE7->area1->setText("Handover52_61");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //Handover52_62
                if(!ok && newLabel->y()>ui->Handover52_62_UE->y() && newLabel->y()<(ui->Handover52_62_UE->y()+66)){
                    if(newLabel->x()>ui->Handover52_62_UE->x() && newLabel->x()<(ui->Handover52_62_UE->x()+86)){
                        ok=true;
                        pointerUE7->area1->setText("Handover52_62");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }

                //Handover61_62
                if(!ok && newLabel->y()>ui->Handover61_62_UE->y() && newLabel->y()<(ui->Handover61_62_UE->y()+96)){
                    if(newLabel->x()>ui->Handover61_62_UE->x() && newLabel->x()<(ui->Handover61_62_UE->x()+116)){
                        ok=true;
                        pointerUE7->area1->setText("Handover61_62");
                    }
                    else{
                        pointerUE7->area1->setText("");
                    }
                }
                actualposition=newLabel;
                tab_UE[6]=newLabel;
            }
            else {
                event->acceptProposedAction();
            }
        }
    }

    //UE8
    if (event->mimeData()->hasFormat("application/x-UE")) {
        const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data("application/x-UE");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString text;
        QPoint offset;
        dataStream >> text >> offset;

        DragUELabel *newLabel = new DragUELabel(text, ui->scrollAreaWidgetContents);

        if(actualposition==tab_UE[7]){
            newLabel->move(event->pos() - offset);
            newLabel->show();
            newLabel->setAttribute(Qt::WA_DeleteOnClose);

            if (event->source() == this) {
                event->setDropAction(Qt::MoveAction);
                event->accept();

                //Cell11
                bool ok=false;
                if(newLabel->y()>ui->cell11_UE->y() && newLabel->y()<ui->cell11_UE->y()+120){
                    if(newLabel->x()>ui->cell11_UE->x() && newLabel->x()<ui->cell11_UE->x()+120){
                        ok=true;
                        pointerUE8->area1->setText("Center11");

                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Cell12
                if(!ok && newLabel->y()>ui->cell12_UE->y() && newLabel->y()<(ui->cell12_UE->y()+110)){
                    if(newLabel->x()>ui->cell12_UE->x() && newLabel->x()<(ui->cell12_UE->x()+100)){
                        ok=true;
                        pointerUE8->area1->setText("Center12");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //cell21
                if(!ok && newLabel->y()>ui->cell21_UE->y() && newLabel->y()<(ui->cell21_UE->y()+50)){
                    if(newLabel->x()>ui->cell21_UE->x() && newLabel->x()<(ui->cell21_UE->x()+150)){
                        ok=true;
                        pointerUE8->area1->setText("Center21");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //cell22
                if(!ok && newLabel->y()>ui->cell22_UE->y() && newLabel->y()<(ui->cell22_UE->y()+50)){
                    if(newLabel->x()>ui->cell22_UE->x() && newLabel->x()<(ui->cell22_UE->x()+150)){
                        ok=true;
                        pointerUE8->area1->setText("Center22");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //cell31
                if(!ok && newLabel->y()>ui->cell31_UE->y() && newLabel->y()<(ui->cell31_UE->y()+150)){
                    if(newLabel->x()>ui->cell31_UE->x() && newLabel->x()<(ui->cell31_UE->x()+130)){
                        ok=true;
                        pointerUE8->area1->setText("Center31");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //cell32
                if(!ok && newLabel->y()>ui->cell32_UE->y() && newLabel->y()<(ui->cell32_UE->y()+160)){
                    if(newLabel->x()>ui->cell32_UE->x() && newLabel->x()<(ui->cell32_UE->x()+140)){
                        ok=true;
                        pointerUE8->area1->setText("Center32");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //cell41
                if(!ok && newLabel->y()>ui->cell41_UE->y() && newLabel->y()<(ui->cell41_UE->y()+101)){
                    if(newLabel->x()>ui->cell41_UE->x() && newLabel->x()<(ui->cell41_UE->x()+141)){
                        ok=true;
                        pointerUE8->area1->setText("Center41");
                    }
                    else{
                        pointerUE8->area1->setText("cell41");
                    }
                }

                //cell42
                if(!ok && newLabel->y()>ui->cell42_UE->y() && newLabel->y()<(ui->cell42_UE->y()+101)){
                    if(newLabel->x()>ui->cell42_UE->x() && newLabel->x()<(ui->cell42_UE->x()+141)){
                        ok=true;
                        pointerUE8->area1->setText("Center42");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //cell51
                if(!ok && newLabel->y()>ui->cell51_UE->y() && newLabel->y()<(ui->cell51_UE->y()+101)){
                    if(newLabel->x()>ui->cell51_UE->x() && newLabel->x()<(ui->cell51_UE->x()+151)){
                        ok=true;
                        pointerUE8->area1->setText("Center51");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //cell52
                if(!ok && newLabel->y()>ui->cell52_UE->y() && newLabel->y()<(ui->cell52_UE->y()+101)){
                    if(newLabel->x()>ui->cell52_UE->x() && newLabel->x()<(ui->cell52_UE->x()+151)){
                        ok=true;
                        pointerUE8->area1->setText("Center52");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //cell61
                if(!ok && newLabel->y()>ui->cell61_UE->y() && newLabel->y()<(ui->cell61_UE->y()+111)){
                    if(newLabel->x()>ui->cell61_UE->x() && newLabel->x()<(ui->cell61_UE->x()+131)){
                        ok=true;
                        pointerUE8->area1->setText("Center61");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //cell62
                if(!ok && newLabel->y()>ui->cell62_UE->y() && newLabel->y()<(ui->cell62_UE->y()+111)){
                    if(newLabel->x()>ui->cell62_UE->x() && newLabel->x()<(ui->cell62_UE->x()+131)){
                        ok=true;
                        pointerUE8->area1->setText("Center62");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Handover11_12
                if(!ok && newLabel->y()>ui->Handover11_12_UE->y() && newLabel->y()<(ui->Handover11_12_UE->y()+120)){
                    if(newLabel->x()>ui->Handover11_12_UE->x() && newLabel->x()<(ui->Handover11_12_UE->x()+60)){
                        ok=true;
                        pointerUE8->area1->setText("Handover11_12");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Handover11_21
                if(!ok && newLabel->y()>ui->Handover11_21_UE->y() && newLabel->y()<(ui->Handover11_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover11_21_UE->x() && newLabel->x()<(ui->Handover11_21_UE->x()+50)){
                        ok=true;
                        pointerUE8->area1->setText("Handover11_21");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Handover12_21
                if(!ok && newLabel->y()>ui->Handover12_21_UE->y() && newLabel->y()<(ui->Handover12_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_21_UE->x() && newLabel->x()<(ui->Handover12_21_UE->x()+70)){
                        ok=true;
                        pointerUE8->area1->setText("Handover12_21");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Handover12_22
                if(!ok && newLabel->y()>ui->Handover12_22_UE->y() && newLabel->y()<(ui->Handover12_22_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_22_UE->x() && newLabel->x()<(ui->Handover12_22_UE->x()+70)){
                        ok=true;
                        pointerUE8->area1->setText("Handover12_22");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Handover21_22
                if(!ok && newLabel->y()>ui->Handover21_22_UE->y() && newLabel->y()<(ui->Handover21_22_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_22_UE->x() && newLabel->x()<(ui->Handover21_22_UE->x()+70)){
                        ok=true;
                        pointerUE8->area1->setText("Handover21_22");
                    }
                    else{
                        pointerUE8->area1->setText("Handover21_22");
                    }
                }

                //Handover21_31
                if(!ok && newLabel->y()>ui->Handover21_31_UE->y() && newLabel->y()<(ui->Handover21_31_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_31_UE->x() && newLabel->x()<(ui->Handover21_31_UE->x()+60)){
                        ok=true;
                        pointerUE8->area1->setText("Handover21_31");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Handover21_32
                if(!ok && newLabel->y()>ui->Handover21_32_UE->y() && newLabel->y()<(ui->Handover21_32_UE->y()+30)){
                    if(newLabel->x()>ui->Handover21_32_UE->x() && newLabel->x()<(ui->Handover21_32_UE->x()+90)){
                        ok=true;
                        pointerUE8->area1->setText("Handover21_32");
                    }
                    else{
                        pointerUE8->area1->setText("Handover21_32");
                    }
                }

                //Handover22_32
                if(!ok && newLabel->y()>ui->Handover22_32_UE->y() && newLabel->y()<(ui->Handover22_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover22_32_UE->x() && newLabel->x()<(ui->Handover22_32_UE->x()+60)){
                        ok=true;
                        pointerUE8->area1->setText("Handover22_32");
                    }
                    else{
                        pointerUE8->area1->setText("Handover22_32");
                    }
                }

                //Handover31_32
                if(!ok && newLabel->y()>ui->Handover31_32_UE->y() && newLabel->y()<(ui->Handover31_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover31_32_UE->x() && newLabel->x()<(ui->Handover31_32_UE->x()+60)){
                        ok=true;
                        pointerUE8->area1->setText("Handover31_32");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Handover31_41
                if(!ok && newLabel->y()>ui->Handover31_41_UE->y() && newLabel->y()<(ui->Handover31_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover31_41_UE->x() && newLabel->x()<(ui->Handover31_41_UE->x()+80)){
                        ok=true;
                        pointerUE8->area1->setText("Handover31_41");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Handover32_41
                if(!ok && newLabel->y()>ui->Handover32_41_UE->y() && newLabel->y()<(ui->Handover32_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_41_UE->x() && newLabel->x()<(ui->Handover32_41_UE->x()+90)){
                        ok=true;
                        pointerUE8->area1->setText("Handover32_41");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Handover32_42
                if(!ok && newLabel->y()>ui->Handover32_42_UE->y() && newLabel->y()<(ui->Handover32_42_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_42_UE->x() && newLabel->x()<(ui->Handover32_42_UE->x()+90)){
                        ok=true;
                        pointerUE8->area1->setText("Handover32_42");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Handover41_42
                if(!ok && newLabel->y()>ui->Handover41_42_UE->y() && newLabel->y()<(ui->Handover41_42_UE->y()+110)){
                    if(newLabel->x()>ui->Handover41_42_UE->x() && newLabel->x()<(ui->Handover41_42_UE->x()+40)){
                        ok=true;
                        pointerUE8->area1->setText("Handover41_42");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Handover41_51
                if(!ok && newLabel->y()>ui->Handover41_51_UE->y() && newLabel->y()<(ui->Handover41_51_UE->y()+66)){
                    if(newLabel->x()>ui->Handover41_51_UE->x() && newLabel->x()<(ui->Handover41_51_UE->x()+81)){
                        ok=true;
                        pointerUE8->area1->setText("Handover41_51");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Handover42_52
                if(!ok && newLabel->y()>ui->Handover42_52_UE->y() && newLabel->y()<(ui->Handover42_52_UE->y()+66)){
                    if(newLabel->x()>ui->Handover42_52_UE->x() && newLabel->x()<(ui->Handover42_52_UE->x()+96)){
                        ok=true;
                        pointerUE8->area1->setText("Handover42_52");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Handover51_52
                if(!ok && newLabel->y()>ui->Handover51_52_UE->y() && newLabel->y()<(ui->Handover51_52_UE->y()+91)){
                    if(newLabel->x()>ui->Handover51_52_UE->x() && newLabel->x()<(ui->Handover51_52_UE->x()+56)){
                        ok=true;
                        pointerUE8->area1->setText("Handover51_52");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Handover51_61
                if(!ok && newLabel->y()>ui->Handover51_61_UE->y() && newLabel->y()<(ui->Handover51_61_UE->y()+41)){
                    if(newLabel->x()>ui->Handover51_61_UE->x() && newLabel->x()<(ui->Handover51_61_UE->x()+76)){
                        ok=true;
                        pointerUE8->area1->setText("Handover51_61");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Handover52_61
                if(!ok && newLabel->y()>ui->Handover52_61_UE->y() && newLabel->y()<(ui->Handover52_61_UE->y()+56)){
                    if(newLabel->x()>ui->Handover52_61_UE->x() && newLabel->x()<(ui->Handover52_61_UE->x()+66)){
                        ok=true;
                        pointerUE8->area1->setText("Handover52_61");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Handover52_62
                if(!ok && newLabel->y()>ui->Handover52_62_UE->y() && newLabel->y()<(ui->Handover52_62_UE->y()+66)){
                    if(newLabel->x()>ui->Handover52_62_UE->x() && newLabel->x()<(ui->Handover52_62_UE->x()+86)){
                        ok=true;
                        pointerUE8->area1->setText("Handover52_62");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }

                //Handover61_62
                if(!ok && newLabel->y()>ui->Handover61_62_UE->y() && newLabel->y()<(ui->Handover61_62_UE->y()+96)){
                    if(newLabel->x()>ui->Handover61_62_UE->x() && newLabel->x()<(ui->Handover61_62_UE->x()+116)){
                        ok=true;
                        pointerUE8->area1->setText("Handover61_62");
                    }
                    else{
                        pointerUE8->area1->setText("");
                    }
                }
                actualposition=newLabel;
                tab_UE[7]=newLabel;
            }
            else {
                event->acceptProposedAction();
            }
        }
    }

    //UE9
    if (event->mimeData()->hasFormat("application/x-UE")) {
        const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data("application/x-UE");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString text;
        QPoint offset;
        dataStream >> text >> offset;

        DragUELabel *newLabel = new DragUELabel(text, ui->scrollAreaWidgetContents);

        if(actualposition==tab_UE[8]){
            newLabel->move(event->pos() - offset);
            newLabel->show();
            newLabel->setAttribute(Qt::WA_DeleteOnClose);

            if (event->source() == this) {
                event->setDropAction(Qt::MoveAction);
                event->accept();

                //Cell11
                bool ok=false;
                if(newLabel->y()>ui->cell11_UE->y() && newLabel->y()<ui->cell11_UE->y()+120){
                    if(newLabel->x()>ui->cell11_UE->x() && newLabel->x()<ui->cell11_UE->x()+120){
                        ok=true;
                        pointerUE9->area1->setText("Center11");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //Cell12
                if(!ok && newLabel->y()>ui->cell12_UE->y() && newLabel->y()<(ui->cell12_UE->y()+110)){
                    if(newLabel->x()>ui->cell12_UE->x() && newLabel->x()<(ui->cell12_UE->x()+100)){
                        ok=true;
                        pointerUE9->area1->setText("Center12");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //cell21
                if(!ok && newLabel->y()>ui->cell21_UE->y() && newLabel->y()<(ui->cell21_UE->y()+50)){
                    if(newLabel->x()>ui->cell21_UE->x() && newLabel->x()<(ui->cell21_UE->x()+150)){
                        ok=true;
                        pointerUE9->area1->setText("Center21");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //cell22
                if(!ok && newLabel->y()>ui->cell22_UE->y() && newLabel->y()<(ui->cell22_UE->y()+50)){
                    if(newLabel->x()>ui->cell22_UE->x() && newLabel->x()<(ui->cell22_UE->x()+150)){
                        ok=true;
                        pointerUE9->area1->setText("Center22");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //cell31
                if(!ok && newLabel->y()>ui->cell31_UE->y() && newLabel->y()<(ui->cell31_UE->y()+150)){
                    if(newLabel->x()>ui->cell31_UE->x() && newLabel->x()<(ui->cell31_UE->x()+130)){
                        ok=true;
                        pointerUE9->area1->setText("Center31");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //cell32
                if(!ok && newLabel->y()>ui->cell32_UE->y() && newLabel->y()<(ui->cell32_UE->y()+160)){
                    if(newLabel->x()>ui->cell32_UE->x() && newLabel->x()<(ui->cell32_UE->x()+140)){
                        ok=true;
                        pointerUE9->area1->setText("Center32");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //cell41
                if(!ok && newLabel->y()>ui->cell41_UE->y() && newLabel->y()<(ui->cell41_UE->y()+101)){
                    if(newLabel->x()>ui->cell41_UE->x() && newLabel->x()<(ui->cell41_UE->x()+141)){
                        ok=true;
                        pointerUE9->area1->setText("Center41");
                    }
                    else{
                        pointerUE9->area1->setText("cell41");
                    }
                }

                //cell42
                if(!ok && newLabel->y()>ui->cell42_UE->y() && newLabel->y()<(ui->cell42_UE->y()+101)){
                    if(newLabel->x()>ui->cell42_UE->x() && newLabel->x()<(ui->cell42_UE->x()+141)){
                        ok=true;
                        pointerUE9->area1->setText("Center42");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //cell51
                if(!ok && newLabel->y()>ui->cell51_UE->y() && newLabel->y()<(ui->cell51_UE->y()+101)){
                    if(newLabel->x()>ui->cell51_UE->x() && newLabel->x()<(ui->cell51_UE->x()+151)){
                        ok=true;
                        pointerUE9->area1->setText("Center51");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //cell52
                if(!ok && newLabel->y()>ui->cell52_UE->y() && newLabel->y()<(ui->cell52_UE->y()+101)){
                    if(newLabel->x()>ui->cell52_UE->x() && newLabel->x()<(ui->cell52_UE->x()+151)){
                        ok=true;
                        pointerUE9->area1->setText("Center52");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //cell61
                if(!ok && newLabel->y()>ui->cell61_UE->y() && newLabel->y()<(ui->cell61_UE->y()+111)){
                    if(newLabel->x()>ui->cell61_UE->x() && newLabel->x()<(ui->cell61_UE->x()+131)){
                        ok=true;
                        pointerUE9->area1->setText("Center61");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //cell62
                if(!ok && newLabel->y()>ui->cell62_UE->y() && newLabel->y()<(ui->cell62_UE->y()+111)){
                    if(newLabel->x()>ui->cell62_UE->x() && newLabel->x()<(ui->cell62_UE->x()+131)){
                        ok=true;
                        pointerUE9->area1->setText("Center62");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //Handover11_12
                if(!ok && newLabel->y()>ui->Handover11_12_UE->y() && newLabel->y()<(ui->Handover11_12_UE->y()+120)){
                    if(newLabel->x()>ui->Handover11_12_UE->x() && newLabel->x()<(ui->Handover11_12_UE->x()+60)){
                        ok=true;
                        pointerUE9->area1->setText("Handover11_12");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //Handover11_21
                if(!ok && newLabel->y()>ui->Handover11_21_UE->y() && newLabel->y()<(ui->Handover11_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover11_21_UE->x() && newLabel->x()<(ui->Handover11_21_UE->x()+50)){
                        ok=true;
                        pointerUE9->area1->setText("Handover11_21");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //Handover12_21
                if(!ok && newLabel->y()>ui->Handover12_21_UE->y() && newLabel->y()<(ui->Handover12_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_21_UE->x() && newLabel->x()<(ui->Handover12_21_UE->x()+70)){
                        ok=true;
                        pointerUE9->area1->setText("Handover12_21");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //Handover12_22
                if(!ok && newLabel->y()>ui->Handover12_22_UE->y() && newLabel->y()<(ui->Handover12_22_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_22_UE->x() && newLabel->x()<(ui->Handover12_22_UE->x()+70)){
                        ok=true;
                        pointerUE9->area1->setText("Handover12_22");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //Handover21_22
                if(!ok && newLabel->y()>ui->Handover21_22_UE->y() && newLabel->y()<(ui->Handover21_22_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_22_UE->x() && newLabel->x()<(ui->Handover21_22_UE->x()+70)){
                        ok=true;
                        pointerUE9->area1->setText("Handover21_22");
                    }
                    else{
                        pointerUE9->area1->setText("Handover21_22");
                    }
                }

                //Handover21_31
                if(!ok && newLabel->y()>ui->Handover21_31_UE->y() && newLabel->y()<(ui->Handover21_31_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_31_UE->x() && newLabel->x()<(ui->Handover21_31_UE->x()+60)){
                        ok=true;
                        pointerUE9->area1->setText("Handover21_31");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //Handover21_32
                if(!ok && newLabel->y()>ui->Handover21_32_UE->y() && newLabel->y()<(ui->Handover21_32_UE->y()+30)){
                    if(newLabel->x()>ui->Handover21_32_UE->x() && newLabel->x()<(ui->Handover21_32_UE->x()+90)){
                        ok=true;
                        pointerUE9->area1->setText("Handover21_32");
                    }
                    else{
                        pointerUE9->area1->setText("Handover21_32");
                    }
                }

                //Handover22_32
                if(!ok && newLabel->y()>ui->Handover22_32_UE->y() && newLabel->y()<(ui->Handover22_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover22_32_UE->x() && newLabel->x()<(ui->Handover22_32_UE->x()+60)){
                        ok=true;
                        pointerUE9->area1->setText("Handover22_32");
                    }
                    else{
                        pointerUE9->area1->setText("Handover22_32");
                    }
                }

                //Handover31_32
                if(!ok && newLabel->y()>ui->Handover31_32_UE->y() && newLabel->y()<(ui->Handover31_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover31_32_UE->x() && newLabel->x()<(ui->Handover31_32_UE->x()+60)){
                        ok=true;
                        pointerUE9->area1->setText("Handover31_32");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //Handover31_41
                if(!ok && newLabel->y()>ui->Handover31_41_UE->y() && newLabel->y()<(ui->Handover31_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover31_41_UE->x() && newLabel->x()<(ui->Handover31_41_UE->x()+80)){
                        ok=true;
                        pointerUE9->area1->setText("Handover31_41");
                    }
                    else{
                        //tab_position_names[UEindex]="";
                    }
                }

                //Handover32_41
                if(!ok && newLabel->y()>ui->Handover32_41_UE->y() && newLabel->y()<(ui->Handover32_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_41_UE->x() && newLabel->x()<(ui->Handover32_41_UE->x()+90)){
                        ok=true;
                        pointerUE9->area1->setText("Handover32_41");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //Handover32_42
                if(!ok && newLabel->y()>ui->Handover32_42_UE->y() && newLabel->y()<(ui->Handover32_42_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_42_UE->x() && newLabel->x()<(ui->Handover32_42_UE->x()+90)){
                        ok=true;
                        pointerUE9->area1->setText("Handover32_42");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //Handover41_42
                if(!ok && newLabel->y()>ui->Handover41_42_UE->y() && newLabel->y()<(ui->Handover41_42_UE->y()+110)){
                    if(newLabel->x()>ui->Handover41_42_UE->x() && newLabel->x()<(ui->Handover41_42_UE->x()+40)){
                        ok=true;
                        pointerUE9->area1->setText("Handover41_42");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //Handover41_51
                if(!ok && newLabel->y()>ui->Handover41_51_UE->y() && newLabel->y()<(ui->Handover41_51_UE->y()+66)){
                    if(newLabel->x()>ui->Handover41_51_UE->x() && newLabel->x()<(ui->Handover41_51_UE->x()+81)){
                        ok=true;
                        pointerUE9->area1->setText("Handover41_51");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //Handover42_52
                if(!ok && newLabel->y()>ui->Handover42_52_UE->y() && newLabel->y()<(ui->Handover42_52_UE->y()+66)){
                    if(newLabel->x()>ui->Handover42_52_UE->x() && newLabel->x()<(ui->Handover42_52_UE->x()+96)){
                        ok=true;
                        pointerUE9->area1->setText("Handover42_52");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //Handover51_52
                if(!ok && newLabel->y()>ui->Handover51_52_UE->y() && newLabel->y()<(ui->Handover51_52_UE->y()+91)){
                    if(newLabel->x()>ui->Handover51_52_UE->x() && newLabel->x()<(ui->Handover51_52_UE->x()+56)){
                        ok=true;
                        pointerUE9->area1->setText("Handover51_52");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //Handover51_61
                if(!ok && newLabel->y()>ui->Handover51_61_UE->y() && newLabel->y()<(ui->Handover51_61_UE->y()+41)){
                    if(newLabel->x()>ui->Handover51_61_UE->x() && newLabel->x()<(ui->Handover51_61_UE->x()+76)){
                        ok=true;
                        pointerUE9->area1->setText("Handover51_61");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //Handover52_61
                if(!ok && newLabel->y()>ui->Handover52_61_UE->y() && newLabel->y()<(ui->Handover52_61_UE->y()+56)){
                    if(newLabel->x()>ui->Handover52_61_UE->x() && newLabel->x()<(ui->Handover52_61_UE->x()+66)){
                        ok=true;
                        pointerUE9->area1->setText("Handover52_61");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //Handover52_62
                if(!ok && newLabel->y()>ui->Handover52_62_UE->y() && newLabel->y()<(ui->Handover52_62_UE->y()+66)){
                    if(newLabel->x()>ui->Handover52_62_UE->x() && newLabel->x()<(ui->Handover52_62_UE->x()+86)){
                        ok=true;
                        pointerUE9->area1->setText("Handover52_62");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }

                //Handover61_62
                if(!ok && newLabel->y()>ui->Handover61_62_UE->y() && newLabel->y()<(ui->Handover61_62_UE->y()+96)){
                    if(newLabel->x()>ui->Handover61_62_UE->x() && newLabel->x()<(ui->Handover61_62_UE->x()+116)){
                        ok=true;
                        pointerUE9->area1->setText("Handover61_62");
                    }
                    else{
                        pointerUE9->area1->setText("");
                    }
                }
                actualposition=newLabel;
                tab_UE[8]=newLabel;
            }
            else {
                event->acceptProposedAction();
            }
        }
    }

    //UE10
    if (event->mimeData()->hasFormat("application/x-UE")) {
        const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data("application/x-UE");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString text;
        QPoint offset;
        dataStream >> text >> offset;

        DragUELabel *newLabel = new DragUELabel(text, ui->scrollAreaWidgetContents);

        if(actualposition==tab_UE[9]){
            newLabel->move(event->pos() - offset);
            newLabel->show();
            newLabel->setAttribute(Qt::WA_DeleteOnClose);

            if (event->source() == this) {
                event->setDropAction(Qt::MoveAction);
                event->accept();

                //Cell11
                bool ok=false;
                if(newLabel->y()>ui->cell11_UE->y() && newLabel->y()<ui->cell11_UE->y()+120){
                    if(newLabel->x()>ui->cell11_UE->x() && newLabel->x()<ui->cell11_UE->x()+120){
                        ok=true;
                        pointerUE10->area1->setText("Center11");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Cell12
                if(!ok && newLabel->y()>ui->cell12_UE->y() && newLabel->y()<(ui->cell12_UE->y()+110)){
                    if(newLabel->x()>ui->cell12_UE->x() && newLabel->x()<(ui->cell12_UE->x()+100)){
                        ok=true;
                        pointerUE10->area1->setText("Center12");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //cell21
                if(!ok && newLabel->y()>ui->cell21_UE->y() && newLabel->y()<(ui->cell21_UE->y()+50)){
                    if(newLabel->x()>ui->cell21_UE->x() && newLabel->x()<(ui->cell21_UE->x()+150)){
                        ok=true;
                        pointerUE10->area1->setText("Center21");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //cell22
                if(!ok && newLabel->y()>ui->cell22_UE->y() && newLabel->y()<(ui->cell22_UE->y()+50)){
                    if(newLabel->x()>ui->cell22_UE->x() && newLabel->x()<(ui->cell22_UE->x()+150)){
                        ok=true;
                        pointerUE10->area1->setText("Center22");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //cell31
                if(!ok && newLabel->y()>ui->cell31_UE->y() && newLabel->y()<(ui->cell31_UE->y()+150)){
                    if(newLabel->x()>ui->cell31_UE->x() && newLabel->x()<(ui->cell31_UE->x()+130)){
                        ok=true;
                        pointerUE10->area1->setText("Center31");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //cell32
                if(!ok && newLabel->y()>ui->cell32_UE->y() && newLabel->y()<(ui->cell32_UE->y()+160)){
                    if(newLabel->x()>ui->cell32_UE->x() && newLabel->x()<(ui->cell32_UE->x()+140)){
                        ok=true;
                        pointerUE10->area1->setText("Center32");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //cell41
                if(!ok && newLabel->y()>ui->cell41_UE->y() && newLabel->y()<(ui->cell41_UE->y()+101)){
                    if(newLabel->x()>ui->cell41_UE->x() && newLabel->x()<(ui->cell41_UE->x()+141)){
                        ok=true;
                        pointerUE10->area1->setText("Center41");
                    }
                    else{
                        pointerUE10->area1->setText("cell41");
                    }
                }

                //cell42
                if(!ok && newLabel->y()>ui->cell42_UE->y() && newLabel->y()<(ui->cell42_UE->y()+101)){
                    if(newLabel->x()>ui->cell42_UE->x() && newLabel->x()<(ui->cell42_UE->x()+141)){
                        ok=true;
                        pointerUE10->area1->setText("Center42");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //cell51
                if(!ok && newLabel->y()>ui->cell51_UE->y() && newLabel->y()<(ui->cell51_UE->y()+101)){
                    if(newLabel->x()>ui->cell51_UE->x() && newLabel->x()<(ui->cell51_UE->x()+151)){
                        ok=true;
                        pointerUE10->area1->setText("Center51");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //cell52
                if(!ok && newLabel->y()>ui->cell52_UE->y() && newLabel->y()<(ui->cell52_UE->y()+101)){
                    if(newLabel->x()>ui->cell52_UE->x() && newLabel->x()<(ui->cell52_UE->x()+151)){
                        ok=true;
                        pointerUE10->area1->setText("Center52");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //cell61
                if(!ok && newLabel->y()>ui->cell61_UE->y() && newLabel->y()<(ui->cell61_UE->y()+111)){
                    if(newLabel->x()>ui->cell61_UE->x() && newLabel->x()<(ui->cell61_UE->x()+131)){
                        ok=true;
                        pointerUE10->area1->setText("Center61");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //cell62
                if(!ok && newLabel->y()>ui->cell62_UE->y() && newLabel->y()<(ui->cell62_UE->y()+111)){
                    if(newLabel->x()>ui->cell62_UE->x() && newLabel->x()<(ui->cell62_UE->x()+131)){
                        ok=true;
                        pointerUE10->area1->setText("Center62");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Handover11_12
                if(!ok && newLabel->y()>ui->Handover11_12_UE->y() && newLabel->y()<(ui->Handover11_12_UE->y()+120)){
                    if(newLabel->x()>ui->Handover11_12_UE->x() && newLabel->x()<(ui->Handover11_12_UE->x()+60)){
                        ok=true;
                        pointerUE10->area1->setText("Handover11_12");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Handover11_21
                if(!ok && newLabel->y()>ui->Handover11_21_UE->y() && newLabel->y()<(ui->Handover11_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover11_21_UE->x() && newLabel->x()<(ui->Handover11_21_UE->x()+50)){
                        ok=true;
                        pointerUE10->area1->setText("Handover11_21");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Handover12_21
                if(!ok && newLabel->y()>ui->Handover12_21_UE->y() && newLabel->y()<(ui->Handover12_21_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_21_UE->x() && newLabel->x()<(ui->Handover12_21_UE->x()+70)){
                        ok=true;
                        pointerUE10->area1->setText("Handover12_21");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Handover12_22
                if(!ok && newLabel->y()>ui->Handover12_22_UE->y() && newLabel->y()<(ui->Handover12_22_UE->y()+100)){
                    if(newLabel->x()>ui->Handover12_22_UE->x() && newLabel->x()<(ui->Handover12_22_UE->x()+70)){
                        ok=true;
                        pointerUE10->area1->setText("Handover12_22");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Handover21_22
                if(!ok && newLabel->y()>ui->Handover21_22_UE->y() && newLabel->y()<(ui->Handover21_22_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_22_UE->x() && newLabel->x()<(ui->Handover21_22_UE->x()+70)){
                        ok=true;
                        pointerUE10->area1->setText("Handover21_22");
                    }
                    else{
                        pointerUE10->area1->setText("Handover21_22");
                    }
                }

                //Handover21_31
                if(!ok && newLabel->y()>ui->Handover21_31_UE->y() && newLabel->y()<(ui->Handover21_31_UE->y()+80)){
                    if(newLabel->x()>ui->Handover21_31_UE->x() && newLabel->x()<(ui->Handover21_31_UE->x()+60)){
                        ok=true;
                        pointerUE10->area1->setText("Handover21_31");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Handover21_32
                if(!ok && newLabel->y()>ui->Handover21_32_UE->y() && newLabel->y()<(ui->Handover21_32_UE->y()+30)){
                    if(newLabel->x()>ui->Handover21_32_UE->x() && newLabel->x()<(ui->Handover21_32_UE->x()+90)){
                        ok=true;
                        pointerUE10->area1->setText("Handover21_32");
                    }
                    else{
                        pointerUE10->area1->setText("Handover21_32");
                    }
                }

                //Handover22_32
                if(!ok && newLabel->y()>ui->Handover22_32_UE->y() && newLabel->y()<(ui->Handover22_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover22_32_UE->x() && newLabel->x()<(ui->Handover22_32_UE->x()+60)){
                        ok=true;
                        pointerUE10->area1->setText("Handover22_32");
                    }
                    else{
                        pointerUE10->area1->setText("Handover22_32");
                    }
                }

                //Handover31_32
                if(!ok && newLabel->y()>ui->Handover31_32_UE->y() && newLabel->y()<(ui->Handover31_32_UE->y()+80)){
                    if(newLabel->x()>ui->Handover31_32_UE->x() && newLabel->x()<(ui->Handover31_32_UE->x()+60)){
                        ok=true;
                        pointerUE10->area1->setText("Handover31_32");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Handover31_41
                if(!ok && newLabel->y()>ui->Handover31_41_UE->y() && newLabel->y()<(ui->Handover31_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover31_41_UE->x() && newLabel->x()<(ui->Handover31_41_UE->x()+80)){
                        ok=true;
                        pointerUE10->area1->setText("Handover31_41");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Handover32_41
                if(!ok && newLabel->y()>ui->Handover32_41_UE->y() && newLabel->y()<(ui->Handover32_41_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_41_UE->x() && newLabel->x()<(ui->Handover32_41_UE->x()+90)){
                        ok=true;
                        pointerUE10->area1->setText("Handover32_41");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Handover32_42
                if(!ok && newLabel->y()>ui->Handover32_42_UE->y() && newLabel->y()<(ui->Handover32_42_UE->y()+90)){
                    if(newLabel->x()>ui->Handover32_42_UE->x() && newLabel->x()<(ui->Handover32_42_UE->x()+90)){
                        ok=true;
                        pointerUE10->area1->setText("Handover32_42");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Handover41_42
                if(!ok && newLabel->y()>ui->Handover41_42_UE->y() && newLabel->y()<(ui->Handover41_42_UE->y()+110)){
                    if(newLabel->x()>ui->Handover41_42_UE->x() && newLabel->x()<(ui->Handover41_42_UE->x()+40)){
                        ok=true;
                        pointerUE10->area1->setText("Handover41_42");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Handover41_51
                if(!ok && newLabel->y()>ui->Handover41_51_UE->y() && newLabel->y()<(ui->Handover41_51_UE->y()+66)){
                    if(newLabel->x()>ui->Handover41_51_UE->x() && newLabel->x()<(ui->Handover41_51_UE->x()+81)){
                        ok=true;
                        pointerUE10->area1->setText("Handover41_51");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Handover42_52
                if(!ok && newLabel->y()>ui->Handover42_52_UE->y() && newLabel->y()<(ui->Handover42_52_UE->y()+66)){
                    if(newLabel->x()>ui->Handover42_52_UE->x() && newLabel->x()<(ui->Handover42_52_UE->x()+96)){
                        ok=true;
                        pointerUE10->area1->setText("Handover42_52");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Handover51_52
                if(!ok && newLabel->y()>ui->Handover51_52_UE->y() && newLabel->y()<(ui->Handover51_52_UE->y()+91)){
                    if(newLabel->x()>ui->Handover51_52_UE->x() && newLabel->x()<(ui->Handover51_52_UE->x()+56)){
                        ok=true;
                        pointerUE10->area1->setText("Handover51_52");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Handover51_61
                if(!ok && newLabel->y()>ui->Handover51_61_UE->y() && newLabel->y()<(ui->Handover51_61_UE->y()+41)){
                    if(newLabel->x()>ui->Handover51_61_UE->x() && newLabel->x()<(ui->Handover51_61_UE->x()+76)){
                        ok=true;
                        pointerUE10->area1->setText("Handover51_61");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Handover52_61
                if(!ok && newLabel->y()>ui->Handover52_61_UE->y() && newLabel->y()<(ui->Handover52_61_UE->y()+56)){
                    if(newLabel->x()>ui->Handover52_61_UE->x() && newLabel->x()<(ui->Handover52_61_UE->x()+66)){
                        ok=true;
                        pointerUE10->area1->setText("Handover52_61");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Handover52_62
                if(!ok && newLabel->y()>ui->Handover52_62_UE->y() && newLabel->y()<(ui->Handover52_62_UE->y()+66)){
                    if(newLabel->x()>ui->Handover52_62_UE->x() && newLabel->x()<(ui->Handover52_62_UE->x()+86)){
                        ok=true;
                        pointerUE10->area1->setText("Handover52_62");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }

                //Handover61_62
                if(!ok && newLabel->y()>ui->Handover61_62_UE->y() && newLabel->y()<(ui->Handover61_62_UE->y()+96)){
                    if(newLabel->x()>ui->Handover61_62_UE->x() && newLabel->x()<(ui->Handover61_62_UE->x()+116)){
                        ok=true;
                        pointerUE10->area1->setText("Handover61_62");
                    }
                    else{
                        pointerUE10->area1->setText("");
                    }
                }
                actualposition=newLabel;
                tab_UE[9]=newLabel;
            }
            else {

                event->acceptProposedAction();
            }
        }
    }

    else if (event->mimeData()->hasText()) {
        QStringList pieces = event->mimeData()->text().split(QRegExp("\\s+"),
                                                             QString::SkipEmptyParts);
        QPoint position = event->pos();

        foreach (QString piece, pieces) {
            DragUELabel *newLabel = new DragUELabel(piece, this);
            newLabel->move(position);
            newLabel->show();
            newLabel->setAttribute(Qt::WA_DeleteOnClose);

            position += QPoint(newLabel->width(), 0);
        }
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void Map_traffic::closeEvent(QCloseEvent *event){
    msgExit.setText("The document has been modified.");
    msgExit.setInformativeText("Do you want to save your changes?");
    msgExit.setIcon(QMessageBox::Question);
    msgExit.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgExit.setDefaultButton(QMessageBox::Save);
    int ret = msgExit.exec();

    switch (ret) {
    case QMessageBox::Save:
        /****************** TO DO : Emit Save File **********************/
    case QMessageBox::Discard:
        break;
    case QMessageBox::Cancel:
        event->ignore();
        break;
    default:
        break;
    }
}
void Map_traffic::parseListToAddPingEtcCM1(){


    //CM buttons parameters

           if(savedCM1List.size() > 19){

                int indexAddPing = savedCM1List.indexOf("AddPing");
                int indexAddFtpDl = savedCM1List.indexOf("AddFtpDl");
                int indexAddFtpUl = savedCM1List.indexOf("AddFtpUl");
                int indexAddServiceReq = savedCM1List.indexOf("AddServiceReq");
                int indexAddStreamDl = savedCM1List.indexOf("AddStreamDl");
                int indexAddStreamUl = savedCM1List.indexOf("AddStreamUl");
                int indexAddSyncedping = savedCM1List.indexOf("AddSyncedPing");
                int indexAddVoip = savedCM1List.indexOf("AddVoip");

    //AddPing
                if(indexAddPing != -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddServiceReq == -1 && indexAddStreamDl == -1 && indexAddStreamUl == -1 && indexAddSyncedping == -1 && indexAddVoip == -1){

                   for(int i = indexAddPing; i < savedCM1List.size(); i++){

                       savedPingList.append(savedCM1List.at(i));

                   }

                }

                if(indexAddPing != -1 && indexAddVoip != -1){

                    for(int i = indexAddPing; i < indexAddVoip; i++){

                        savedPingList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddPing != -1 && indexAddVoip == -1 && indexAddSyncedping != -1){

                    for(int i = indexAddPing; i < indexAddSyncedping; i++){

                        savedPingList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddPing != -1 && indexAddVoip == -1 && indexAddSyncedping == -1 && indexAddServiceReq != -1){

                    for(int i = indexAddPing; i < indexAddServiceReq; i++){

                        savedPingList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddPing != -1 && indexAddVoip == -1 && indexAddSyncedping == -1 && indexAddServiceReq == -1 && indexAddFtpDl != -1){

                    for(int i = indexAddPing; i < indexAddFtpDl; i++){

                        savedPingList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddPing != -1 && indexAddVoip == -1 && indexAddSyncedping == -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl != -1){

                    for(int i = indexAddPing; i < indexAddFtpUl; i++){

                        savedPingList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddPing != -1 && indexAddVoip == -1 && indexAddSyncedping == -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl != -1){

                    for(int i = indexAddPing; i < indexAddStreamDl; i++){

                        savedPingList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddPing != -1 && indexAddVoip == -1 && indexAddSyncedping == -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl == -1 && indexAddStreamUl != -1){

                    for(int i = indexAddPing; i < indexAddStreamUl; i++){

                        savedPingList.append(savedCM1List.at(i));

                    }

                }

    //AddVoip
                if(indexAddVoip != -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddServiceReq == -1 && indexAddStreamDl == -1 && indexAddStreamUl == -1 && indexAddSyncedping == -1){

                    for(int i = indexAddVoip; i < savedCM1List.size(); i++){

                        savedVoipList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddVoip != -1 && indexAddSyncedping != -1){

                    for(int i = indexAddVoip; i < indexAddSyncedping; i++){

                        savedVoipList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddVoip != -1 && indexAddSyncedping == -1 && indexAddServiceReq != -1){

                    for(int i = indexAddVoip; i < indexAddServiceReq; i++){

                        savedVoipList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddVoip != -1 && indexAddSyncedping == -1 && indexAddServiceReq == -1 && indexAddFtpDl != -1){

                    for(int i = indexAddVoip; i < indexAddFtpDl; i++){

                        savedVoipList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddVoip != -1 && indexAddSyncedping == -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl != -1){

                    for(int i = indexAddVoip; i < indexAddFtpUl; i++){

                        savedVoipList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddVoip != -1 && indexAddSyncedping == -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl != -1){

                    for(int i = indexAddVoip; i < indexAddStreamDl; i++){

                        savedVoipList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddVoip != -1 && indexAddSyncedping == -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl == -1 && indexAddStreamUl != -1){

                    for(int i = indexAddVoip; i < indexAddStreamUl; i++){

                        savedVoipList.append(savedCM1List.at(i));

                    }

                }
    //AddSyncedPing

                if(indexAddSyncedping != -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl == -1 && indexAddStreamUl == -1){

                    for(int i = indexAddSyncedping; i < savedCM1List.size(); i++){

                        savedSyncedPingList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddSyncedping != -1 && indexAddServiceReq != -1){

                    for(int i = indexAddSyncedping; i < indexAddServiceReq; i++){

                        savedSyncedPingList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddSyncedping != -1 && indexAddServiceReq == -1 && indexAddFtpDl != -1){

                    for(int i = indexAddSyncedping; i < indexAddFtpDl; i++){

                        savedSyncedPingList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddSyncedping != -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl != -1){

                    for(int i = indexAddSyncedping; i < indexAddFtpUl; i++){

                        savedSyncedPingList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddSyncedping != -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl != -1){

                    for(int i = indexAddSyncedping; i < indexAddStreamDl; i++){

                        savedSyncedPingList.append(savedCM1List.at(i));

                    }

                }


                if(indexAddSyncedping != -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl == -1 && indexAddStreamUl != -1){

                    for(int i = indexAddSyncedping; i < indexAddStreamUl; i++){

                        savedSyncedPingList.append(savedCM1List.at(i));

                    }

                }
    //AddServiceReq

                if(indexAddServiceReq != -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl == -1 && indexAddStreamUl == -1){

                    for(int i = indexAddServiceReq; i < savedCM1List.size(); i++){

                        savedServiceReqList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddServiceReq != -1 && indexAddFtpDl != -1){

                    for(int i = indexAddServiceReq; i < indexAddFtpDl; i++){

                        savedServiceReqList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddServiceReq != -1 && indexAddFtpDl == -1 && indexAddFtpUl != -1){

                    for(int i = indexAddServiceReq; i < indexAddFtpUl; i++){

                        savedServiceReqList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddServiceReq != -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl != -1){

                    for(int i = indexAddServiceReq; i < indexAddStreamDl; i++){

                        savedServiceReqList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddServiceReq != -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl == -1 && indexAddStreamUl != -1){

                    for(int i = indexAddServiceReq; i < indexAddStreamUl; i++){

                        savedServiceReqList.append(savedCM1List.at(i));

                    }

                }
    //AddFtpDl

                if(indexAddFtpDl != -1 && indexAddFtpUl == -1 && indexAddStreamDl == -1 && indexAddStreamUl == -1){

                    for(int i = indexAddFtpDl; i < savedCM1List.size(); i++){

                        savedFtpDlList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddFtpDl != -1 && indexAddFtpUl != -1){

                    for(int i = indexAddFtpDl; i < indexAddFtpUl; i++){

                        savedFtpDlList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddFtpDl != -1 && indexAddFtpUl == -1 && indexAddStreamDl != -1){

                    for(int i = indexAddFtpDl; i < indexAddStreamDl; i++){

                        savedFtpDlList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddFtpDl != -1 && indexAddFtpUl == -1 && indexAddStreamDl == -1 && indexAddStreamUl != -1){

                    for(int i = indexAddFtpDl; i < indexAddStreamUl; i++){

                        savedFtpDlList.append(savedCM1List.at(i));

                    }

                }

//AddFtpUl

                if(indexAddFtpUl != -1 && indexAddStreamDl == -1 && indexAddStreamUl == -1){

                    for(int i = indexAddFtpUl; i < savedCM1List.size(); i++){

                        savedFtpUlList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddFtpUl != -1 && indexAddStreamDl != -1){

                    for(int i = indexAddFtpUl; i < indexAddStreamUl; i++){

                        savedFtpUlList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddFtpUl != -1 && indexAddStreamDl == -1 && indexAddStreamUl != -1){

                    for(int i = indexAddFtpUl; i < indexAddStreamUl; i++){

                        savedFtpUlList.append(savedCM1List.at(i));

                    }

                }

//AddStreamDl
                if(indexAddStreamDl != -1 && indexAddStreamUl == -1){

                    for(int i = indexAddStreamDl; i < savedCM1List.size(); i++){

                        savedStreamDlList.append(savedCM1List.at(i));

                    }

                }

                if(indexAddStreamDl != -1 && indexAddStreamUl != -1){

                    for(int i = indexAddStreamDl; i < indexAddStreamUl; i++){

                        savedStreamDlList.append(savedCM1List.at(i));

                    }

                }
//AddStreamUl

                if(indexAddStreamUl != -1){

                    for(int i = indexAddStreamUl; i < savedCM1List.size(); i++){

                        savedStreamUlList.append(savedCM1List.at(i));

              }
         }
    }
}


void Map_traffic::parseListToAddPingEtcCM2(){


    //CM buttons parameters

           if(savedCM2List.size() > 19){

                int indexAddPing = savedCM2List.indexOf("AddPing");
                int indexAddFtpDl = savedCM2List.indexOf("AddFtpDl");
                int indexAddFtpUl = savedCM2List.indexOf("AddFtpUl");
                int indexAddServiceReq = savedCM2List.indexOf("AddServiceReq");
                int indexAddStreamDl = savedCM2List.indexOf("AddStreamDl");
                int indexAddStreamUl = savedCM2List.indexOf("AddStreamUl");
                int indexAddSyncedping = savedCM2List.indexOf("AddSyncedPing");
                int indexAddVoip = savedCM2List.indexOf("AddVoip");

    //AddPing
                if(indexAddPing != -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddServiceReq == -1 && indexAddStreamDl == -1 && indexAddStreamUl == -1 && indexAddSyncedping == -1 && indexAddVoip == -1){

                   for(int i = indexAddPing; i < savedCM2List.size(); i++){

                       savedPingList.append(savedCM2List.at(i));

                   }

                }

                if(indexAddPing != -1 && indexAddVoip != -1){

                    for(int i = indexAddPing; i < indexAddVoip; i++){

                        savedPingList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddPing != -1 && indexAddVoip == -1 && indexAddSyncedping != -1){

                    for(int i = indexAddPing; i < indexAddSyncedping; i++){

                        savedPingList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddPing != -1 && indexAddVoip == -1 && indexAddSyncedping == -1 && indexAddServiceReq != -1){

                    for(int i = indexAddPing; i < indexAddServiceReq; i++){

                        savedPingList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddPing != -1 && indexAddVoip == -1 && indexAddSyncedping == -1 && indexAddServiceReq == -1 && indexAddFtpDl != -1){

                    for(int i = indexAddPing; i < indexAddFtpDl; i++){

                        savedPingList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddPing != -1 && indexAddVoip == -1 && indexAddSyncedping == -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl != -1){

                    for(int i = indexAddPing; i < indexAddFtpUl; i++){

                        savedPingList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddPing != -1 && indexAddVoip == -1 && indexAddSyncedping == -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl != -1){

                    for(int i = indexAddPing; i < indexAddStreamDl; i++){

                        savedPingList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddPing != -1 && indexAddVoip == -1 && indexAddSyncedping == -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl == -1 && indexAddStreamUl != -1){

                    for(int i = indexAddPing; i < indexAddStreamUl; i++){

                        savedPingList.append(savedCM2List.at(i));

                    }

                }

    //AddVoip
                if(indexAddVoip != -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddServiceReq == -1 && indexAddStreamDl == -1 && indexAddStreamUl == -1 && indexAddSyncedping == -1){

                    for(int i = indexAddVoip; i < savedCM2List.size(); i++){

                        savedVoipList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddVoip != -1 && indexAddSyncedping != -1){

                    for(int i = indexAddVoip; i < indexAddSyncedping; i++){

                        savedVoipList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddVoip != -1 && indexAddSyncedping == -1 && indexAddServiceReq != -1){

                    for(int i = indexAddVoip; i < indexAddServiceReq; i++){

                        savedVoipList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddVoip != -1 && indexAddSyncedping == -1 && indexAddServiceReq == -1 && indexAddFtpDl != -1){

                    for(int i = indexAddVoip; i < indexAddFtpDl; i++){

                        savedVoipList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddVoip != -1 && indexAddSyncedping == -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl != -1){

                    for(int i = indexAddVoip; i < indexAddFtpUl; i++){

                        savedVoipList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddVoip != -1 && indexAddSyncedping == -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl != -1){

                    for(int i = indexAddVoip; i < indexAddStreamDl; i++){

                        savedVoipList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddVoip != -1 && indexAddSyncedping == -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl == -1 && indexAddStreamUl != -1){

                    for(int i = indexAddVoip; i < indexAddStreamUl; i++){

                        savedVoipList.append(savedCM2List.at(i));

                    }

                }
    //AddSyncedPing

                if(indexAddSyncedping != -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl == -1 && indexAddStreamUl == -1){

                    for(int i = indexAddSyncedping; i < savedCM2List.size(); i++){

                        savedSyncedPingList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddSyncedping != -1 && indexAddServiceReq != -1){

                    for(int i = indexAddSyncedping; i < indexAddServiceReq; i++){

                        savedSyncedPingList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddSyncedping != -1 && indexAddServiceReq == -1 && indexAddFtpDl != -1){

                    for(int i = indexAddSyncedping; i < indexAddFtpDl; i++){

                        savedSyncedPingList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddSyncedping != -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl != -1){

                    for(int i = indexAddSyncedping; i < indexAddFtpUl; i++){

                        savedSyncedPingList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddSyncedping != -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl != -1){

                    for(int i = indexAddSyncedping; i < indexAddStreamDl; i++){

                        savedSyncedPingList.append(savedCM2List.at(i));

                    }

                }


                if(indexAddSyncedping != -1 && indexAddServiceReq == -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl == -1 && indexAddStreamUl != -1){

                    for(int i = indexAddSyncedping; i < indexAddStreamUl; i++){

                        savedSyncedPingList.append(savedCM2List.at(i));

                    }

                }
    //AddServiceReq

                if(indexAddServiceReq != -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl == -1 && indexAddStreamUl == -1){

                    for(int i = indexAddServiceReq; i < savedCM2List.size(); i++){

                        savedServiceReqList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddServiceReq != -1 && indexAddFtpDl != -1){

                    for(int i = indexAddServiceReq; i < indexAddFtpDl; i++){

                        savedServiceReqList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddServiceReq != -1 && indexAddFtpDl == -1 && indexAddFtpUl != -1){

                    for(int i = indexAddServiceReq; i < indexAddFtpUl; i++){

                        savedServiceReqList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddServiceReq != -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl != -1){

                    for(int i = indexAddServiceReq; i < indexAddStreamDl; i++){

                        savedServiceReqList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddServiceReq != -1 && indexAddFtpDl == -1 && indexAddFtpUl == -1 && indexAddStreamDl == -1 && indexAddStreamUl != -1){

                    for(int i = indexAddServiceReq; i < indexAddStreamUl; i++){

                        savedServiceReqList.append(savedCM2List.at(i));

                    }

                }
    //AddFtpDl

                if(indexAddFtpDl != -1 && indexAddFtpUl == -1 && indexAddStreamDl == -1 && indexAddStreamUl == -1){

                    for(int i = indexAddFtpDl; i < savedCM2List.size(); i++){

                        savedFtpDlList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddFtpDl != -1 && indexAddFtpUl != -1){

                    for(int i = indexAddFtpDl; i < indexAddFtpUl; i++){

                        savedFtpDlList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddFtpDl != -1 && indexAddFtpUl == -1 && indexAddStreamDl != -1){

                    for(int i = indexAddFtpDl; i < indexAddStreamDl; i++){

                        savedFtpDlList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddFtpDl != -1 && indexAddFtpUl == -1 && indexAddStreamDl == -1 && indexAddStreamUl != -1){

                    for(int i = indexAddFtpDl; i < indexAddStreamUl; i++){

                        savedFtpDlList.append(savedCM2List.at(i));

                    }

                }

//AddFtpUl

                if(indexAddFtpUl != -1 && indexAddStreamDl == -1 && indexAddStreamUl == -1){

                    for(int i = indexAddFtpUl; i < savedCM2List.size(); i++){

                        savedFtpUlList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddFtpUl != -1 && indexAddStreamDl != -1){

                    for(int i = indexAddFtpUl; i < indexAddStreamUl; i++){

                        savedFtpUlList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddFtpUl != -1 && indexAddStreamDl == -1 && indexAddStreamUl != -1){

                    for(int i = indexAddFtpUl; i < indexAddStreamUl; i++){

                        savedFtpUlList.append(savedCM2List.at(i));

                    }

                }

//AddStreamDl
                if(indexAddStreamDl != -1 && indexAddStreamUl == -1){

                    for(int i = indexAddStreamDl; i < savedCM2List.size(); i++){

                        savedStreamDlList.append(savedCM2List.at(i));

                    }

                }

                if(indexAddStreamDl != -1 && indexAddStreamUl != -1){

                    for(int i = indexAddStreamDl; i < indexAddStreamUl; i++){

                        savedStreamDlList.append(savedCM2List.at(i));

                    }

                }
//AddStreamUl

                if(indexAddStreamUl != -1){

                    for(int i = indexAddStreamUl; i < savedCM2List.size(); i++){

                        savedStreamUlList.append(savedCM2List.at(i));

             }
        }
    }
}



// ciag dalszy reszty

void Map_traffic::on_bt_statistics_clicked()
{
//    viewStatistics.close();
//    viewStatistics.showStatisticsWindow(*(this->statistics));
//    //viewStatistics.setParameters(statistics, appSettings);
//    viewStatistics.show();
}

void Map_traffic::on_bt_tuningtraffic_clicked()
{
    //counts quantity of indetical models;
    int tmp_cs_iter_counter = 0;
    int tmp_ps_iter_counter = 0;
    int tmp_area_iter_counter = 0;
    //holds maximum index for removed item
    int tmp_removedItemCounter = tmp_counter_UE;

    if (tmp_counter_UE == 0)
    {
        viewTuningtraffic.clearCSCombobox();
        viewTuningtraffic.clearPSCombobox();
        viewTuningtraffic.clearAreaCombobox();
        for (int i = 0; i < counter_UE; ++i)
        {
            if (tableview[i]->is_Accepted())
            {
                viewTuningtraffic.setUEGroup(tableview[i]);
                viewTuningtraffic.setCSCombobox();
                viewTuningtraffic.setPSCombobox();
                viewTuningtraffic.setAreaCombobox();
                viewTuningtraffic.initialize(tuningtraffic);

                viewTuningtraffic.setParameters();
            }
        }
    }
    else if (tmp_counter_UE > 0)
    {
        if (counter_UE > tmp_counter_UE)
        {
            for (int i = tmp_counter_UE; i < counter_UE; ++i)
            {
                viewTuningtraffic.setUEGroup(tableview[i]);
                viewTuningtraffic.setCSCombobox();
                viewTuningtraffic.setPSCombobox();
                viewTuningtraffic.setAreaCombobox();
                viewTuningtraffic.pushModel(tuningtraffic);
            }
            viewTuningtraffic.setParameters();
        }
        else if (counter_UE < tmp_counter_UE)
        {
            for (int i = 0; i < (tmp_counter_UE - counter_UE); ++i)
            {
                for (int j = 0; j < counter_UE; j++)
                {
                    if (tableview[j]->get_currentCSBehavior() != tableview[tmp_removedItemCounter-1]->get_currentCSBehavior())
                        tmp_cs_iter_counter++;
                    if (tableview[j]->get_currentPSBehavior() != tableview[tmp_removedItemCounter-1]->get_currentPSBehavior())
                        tmp_ps_iter_counter++;
                    if (tableview[j]->get_currentArea() != tableview[tmp_removedItemCounter-1]->get_currentArea())
                        tmp_area_iter_counter++;
                }
                if (tmp_cs_iter_counter == counter_UE)
                    viewTuningtraffic.popCSModel(tuningtraffic);
                if (tmp_ps_iter_counter == counter_UE)
                    viewTuningtraffic.popPSModel(tuningtraffic);
                if (tmp_area_iter_counter == counter_UE)
                    viewTuningtraffic.popArea(tuningtraffic);
                tmp_removedItemCounter--;
            }
            viewTuningtraffic.setParameters();
        }
        else if (counter_UE == tmp_counter_UE)
        {
            if (viewTuningtraffic.get_csComboboxCount() > 0 and viewTuningtraffic.get_psComboboxCount() > 0)
                viewTuningtraffic.setParameters();
        }
    }
    for (int i = 0; i < 10; ++i)
        tableview[i]->resetAccept();
    viewTuningtraffic.show();
    if (viewTuningtraffic.get_csComboboxCount() > 0 and viewTuningtraffic.get_psComboboxCount() > 0)
        tmp_counter_UE = counter_UE;
}

void Map_traffic::on_bt_time_clicked()
{
    viewTimeTraffic.setParameters(timetraffic);
    viewTimeTraffic.exec();
}


void Map_traffic::on_add_button_clicked(){
    if(counter_UE<10)
    {
        if(counter_UE<5){
            tab_UE[counter_UE]=new DragUELabel("e"+QString::number(counter_UE+1), ui->scrollAreaWidgetContents);
            tab_UE[counter_UE]->setGeometry(750+offset_x,60,40,40);
            tab_UE[counter_UE]->show();
            counter_UE++;
        }else{
            tab_UE[counter_UE]=new DragUELabel("e"+QString::number(counter_UE+1), ui->scrollAreaWidgetContents);
            tab_UE[counter_UE]->setGeometry(710+offset_x_2,100,40,40);
            tab_UE[counter_UE]->show();
            counter_UE++;
            offset_x_2=offset_x_2+40;
        }
        offset_x=offset_x+40;
        ui->tet_UE->setText(QString::number(counter_UE));
    }
}


void Map_traffic::on_remove_button_clicked(){
    if(counter_UE>1)
    {
        //delete last_element_traffic;
        for(int i=0;i<counter_UE;i++){
            delete tab_UE[counter_UE-1];
            counter_UE--;
            offset_x=40;
            offset_x_2=40;
            break;
        }

        //counter_UE--;
        ui->tet_UE->setText(QString::number(counter_UE));
    }
}

