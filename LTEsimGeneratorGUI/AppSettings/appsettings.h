#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>
#include <QDir>
#include <ManagementWindow/Encryption/encryption.h>
#include <QTextStream>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QListWidgetItem>

class AppSettings
{
public:
    AppSettings();
    ~AppSettings();

    std::vector<Project> projects;

    std::vector<QListWidgetItem*> loadSettings();
    void checkIfExistAndCreateSettingsFile();
    void checkIfExistAndCreateProjectsFile();
    void checkIfExistAndCreateProjectsDir();
    void readProjectsFile();
    std::vector<QListWidgetItem*> testProjectsObtainedFromTheFile();
    void traverseProjectsListAndAddProjectIfNotFound();

    QString getProjectDirectory(const QString &projectName);

    void write_settings_file();
    void read_settings_file();

    QStringList read_project_file(QString project_name, QString dir);
    void write_project_file(QString project_name, QString project_content, QString dir);

    void write_projects_file();
    void read_projects_file();

    bool projectNameTaken(QString projectName);

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

    QDir getProject_dir() const;
    void setProject_dir(const QDir &value);

    QFile getProjects_file() const;
    void setProjects_file(const QFile &value);

    QFile getSettings_file() const;
    void setSettings_file(const QFile &value);

private:

    QFile project_file;
    QFileInfoList projects_dir_content;
    QStringList projects_file_content;
    int projectC_file;
    QDir project_dir;
    QFile settings_file;
    QFile projects_file;
    const QString proFileExt = ".proj";
    QString defaultNewProjectDir;
    QString parametersFile;
    QString projectFile;
    QString projectName;
    QDir projectDir;
};

#endif // APPSETTINGS_H
