#include "mapdata.h"

MapData::MapData(const QString &name , bool whichMap, AppSettings *appSettings) : appSettings(appSettings)
{
    mapName = name;
    readyToSave = false;
    largeMap = whichMap;

    projectReaderWriter = new ProjectReaderWriter(appSettings);


}

void MapData::addUEGroup(const QString &UEName)
{
 (void) UEName;
}

void MapData::fillActiveCellList()
{
    QString cellName = "cell";
    QString centerName = "Center";
    QString index;

    QByteArray tempArray = projectReaderWriter->readDataFromProj(beginningOfCellSector,endOfCellSector);

    QString fileContent(tempArray);
    int rows,columns;

    if(largeMap == true)
    {
        rows = largeMapRows;
        columns = largeMapColumns;
    }
    else
    {
        rows = smallMapRows;
        columns = smallMapColumns;
    }

    for(int i = 1; i <= rows; i++)
    {
        for(int j = 1; j <= columns; j++)
        {

            index.clear();
            index.append(QString::number(i) );
            index.append(QString::number(j) );

            if(fileContent.contains(cellName) )
            {
                CellData* cell = new CellData(cellName + index,centerName + index, appSettings);
                parameterLists.activeCellList.append(cell);
            }
        }
    }

}

void MapData::fillHandoverList()
{
    QString handoverName = "Handover";
    QString index;
    QByteArray tempArray = projectReaderWriter->readDataFromProj(beginningOfHandoverSector,endOfHandoverSector);

    QString fileContent(tempArray);

    for(int i = 0; i < maxHandoverCount; i++)
    {

        if(fileContent.contains(handoverName) )
        {
            int start = fileContent.indexOf(handoverName);

            for(int i = 8; i < handoverPhraseSigns; i++)
            {
                index.append(fileContent.at(start + i) );
            }

            fileContent.remove(0,start + 1);
            HandoverData* handover = new HandoverData(handoverName + index, appSettings);
            parameterLists.handoverList.append(handover);

        }
    }

}

QString MapData::getElementType() const
{
    return QString("Traffic Map");
}

void MapData::serializeFromProjectFileOld(QByteArray rawData)
{
    (void) rawData;
}

void MapData::serializeFromProjectFileNew(QDomDocument xmlDocument)
{
    (void) xmlDocument;
}

void MapData::setProjectReaderWriter(ProjectReaderWriter *value)
{
    projectReaderWriter = value;
}
