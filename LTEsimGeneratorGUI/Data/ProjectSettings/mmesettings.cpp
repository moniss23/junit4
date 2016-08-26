#include "mmesettings.h"
#include <QBuffer>
#include <QDataStream>
MmeSettings::MmeSettings()
{

}
MmeSettings::~MmeSettings(){}
QString MmeSettings::getElementType() const
{
    return QString("MmeSettings");
}

QByteArray MmeSettings::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << simulatedCoreNetwork << name << tais << numberOfMme << uris << pluginFilterPath;
    return serializedData.buffer();
}

void MmeSettings::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> simulatedCoreNetwork >> name >> tais >> numberOfMme >> uris >> pluginFilterPath;
}
