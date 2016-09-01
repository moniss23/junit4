#include "datasystem.h"
#include "Data/appglobaldata.h"
#include "Data/Objects/trafficfiledata.h"
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

/*********
 * SLOTS *
 *********/

void DataSystem::updateFileContent(const QString &projectName, const QString &fileName, const QString &content) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project");
        return;
    }
    if(project->parametersFile.filename == fileName) {
        project->parametersFile.content = content;
    }else {
        auto trafficFile = project->findTrafficFileByName(fileName);
        if(trafficFile == nullptr) {
            emit errorInData("Can't find right file");
            return;
        }
        trafficFile->content = content;
    }
    emit currentProjectChanged(*project);
}

void DataSystem::spawnWindow_ProjectManagement() {
    emit currentProjects(projects);
    emit spawnWindow_ProjectMng();
}

void DataSystem::setDefaultParametersFileContent(const QString &projectName) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project");
        return;
    }
    project->parametersFile.content = getDefaultParametersFileContent();
    emit currentProjectChanged(*project);
}

void DataSystem::setDefaultTrafficFileContent(const QString &projectName, const QString &trafficName) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project");
        return;
    }
    auto trafficFile = project->findTrafficFileByName(trafficName);
    if(trafficFile == nullptr) {
        emit errorInData("Can't find right traffic file");
        return;
    }
    trafficFile->content = getDefaultTrafficFileContent();
    emit currentProjectChanged(*project);
}

void DataSystem::removeFile_TrafficFile(const QString& ProjectName, const QString& fileName) {
    auto project = findProjectByName(ProjectName);
    if(project == nullptr) {
        emit errorInData("Cannot find right Project");
        return;
    }

    auto traffic = project->findTrafficFileByName(fileName);
    if(traffic == nullptr) {
        emit errorInData("Cannot find right traffic file");
        return;
    }

    project->trafficFilesList.erase(traffic);
    emit currentProjectChanged(*project);

    saveProjectsFile();
}

QString DataSystem::getDefaultParametersFileContent()
{
    QFile param_template(":/RbFiles/parameters.rb");
    param_template.open(QIODevice::ReadOnly);
    QTextStream param_template_str(&param_template);
    QString fileContent = param_template_str.readAll();
    param_template.close();

    return fileContent;
}

//Currently not used, because restore defaults functionality in ParametersWindow is disabled
QString DataSystem::getDefaultTrafficFileContent() {
    QFile trafficTemplate(":/RbFiles/tune_traffic_models.rb");
    trafficTemplate.open((QIODevice::ReadOnly));
    QTextStream trafficTemplateStr(&trafficTemplate);
    QString fileContent = trafficTemplateStr.readAll();
    trafficTemplate.close();

    return fileContent;

}

void DataSystem::createNewProject(const QString &projectName, const QString &directory) {

    if(isProjectNameUsed(projectName)) {
        emit errorInData("Name already in use. Choose another one.");
        return;
    }

    Project newProject;
    newProject.name = projectName;
    newProject.fullpath = directory.isEmpty() ? getDefaultNewProjectDir() : directory;
    newProject.parametersFile.filename = "Parameters.rb";
    newProject.parametersFile.content = getDefaultParametersFileContent();

    QString rbContent = newProject.parametersFile.content;

    scriptParserManager.parseFromScript(rbContent,newProject);

    projects.push_back(newProject);
    emit currentProjects(projects);
    saveProjectsFile();
}

void DataSystem::setGlobalLocationForNewProjects(const QString &location)
{
    if(location.isEmpty()) {
        emit errorInData("You must specify the directory.");
        return;
    }
    if(location!="<default>") {
        QDir new_dir(location);
        if(!new_dir.exists()) {
            emit errorInData("Selected directory does not seem to exist.");
            return;
        }
    }
    appGlobalData.setDefaultNewProjectsPath(location);
}

void DataSystem::addToProject_TrafficFile(const QString &ProjectName, const QString& fileName)
{
    auto proj = findProjectByName(ProjectName);

    if(proj == nullptr) {
        emit errorInData("Error while adding traffic file");
        return;
    }

    TrafficFileData trafficData;
    trafficData.filename = fileName.isEmpty() ? generateUniqueTrafficFilename(proj) : fileName;
    proj->trafficFilesList.push_back(trafficData);
    emit currentProjectChanged(*proj);

    saveProjectsFile();
}

QString DataSystem::generateUniqueTrafficFilename(Project *project)
{
    for(unsigned i=0; i<UINT_MAX; ++i) {
        const QString filename = "Traffic_" + QString::number(i) + ".rb";
        if(project->findTrafficFileByName(filename) == nullptr) {return filename;}
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

    if(proj->parametersFile.filename == oldFilename) {
        proj->parametersFile.filename = newFilename;
        emit currentProjectChanged(*proj);
        saveProjectsFile();
        return;
    }
    else {
        if(proj->findTrafficFileByName(newFilename) != nullptr) {
            emit errorInData("Name already in use. Choose another one");
            return;
        }

        proj->findTrafficFileByName(oldFilename)->filename = newFilename;
        emit currentProjectChanged(*proj);
        saveProjectsFile();
        return;
    }

    emit errorInData("Can't find right trafficFile to rename!");
}

void DataSystem::set_RB_FilesLocationForProject(const QString& projectName, const QString& location) {

    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project");
        return;
    }
    if(location.isEmpty()) {
        emit errorInData("You must specify the directory.");
        return;
    }
    if(location!="<default>" && location!="<individually>") {
        QDir new_dir(location);
        if(!new_dir.exists()) {
            emit errorInData("Selected directory does not seem to exist.");
            return;
        }
    }
    project->genScriptDir = location;
    saveProjectsFile();
    emit currentProjectChanged(*project);
}

void DataSystem::updateDataGeneratorSettings(const DataGeneratorSettings &dataGeneratorSettings, const QString &projectName) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project.\nData not saved");
        return;
    }
    project->dataGeneratorSettings = dataGeneratorSettings;
    saveProjectsFile();
    //Maybe emit signal that refresh map UI but not sure yet if we need this
}

void DataSystem::updateUCToolSettings(const UCToolSettings &ucToolSettings, const QString &projectName)
{
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project.\nData not saved");
        return;
    }
    project->ucToolSettings = ucToolSettings;
    saveProjectsFile();
}

void DataSystem::updateChannelModelSettings(const ChannelModelSettings &channelModelSettings, const QString &projectName) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project.\nDatanot saved.");
        return;
    }
    project->channelModelSettings = channelModelSettings;
    saveProjectsFile();
}

void DataSystem::updateUBSimSettings(const UBSimSettings &ubSimSettings, const QString &projectName) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project.\nDatanot saved.");
        return;
    }
    project->ubSimSettings = ubSimSettings;
    saveProjectsFile();
}

void DataSystem::updateGeneralConfigurationParameters(const GeneralConfigurationParameters &generalConfigurationParameters, const QString &projectName) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project.\nDatanot saved.");
        return;
    }
    project->generalConfiguration = generalConfigurationParameters;
    saveProjectsFile();
}

void DataSystem::generateParametersScript(const Project &project)
{
    fileManager.generateParametersScript(project);
}

void DataSystem::generateTrafficScript(const Project &project, const int &indexOfFile)
{
    fileManager.generateTrafficScript(project,indexOfFile);
}

/**********************
 * GETTERS AND SETTERS
 **********************/


QString DataSystem::getDefaultNewProjectDir() const {
    return appGlobalData.getDefaultNewProjectsPath();
}

AppGlobalData DataSystem::getAppGlobalData() const {
    return appGlobalData;
}
void DataSystem::updateSgwSettings(const SgwSettings &sgwSettings, const QString &projectName){
    auto project = findProjectByName(projectName);
    if (project==nullptr){
        emit errorInData("Can't find right project.\nData not saved");
        return;
    }
    project->sgwSettings = sgwSettings;
    saveProjectsFile();
}
void DataSystem::updateSimulatedCoreNetworkState(const QString &projectName, bool state){
    auto project = findProjectByName(projectName);
    project->SimulatedCoreNetwork = state;
}
void DataSystem::updateSimulatedUeState(const QString &projectName, bool state){
    auto project = findProjectByName(projectName);
    project->SimulatedUe=state;
}
void DataSystem::updateMme(const MmeSettings &mmeSettings, QString projectName){
    auto project = findProjectByName(projectName);
    if (project==nullptr){
        emit errorInData("Can't find right project.\nData not saved");
        return;
    }
    project->mmeSettings = mmeSettings;
    saveProjectsFile();
}
void DataSystem::updatePaging(const PagingSettings &pagingSettings, QString projectName){
    auto project = findProjectByName(projectName);
    if (project==nullptr){
        emit errorInData("Can't find right project.\nData not saved");
        return;
    }
    project->pagingSettings = pagingSettings;
    saveProjectsFile();
}
