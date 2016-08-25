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
#include "Data/appglobaldata.h"
#include "Data/Managers/filemanager.h"
#include "Data/Managers/scriptparsermanager.h"
#include "Data/ProjectSettings/datageneratorsettings.h"

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
    void spawnWindow_ProjectMng();
    void update_RB_FilesLocation(const QString& location);

public slots:

    void LoadAppData();
    void saveProjectsFile();
    void setGlobalLocationForNewProjects(const QString& location);
    void set_RB_FilesLocationForProject(const QString& projectName, const QString& location);

    void findProject(const QString& projectName);
    void createNewProject(const QString &projectName, const QString & directory);
    void deleteProject(const QString);

    void addToProject_TrafficFile(const QString &ProjectName, const QString &fileName);
    void removeFile_TrafficFile(const QString& ProjectName, const QString& fileName);
    void checkAndRenameIfFilenameUnique(const QString &filename, const QString& oldFilename, const QString& projectName);

    void setDefaultTrafficFileContent(const QString &projectName, const QString &trafficName);
    void setDefaultParametersFileContent(const QString &projectName);

    void updateFileContent(const QString& projectName, const QString& fileName, const QString& content);
    void spawnWindow_ProjectManagement();

    void updateDataGeneratorSettings(const DataGeneratorSettings &dataGeneratorSettings, const QString &projectName);
    void updateSgwSettings(const SgwSettings &sgwSettings,const QString &projectName);
    void updateUCToolSettings(const UCToolSettings & ucToolSettings, const QString &projectName);
public:
    bool isProjectNameUsed(QString projectName);
    QString getDefaultNewProjectDir() const;
    AppGlobalData getAppGlobalData() const;

private:
    AppGlobalData       appGlobalData;

    FileManager         fileManager;
    ScriptParserManager scriptParserManager;

    void loadProjectsFile();
    void projectsFileSetup();
    QString getDefaultParametersFileContent();
    QString getDefaultTrafficFileContent();

    Project* findProjectByName(const QString &projectName);
    QString generateUniqueTrafficFilename(Project *project);
};

#endif // DATASYSTEM_H
