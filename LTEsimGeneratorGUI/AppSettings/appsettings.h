#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>
#include <QDir>
#include <QTextStream>
#include <QFile>
#include <QStringList>
#include <QListWidgetItem>

#include "ManagementWindow/Encryption/encryption.h"
#include "Data/project.h"
#include "Data/appglobaldata.h"


class AppSettings : public QObject
{
    Q_OBJECT

public:
    AppSettings();
    ~AppSettings();

    std::vector<Project> projects;

signals:
    void currentProjects(const std::vector<Project> &projects);
    void errorInData(const QString& errorDescription);

public slots:

    void LoadAppData();
    void createNewProject(const QString &projectName, const QString & directory);
    void importProject(const QString &ProjectDirectory);
    void deleteProject(const QString);


public:

    QString getProjectDirectory(const QString &projectName);

    void setMapType(const QString& projectName, const QString& mapType);

    void write_project_file(QString project_name, QString project_content, QString dir);
    QStringList read_project_file(QString project_name, QString dir);

    void write_settings_file();

    QString get_project_dir(QListWidgetItem* item);
    QString get_project_dir(QString project_name);

    void write_projects_file();
    void read_projects_file();//TODO: remove ?

    bool projectNameTaken(QString projectName);

    //Those functions need implementation.
    //-------------------------------------------------------------
    bool isProjectNameValid(const QString& projectName);
    bool isProjectDirValid(const QString& projectDir);
    //-------------------------------------------------------------
    //-------------------------------------------------------------

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

    QDir getProject_dir() const;
    void setProject_dir(const QDir &value);

    QFile getProjects_file() const;
    void setProjects_file(const QFile &value);

    QFile getSettings_file() const;
    void setSettings_file(const QFile &value);

    QString readParametersFile();

    AppGlobalData getAppGlobalData() const;


     /************************************
     *          PRIVATE METHODS          *
     ************************************/
private:
    void settingsFileSetup();
    void projectsFileSetup();
    void projectsDirSetup();
    void readProjectsFile();
    void testProjectsObtainedFromTheFile();
    void traverseProjectsListAndAddProjectIfNotFound();
    void removeDirectoryRecursively(QString dir_name);
    void read_settings_file();

private:

    AppGlobalData appGlobalData;

    QFile project_file;
    QFileInfoList projects_dir_content;
    QStringList projects_file_content;
    int projectC_file;
    QDir project_dir;
    QFile settings_file;
    QFile projects_file;
    QString defaultNewProjectDir;
    QString parametersFile;
    QString projectFile;
    QString projectName;
    QDir projectDir;
};

#endif // APPSETTINGS_H
