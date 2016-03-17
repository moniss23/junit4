#ifndef CELLDATA_H
#define CELLDATA_H
#include <QString>
#include <common_constans.h>
#include <dataelementsinterface.h>


struct CenterParams
{
    QString centerName;
    QRect centerArea;
};
struct CellParams
{
    QString cellName;
    QPoint cellPosition;
    float transmitPower;
    float ulNoiseAndInterference;
    int pci;
    int earfcnDl;
    CenterParams centerParams;
};

class CellData : public DataElementsInterface
{

public:

    CellData(const QString &nameCell,const QString &nameCenter);

    //----------------------------Getters------------------------------------------------

    QString getCellName() const;
    int getPci() const;
    int getPosition_X() const;
    int getPosition_Y() const;
    int getEarfcnDl() const;
    float getTransmitPower() const;
    float getUlNoiseAndInterference() const;

    QString getCenterName() const;
    int getSouthCellBoundary() const;
    int getNorthCellBoundary() const;
    int getWestCellBoundary() const;
    int getEastCellBoundary() const;
    CellParams getCellParams() const;
    CenterParams getCenterParams() const;


    //----------------------------Setters------------------------------------------------

    void setCellName(const QString &cell);
    void setPci(int pci);
    void setPosition_X(int positionX);
    void setPosition_Y(int positionY);
    void setEarfcnDl(int earfcndl);
    void setTransmitPower(float power);
    void setUlNoiseAndInterference(float ulNoise);
    void setCellParams(const CellParams &params);

    void setCenterName(const QString &center);
    void setSouthCellBoundary(int south);
    void setNorthCellBoundary(int north);
    void setWestCellBoundary(int west);
    void setEastCellBoundary(int east);
    void setCenterParams(const CenterParams &params);

    CellParams parseCellDataFromList(QStringList &paramsList);
    CenterParams parseCenterDataFromList(QStringList &paramsList);



    //-------------------Overriden methods from DataElemetsInterface----------------------

    QString getElementType() const override;
    void serializeToProjectFile() override {}
    void serializeFromProjectFileOld(QByteArray rawData) override;
    void serializeFromProjectFileNew(QByteArray rawData) override {}
    void serializeToScriptCommands() override {}

private:
    CellParams cellParams;
};

QDataStream &operator<<(QDataStream& out,CellParams &cell);
QDataStream &operator>>(QDataStream& in,CellParams &cell);
#endif // CELLDATA_H
