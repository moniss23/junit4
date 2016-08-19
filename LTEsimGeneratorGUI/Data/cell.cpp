#include "Data/cell.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <Maps/Parameters/MapWindow/mapwindow.h>

extern QStringList parametersFileContentList;

Cell::Cell() {}
Cell::~Cell() {}

Cell::Cell(const QString &name)
{
    cell = name;
    setParams();
}

QVector<QString> Cell::setParams() {

    QVector<QString> cellParams(8);
    QString rbCellPattern = ":cell => \"" + cell;

    for(int i=0; i<parametersFileContentList.size(); i++) {

        if(parametersFileContentList[i].contains(rbCellPattern)) {
            cellParams[0] = parametersFileContentList[i].trimmed();
            cellParams[1] = parametersFileContentList[i+1].trimmed();
            cellParams[2] = parametersFileContentList[i+2].trimmed();
            cellParams[3] = parametersFileContentList[i+3].trimmed();
            cellParams[4] = parametersFileContentList[i+4].trimmed();
            cellParams[5] = parametersFileContentList[i+5].trimmed();
            cellParams[6] = parametersFileContentList[i+6].trimmed();
            cellParams[7] = parametersFileContentList[i+7].trimmed();
            break;
        }
    }

    for(int i=0; i<cellParams.size(); i++) {
        cellParams[i] = cellParams[i].split(' ', QString::SkipEmptyParts)[2];
        cellParams[i].remove(QChar('"'));
        cellParams[i].remove(QChar(','));
    }

    cell_new_name = "";
    cell = cellParams[0];
    site = cellParams[1];
    pci = cellParams[2].toInt();
    position_X = cellParams[3].toInt();
    position_Y = cellParams[4].toInt();
    earfcnDl = cellParams[5].toInt();
    transmitPower = cellParams[6].toFloat();
    ulNoiseAndInterference = cellParams[7].toFloat();

    return cellParams;
}

void Cell::resetParams()
{
    QString rbCellPattern = ":cell => \"" + cell;

    // TODO: DataSystem::getDefaultParamContent() ?
    QFile paramTemplateFile(":/RbFiles/parameters.rb");
    if(!paramTemplateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {return;}

    QTextStream stream(&paramTemplateFile);
    QList <QString> parametersTemplateContentList;
    while(not stream.atEnd()) {parametersTemplateContentList << stream.readLine().trimmed();}

    QVector<QString> cellParams(8);
    for(int i=0; i<parametersTemplateContentList.size(); i++) {

        if(parametersTemplateContentList[i].contains(rbCellPattern)) {
            cellParams[0] = parametersTemplateContentList[i].trimmed();
            cellParams[1] = parametersTemplateContentList[i+1].trimmed();
            cellParams[2] = parametersTemplateContentList[i+2].trimmed();
            cellParams[3] = parametersTemplateContentList[i+3].trimmed();
            cellParams[4] = parametersTemplateContentList[i+4].trimmed();
            cellParams[5] = parametersTemplateContentList[i+5].trimmed();
            cellParams[6] = parametersTemplateContentList[i+6].trimmed();
            cellParams[7] = parametersTemplateContentList[i+7].trimmed();
            break;
        }
    }

    for (int i=0; i<cellParams.size(); i++) {
        cellParams[i] = cellParams[i].split(" ", QString::SkipEmptyParts)[2];
        cellParams[i].remove(QChar('"'));
        cellParams[i].remove(QChar(','));
    }

    cell = cellParams[0];
    site = cellParams[1];
    pci = cellParams[2].toInt();
    position_X = cellParams[3].toInt();
    position_Y = cellParams[4].toInt();
    earfcnDl = cellParams[5].toInt();
    transmitPower = cellParams[6].toFloat();
    ulNoiseAndInterference = cellParams[7].toFloat();

    chBox->setText(cell);
}

bool Cell::wasThereChanges() {
    return false;
}

/**** GETTERS && SETTERS ****/

QString Cell::getCell() {return cell;}
void Cell::setCell(const QString &c) {cell = cell + " " + c; }

QString Cell::getSite() {return site;}
void Cell::setSite(const QString &s) {site = s;}

QString Cell::getPci() {return QString::number(pci);}
void Cell::setPci(const QString &p) {pci = p.toInt();}

QString Cell::getPosition_X() {return QString::number(position_X);}
void Cell::setPosition_X(const QString &p_x) {position_X = p_x.toInt();}

QString Cell::getPosition_Y() {return QString::number(position_Y);}
void Cell::setPosition_Y(const QString &p_y) {position_Y = p_y.toInt();}

QString Cell::getEarfcnDl() {return QString::number(earfcnDl);}
void Cell::setEarfcnDl(const QString &e) {earfcnDl = e.toInt();}

QString Cell::getTransmitPower() {return QString::number(transmitPower);}
void Cell::setTransmitPower(const QString &t) {transmitPower = t.toFloat();}

QString Cell::getUlNoiseAndInterference() {return QString::number(ulNoiseAndInterference);}
void Cell::setUlNoiseAndInterference(const QString &u) {ulNoiseAndInterference = u.toFloat();}

QString Cell::getCell_new_name() const { return cell_new_name; }
void Cell::setCell_new_name(const QString &value) { cell_new_name = value; }
