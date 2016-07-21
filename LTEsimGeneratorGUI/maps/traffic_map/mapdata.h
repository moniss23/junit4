#ifndef MAPDATA_H
#define MAPDATA_H
#include <maps/traffic_map/data_objects/celldata.h>
#include <maps/traffic_map/data_objects/handoverdata.h>
#include <maps/traffic_map/custom_model/custommodels.h>
#include <maps/traffic_map/ue_param/uegroupdata.h>
#include <common_constans.h>
#include <dataelementsinterface.h>
#include <maps/projectreaderwriter.h>
#include <QObject>
#include <QList>
#include <QtXml>

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
    void addUEGroup(const QString &UEName){}
    void deleteUEGroup(const QString &UEName){}
    void fillActiveCellList();
    void fillHandoverList();
    void fillUEList(QDomDocument xmlDocument){}
    void includeXmlPartsFromObjects(){}

    //-------------Overriden methods from interface-------------
    QString getElementType() const override;
    void serializeToProjectFile() override {}
    void serializeFromProjectFileOld(QByteArray rawData) override {}
    void serializeFromProjectFileNew(QDomDocument xmlDocument) override {}
    void serializeToScriptCommands() override {}
    void setProjectReaderWriter(ProjectReaderWriter *value);

private:
    ProjectReaderWriter* projectReaderWriter;
    AppSettings *appSettings;

};

#endif // MAPDATA_H
