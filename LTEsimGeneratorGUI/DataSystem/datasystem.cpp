#include "datasystem.h"
#include "Data/appglobaldata.h"
#include "Data/trafficdata.h"

DataSystem::DataSystem() {
    projectsFileSetup();
}

DataSystem::~DataSystem() {
}

void DataSystem::LoadAppData() {
    loadProjectsFile();
    emit currentProjects(projects);
}

void DataSystem::loadProjectsFile() {
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

void DataSystem::saveProjectsFile() {
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

// Returns pointer to a Project element or nullptr if not found
Project* DataSystem::findProjectByName(const QString &projectName) {
    auto it = std::find_if(std::begin(projects), std::end(projects),
                           [&projectName](const Project &p)->bool {return p.name==projectName; });

    return it != std::end(projects) ? it : nullptr;
}


bool DataSystem::projectNameTaken(QString projectName) {
    auto proj = findProjectByName(projectName);
    return proj != nullptr;
}

QString DataSystem::getProjectDir(QString project_name) {
    auto proj = findProjectByName(project_name);
    return proj == nullptr ? QString() : proj->fullpath;
}

// check if the projects file exists, create it if it doesn't
void DataSystem::projectsFileSetup() {
    QFile projects_file(appGlobalData.getProjectsFile());

    if(!projects_file.exists()) {
        projects_file.open(QIODevice::WriteOnly);
        QTextStream str(&projects_file);
        str << "0";
        projects_file.close();
    }
}

// recursively remove entire directory and its content
void DataSystem::removeDirectoryRecursively(QString dir_name){
    QDir directory("projects/" + dir_name);
    directory.removeRecursively();
}

QString DataSystem::readParametersFile()
{
    QFile param_template(appGlobalData.getProjectsFile());
    param_template.open(QIODevice::ReadOnly);
    QTextStream param_template_str(&param_template);
    param_template.close();

    return param_template_str.readAll();
}

/*
 * Slots
 *
 */

void DataSystem::removeFile_TrafficFile(const QString& ProjectName, const QString& fileName) {
    auto project = findProjectByName(ProjectName);

    if(project == nullptr) {
        emit errorInData("Cannot find right Project");
        return;
    }

    auto it = std::find_if(project->trafficFilesList.begin(), project->trafficFilesList.end(),[&fileName](const TrafficData& traffic)-> bool{
         return traffic.fileName == fileName;
    });
    if(it == project->trafficFilesList.end()) {
        emit errorInData("Cannot find right traffic file");
        return;
    }

    project->trafficFilesList.erase(it);
    emit currentProjectChanged(*project);
}

QString DataSystem::GetDefaultParametersFileContent()
{
    QFile param_template(":/RbFiles/parameters.rb");
    param_template.open(QIODevice::ReadOnly);
    QTextStream param_template_str(&param_template);
    QString content = param_template_str.readAll();
    param_template.close();

    return content;
}

void DataSystem::createNewProject(const QString &projectName, const QString &directory) {

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

    QString project_content;
    project_content += "<default>\n";
    project_content += "normal\n";
    project_content += "Parameters.rb\n";
    project_content += "0\n";
    project_content += QString::number(param_template_content.split("\n").size()) + "\n";
    project_content += param_template_content + "\n";

    setProjectName(projectName); //TODO: Should not be needed in good architecture

    emit currentProjects(projects);

    saveProjectsFile();
}

void DataSystem::importProject(const QString &project_directory) {
    (void) project_directory;
    // TODO: Implement adjusted to a new logic
}

void DataSystem::addToProject_TrafficFile(const QString &ProjectName, const QString& fileName)
{
    auto proj = findProjectByName(ProjectName);

    if(proj == nullptr) {
        emit errorInData("Error while adding traffic file");
        return;
    }

    TrafficData trafficData;
    trafficData.fileName = fileName.isEmpty() ? generateUniqueTrafficFilename(*proj) : fileName;
    proj->trafficFilesList.push_back(trafficData);
    emit currentProjectChanged(*proj);

    saveProjectsFile();
}

QString DataSystem::generateUniqueTrafficFilename(const Project& project)
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

void DataSystem::deleteProject(const QString projectName)
{
    removeDirectoryRecursively(projectName);
    auto proj = findProjectByName(projectName);

    projects.erase(proj);
    emit currentProjects(projects);

    saveProjectsFile();
}

void DataSystem::findProject(const QString &projectName)
{
    auto proj = findProjectByName(projectName);

    if(proj == nullptr) { return; }
    emit currentProjectChanged(*proj);
}

void DataSystem::checkAndRenameIfFilenameUnique(const QString &newFilename, const QString &oldFilename, const QString& projectName) {

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

/* ___ GETTERS & SETTERS ___ */

QString DataSystem::getDefaultNewProjectDir() const {
    return appGlobalData.getDefaultNewProjectsPath();
}
void DataSystem::setDefaultNewProjectDir(const QString &value) {
    appGlobalData.setDefaultNewProjectsPath(value);
}

QString DataSystem::getProjectName() const {
    return projectName;
}
void DataSystem::setProjectName(const QString &value) {
    projectName = value;
}

AppGlobalData DataSystem::getAppGlobalData() const {
    return appGlobalData;
}

void DataSystem::setNewDirForProjects(const QString &location) {
    appGlobalData.setDefaultNewProjectsPath(location);
}
