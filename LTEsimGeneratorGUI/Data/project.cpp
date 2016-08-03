#include "project.h"

QString Project::getElementType() const
{
    return QString("Project");
}

QByteArray Project::serializeData()
{
    QByteArray serializedData;
    QDataStream stream(serializedData);
    stream << name << fullpath << rbOutputDir << chosenMapType;

    return serializedData;
}

void Project::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> name >> fullpath >> rbOutputDir >> chosenMapType;
}
