#include "cell.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <maps/parameters_map/mapwindow.h>
#include <qdebug.h>

extern QString parametersFileContent;
extern QStringList parametersFileContentList;
extern QString savedParametersFileContent;
extern std::vector<QString> trafficFilesContent;
extern std::vector<QString> savedTrafficFilesContent;
extern bool paramFileChanged;
extern bool paramFileModified;
extern std::vector<bool> trafficFilesChanged;
extern std::vector<bool> trafficFilesModified;

extern MapWindow* map_w;

Cell::Cell(QString name)
{
   cell = name;
   setParams();
}
Cell::Cell()
{

}

Cell::~Cell()
{

}
//------------Getters--------------------------------
QString Cell::getCell(){
    return cell;
}
QString Cell::getSite(){
    return site;
}
QString Cell::getPci(){
    return QString::number(pci);
}
QString Cell::getPosition_X(){
    return QString::number(position_X);
}
QString Cell::getPosition_Y(){
    return QString::number(position_Y);
}
QString Cell::getEarfcnDl(){
    return QString::number(earfcnDl);
}
QString Cell::getTransmitPower(){
    return QString::number(transmitPower);
}
QString Cell::getUlNoiseAndInterference(){
    return QString::number(ulNoiseAndInterference);
}
//----------------Setters---------------------------
void Cell::setCell(QString c){
    cell = cell + " " + c;
}
void Cell::setSite(QString s){
    site = s;
}
void Cell::setPci(QString p){
     pci = p.toInt();
}
void Cell::setPosition_X(QString px){
        position_X = px.toInt();
}
void Cell::setPosition_Y(QString py){
        position_Y = py.toInt();
}
void Cell::setEarfcnDl(QString e){
     earfcnDl = e.toInt();
}
void Cell::setTransmitPower(QString t){
     transmitPower = t.toFloat();
}
void Cell::setUlNoiseAndInterference(QString u){
     ulNoiseAndInterference = u.toFloat();
}
QString Cell::getCell_new_name() const
{
    return cell_new_name;
}

void Cell::setCell_new_name(const QString &value)
{
    cell_new_name = value;
    qDebug() <<"Nowa nazwa celli: "  + cell_new_name;
}


//--------------Funcion-------------------------------------------------------

//QString* Cell::setParams(){
//    QString name_search = ":cell => \"" +cell + "\""+",";

//    QString fileName = ":/file/parameters.rb";
//    QString text1;
//    QFile file1(fileName);
//    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
//        return NULL;              // if coudn't open file: stop loading file
//    text1.clear();
//    QTextStream stream(&file1);
//    QString text_search;
//    while(text_search != name_search && !stream.atEnd()){
//        text1 = stream.readLine();
//        text_search = text1.trimmed();
//   }
//    tabParams = new QString [8];
//    for (int i=0; i<8; i++)
//    {
//        tabParams[i] = text_search;
//        text1 = stream.readLine();
//        text_search = text1.trimmed();
//    }

//    QStringList list;
//    for (int i=0; i<8; i++)
//    {
//        list = tabParams[i].split(" ");
//        tabParams[i]= list[2];
//        tabParams[i].remove(QChar('"'));
//        tabParams[i].remove(QChar(','));
//    }
//    cell = tabParams[0];
//    site = tabParams[1];
//    pci = tabParams[2].toInt();
//    position_X = tabParams[3].toInt();
//    position_Y = tabParams[4].toInt();
//    earfcnDl = tabParams[5].toInt();
//    transmitPower = tabParams[6].toFloat();
//    ulNoiseAndInterference = tabParams[7].toFloat();

//    return tabParams;
//}

QString* Cell::setParams(){
//    QString name_search = ":cell => \"" +cell + "\""+",";
    QString name_search = ":cell => \"" +cell;
    qDebug() <<" nazwa szukanej celi: " +cell;
    tabParams = new QString [8];
    for( int i=0; i<parametersFileContentList.size(); i++){
        if(parametersFileContentList[i].contains(name_search)){
            tabParams[0] = parametersFileContentList[i].trimmed();
            tabParams[1] = parametersFileContentList[i+1].trimmed();
            tabParams[2] = parametersFileContentList[i+2].trimmed();
            tabParams[3] = parametersFileContentList[i+3].trimmed();
            tabParams[4] = parametersFileContentList[i+4].trimmed();
            tabParams[5] = parametersFileContentList[i+5].trimmed();
            tabParams[6] = parametersFileContentList[i+6].trimmed();
            tabParams[7] = parametersFileContentList[i+7].trimmed();
        }
    }

    QStringList list;
    for (int i=0; i<8; i++)
    {
        list = tabParams[i].trimmed().split(" ", QString::SkipEmptyParts);
        if (list.size() > 3){
            tabParams[i] = list[2];
            list[3].remove(",");
            cell_new_name = list[3].remove("\"");
        }
        else tabParams[i]= list[2];
        tabParams[i].remove(QChar('"'));
        tabParams[i].remove(QChar(','));
    }
    cell = tabParams[0];
    site = tabParams[1];
    pci = tabParams[2].toInt();
    position_X = tabParams[3].toInt();
    position_Y = tabParams[4].toInt();
    earfcnDl = tabParams[5].toInt();
    transmitPower = tabParams[6].toFloat();
    ulNoiseAndInterference = tabParams[7].toFloat();


    return tabParams;
}

void Cell::resetParams()
{
    QString name_search = ":cell => \"" +cell;
    QString fileName = ":/file/parameters.rb";
    QFile file1(fileName);

    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
        return;              // if coudn't open file: stop loading file

    QString text1="";
    QTextStream stream(&file1);
    QList <QString> fileParameters;
    while(!stream.atEnd()){
        text1 = stream.readLine();
        fileParameters << text1.trimmed();
   }

    tabParams = new QString [8];
    for( int i=0; i<fileParameters.size(); i++){
        if(fileParameters[i].contains(name_search)){
            tabParams[0] = fileParameters[i].trimmed();
            tabParams[1] = fileParameters[i+1].trimmed();
            tabParams[2] = fileParameters[i+2].trimmed();
            tabParams[3] = fileParameters[i+3].trimmed();
            tabParams[4] = fileParameters[i+4].trimmed();
            tabParams[5] = fileParameters[i+5].trimmed();
            tabParams[6] = fileParameters[i+6].trimmed();
            tabParams[7] = fileParameters[i+7].trimmed();
        }
    }

    QStringList list;
    for (int i=0; i<8; i++)
    {
        list = tabParams[i].trimmed().split(" ", QString::SkipEmptyParts);
        if (list.size() > 3){
            tabParams[i] = list[2];
            list[3].remove(",");
            cell_new_name = list[3].remove("\"");
        }
        else tabParams[i]= list[2];
        tabParams[i].remove(QChar('"'));
        tabParams[i].remove(QChar(','));
    }
    cell_new_name = "";
    cell = tabParams[0];
    chBox->setText(cell);
    site = tabParams[1];
    pci = tabParams[2].toInt();
    position_X = tabParams[3].toInt();
    position_Y = tabParams[4].toInt();
    earfcnDl = tabParams[5].toInt();
    transmitPower = tabParams[6].toFloat();
    ulNoiseAndInterference = tabParams[7].toFloat();
}

bool Cell::wasThereChanges()
{
  return false;
}
