#ifndef HANDOVERDATA_H
#define HANDOVERDATA_H
#include <QString>
#include <dataelementsinterface.h>


#include <CommonConstans/common_constans.h>
#include <ProjectReaderWriter/projectreaderwriter.h>
#include <AppSettings/appsettings.h>

struct HandoverParams
{
    QString handoverName;
    QRect handoverArea;
};

class HandoverData : public DataElementsInterface

{
public:

    HandoverData(QString name, AppSettings *appSettings);

//----------------------------Getters------------------------------------------------

    QString getHandoverName() const;
    int getSouthBoundary() const;
    int getNorthBoundary() const;
    int getWestBoundary() const;
    int getEastBoundary() const;
    HandoverParams getHandoverParams() const;

//----------------------------Setters------------------------------------------------

    void setHandoverName(const QString &name);
    void setSouthBoundary(int south);
    void setNorthBoundary(int north);
    void setWestBoundary(int west);
    void setEastBoundary(int east);
    void setHandoverParams(const HandoverParams &params);

    HandoverParams parseDataFromList(QStringList &paramsList);

//-------------------Overriden methods from DataElemetsInterface----------------------

    QString getElementType() const override;
    void serializeToProjectFile() override {}
    void serializeFromProjectFileOld(QByteArray rawData) override;
    void serializeFromProjectFileNew(QDomDocument xmlDocument) override;
    void serializeToScriptCommands() override {}

//-------------------Overriden methods from DataElemetsInterface----------------------

    void setProjectReaderWriter(ProjectReaderWriter *value);

private:
    HandoverParams handoverParams;
    ProjectReaderWriter* projectReaderWriter;

    AppSettings *appSettings;

};

//------------------Serialize/Deserialize operators for future-------------------------

QDataStream &operator<<(QDataStream& out,HandoverParams &handover);
QDataStream &operator>>(QDataStream& in,HandoverParams &handover);

#endif // HANDOVERDATA_H
