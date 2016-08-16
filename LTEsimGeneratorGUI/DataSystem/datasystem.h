#ifndef DATASYSTEM_H
#define DATASYSTEM_H

#include <QString>
#include <QDir>
#include <QTextStream>
#include <QFile>
#include <QStringList>
#include <QListWidgetItem>

#include "Data/project.h"
#include "Data/filemanager.h"
#include "Data/appglobaldata.h"

class DataSystem : public QObject
{
    Q_OBJECT

public:
    DataSystem();
    ~DataSystem();

    QVector<Project> projects;

signals:
    void currentProjects(const QVector<Project> &projects);
    void currentProjectChanged(const Project &current);
    void errorInData(const QString& errorDescription);
    void returnProject(const Project& project);

public slots:

    void LoadAppData();
    //----------PROJECTS---------------//

    Project* findProjectByName(const QString &);
    void importProject(const QString &ProjectDirectory);
    void createNewProject(const QString &projectName, const QString & directory);
    void deleteProject(const QString);
    void setProjectName(const QString &value); //TODO: Should not be needed in good architecture
    //--------SETTINGS CLASS--------//
    void setNewDirForProjects(const QString& location);
    void saveProjectsFile();
    //----------PROJECT TRAFFIC FILES--//
    void addToProject_TrafficFile(const QString &ProjectName, const QString &fileName);
    void findProject(const QString& projectName);
    void checkAndRenameIfFilenameUnique(const QString &filename, const QString& oldFilename, const QString& projectName);



public:
    QString GetDefaultParametersFileContent(); //TODO: move to private when You can

    QString getProjectDir(QString project_name);

    bool projectNameTaken(QString projectName);

    //Those functions need implementation.
    //-------------------------------------------------------------
    bool isProjectNameValid(const QString& projectName);
    bool isProjectDirValid(const QString& projectDir);
    //-------------------------------------------------------------
    //-------------------------------------------------------------

    QString getProjectName() const;

    QString getDefaultNewProjectDir() const;
    void setDefaultNewProjectDir(const QString &value);

    QString readParametersFile();

    AppGlobalData getAppGlobalData() const;


     /************************************
     *          PRIVATE METHODS          *
     ************************************/
private:
    void projectsFileSetup();
    void projectsDirSetup();
    void removeDirectoryRecursively(QString dir_name);

    void loadProjectsFile();

    QString generateUniqueTrafficFilename(const Project& project);

private:
    FileManager fileManager;
    AppGlobalData appGlobalData;

    QString projectName;
};

#endif // DATASYSTEM_H
