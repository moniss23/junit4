#include "appsettings.h"
#include "Data/appglobaldata.h"
#include "Data/trafficdata.h"

AppSettings::AppSettings()
{
    settingsFileSetup();
    projectsFileSetup();
    projectsDirSetup();
}

AppSettings::~AppSettings() {
}

void AppSettings::LoadAppData() {
    loadProjectsFile();
    emit currentProjects(projects);
}

void AppSettings::loadProjectsFile() {
    QDataStream dataStream(fileManager.readFromFile(appGlobalData.getProjectsFile()));

    int projectsAmount;
    dataStream >> projectsAmount;

    while(projectsAmount--) {
        QByteArray singleProjectData;
        dataStream >> singleProjectData;

        Project p;
        p.deserializeData(singleProjectData);
        projects.push_back(p);
    }
}

void AppSettings::saveProjectsFile() {
    QBuffer rawDataBuff;
    rawDataBuff.open(QBuffer::WriteOnly);
    QDataStream dataStream(&rawDataBuff);

    dataStream << projects.size();

    for(auto &&elem : projects) {
        QByteArray singleProjectData = elem.serializeData();
        dataStream << singleProjectData;
    }

    fileManager.writeToFile(appGlobalData.getProjectsFile(), rawDataBuff.buffer());
}

// Read the content of the project file, decrypt it and split into a list
QStringList AppSettings::read_project_file(QString project_name, QString dir){

    dir = (dir == "<default>") ? appGlobalData.getProjectsDirectory() : dir;

    QFile project_file(dir + "/" + project_name + "/" + project_name + appGlobalData.getProFileExt());
    project_file.open(QIODevice::ReadOnly);
    QDataStream project_file_stream(&project_file);

    QString projFileContent;
    project_file_stream >> projFileContent;

    project_file.close();
    return projFileContent.split('\n');
}

// encrypt the project data and write it into the file
void AppSettings::write_project_file(QString project_name, QString project_content, QString dir){

    dir = (dir == "<default>") ? appGlobalData.getProjectsDirectory() : dir;

    QFile project_file(dir + "/" + project_name + "/" + project_name + appGlobalData.getProFileExt());
    project_file.open(QIODevice::WriteOnly);
    QDataStream project_file_stream(&project_file);

    project_file_stream << project_content;
    project_file.close();
}

void AppSettings::write_settings_file(){
    QFile file(appGlobalData.getSettingsFile());
    file.open(QIODevice::WriteOnly);
    QDataStream file_str(&file);

    // #TUBYLCI
    QString content(defaultNewProjectDir);
    file_str << content;
    file.close();
}

void AppSettings::read_settings_file(){
    QFile file(appGlobalData.getSettingsFile());
    file.open(QIODevice::ReadOnly);

    QString settingsFileContent;
    QDataStream file_str(&file);
    file_str >> settingsFileContent;
    file.close();

    QStringList content_list(settingsFileContent.split("\n") );

    defaultNewProjectDir = content_list[0];
}

// Returns pointer to a Project element or nullptr if not found
Project* AppSettings::findProjectByName(const QString &projectName) {
    auto it = std::find_if(std::begin(projects), std::end(projects),
                           [&projectName](const Project &p)->bool {return p.name==projectName; });

    return it != std::end(projects) ? it : nullptr;
}


QString AppSettings::get_project_dir(QListWidgetItem *item)
{
    auto proj = findProjectByName(item->text());
    return proj == nullptr ? QString() : proj->fullpath;
}

QString AppSettings::get_project_dir(QString project_name)
{
    auto proj = findProjectByName(project_name);
    return proj == nullptr ? QString() : proj->fullpath;
}

bool AppSettings::projectNameTaken(QString projectName)
{
    auto proj = findProjectByName(projectName);
    return proj != nullptr;
}

// check if the settings file exists, create it if it doesn't
void AppSettings::settingsFileSetup() {
    settings_file.setFileName(appGlobalData.getSettingsFile());
    if(!settings_file.exists()){
        setDefaultNewProjectDir("<default>");
        write_settings_file();
    } else {
        read_settings_file();
    }
}

// check if the projects file exists, create it if it doesn't
void AppSettings::projectsFileSetup() {
    projects_file.setFileName(appGlobalData.getProjectsFile());

    if(!projects_file.exists()) {
        projects_file.open(QIODevice::WriteOnly);
        QTextStream str(&projects_file);
        str << "0";
        projects_file.close();
    }
}

// create project dir if doesn't exist
void AppSettings::projectsDirSetup() {
    project_dir.mkdir(appGlobalData.getProjectsDirectory());
}

QString AppSettings::getProjectDirectory(const QString &projectName) {
    auto proj = findProjectByName(projectName);
    return proj == nullptr ? QString() : proj->fullpath;
}

// recursively remove entire directory and its content
void AppSettings::removeDirectoryRecursively(QString dir_name){
    QDir directory("projects/" + dir_name);
    directory.removeRecursively();
}

QString AppSettings::readParametersFile()
{
    QFile param_template(appGlobalData.getProjectsFile());
    param_template.open(QIODevice::ReadOnly);
    QTextStream param_template_str(&param_template);
    param_template.close();

    return param_template_str.readAll();
}

AppGlobalData AppSettings::getAppGlobalData() const
{
    return appGlobalData;
}

/*
 * Slots
 *
 */

QString AppSettings::GetDefaultParametersFileContent()
{
    QFile param_template(":/RbFiles/parameters.rb");
    param_template.open(QIODevice::ReadOnly);
    QTextStream param_template_str(&param_template);
    QString content = param_template_str.readAll();
    param_template.close();

    return content;
}

void AppSettings::createNewProject(const QString &projectName, const QString &directory) {

    if(projectNameTaken(projectName)) {
        emit errorInData("Name already in use. Choose another one.");
        return;
    }

    QString dir = directory.isEmpty() ? getDefaultNewProjectDir() : directory;

    QString param_template_content = GetDefaultParametersFileContent();

    Project new_project;
    new_project.name = projectName;
    new_project.fullpath = dir;
    new_project.parametersFile.fileName = "Parameters.rb";
    new_project.parametersFile.content = param_template_content;
    projects.push_back(new_project);

    QDir projectDir;
    projectDir.setPath(dir=="<default>" ? appGlobalData.getProjectsDirectory() : dir);
    projectDir.mkdir(projectName);

    QString project_content;
    project_content += "<default>\n";
    project_content += "normal\n";
    project_content += "Parameters.rb\n";
    project_content += "0\n";
    project_content += QString::number(param_template_content.split("\n").size()) + "\n";
    project_content += param_template_content + "\n";

    write_project_file(projectName, project_content,
                       dir=="<default>" ? getProjectDirectory(projectName) : dir);

    // store the project name in a global variable for use by other files and methods
    setProjectName(projectName); //TODO: Should not be needed in good architecture

    emit currentProjects(projects);

    saveProjectsFile();
}


/*
 *
 * Getters and Setters
 *
 */

QString AppSettings::getProjectFile() const
{
    return projectFile;
}

void AppSettings::setProjectFile(const QString &value)
{
    projectFile = value;
}

QString AppSettings::getProjectName() const
{
    return projectName;
}

void AppSettings::setProjectName(const QString &value)
{
    projectName = value;
}

void AppSettings::setNewDirForProjects(const QString& location)
{
    appGlobalData.setDefaultNewProjectsPath(location);
}

void AppSettings::addToProject_TrafficFile(const QString &ProjectName, const QString& fileName)
{
    auto proj = findProjectByName(ProjectName);

    if(proj == nullptr) {
        emit errorInData("Error while adding traffic file");
        return;
    }

    TrafficData trafficData;
    trafficData.fileName = fileName.isEmpty() ? generateUniqueTrafficFilename(*proj) : fileName;
    it->trafficFilesList.push_back(trafficData);
    emit currentProjectChanged(*it);
}

QString AppSettings::generateUniqueTrafficFilename(const Project& project)
{
    QString filename;
    bool filename_unique = false;
    int i = 0;

    while(!filename_unique){
        filename="Traffic_"+QString::number(i)+".rb";
        filename_unique=true;
        for(auto &&it : project.trafficFilesList) {
            if(filename == it.fileName){
                filename_unique=false;
                break;
            }
        }
        i++;
    }
    return filename;
}

QDir AppSettings::getProjectDir() const
{
    return projectDir;
}

void AppSettings::setProjectDir(const QDir &value)
{
    projectDir = value;
}

QString AppSettings::getDefaultNewProjectDir() const
{
    return appGlobalData.getDefaultNewProjectsPath();
}

void AppSettings::setDefaultNewProjectDir(const QString &value)
{
    appGlobalData.setDefaultNewProjectsPath(value);
}

QDir AppSettings::getProject_dir() const
{
    return project_dir;
}

void AppSettings::setProject_dir(const QDir &value)
{
    project_dir = value;
}
void AppSettings::deleteProject(const QString projectName)
{
    removeDirectoryRecursively(projectName);
    auto proj = findProjectByName(projectName);

    projects.erase(proj);
    emit currentProjects(projects);

    saveProjectsFile();
}

void AppSettings::findProject(const QString &projectName)
{
    auto proj = findProjectByName(projectName);

    if(proj == nullptr) { return; }
    emit currentProjectChanged(*proj);
}

void AppSettings::checkAndRenameIfFilenameUnique(const QString &newFilename, const QString &oldFilename, const QString& projectName) {

    if(newFilename == oldFilename) {
        emit errorInData("Filename not changed, can't rename.");
        return;
    }

    auto proj = findProjectByName(projectName);


    if(proj == nullptr) {
        emit errorInData("Can't find right project while renaming a file");
        return;
    }

    if(proj->parametersFile.fileName == oldFilename) {
        proj->parametersFile.fileName = newFilename;
        emit currentProjectChanged(*proj);
        return;
    } else {
        for(auto &&iterator : proj->trafficFilesList) {
            if(iterator.fileName == newFilename) {
                emit errorInData("Name already in use. Choose another one");
                return;
            }
        }
        for(auto &&trafficfile : proj->trafficFilesList) {
            if(trafficfile.fileName == oldFilename) {
                trafficfile.fileName = newFilename;
                emit currentProjectChanged(*proj);
                return;
            }
        }
    }
    emit errorInData("Can't find right trafficFile to rename!");
}
