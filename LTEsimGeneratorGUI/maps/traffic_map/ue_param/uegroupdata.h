#ifndef UEGROUPDATA_H
#define UEGROUPDATA_H
#include <QString>
#include <dataelementsinterface.h>
#include <QtXml>
#include <common_constans.h>

class UEgroupData : DataElementsInterface
{
public:
    UEgroupData(const QString &name, const QString &mapIndex) : ueName(name), mapIndexConst(mapIndex){}

    //getters and setters
    QString getUEname() const;

    QString getMapIndex() const;

    QString getPairsName() const;
    void setPairsName(const QString &pairsNameCurrent);

    int getAmountOfPairs();
    void setAmountOfPairs(int amountOfPairsCurrent);

    QString getMobilityModel() const;
    void setMobilityModel(const QString &mobilityModelCurrent);

    QString getCSbehaviourMode() const;
    void setCSbehaviourMode(const QString &CSbehaviourModeCurrent);

    QString getPSbehaviourMode() const;
    void setPSbehaviourMode(const QString &PSbehaviorModeCurrent);

    QString getUEtype() const;
    void setUEtype(const QString &ueTypeCurrent);

    QString getArea() const;
    void setArea(const QString &areaCurrent);

    QString getElementType() const override {}
    void serializeToProjectFile() const override {}
    void serializeFromProjectFileOld(QByteArray rawData) override {}
    void serializeFromProjectFileNew(QByteArray rawData) override {}
    void serializeToScriptCommands() override {}
    QByteArray readDataFromProj() override;


private:
    QString ueName;
    QString mapIndexConst;
    QString pairsName;
    int amountOfPairs;
    QString mobilityModel;
    QString CSbehaviourMode;
    QString PSbehaviorMode;
    QString ueType;
    QString area;
};

#endif // UEGROUPDATA_H
