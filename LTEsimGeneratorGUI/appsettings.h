#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>
#include <QDir>
#include "management_window/encryption.h"

class AppSettings
{
public:
    AppSettings();
    ~AppSettings();

    void write_settings_file();
    void read_settings_file();

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

private:

    QString defaultNewProjectDir;
    QString parametersFile;
    QString projectFile;
    QString projectName;
    QDir projectDir;
};

#endif // APPSETTINGS_H
