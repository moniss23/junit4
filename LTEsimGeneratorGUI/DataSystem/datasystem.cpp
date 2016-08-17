#include "datasystem.h"
#include "Data/appglobaldata.h"
#include "Data/trafficfiledata.h"

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

bool DataSystem::isProjectNameUsed(QString projectName) {
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

    auto it = std::find_if(project->trafficFilesList.begin(), project->trafficFilesList.end(),
                           [&fileName](const auto &traffic)->bool{return traffic.fileName==fileName;});

    if(it == project->trafficFilesList.end()) {
        emit errorInData("Cannot find right traffic file");
        return;
    }

    project->trafficFilesList.erase(it);
    emit currentProjectChanged(*project);
}

QString DataSystem::getDefaultParametersFileContent()
{
    QFile param_template(":/RbFiles/parameters.rb");
    param_template.open(QIODevice::ReadOnly);
    QTextStream param_template_str(&param_template);
    QString content = param_template_str.readAll();
    param_template.close();

    return content;
}

void DataSystem::createNewProject(const QString &projectName, const QString &directory) {

    if(isProjectNameUsed(projectName)) {
        emit errorInData("Name already in use. Choose another one.");
        return;
    }

    QString dir = directory.isEmpty() ? getDefaultNewProjectDir() : directory;

    QString param_template_content = getDefaultParametersFileContent();

    Project new_project;
    new_project.name = projectName;
    new_project.fullpath = dir;
    new_project.parametersFile.fileName = "Parameters.rb";
    new_project.parametersFile.content = param_template_content;
    projects.push_back(new_project);

    setProjectName(projectName); //TODO: Should not be needed in good architecture

    emit currentProjects(projects);

    saveProjectsFile();
}

void DataSystem::setNewDirForProjects(const QString &location)
{
    if(location=="") {
        QMessageBox(QMessageBox::Critical,"No directory specified!","You must specify the directory.",QMessageBox::Ok).exec();
        emit updateSettingsView(location);
        return;
    }
    if(location!="<default>") {
        QDir new_dir(location);
        if(!new_dir.exists()) {
            QMessageBox(QMessageBox::Critical,"Directory does not exist!","Selected directory does not seem to exist.\nAre you sure you selected it right?",QMessageBox::Ok).exec();
            emit updateSettingsView(location);
            return;
        }
    }
    appGlobalData.setDefaultNewProjectsPath(location);
    emit updateSettingsView(location);
}

void DataSystem::addToProject_TrafficFile(const QString &ProjectName, const QString& fileName)
{
    auto proj = findProjectByName(ProjectName);

    if(proj == nullptr) {
        emit errorInData("Error while adding traffic file");
        return;
    }

    TrafficFileData trafficData;
    trafficData.fileName = fileName.isEmpty() ? generateUniqueTrafficFilename(*proj) : fileName;
    proj->trafficFilesList.push_back(trafficData);
    emit currentProjectChanged(*proj);

    saveProjectsFile();
}

QString DataSystem::generateUniqueTrafficFilename(const Project& project)
{
    for(unsigned i=0; i<UINT_MAX; ++i) {
        QString filename = "Traffic_" + QString::number(i) + ".rb";
        if(std::find_if(project.trafficFilesList.begin(), project.trafficFilesList.end(),
        [&filename](const auto &td)->bool {return td.fileName==filename;}) == project.trafficFilesList.end()) {
            return filename;
        }
    }

    emit errorInData("Cannot add more traffic files");
    return QString();
}

void DataSystem::deleteProject(const QString projectName)
{
    projects.erase(findProjectByName(projectName));
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

/*******************
 GETTERS AND SETTERS
 *******************/

QString DataSystem::getProjectName() const {
    return projectName;
}
void DataSystem::setProjectName(const QString &value) {
    projectName = value;
}

QString DataSystem::getDefaultNewProjectDir() const {
    return appGlobalData.getDefaultNewProjectsPath();
}
void DataSystem::setDefaultNewProjectDir(const QString &value) {
    appGlobalData.setDefaultNewProjectsPath(value);
}

AppGlobalData DataSystem::getAppGlobalData() const {
    return appGlobalData;
}
