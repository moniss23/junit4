#ifndef DATASYSTEM_H
#define DATASYSTEM_H

#include <QString>
#include <QDir>
#include <QTextStream>
#include <QFile>
#include <QStringList>
#include <QListWidgetItem>
#include <QMessageBox>

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
    void updateSettingsView(const QString& path);

public slots:

    void LoadAppData();
    void saveProjectsFile();
    void setNewDirForProjects(const QString& location);

    void findProject(const QString& projectName);
    void createNewProject(const QString &projectName, const QString & directory);
    void deleteProject(const QString);
    void setProjectName(const QString &value); //TODO: Should not be needed in good architecture

    void addToProject_TrafficFile(const QString &ProjectName, const QString &fileName);
    void removeFile_TrafficFile(const QString& ProjectName, const QString& fileName);

    void checkAndRenameIfFilenameUnique(const QString &filename, const QString& oldFilename, const QString& projectName);

public:
    QString getProjectName() const;
    QString getProjectDir(QString project_name);

    bool isProjectNameUsed(QString projectName);

    //Those functions need implementation.
    //-------------------------------------------------------------
    bool isProjectNameValid(const QString& projectName);
    bool isProjectDirValid(const QString& projectDir);
    //-------------------------------------------------------------

    QString getDefaultNewProjectDir() const;
    void setDefaultNewProjectDir(const QString &value);

    AppGlobalData getAppGlobalData() const;

private:
    QString projectName;
    FileManager fileManager;
    AppGlobalData appGlobalData;

    void loadProjectsFile();
    void projectsFileSetup();
    QString getDefaultParametersFileContent();

    Project* findProjectByName(const QString &projectName);
    QString generateUniqueTrafficFilename(Project *project);
};

#endif // DATASYSTEM_H
