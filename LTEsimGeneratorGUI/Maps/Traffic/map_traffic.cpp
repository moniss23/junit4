#include "map_traffic.h"
#include "ui_map_traffic.h"
#include <QString>
#include <QCloseEvent>
#include <QFile>
#include <QtWidgets>
#include "QRect"
#include <QPoint>
#include <QSettings>
#include <QMessageBox>
#include <QInputDialog>

#include <Maps/Traffic/MapComponents/draguelabel.h>
#include <Maps/Traffic/UeParameters/UE_param_form.h>
#include <Maps/Traffic/DataObjects/handoverdata.h>
#include <ManagementWindow/ParametersWindow/parameterswindow.h>
#include <Data/cell.h>

//externed checkbox settings from MapWindow
extern bool tmp_chkCell11;
extern bool tmp_chkCell12;
extern bool tmp_chkCell21;
extern bool tmp_chkCell22;
extern bool tmp_chkCell31;
extern bool tmp_chkCell32;
extern bool tmp_chkCell41;
extern bool tmp_chkCell42;
extern bool tmp_chkCell51;
extern bool tmp_chkCell52;
extern bool tmp_chkCell61;
extern bool tmp_chkCell62;
//.............

//changes saving map traffic

extern int currentOpenedTrafficFile;
extern QVector<QStringList> trafficFilesContentLists;
extern QVector<QString> trafficFilesContent;

extern QStringList readyCMList[10];

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


bool small;
QWidget *pointerWinTitle;

bool MainSaveWasClicked;

//int UEindex;
QString CMname;
extern QStringList CMList;
extern QStringList PS_List;

//extern QString currentPS;

extern bool isCMActive[10];



my_qlabel *pointerCM[10];

extern QStringList customModelList;

class QWidget;
class DragUELabel;
class Form;
int offset_x=40;
int offset_x_2=40;
DragUELabel *actualposition;
//int UEindex;
extern int currentOpenedTrafficFile;
extern QStringList timeParametersContentList;
extern QStringList tuningParametersContentList;
extern QVector<QString> trafficFilesContent;
extern ParametersWindow* p;
Map_traffic::Map_traffic(DataSystem* appSettings, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Map_traffic),
    appSettings(appSettings)
{
        ui->setupUi(this);
        //int n=12;
        tuningtraffic = new Tuningtraffic();
        timetraffic = new TimeData();
        QString mapIndex("");
        statistics = new StatisticsData(mapIndex,appSettings);
        createCell();

        this->counter_UE=1;
        tab_UE = new DragUELabel*[counter_UE];

        ui->tet_UE->setText(QString::number(counter_UE));
        tab_UE[0] = new DragUELabel("e1",ui->scrollAreaWidgetContents);
        tab_UE[0]->setGeometry(750,60,40,40);

        small = true;
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

        if(trafficFilesContent.size() > 0 && trafficFilesContentLists.size() > 0){

            parseSavedList();
            if(savedCM1List.size() > 0){
            ui->CM_1->setStyleSheet(savedCM1List.at(2));
            }
            if(savedCM2List.size() > 0){
                ui->CM_2->setStyleSheet(savedCM2List.at(2));
            }
            if(savedCM3List.size() > 0){
                ui->CM_3->setStyleSheet(savedCM3List.at(2));
            }
            if(savedCM4List.size() > 0){
                ui->CM_4->setStyleSheet(savedCM4List.at(2));
            }
            if(savedCM5List.size() > 0){
                ui->CM_5->setStyleSheet(savedCM5List.at(2));
            }
            if(savedCM6List.size() > 0){
                ui->CM_6->setStyleSheet(savedCM6List.at(2));
            }
            if(savedCM7List.size() > 0){
                ui->CM_7->setStyleSheet(savedCM7List.at(2));
            }
            if(savedCM8List.size() > 0){
                ui->CM_8->setStyleSheet(savedCM8List.at(2));
            }
            if(savedCM9List.size() > 0){
                ui->CM_9->setStyleSheet(savedCM9List.at(2));
            }
            if(savedCM10List.size() > 0){
                ui->CM_10->setStyleSheet(savedCM10List.at(2));
            }

            readyCMList[0] = savedCM1List;
            readyCMList[1] = savedCM2List;
            readyCMList[2] = savedCM3List;
            readyCMList[3] = savedCM4List;
            readyCMList[4] = savedCM5List;
            readyCMList[5] = savedCM6List;
            readyCMList[6] = savedCM7List;
            readyCMList[7] = savedCM8List;
            readyCMList[8] = savedCM9List;
            readyCMList[9] = savedCM10List;
        }

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

        mapRange_traffic = new MapRange();

        changeMapRange_y_northBoundMap();
        changeMapRange_x_northBoundMap();

        this->number1 =0;

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


        viewStatistics.adjustSize();
        viewStatistics.move(QApplication::desktop()->screen()->rect().center() + viewStatistics.rect().bottomRight());

        viewTuningtraffic.adjustSize();
        viewTuningtraffic.move(QApplication::desktop()->screen()->rect().center()+ viewTuningtraffic.rect().bottomRight());

        viewcustomModel[0]->adjustSize();
        viewcustomModel[0]->move(QApplication::desktop()->screen()->rect().center()+ viewcustomModel[0]->rect().bottomRight());
        setAcceptDrops(true);

        ui->checkBoxCell11->setChecked(tmp_chkCell11);
        ui->checkBoxCell12->setChecked(tmp_chkCell12);
        ui->checkBoxCell21->setChecked(tmp_chkCell21);
        ui->checkBoxCell22->setChecked(tmp_chkCell22);
        ui->checkBoxCell31->setChecked(tmp_chkCell31);
        ui->checkBoxCell32->setChecked(tmp_chkCell32);
        ui->checkBoxCell41->setChecked(tmp_chkCell41);
        ui->checkBoxCell42->setChecked(tmp_chkCell42);
        ui->checkBoxCell51->setChecked(tmp_chkCell51);
        ui->checkBoxCell52->setChecked(tmp_chkCell52);
        ui->checkBoxCell61->setChecked(tmp_chkCell61);
        ui->checkBoxCell62->setChecked(tmp_chkCell62);
}

Map_traffic::~Map_traffic()
{
    delete ui;
}

bool Map_traffic::toBool(QString value){
    return value == QString("1");
}

void Map_traffic::createCell(){
    cell61 = new Cell ("cell61");
    cell61->chBox = ui->checkBoxCell61;
    cell61->center = center61;
    if(!cell61->getCell_new_name().isEmpty())
        cell61->chBox->setText(cell61->getCell_new_name());
    cell62 = new Cell ("cell62");
    cell62->chBox = ui->checkBoxCell62;
    cell62->center = center62;
    if(!cell62->getCell_new_name().isEmpty())
        cell62->chBox->setText(cell62->getCell_new_name());
    cell52 = new Cell ("cell52");
    cell52->chBox = ui->checkBoxCell52;
    cell52->center = center52;
    if(!cell52->getCell_new_name().isEmpty())
        cell52->chBox->setText(cell52->getCell_new_name());
    cell51 = new Cell ("cell51");
    cell51->chBox = ui->checkBoxCell51;
    cell51->center = center51;
    if(!cell51->getCell_new_name().isEmpty())
        cell51->chBox->setText(cell51->getCell_new_name());
    cell42 = new Cell ("cell42");
    cell42->chBox = ui->checkBoxCell42;
    cell42->center = center42;
    if(!cell42->getCell_new_name().isEmpty())
        cell42->chBox->setText(cell42->getCell_new_name());
    cell41 = new Cell ("cell41");
    cell41->chBox = ui->checkBoxCell41;
    cell41->center = center41;
    if(!cell41->getCell_new_name().isEmpty())
        cell41->chBox->setText(cell41->getCell_new_name());
    cell32 = new Cell ("cell32");
    cell32->chBox = ui->checkBoxCell32;
    cell32->center = center32;
    if(!cell32->getCell_new_name().isEmpty())
        cell32->chBox->setText(cell32->getCell_new_name());
    cell31 = new Cell ("cell31");
    cell31->chBox = ui->checkBoxCell31;
    cell31->center = center31;
    if(!cell31->getCell_new_name().isEmpty())
        cell31->chBox->setText(cell31->getCell_new_name());
    cell22 = new Cell ("cell22");
    cell22->chBox = ui->checkBoxCell22;
    cell22->center = center22;
    if(!cell22->getCell_new_name().isEmpty())
        cell22->chBox->setText(cell22->getCell_new_name());
    cell21 = new Cell ("cell21");
    cell21->chBox = ui->checkBoxCell21;
    cell21->center = center21;
    if(!cell21->getCell_new_name().isEmpty())
        cell21->chBox->setText(cell21->getCell_new_name());
    cell12 = new Cell ("cell12");
    cell12->chBox = ui->checkBoxCell12;
    cell12->center = center12;
    if(!cell12->getCell_new_name().isEmpty())
        cell12->chBox->setText(cell12->getCell_new_name());
    cell11 = new Cell ("cell11");
    cell11->chBox = ui->checkBoxCell11;
    cell11->center = center11;
    if(!cell11->getCell_new_name().isEmpty())
        cell11->chBox->setText(cell11->getCell_new_name());
    tabCell = new Cell *[12];
    tabCell[0] = cell11;
    tabCell[1] = cell12;
    tabCell[2] = cell21;
    tabCell[3] = cell22;
    tabCell[4] = cell31;
    tabCell[5] = cell32;
    tabCell[6] = cell41;
    tabCell[7] = cell42;
    tabCell[8] = cell51;
    tabCell[9] = cell52;
    tabCell[10] = cell61;
    tabCell[11] = cell62;

    //    for(unsigned int i=0; i<cellCount; i++){
    //        cellNames[i].name=tabCell[i]->getCell();
    //        cellNames[i].obj=tabCell[i];
    //    }
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





void Map_traffic::mouseDoubleClickEvent( QMouseEvent *event )
{
    if ( event->button() == Qt::LeftButton )
    {
        //Okno wyskakujace z parametrami
        DragUELabel *child = dynamic_cast<DragUELabel*>(childAt(event->pos()));
        if (!child)
            return;

        //Cell11
        if(child==tab_UE[0]) show_UE_params1();
        if(child==tab_UE[1]) show_UE_params2();
        if(child==tab_UE[2]) show_UE_params3();
        if(child==tab_UE[3]) show_UE_params4();
        if(child==tab_UE[4]) show_UE_params5();
        if(child==tab_UE[5]) show_UE_params6();
        if(child==tab_UE[6]) show_UE_params7();
        if(child==tab_UE[7]) show_UE_params8();
        if(child==tab_UE[8]) show_UE_params9();
        if(child==tab_UE[9]) show_UE_params10();
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

void Map_traffic::show_UE_params1(){

  //  pointerWinTitle->setWindowTitle("UE params 1");

    if(pointerUE1->pointerPS->currentText() == ""){

            pointerUE1->pointerPS->clear();
            qSort(CMList.begin(), CMList.end());
            if(isCMActive[10]){
                CMList.removeOne("Custom Model 10");
                CMList.push_back("Custom Model 10");
            }
            PS_List.removeDuplicates();
            CMList.removeDuplicates();
            pointerUE1->pointerPS->addItem(0, "");
            pointerUE1->pointerPS->setCurrentIndex(0);
            pointerUE1->pointerPS->insertItems(1,(CMList + PS_List));
            pointerUE1->show();

        }
    else {
        QString PS1 = pointerUE1->pointerPS->currentText();
        pointerUE1->pointerPS->clear();
        qSort(CMList.begin(), CMList.end());
        if(isCMActive[10]){
            CMList.removeOne("Custom Model 10");
            CMList.push_back("Custom Model 10");
        }
        PS_List.removeDuplicates();
        CMList.removeDuplicates();
        pointerUE1->pointerPS->addItem(0, "");
        pointerUE1->pointerPS->insertItems(1,(CMList + PS_List));
        pointerUE1->pointerPS->setCurrentText(PS1);
        pointerUE1->show();

    }

}

void Map_traffic::show_UE_params2(){

    if(pointerUE2->pointerPS->currentText() == ""){

            pointerUE2->pointerPS->clear();
            qSort(CMList.begin(), CMList.end());
            if(isCMActive[10]){
                CMList.removeOne("Custom Model 10");
                CMList.push_back("Custom Model 10");
            }
            PS_List.removeDuplicates();
            CMList.removeDuplicates();
            pointerUE2->pointerPS->addItem(0, "");
            pointerUE2->pointerPS->setCurrentIndex(0);
            pointerUE2->pointerPS->insertItems(1,(CMList + PS_List));
            pointerUE2->show();
        }
    else {
        QString PS2 = pointerUE2->pointerPS->currentText();
        pointerUE2->pointerPS->clear();
        qSort(CMList.begin(), CMList.end());
        if(isCMActive[10]){
            CMList.removeOne("Custom Model 10");
            CMList.push_back("Custom Model 10");
        }
        PS_List.removeDuplicates();
        CMList.removeDuplicates();
        pointerUE2->pointerPS->addItem(0, "");
        pointerUE2->pointerPS->insertItems(1,(CMList + PS_List));
        pointerUE2->pointerPS->setCurrentText(PS2);
        pointerUE2->show();

    }
}

void Map_traffic::show_UE_params3(){

    if(pointerUE3->pointerPS->currentText() == ""){

            pointerUE3->pointerPS->clear();
            qSort(CMList.begin(), CMList.end());
            if(isCMActive[10]){
                CMList.removeOne("Custom Model 10");
                CMList.push_back("Custom Model 10");
            }
            PS_List.removeDuplicates();
            CMList.removeDuplicates();
            pointerUE3->pointerPS->addItem(0, "");
            pointerUE3->pointerPS->setCurrentIndex(0);
            pointerUE3->pointerPS->insertItems(1,(CMList + PS_List));
            pointerUE3->show();
        }
    else {
        QString PS3 = pointerUE3->pointerPS->currentText();
        pointerUE3->pointerPS->clear();
        qSort(CMList.begin(), CMList.end());
        if(isCMActive[10]){
            CMList.removeOne("Custom Model 10");
            CMList.push_back("Custom Model 10");
        }
        PS_List.removeDuplicates();
        CMList.removeDuplicates();
        pointerUE3->pointerPS->addItem(0, "");
        pointerUE3->pointerPS->insertItems(1,(CMList + PS_List));
        pointerUE3->pointerPS->setCurrentText(PS3);
        pointerUE3->show();

    }
}

void Map_traffic::show_UE_params4(){
    if(pointerUE4->pointerPS->currentText() == ""){

            pointerUE4->pointerPS->clear();
            qSort(CMList.begin(), CMList.end());
            if(isCMActive[10]){
                CMList.removeOne("Custom Model 10");
                CMList.push_back("Custom Model 10");
            }
            PS_List.removeDuplicates();
            CMList.removeDuplicates();
            pointerUE4->pointerPS->addItem(0, "");
            pointerUE4->pointerPS->setCurrentIndex(0);
            pointerUE4->pointerPS->insertItems(1,(CMList + PS_List));
            pointerUE4->show();
        }
    else {
        QString PS4 = pointerUE4->pointerPS->currentText();
        pointerUE4->pointerPS->clear();
        qSort(CMList.begin(), CMList.end());
        if(isCMActive[10]){
            CMList.removeOne("Custom Model 10");
            CMList.push_back("Custom Model 10");
        }
        PS_List.removeDuplicates();
        CMList.removeDuplicates();
        pointerUE4->pointerPS->addItem(0, "");
        pointerUE4->pointerPS->insertItems(1,(CMList + PS_List));
        pointerUE4->pointerPS->setCurrentText(PS4);
        pointerUE4->show();

    }
}

void Map_traffic::show_UE_params5(){
    if(pointerUE5->pointerPS->currentText() == ""){

            pointerUE5->pointerPS->clear();
            qSort(CMList.begin(), CMList.end());
            if(isCMActive[10]){
                CMList.removeOne("Custom Model 10");
                CMList.push_back("Custom Model 10");
            }
            PS_List.removeDuplicates();
            CMList.removeDuplicates();
            pointerUE5->pointerPS->addItem(0, "");
            pointerUE5->pointerPS->setCurrentIndex(0);
            pointerUE5->pointerPS->insertItems(1,(CMList + PS_List));
            pointerUE5->show();
        }
    else {
        QString PS5 = pointerUE5->pointerPS->currentText();
        pointerUE5->pointerPS->clear();
        qSort(CMList.begin(), CMList.end());
        if(isCMActive[10]){
            CMList.removeOne("Custom Model 10");
            CMList.push_back("Custom Model 10");
        }
        PS_List.removeDuplicates();
        CMList.removeDuplicates();
        pointerUE5->pointerPS->addItem(0, "");
        pointerUE5->pointerPS->insertItems(1,(CMList + PS_List));
        pointerUE5->pointerPS->setCurrentText(PS5);
        pointerUE5->show();

    }
}

void Map_traffic::show_UE_params6(){
    if(pointerUE6->pointerPS->currentText() == ""){

            pointerUE6->pointerPS->clear();
            qSort(CMList.begin(), CMList.end());
            if(isCMActive[10]){
                CMList.removeOne("Custom Model 10");
                CMList.push_back("Custom Model 10");
            }
            PS_List.removeDuplicates();
            CMList.removeDuplicates();
            pointerUE6->pointerPS->addItem(0, "");
            pointerUE6->pointerPS->setCurrentIndex(0);
            pointerUE6->pointerPS->insertItems(1,(CMList + PS_List));
            pointerUE6->show();
        }
    else {
        QString PS6 = pointerUE6->pointerPS->currentText();
        pointerUE6->pointerPS->clear();
        qSort(CMList.begin(), CMList.end());
        if(isCMActive[10]){
            CMList.removeOne("Custom Model 10");
            CMList.push_back("Custom Model 10");
        }
        PS_List.removeDuplicates();
        CMList.removeDuplicates();
        pointerUE6->pointerPS->addItem(0, "");
        pointerUE6->pointerPS->insertItems(1,(CMList + PS_List));
        pointerUE6->pointerPS->setCurrentText(PS6);
        pointerUE6->show();

    }
}

void Map_traffic::show_UE_params7(){
    if(pointerUE7->pointerPS->currentText() == ""){

            pointerUE7->pointerPS->clear();
            qSort(CMList.begin(), CMList.end());
            if(isCMActive[10]){
                CMList.removeOne("Custom Model 10");
                CMList.push_back("Custom Model 10");
            }
            PS_List.removeDuplicates();
            CMList.removeDuplicates();
            pointerUE7->pointerPS->addItem(0, "");
            pointerUE7->pointerPS->setCurrentIndex(0);
            pointerUE7->pointerPS->insertItems(1,(CMList + PS_List));
            pointerUE7->show();
        }
    else {
        QString PS7 = pointerUE7->pointerPS->currentText();
        pointerUE7->pointerPS->clear();
        qSort(CMList.begin(), CMList.end());
        if(isCMActive[10]){
            CMList.removeOne("Custom Model 10");
            CMList.push_back("Custom Model 10");
        }
        PS_List.removeDuplicates();
        CMList.removeDuplicates();
        pointerUE7->pointerPS->addItem(0, "");
        pointerUE7->pointerPS->insertItems(1,(CMList + PS_List));
        pointerUE7->pointerPS->setCurrentText(PS7);
        pointerUE7->show();

    }
}

void Map_traffic::show_UE_params8(){
    if(pointerUE8->pointerPS->currentText() == ""){

            pointerUE8->pointerPS->clear();
            qSort(CMList.begin(), CMList.end());
            if(isCMActive[10]){
                CMList.removeOne("Custom Model 10");
                CMList.push_back("Custom Model 10");
            }
            PS_List.removeDuplicates();
            CMList.removeDuplicates();
            pointerUE8->pointerPS->addItem(0, "");
            pointerUE8->pointerPS->setCurrentIndex(0);
            pointerUE8->pointerPS->insertItems(1,(CMList + PS_List));
            pointerUE8->show();
        }
    else {
        QString PS8 = pointerUE8->pointerPS->currentText();
        pointerUE8->pointerPS->clear();
        qSort(CMList.begin(), CMList.end());
        if(isCMActive[10]){
            CMList.removeOne("Custom Model 10");
            CMList.push_back("Custom Model 10");
        }
        PS_List.removeDuplicates();
        CMList.removeDuplicates();
        pointerUE8->pointerPS->addItem(0, "");
        pointerUE8->pointerPS->insertItems(1,(CMList + PS_List));
        pointerUE8->pointerPS->setCurrentText(PS8);
        pointerUE8->show();

    }
}

void Map_traffic::show_UE_params9(){
    if(pointerUE9->pointerPS->currentText() == ""){

            pointerUE9->pointerPS->clear();
            qSort(CMList.begin(), CMList.end());
            if(isCMActive[10]){
                CMList.removeOne("Custom Model 10");
                CMList.push_back("Custom Model 10");
            }
            PS_List.removeDuplicates();
            CMList.removeDuplicates();
            pointerUE9->pointerPS->addItem(0, "");
            pointerUE9->pointerPS->setCurrentIndex(0);
            pointerUE9->pointerPS->insertItems(1,(CMList + PS_List));
            pointerUE9->show();
        }
    else {
       QString PS9 = pointerUE9->pointerPS->currentText();
        pointerUE9->pointerPS->clear();
        qSort(CMList.begin(), CMList.end());
        if(isCMActive[10]){
            CMList.removeOne("Custom Model 10");
            CMList.push_back("Custom Model 10");
        }
        PS_List.removeDuplicates();
        CMList.removeDuplicates();
        pointerUE9->pointerPS->addItem(0, "");
        pointerUE9->pointerPS->insertItems(1,(CMList + PS_List));
        pointerUE9->pointerPS->setCurrentText(PS9);
        pointerUE9->show();

    }
}

void Map_traffic::show_UE_params10(){
    if(pointerUE10->pointerPS->currentText() == ""){

            pointerUE10->pointerPS->clear();
            qSort(CMList.begin(), CMList.end());
            if(isCMActive[10]){
                CMList.removeOne("Custom Model 10");
                CMList.push_back("Custom Model 10");
            }
            PS_List.removeDuplicates();
            CMList.removeDuplicates();
            pointerUE10->pointerPS->addItem(0, "");
            pointerUE10->pointerPS->setCurrentIndex(0);
            pointerUE10->pointerPS->insertItems(1,(CMList + PS_List));
            pointerUE10->show();
        }
    else {
        QString PS10 = pointerUE10->pointerPS->currentText();
        pointerUE10->pointerPS->clear();
        qSort(CMList.begin(), CMList.end());
        if(isCMActive[10]){
            CMList.removeOne("Custom Model 10");
            CMList.push_back("Custom Model 10");
        }
        PS_List.removeDuplicates();
        CMList.removeDuplicates();
        pointerUE10->pointerPS->addItem(0, "");
        pointerUE10->pointerPS->insertItems(1,(CMList + PS_List));
        pointerUE10->pointerPS->setCurrentText(PS10);
        pointerUE10->show();

    }
}









//----------------change Map scale ---------------------------------------------------------------
void Map_traffic::changeMapRange_x_northBoundMap()
{
    int max_map = mapRange_traffic->getNorthBoundMap();
    int scale = max_map/7;
    int position_zero = 1000+scale;
    ui->y->setText(QString::number(position_zero));
    ui->y_2->setText(QString::number(position_zero +scale));
    ui->y_3->setText(QString::number(position_zero +2*scale));
    ui->y_4->setText(QString::number(position_zero +3*scale));
    ui->y_5->setText(QString::number(position_zero +4*scale));
    ui->y_6->setText(QString::number(position_zero +5*scale));

    counter_cell = 0;
    counter_center = 0;
    couter_handover = 0;
    divisor = 0;
    //for (int i = 0; i<6 ; i++)
    //changeCenterValue_Y(position_zero + scale*i);

}

void Map_traffic::changeMapRange_y_northBoundMap()
{
    int max_map = this->mapRange_traffic->getEastBoundMap();
    int scale = max_map/5;
    ui->x->setText(QString::number(scale));
    ui->x_2->setText(QString::number(2*scale));
    ui->x_3->setText(QString::number(3*scale));
    ui->x_4->setText(QString::number(4*scale));

    counter_cell =0;
    counter_center =0;
    couter_handover =0;
    divisor = 0;
    //for (int i= 1; i<=2;i++)
    //changeCenterValue_X(scale*i);
}

void Map_traffic::closeEvent(QCloseEvent *event){
    msgExit.setText("The document has been modified.");
    msgExit.setInformativeText("Do you want to save your changes?");
    msgExit.setIcon(QMessageBox::Question);
    msgExit.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgExit.setDefaultButton(QMessageBox::Save);
    int ret = msgExit.exec();

    QStringList finalList;
    switch (ret) {
    case QMessageBox::Save:

        // Save was clicked
                          //anyChangesInMap=true;

                        //finalList.clear();
                        for(unsigned i=0;i<10;i++)
                            finalList.append(readyCMList[i]);



                          trafficFilesContentLists[currentOpenedTrafficFile] = finalList;

                          trafficFilesContent[currentOpenedTrafficFile] = finalList.join("\n");


                         //QMap<QString, QString> parsedCM1 = parseCM(readyCMList[0]);
                            for(unsigned i=0;i<10;i++)
                             readyCMList[i].clear();

                          // move changes to the global QString

                          p->refreshPreview();

                          // tutaj nowy szit

                          // przejscie po wszystkich widzetach i dodanie do listy
                         // trafficFilesContentLists[currentOpenedTrafficFile].append( ... );

                          // przejscie po liscie i dodanie do stringa
                          //new line pamietac

                          event->accept();


                       //   enteringMapView=false;
                          p->show();


                MainSaveWasClicked = true;

                counter_UE=1;
                offset_x=40;
                offset_x_2=40;
                small = false;

                break;


    case QMessageBox::Discard:
        // Don't Save was clicked
        //          enteringMapView=false;
        //          p->show();
        break;
    case QMessageBox::Cancel:
        // Cancel was clicked
                small = false;
        event->ignore();
        break;
    default:
        // should never be reached
        break;
    }
}

//parsowanie zapisanej listy

void Map_traffic::parseSavedList(){

    savedCM1List.clear();
    savedCM2List.clear();
    savedCM3List.clear();
    savedCM4List.clear();
    savedCM5List.clear();
    savedCM6List.clear();
    savedCM7List.clear();
    savedCM8List.clear();
    savedCM9List.clear();
    savedCM10List.clear();

    QStringList allSavedInVector = trafficFilesContentLists[currentOpenedTrafficFile];

    if(allSavedInVector.size() > 0){

        int indexCM1 = -2;
        int indexCM2 = -2;
        int indexCM3 = -2;
        int indexCM4 = -2;
        int indexCM5 = -2;
        int indexCM6 = -2;
        int indexCM7 = -2;
        int indexCM8 = -2;
        int indexCM9 = -2;
        int indexCM10 = -2;


        if(allSavedInVector.indexOf("Custom Model 1") != -1){
             indexCM1 = allSavedInVector.indexOf("Custom Model 1");
        }
        if(allSavedInVector.indexOf("Custom Model 2") != -1){
             indexCM2 = allSavedInVector.indexOf("Custom Model 2");
        }
        if(allSavedInVector.indexOf("Custom Model 3") != -1){
             indexCM3 = allSavedInVector.indexOf("Custom Model 3");
        }
        if(allSavedInVector.indexOf("Custom Model 4") != -1){
             indexCM4 = allSavedInVector.indexOf("Custom Model 4");
        }
        if(allSavedInVector.indexOf("Custom Model 5") != -1){
             indexCM5 = allSavedInVector.indexOf("Custom Model 5");
        }
        if(allSavedInVector.indexOf("Custom Model 6") != -1){
             indexCM6 = allSavedInVector.indexOf("Custom Model 6");
        }
        if(allSavedInVector.indexOf("Custom Model 7") != -1){
             indexCM7 = allSavedInVector.indexOf("Custom Model 7");
        }
        if(allSavedInVector.indexOf("Custom Model 8") != -1){
             indexCM8 = allSavedInVector.indexOf("Custom Model 8");
        }
        if(allSavedInVector.indexOf("Custom Model 9") != -1){
             indexCM9 = allSavedInVector.indexOf("Custom Model 9");
        }
        if(allSavedInVector.indexOf("Custom Model 10") != -1){
             indexCM10 = allSavedInVector.indexOf("Custom Model 10");
        }


//List 1


        if(indexCM1 != -2 && indexCM2 == -2 && indexCM3 == -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 == -2 && indexCM10 == -2){
            for(int i=indexCM1; i < allSavedInVector.size(); i++){

                savedCM1List.append(allSavedInVector.at(i));

            }
        }
        if(indexCM1 != -2 && indexCM2 != -2){

            for(int i=indexCM1; i < indexCM2; i++){

                savedCM1List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM1 != -2 && indexCM2 == -2 && indexCM3 != -2){

            for(int i=indexCM1; i < indexCM3; i++){

                savedCM1List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM1 != -2 && indexCM2 == -2 && indexCM3 == -2 && indexCM4 != -2){

            for(int i=indexCM1; i < indexCM4; i++){

                savedCM1List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM1 != -2 && indexCM2 == -2 && indexCM3 == -2 && indexCM4 == -2 && indexCM5 != -2){

            for(int i=indexCM1; i < indexCM5; i++){

                savedCM1List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM1 != -2 && indexCM2 == -2 && indexCM3 == -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 != -2){

            for(int i=indexCM1; i < indexCM6; i++){

                savedCM1List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM1 != -2 && indexCM2 == -2 && indexCM3 == -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 != -2){

            for(int i=indexCM1; i < indexCM7; i++){

                savedCM1List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM1 != -2 && indexCM2 == -2 && indexCM3 == -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 != -2){

            for(int i=indexCM1; i < indexCM8; i++){

                savedCM1List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM1 != -2 && indexCM2 == -2 && indexCM3 == -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 != -2){

            for(int i=indexCM1; i < indexCM9; i++){

                savedCM1List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM1 != -2 && indexCM2 == -2 && indexCM3 == -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 == -2 && indexCM10 != -2){

            for(int i=indexCM1; i < indexCM10; i++){

                savedCM1List.append(allSavedInVector.at(i));

            }

        }






// List 2
        if(indexCM2 != -2 && indexCM3 == -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 == -2 && indexCM10 == -2){
            for(int i=indexCM2; i < allSavedInVector.size(); i++){

                savedCM2List.append(allSavedInVector.at(i));

            }
        }


        if(indexCM2 != -2 && indexCM3 != -2){

            for(int i=indexCM2; i < indexCM3; i++){

                savedCM2List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM2 != -2 && indexCM3 == -2 && indexCM4 != -2){

            for(int i=indexCM2; i < indexCM4; i++){

                savedCM2List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM2 != -2 && indexCM3 == -2 && indexCM4 == -2 && indexCM5 != -2){

            for(int i=indexCM2; i < indexCM5; i++){

                savedCM2List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM2 != -2 && indexCM3 == -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 != -2){

            for(int i=indexCM2; i < indexCM6; i++){

                savedCM2List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM2 != -2 && indexCM3 == -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 != -2){

            for(int i=indexCM2; i < indexCM7; i++){

                savedCM2List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM2 != -2 && indexCM3 == -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 != -2){

            for(int i=indexCM2; i < indexCM8; i++){

                savedCM2List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM2 != -2 && indexCM3 == -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 != -2){

            for(int i=indexCM2; i < indexCM9; i++){

                savedCM2List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM2 != -2 && indexCM3 == -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 == -2 && indexCM10 != -2){

            for(int i=indexCM2; i < indexCM10; i++){

                savedCM2List.append(allSavedInVector.at(i));

            }

        }



//List 3

        if(indexCM3 != -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 == -2 && indexCM10 == -2){
            for(int i=indexCM3; i < allSavedInVector.size(); i++){

                savedCM3List.append(allSavedInVector.at(i));

            }
        }

        if(indexCM3 != -2 && indexCM4 != -2){

            for(int i=indexCM3; i < indexCM4; i++){

                savedCM3List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM3 != -2 && indexCM4 == -2 && indexCM5 != -2){

            for(int i=indexCM3; i < indexCM5; i++){

                savedCM3List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM3 != -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 != -2){

            for(int i=indexCM3; i < indexCM6; i++){

                savedCM3List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM3 != -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 != -2){

            for(int i=indexCM3; i < indexCM7; i++){

                savedCM3List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM3 != -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 != -2){

            for(int i=indexCM3; i < indexCM8; i++){

                savedCM3List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM3 != -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 != -2){

            for(int i=indexCM3; i < indexCM9; i++){

                savedCM3List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM3 != -2 && indexCM4 == -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 == -2 && indexCM10 != -2){

            for(int i=indexCM3; i < indexCM10; i++){

                savedCM3List.append(allSavedInVector.at(i));

            }

        }

//List 4

        if(indexCM4 != -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 == -2 && indexCM10 == -2){
            for(int i=indexCM4; i < allSavedInVector.size(); i++){

                savedCM4List.append(allSavedInVector.at(i));

            }
        }

        if(indexCM4 != -2 && indexCM5 != -2){

            for(int i=indexCM4; i < indexCM5; i++){

                savedCM4List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM4 != -2 && indexCM5 == -2 && indexCM6 != -2){

            for(int i=indexCM4; i < indexCM6; i++){

                savedCM4List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM4 != -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 != -2){

            for(int i=indexCM4; i < indexCM7; i++){

                savedCM4List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM4 != -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 != -2){

            for(int i=indexCM4; i < indexCM8; i++){

                savedCM4List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM4 != -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 != -2){

            for(int i=indexCM4; i < indexCM9; i++){

                savedCM4List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM4 != -2 && indexCM5 == -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 == -2 && indexCM10 != -2){

            for(int i=indexCM4; i < indexCM10; i++){

                savedCM4List.append(allSavedInVector.at(i));

            }

        }

//List 5

        if(indexCM5 != -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 == -2 && indexCM10 == -2){
            for(int i=indexCM5; i < allSavedInVector.size(); i++){

                savedCM5List.append(allSavedInVector.at(i));

            }
        }


        if(indexCM5 != -2 && indexCM6 != -2){

            for(int i=indexCM5; i < indexCM6; i++){

                savedCM5List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM5 != -2 && indexCM6 == -2 && indexCM7 != -2){

            for(int i=indexCM5; i < indexCM7; i++){

                savedCM5List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM5 != -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 != -2){

            for(int i=indexCM5; i < indexCM8; i++){

                savedCM5List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM5 != -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 != -2){

            for(int i=indexCM5; i < indexCM9; i++){

                savedCM5List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM5 != -2 && indexCM6 == -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 == -2 && indexCM10 != -2){

            for(int i=indexCM5; i < indexCM10; i++){

                savedCM5List.append(allSavedInVector.at(i));

            }

        }

//List 6

        if(indexCM6 != -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 == -2 && indexCM10 == -2){
            for(int i=indexCM6; i < allSavedInVector.size(); i++){

                savedCM6List.append(allSavedInVector.at(i));

            }
        }

        if(indexCM6 != -2 && indexCM7 != -2){

            for(int i=indexCM6; i < indexCM7; i++){

                savedCM6List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM6 != -2 && indexCM7 == -2 && indexCM8 != -2){

            for(int i=indexCM6; i < indexCM8; i++){

                savedCM6List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM6 != -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 != -2){

            for(int i=indexCM6; i < indexCM9; i++){

                savedCM6List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM6 != -2 && indexCM7 == -2 && indexCM8 == -2 && indexCM9 == -2 && indexCM10 != -2){

            for(int i=indexCM6; i < indexCM10; i++){

                savedCM6List.append(allSavedInVector.at(i));

            }

        }

//List 7

        if(indexCM7 != -2 && indexCM8 == -2 && indexCM9 == -2 && indexCM10 == -2){
            for(int i=indexCM7; i < allSavedInVector.size(); i++){

                savedCM7List.append(allSavedInVector.at(i));

            }
        }

        if(indexCM7 != -2 && indexCM8 != -2){

            for(int i=indexCM7; i < indexCM8; i++){

                savedCM7List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM7 != -2 && indexCM8 == -2 && indexCM9 != -2){

            for(int i=indexCM7; i < indexCM9; i++){

                savedCM7List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM7 != -2 && indexCM8 == -2 && indexCM9 == -2 && indexCM10 != -2){

            for(int i=indexCM7; i < indexCM10; i++){

                savedCM7List.append(allSavedInVector.at(i));

            }

        }

//List 8

        if(indexCM8 != -2 && indexCM9 == -2 && indexCM10 == -2){
            for(int i=indexCM8; i < allSavedInVector.size(); i++){

                savedCM8List.append(allSavedInVector.at(i));

            }
        }

        if(indexCM8 != -2 && indexCM9 != -2){

            for(int i=indexCM8; i < indexCM9; i++){

                savedCM8List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM8 != -2 && indexCM9 == -2 && indexCM10 != -2){

            for(int i=indexCM8; i < indexCM10; i++){

                savedCM8List.append(allSavedInVector.at(i));

            }

        }

//List 9

        if(indexCM9 != -2 && indexCM10 == -2){

            for(int i=indexCM9; i < allSavedInVector.size(); i++){

                savedCM9List.append(allSavedInVector.at(i));

            }

        }

        if(indexCM9 != -2 && indexCM10 != -2){

            for(int i=indexCM9; i < indexCM10; i++){

                savedCM9List.append(allSavedInVector.at(i));

            }

        }

//List 10

        if(indexCM10 != -2){
            for(int i=indexCM10; i < allSavedInVector.size(); i++){

                savedCM10List.append(allSavedInVector.at(i));

            }
        }
    }

   }





QMap<QString, QString>* Map_traffic::parseCM(QStringList customModelListToParse)
{
    QRegExp keyRegexPattern("\\:$");
    int currentIndex = 0;
    QMap<QString, QString> *parsedCM = new QMap<QString, QString>;
    foreach(QString customModelKey, customModelListToParse)
    {
        if(customModelKey.contains(keyRegexPattern))
        {
            if(customModelListToParse.length() - 1 > currentIndex + 1) {
                parsedCM->insert(customModelKey, customModelListToParse[currentIndex + 1]);
            }

        }
        currentIndex++;
    }
    return parsedCM;
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
    viewStatistics.close();
    viewStatistics.setParameters(statistics, appSettings);
    viewStatistics.show();
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

