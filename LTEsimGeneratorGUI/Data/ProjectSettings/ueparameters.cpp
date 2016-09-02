#include "ueparameters.h"

#include <QBuffer>
#include <QDataStream>

UeParameters::UeParameters()
{

}
UeParameters::~UeParameters()
{

}

QString UeParameters::getElementType() const
{
    return QString("UeParameters");
}

QByteArray UeParameters::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << startUeComponent << name << managers << pluginFilterPath <<
              ucToolIp << ucToolcIds << ueNetworkCapability <<
              ueKeyDerivationAlgorithm << ueKey << ueOp;
    return serializedData.buffer();
}

void UeParameters::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> startUeComponent >> name >> managers >> pluginFilterPath >>
              ucToolIp >> ucToolcIds >> ueNetworkCapability >>
              ueKeyDerivationAlgorithm >> ueKey >> ueOp;
}
