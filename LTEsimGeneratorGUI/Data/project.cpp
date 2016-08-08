#include "project.h"

QString Project::getElementType() const
{
    return QString("Project");
}

QByteArray Project::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << name << fullpath << rbOutputDir << chosenMapType;

    return serializedData.buffer();
}

void Project::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> name >> fullpath >> rbOutputDir >> chosenMapType;
}
