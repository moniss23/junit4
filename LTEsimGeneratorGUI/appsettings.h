#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>
#include <QDir>

class AppSettings
{
public:
    AppSettings();
    ~AppSettings();



    QString getParametersFile() const;
    void setParametersFile(const QString &value);

    QString getProjectFile() const;
    void setProjectFile(const QString &value);

    QString getProjectName() const;
    void setProjectName(const QString &value);

    QDir getProjectDir() const;
    void setProjectDir(const QDir &value);

private:
    QString parametersFile;
    QString projectFile;
    QString projectName;
    QDir projectDir;
};

#endif // APPSETTINGS_H
