#ifndef APPGLOBALDATA_H
#define APPGLOBALDATA_H

#include <QString>
#include <QStringList>

class AppGlobalData
{
public:
    AppGlobalData();

    void setDefaultNewProjectsPath(const QString &value);
    const QString getDefaultNewProjectsPath() const;

    QString getParameterFile() const;

    QString getTrafficFile() const;

    QString getProjectsDirectory() const;

    QString getProjectsFile() const;

    QString getSettingsFile() const;

    QString getProFileExt() const;

    QString getRbFileExt() const;

private:

    QString defaultNewProjectsPath;
    const QString proFileExt = ".proj";
    const QString rbFileExt = ".rb";
    const QString settingsFile = "settings.dat";
    const QString projectsFile = "projects.dat";
    const QString projectsDirectory = "projects";
    const QString parameterFile = ":/RbFiles/ParametersTemplate.rb";
    const QString trafficFile = ":/RbFiles/TrafficTemplate.rb";
};

#endif // APPGLOBALDATA_H
