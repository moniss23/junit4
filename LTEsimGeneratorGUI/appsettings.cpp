#include "appsettings.h"

AppSettings::AppSettings() {

}

AppSettings::~AppSettings() {

}

QString AppSettings::getParametersFile() const
{
    return parametersFile;
}

void AppSettings::setParametersFile(const QString &value)
{
    parametersFile = value;
}

QString AppSettings::getProjectFile() const
{
    return projectFile;
}

void AppSettings::setProjectFile(const QString &value)
{
    projectFile = value;
}

QString AppSettings::getProjectName() const
{
    return projectName;
}

void AppSettings::setProjectName(const QString &value)
{
    projectName = value;
}

QDir AppSettings::getProjectDir() const
{
    return projectDir;
}

void AppSettings::setProjectDir(const QDir &value)
{
    projectDir = value;
}
