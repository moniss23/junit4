#ifndef MAPDATA_H
#define MAPDATA_H
#include <dataelementsinterface.h>
#include <QObject>
#include <QList>
#include <QtXml>

#include <Maps/Traffic/DataObjects/celldata.h>
#include <Maps/Traffic/DataObjects/handoverdata.h>
#include <Maps/Traffic/CustomModel/custommodels.h>
#include <Maps/Traffic/UeParameters/uegroupdata.h>
#include <CommonConstans/common_constans.h>
#include <ProjectReaderWriter/projectreaderwriter.h>

#define maxHandoverCount 53 //maximum number of possible handovers
#define handoverPhraseSigns 13 //number of signs in handover name phrase

struct ParametersLists
{
    QList<CellData*> activeCellList;
    QList<HandoverData*> handoverList;
};

class MapData : public DataElementsInterface
{

public:
    QString mapName;
    ParametersLists parameterLists;
    QList<UEgroupData*> UEList;
    QList<Custommodels*> CustomModelsList;
    QDomDocument mapXmlDocument;
    bool readyToSave;
    bool largeMap;

public:
    MapData(const QString &name,bool whichMap, AppSettings *appSettings);
    ~MapData(){}
    void addUEGroup(const QString &UEName);
    void deleteUEGroup(const QString &UEName);
    void fillActiveCellList();
    void fillHandoverList();
    void fillUEList(QDomDocument xmlDocument);
    void includeXmlPartsFromObjects(){}

    //-------------Overriden methods from interface-------------
    QString getElementType() const override;
    void serializeToProjectFile() override {}
    void serializeFromProjectFileOld(QByteArray rawData) override;
    void serializeFromProjectFileNew(QDomDocument xmlDocument) override;
    void serializeToScriptCommands() override {}
    void setProjectReaderWriter(ProjectReaderWriter *value);

private:
    ProjectReaderWriter* projectReaderWriter;
    AppSettings *appSettings;

};

#endif // MAPDATA_H
