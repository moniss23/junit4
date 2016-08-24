#ifndef UEGROUPDATA_H
#define UEGROUPDATA_H
#include <QString>
#include <QtXml>

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

class UEgroupData //TODO: it seems this class is not used, obsolete
{
public:
    UEgroupData(const QString &name, const QString &mapIndex);

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
    QString getElementType() const;
    void serializeToProjectFile();
    void serializeFromProjectFileOld(QByteArray rawData);
    void serializeFromProjectFileNew(QDomDocument xmlDocument);
    void serializeToScriptCommands() {}

private:
    UEgroupParams ue;
    QString mapIndexConst;
    QDomDocument xmlUePart;

};

#endif // UEGROUPDATA_H
