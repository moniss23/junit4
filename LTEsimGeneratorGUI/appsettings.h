#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>
#include <QDir>
#include "management_window/encryption.h"
#include <QTextStream>

class AppSettings
{
public:
    AppSettings();
    ~AppSettings();

    std::vector<Project> projects;

    void write_settings_file();
    void read_settings_file();

    QStringList read_project_file(QString project_name, QString dir);
    void write_project_file(QString project_name, QString project_content, QString dir);

    void write_projects_file();
    void read_projects_file();

    QString getParametersFile() const;
    void setParametersFile(const QString &value);

    QString getProjectFile() const;
    void setProjectFile(const QString &value);

    QString getProjectName() const;
    void setProjectName(const QString &value);

    QDir getProjectDir() const;
    void setProjectDir(const QDir &value);

    QString getDefaultNewProjectDir() const;
    void setDefaultNewProjectDir(const QString &value);

    QString getProFileExt() const;

private:

    const QString proFileExt = ".proj";
    QString defaultNewProjectDir;
    QString parametersFile;
    QString projectFile;
    QString projectName;
    QDir projectDir;
};

#endif // APPSETTINGS_H
