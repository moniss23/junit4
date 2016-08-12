#ifndef UEGROUPDATA_H
#define UEGROUPDATA_H
#include <QString>
#include <dataelementsinterface.h>
#include <QtXml>
#include <ProjectReaderWriter/projectreaderwriter.h>
#include <CommonConstans/common_constans.h>
struct UEgroupParams
{
    QString ueName;
    QString pairsName;
    int amountOfPairs;
    QString mobilityModel;
    QString csBehaviorMode;
    QString psBehaviorMode;
    QString ueType;
    QString area;
};

class UEgroupData : DataElementsInterface
{
public:
    UEgroupData(const QString &name, const QString &mapIndex, DataSystem *appSettings);

    //getters
    QString getUEname() const;
    QString getMapIndex() const;
    int getAmountOfPairs();
    QString getPairsName() const;
    QString getMobilityModel() const;
    QString getCSbehaviourMode() const;
    QString getPSbehaviourMode() const;
    QString getUEtype() const;
    QString getArea() const;

    //setters
    void setPairsName(const QString &pairsNameCurrent);
    void setAmountOfPairs(int amountOfPairsCurrent);
    void setMobilityModel(const QString &mobilityModelCurrent);
    void setCSbehaviourMode(const QString &csBehaviorModeCurrent);
    void setPSbehaviourMode(const QString &psBehaviorModeCurrent);
    void setUEtype(const QString &ueTypeCurrent);
    void setArea(const QString &areaCurrent);

    //interface methods
    QString getElementType() const override;
    void serializeToProjectFile() override;
    void serializeFromProjectFileOld(QByteArray rawData) override;
    void serializeFromProjectFileNew(QDomDocument xmlDocument) override;
    void serializeToScriptCommands() override {}

    void setProjectReaderWriter(ProjectReaderWriter *value);

private:
    UEgroupParams ue;
    QString mapIndexConst;
    QDomDocument xmlUePart;
    ProjectReaderWriter* projectReaderWriter;

    DataSystem *appSettings;
};

#endif // UEGROUPDATA_H
