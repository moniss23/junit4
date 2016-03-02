#ifndef HANDOVERDATA_H
#define HANDOVERDATA_H
#include <QString>
#include <QDir>
#include <common_constans.h>
#include <dataelementsinterface.h>

struct HandoverParams
{
   QString handoverName;
   QRect handoverArea;
};

class HandoverData : public DataElementsInterface
{
public:

    HandoverData(QString name);

    //----------------------------Getters------------------------------------------------

    QString getHandoverName();
    QString getSouthBoundary();
    QString getNorthBoundary();
    QString getWestBoundary();
    QString getEastBoundary();
    HandoverParams getHandoverParams();

    //----------------------------Setters------------------------------------------------

    void setHandoverName(QString name);
    void setSouthBoundary(int south);
    void setNorthBoundary(int north);
    void setWestBoundary(int west);
    void setEastBoundary(int east);
    void setHandoverParams(HandoverParams params);


    HandoverParams parseDataFromList(QStringList paramsList);

//-------------------Overriden methods from DataElemetsInterface----------------------

    QString getElementType() const override;
    QByteArray serializeToProjectFile() const override {}
    void serializeFromProjectFileOld(QByteArray rawData) override;
    void serializeFromProjectFileNew(QByteArray rawData) override {}
    void serializeToScriptCommands() override {}
    QByteArray readDataFromProj() override;


private:
    HandoverParams handoverParams;

};

//------------------Serialize/Deserialize operators for future-------------------------

QDataStream &operator<<(QDataStream& out,HandoverParams &handover);
QDataStream &operator>>(QDataStream& in,HandoverParams &handover);

#endif // HANDOVERDATA_H
