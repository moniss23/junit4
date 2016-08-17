#include "parametersfiledata.h"

#include <QBuffer>
#include <QDataStream>

QString ParametersFileData::getElementType() const
{
    return QString("ParametersFileData");
}

QByteArray ParametersFileData::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << fileName << content;

    return serializedData.buffer();
}

void ParametersFileData::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> fileName >> content;
}
