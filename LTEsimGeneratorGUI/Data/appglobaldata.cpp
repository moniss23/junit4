#include "appglobaldata.h"

AppGlobalData::AppGlobalData():
    defaultNewProjectsPath("./Projects")
{

}

void AppGlobalData::setDefaultNewProjectsPath(const QString &value)
{
  defaultNewProjectsPath = value;
}

const QString AppGlobalData::getDefaultNewProjectsPath() const
{
  return defaultNewProjectsPath;
}

/*
 *
 * Getters and Setters
 *
 */

QString AppGlobalData::getParameterFile() const
{
    return parameterFile;
}

QString AppGlobalData::getTrafficFile() const
{
    return trafficFile;
}

QString AppGlobalData::getProjectsDirectory() const
{
    return projectsDirectory;
}

QString AppGlobalData::getProjectsFile() const
{
    return projectsFile;
}

QString AppGlobalData::getSettingsFile() const
{
    return settingsFile;
}

QString AppGlobalData::getProFileExt() const
{
    return proFileExt;
}

QString AppGlobalData::getRbFileExt() const
{
    return rbFileExt;
}

QString AppGlobalData::getElementType() const
{
    return QString("AppGlobalData");
}

QByteArray AppGlobalData::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << defaultNewProjectsPath;

    return serializedData.buffer();
}

void AppGlobalData::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);

    stream >> defaultNewProjectsPath;
}
