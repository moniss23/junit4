#ifndef APPGLOBALDATA_H
#define APPGLOBALDATA_H

#include <QString>
#include <QFile>
#include <QDataStream>


class AppGlobalData
{
public:
    AppGlobalData();

    QString getParameterFile() const;

    QString getProjectsDirectory() const;

    QString getProjectsFile() const;

    QString getSettingsFile() const;

    QString getProFileExt() const;


private:


    const QString proFileExt = ".proj";
    const QString settingsFile = "settings.dat";
    const QString projectsFile = "projects.dat";
    const QString projectsDirectory = "projects";
    const QString parameterFile = ":/RbFiles/parameters.rb";
};

#endif // APPGLOBALDATA_H
