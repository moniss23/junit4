#include "celldata.h"


CellData::CellData(const QString &nameCell, const QString &nameCenter)
{
    cellParams.cellName = nameCell;
    cellParams.centerParams.centerName = nameCenter;
    QByteArray data = ProjectReaderWriter::readDataFromProj(beginningOfCellSector,endOfCellSector);
    serializeFromProjectFileOld(data);
}


//----------------------------Getters------------------------------------------------

QString CellData::getCellName() const
{
    return cellParams.cellName;
}

int CellData::getPci() const
{
    return cellParams.pci;
}

int CellData::getPosition_X() const
{
    return cellParams.cellPosition.x();
}

int CellData::getPosition_Y() const
{
    return cellParams.cellPosition.y();
}

int CellData::getEarfcnDl() const
{
    return cellParams.earfcnDl;
}

float CellData::getTransmitPower() const
{
    return cellParams.transmitPower;
}

float CellData::getUlNoiseAndInterference() const
{
    return cellParams.ulNoiseAndInterference;
}

CellParams CellData::getCellParams() const
{
    return cellParams;
}

QString CellData::getCenterName() const
{
    return cellParams.centerParams.centerName;
}

int CellData::getSouthCellBoundary() const
{
    return cellParams.centerParams.centerArea.bottom();
}

int CellData::getNorthCellBoundary() const
{
    return cellParams.centerParams.centerArea.top();
}

int CellData::getWestCellBoundary() const
{
    return cellParams.centerParams.centerArea.left();
}

int CellData::getEastCellBoundary() const
{
    return cellParams.centerParams.centerArea.right();
}

CenterParams CellData::getCenterParams() const
{
    return cellParams.centerParams;
}


//----------------------------Setters------------------------------------------------


void CellData::setCellName(const QString &cell)
{
    this->cellParams.cellName = cell;
}

void CellData::setPci(int pci)
{
    this->cellParams.pci = pci;
}

void CellData::setPosition_X(int positionX)
{
    this->cellParams.cellPosition.setX(positionX);
}

void CellData::setPosition_Y(int positionY)
{
    this->cellParams.cellPosition.setY(positionY);
}

void CellData::setEarfcnDl(int earfcndl)
{
    this->cellParams.earfcnDl = earfcndl;
}

void CellData::setTransmitPower(float power)
{
    this->cellParams.transmitPower = power;
}

void CellData::setUlNoiseAndInterference(float ulNoise)
{
    this->cellParams.ulNoiseAndInterference = ulNoise;
}

void CellData::setCenterName(const QString &center)
{
    this->cellParams.centerParams.centerName = center;
}

void CellData::setSouthCellBoundary(int south)
{
    this->cellParams.centerParams.centerArea.setBottom(south);
}

void CellData::setNorthCellBoundary(int north)
{
    this->cellParams.centerParams.centerArea.setTop(north);
}

void CellData::setWestCellBoundary(int west)
{
    this->cellParams.centerParams.centerArea.setLeft(west);
}

void CellData::setEastCellBoundary(int east)
{
    this->cellParams.centerParams.centerArea.setRight(east);
}

void CellData::setCellParams(const CellParams &params)
{
    this->cellParams = params;
}

void CellData::setCenterParams(const CenterParams &params)
{
    this->cellParams.centerParams = params;
}


CellParams CellData::parseCellDataFromList(QStringList &paramsList)
{
    CellParams loadedCellParams;
    QString searchCellName = ":cell => \"" + cellParams.cellName;

    for(int i = 0; i < paramsList.size(); i++)
    {

        if(paramsList[i].contains(searchCellName) )
        {

            //cutting needed phrase from list
            loadedCellParams.cellName = paramsList[i].section('"',1,1);

            for(int j = cellPciOffset; j < numberOfCellParams; j++)
            {
                paramsList[i + j].remove(0,8);
                paramsList[i + j] = paramsList[i + j].section(' ',2,2);
                paramsList[i + j].remove(",");
            }

            loadedCellParams.pci = paramsList[i + cellPciOffset].toInt();
            loadedCellParams.cellPosition.setX(paramsList[i + cellXPositionOffset].toInt() );
            loadedCellParams.cellPosition.setY(paramsList[i + cellYPositionOffset].toInt() );
            loadedCellParams.earfcnDl = paramsList[i + cellEarfnDlOffset].toInt();
            loadedCellParams.transmitPower = paramsList[i + cellTransmitPowerOffset].toFloat();
            loadedCellParams.ulNoiseAndInterference = paramsList[i + cellUlNoiseOffset].toFloat();

        }
    }

    return loadedCellParams;
}

CenterParams CellData::parseCenterDataFromList(QStringList &paramsList)
{
    CenterParams loadedCenterParams;
    QString searchCenterName = ":area => \"" + cellParams.centerParams.centerName;

    for(int i = 0; i < paramsList.size(); i++)
    {

        if(paramsList[i].contains(searchCenterName) )
        {

            //cutting needed phrase from list
            loadedCenterParams.centerName = paramsList[i].section('"',1,1);

            for(int j = centerSouthBoundaryOffset; j < numberOfCenterParams; j++)
            {
                paramsList[i + j].remove(0,8);
                paramsList[i + j] = paramsList[i + j].section(' ',2,2);
                paramsList[i + j].remove(",");
            }

            loadedCenterParams.centerArea.setBottom(paramsList[i + centerSouthBoundaryOffset].toInt() );
            loadedCenterParams.centerArea.setTop(paramsList[i + centerNorthBoundaryOffset].toInt() );
            loadedCenterParams.centerArea.setLeft(paramsList[i + centerWestBoundaryOffset].toInt() );
            loadedCenterParams.centerArea.setRight(paramsList[i + centerEastBoundaryOffset].toInt() );

        }
    }

    return loadedCenterParams;

}


//---------------Overriden methods from DataElementsInterface---------------------

QString CellData::getElementType() const
{
    return QString("Cell");
}

void CellData::serializeFromProjectFileOld(QByteArray rawData)
{
    CellParams loadedCellParams;
    CenterParams loadedCenterParams;
    QString projectData(rawData);
    QStringList projectDataList = projectData.split('\n');
    loadedCellParams = parseCellDataFromList(projectDataList);
    loadedCenterParams = parseCenterDataFromList(projectDataList);
    setCellParams(loadedCellParams);
    setCenterParams(loadedCenterParams);
}

QDataStream &operator<<(QDataStream &out, CellParams &cell)
{
    out << cell.cellName << cell.cellPosition << cell.earfcnDl
        << cell.pci << cell.transmitPower << cell.ulNoiseAndInterference
        << cell.centerParams.centerName << cell.centerParams.centerArea;
    return out;
}

QDataStream &operator>>(QDataStream &in, CellParams &cell)
{
    in >> cell.cellName >> cell.cellPosition >> cell.earfcnDl
       >> cell.pci >> cell.transmitPower >> cell.ulNoiseAndInterference
       >> cell.centerParams.centerName >> cell.centerParams.centerArea;
    return in;
}
