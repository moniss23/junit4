#include "datasystem.h"

#include <QDir>
#include <QTextStream>

#include "Data/Managers/filemanager.h"
#include "Data/Managers/scriptparsermanager.h"
#include "Data/ProjectSettings/Helpers/mapparser.h"

DataSystem::DataSystem() {

    fileManager         = std::make_unique<FileManager>();
    scriptParserManager = std::make_unique<ScriptParserManager>();

    fileManager->projectsFileSetup(appGlobalData.getProjectsFile());
}

DataSystem::~DataSystem() {
}

void DataSystem::LoadAppData() {
    loadProjectsFile();
    emit currentProjects(projects);
}

void DataSystem::loadProjectsFile() {
    QDataStream dataStream(fileManager->readFromFile(appGlobalData.getProjectsFile()));

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

    fileManager->writeToFile(appGlobalData.getProjectsFile(), rawDataBuff.buffer());
}

// Returns pointer to a Project element or nullptr if not found
Project* DataSystem::findProjectByName(const QString &projectName) {
    auto it = std::find_if(std::begin(projects), std::end(projects),
                           [&projectName](const Project &p)->bool {return p.name==projectName; });

    return it != std::end(projects) ? it : nullptr;
}

bool DataSystem::isProjectNameUsed(QString projectName) {
    return findProjectByName(projectName) != nullptr;
}

/*********
 * SLOTS *
 *********/

void DataSystem::addUe(const QString &projectName, const QString &trafficFileName) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project");
        return;
    }

    TrafficFileData* trafficFound = project->findTrafficFileByName(trafficFileName);
    if(trafficFound != nullptr) {
        UEData ueData;
        ueData.pairName = QString("ue") + QString::number(trafficFound->userEquipments.size());

        trafficFound->userEquipments.append(ueData);

        emit currentProjectChanged(*project);
        emit refreshMapView(*project, trafficFound); //TODO: get rid of that. currentProjectCHanged should notify Map to repaint.
        saveProjectsFile();
    }
    else emit errorInData("Couldn't find " + trafficFileName + " in current project");
}

void DataSystem::updateUe(const QString &projectName, const QString &trafficFileName, const UEData &ueData) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project");
        return;
    }

    TrafficFileData* trafficFound = project->findTrafficFileByName(trafficFileName);
    if(trafficFound != nullptr) {
        trafficFound->userEquipments[ueData.pairName.mid(2).toInt()] = ueData;
        saveProjectsFile();
    }
    else emit errorInData("Couldn't find " + trafficFileName + " in current project");
}

void DataSystem::addCell(const QString &projectName) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project");
        return;
    }

    QString newCellName = this->generateUniqueCellName(project);

    QPair<Cell,Center> cellInfo;
    cellInfo.first.name = cellInfo.second.area = newCellName;
    cellInfo.first.position_X = cellInfo.first.position_Y = 3500;

    project->cellsInfo.append(cellInfo);
    emit currentProjectChanged(*project);
    emit refreshMapView(*project); //TODO: get rid of that. currentProjectCHanged should notify Map to repaint.
    saveProjectsFile();
}

void DataSystem::addHandover(const QString &projectName) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project");
        return;
    }

    Handover handover;
    handover.area = this->generateUniqueHandoverName(project);
    handover.westBoundary = 2500;
    handover.southBoundary = 2500;
    handover.eastBoundary = handover.westBoundary + 4500;
    handover.northBoundary = handover.southBoundary + 1000;

    project->handovers.append(handover);
    emit currentProjectChanged(*project);
    emit refreshMapView(*project); //TODO: get rid of that. currentProjectCHanged should notify Map to repaint.
    saveProjectsFile();
}

void DataSystem::removeCell(const QPair<Cell,Center> &cell, const QString &projectName) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project");
        return;
    }

    project->cellsInfo.erase(std::remove_if(project->cellsInfo.begin(), project->cellsInfo.end(),
                            [&cell](const auto &cellFound){return cellFound.first.name==cell.first.name;}));

     saveProjectsFile();
}

void DataSystem::removeHandover(const Handover &handover, const QString &projectName) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project");
        return;
    }

    project->handovers.erase(std::remove_if(project->handovers.begin(), project->handovers.end(),
                            [&handover](const auto &hoFound){return hoFound.area==handover.area;}));

     saveProjectsFile();
}

void DataSystem::updateCell(const QPair<Cell,Center> &cell, const QString &cellName, const QString &projectName) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project");
        return;
    }

     auto cellFound = project->findCellByName(cellName);
     if(cellFound != nullptr) {
         *cellFound = cell;
     }

     saveProjectsFile();
}

void DataSystem::updateStatisticsData(const QString &projectName, const QString &trafficFileName, const StatisticsData &statisticsData)
{
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project");
        return;
    }

    auto trafficFile = project->findTrafficFileByName(trafficFileName);
    if(trafficFile == nullptr) {
        emit errorInData("Can't find right project");
        return;
    }

    trafficFile->statisticsData = statisticsData;
}

void DataSystem::updateHandover(const Handover &handover, const QString &projectName) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project");
        return;
    }

     auto handoverFound = project->findHandoverByName(handover.area);
     if(handoverFound != nullptr) {
         *handoverFound = handover;
     }

     saveProjectsFile();
}

void DataSystem::updateFileContent(const QString &projectName, const QString &fileName, const QString &content) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        emit errorInData("Can't find right project");
        return;
    }

    if(project->parametersFile.filename == fileName) {
        project->parametersFile.content = content;
        scriptParserManager->parseFromScript(content,*project);
    }else {
        auto trafficFile = project->findTrafficFileByName(fileName);
        if(trafficFile == nullptr) {
            emit errorInData("Can't find right file");
            return;
        }

        trafficFile->content = content;
    }

    saveProjectsFile();
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
    project->parametersFile.content = fileManager->readFileToQString(appGlobalData.getParameterFile());
    scriptParserManager->parseFromScript(project->parametersFile.content, *project);
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
    newProject.parametersFile.content = fileManager->readFileToQString(appGlobalData.getParameterFile());

    QString rbContent = newProject.parametersFile.content;

    scriptParserManager->parseFromScript(rbContent,newProject);

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

QString DataSystem::generateUniqueCellName(Project *project)
{
    for(unsigned i=10; i<UINT_MAX; ++i) {
        const QString newCellName = "cell" + QString::number(i);
        if(std::none_of(project->cellsInfo.begin(), project->cellsInfo.end(),
            [&newCellName](auto &cellInfo){return cellInfo.first.name==newCellName;})) {
            return newCellName;
        }
    }

    emit errorInData("Cannot add more cells");
    return QString();
}

QString DataSystem::generateUniqueHandoverName(Project *project)
{
    for(unsigned i=1011; i<UINT_MAX; ++i) {
        const QString newHOName = "handover" + QString::number(i/100) + "_" + QString::number(i%100);
        if(std::none_of(project->handovers.begin(), project->handovers.end(),
            [&newHOName](auto &handover){return newHOName==handover.area;})) {
            return newHOName;
        }
    }

    emit errorInData("Cannot add more handovers");
    return QString();
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

void DataSystem::generateParametersScript(Project &project)
{
    QString content = scriptParserManager->GenerateParametersQString(project);
    emit updateFileContent(project.name,project.parametersFile.filename,content);
    fileManager->generateParametersScript(project.fullpath,project.name,content);
}

void DataSystem::generateTrafficScript(const Project &project, const int &indexOfFile)
{
    MapParser mapParser;
    QString content;
    content.append(mapParser.GenerateTrafficScript(project.trafficFilesList.at(indexOfFile)));
    fileManager->generateTrafficScript(project.fullpath,project.name,content,project.trafficFilesList.at(indexOfFile).filename);
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
    project->mmeSettings.simulatedCoreNetwork = state;
    saveProjectsFile();
}
void DataSystem::updateSimulatedUeState(const QString &projectName, bool state){
    auto project = findProjectByName(projectName);
    project->ueParameters.startUeComponent = state;
    saveProjectsFile();
}
void DataSystem::updateSgwState(const QString &projectName, bool state){
    auto project = findProjectByName(projectName);
    project->sgwSettings.coreNetworkGateway = state;
    saveProjectsFile();
}
void DataSystem::updatePagingState(const QString &projectName, bool state){
    auto project = findProjectByName(projectName);
    project->pagingSettings.isUsedInConfiguration = state;
    saveProjectsFile();
}
void DataSystem::updateUBSimState(const QString &projectName, bool state){
    auto project = findProjectByName(projectName);
    project->ubSimSettings.UBSimGui = state;
    saveProjectsFile();
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
void DataSystem::updateMapRange(const MapRange &mapRange, QString projectName){
    auto project = findProjectByName(projectName);
    if (project==nullptr){
        emit errorInData("Can't find right project.\nData not saved");
        return;
    }
    project->mapRange = mapRange;
    emit currentProjectChanged(*project);
    emit refreshMapView(*project); //TODO: get rid of that. currentProjectCHanged should notify Map to repaint.
    saveProjectsFile();
}

void DataSystem::savePingData(const QString &projectName, const QString &trafficName, const int &CMindex, const Ping &ping, const int &pingIndex, const bool &modification) {
    auto project = findProjectByName(projectName);
    if (project==nullptr){
        emit errorInData("Can't find right project.\nData not saved");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        emit errorInData("Can't find right trafficFile");
        return;
    }
    if(!modification) {
        traffic->customModels[CMindex].CMPings.push_back(ping);
        traffic->customModels[CMindex].qciUsed[ping.pingQci-1] = true;
        traffic->cmUsed[CMindex] = true;
    } else {
        traffic->customModels[CMindex].qciUsed[traffic->customModels[CMindex].CMPings[pingIndex].pingQci-1] = false;
        traffic->customModels[CMindex].CMPings[pingIndex] = ping;
        traffic->customModels[CMindex].qciUsed[ping.pingQci-1] = true;
    }
    this->saveProjectsFile();
    emit currentCustomModelChanged(traffic->customModels[CMindex], traffic->cmUsed);
}

void DataSystem::saveVoipData(const QString &projectName, const QString &trafficName, const int &CMindex, const Voip &voip, const int &voipIndex, const bool &modification)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr){
        emit errorInData("Can't find right project.\nData not saved");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        emit errorInData("Can't find right trafficFile");
        return;
    }
    if(!modification) {
        traffic->customModels[CMindex].CMVoips.push_back(voip);
        traffic->customModels[CMindex].qciUsed[voip.voipQci-1] = true;
        traffic->cmUsed[CMindex] = true;
    } else {
        traffic->customModels[CMindex].qciUsed[traffic->customModels[CMindex].CMVoips[voipIndex].voipQci-1] = false;
        traffic->customModels[CMindex].CMVoips[voipIndex] = voip;
        traffic->customModels[CMindex].qciUsed[voip.voipQci-1] = true;
    }
    this->saveProjectsFile();
    emit currentCustomModelChanged(traffic->customModels[CMindex], traffic->cmUsed);
}

void DataSystem::saveFtpDlData(const QString &projectName, const QString &trafficName, const int &CMindex, const FtpDl &ftpDl)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr){
        emit errorInData("Can't find right project.\nData not saved");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        emit errorInData("Can't find right trafficFile");
        return;
    }
    traffic->customModels[CMindex].CMFtpDls.push_back(ftpDl);
    traffic->customModels[CMindex].qciUsed[ftpDl.ftpDlQci-1] = true;
    traffic->cmUsed[CMindex] = true;
    this->saveProjectsFile();
    emit currentCustomModelChanged(traffic->customModels[CMindex], traffic->cmUsed);
}

void DataSystem::saveFtpUlData(const QString &projectName, const QString &trafficName, const int &CMindex, const FtpUl &ftpUl)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr){
        emit errorInData("Can't find right project.\nData not saved");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        emit errorInData("Can't find right trafficFile");
        return;
    }
    traffic->customModels[CMindex].CMFtpUls.push_back(ftpUl);
    traffic->customModels[CMindex].qciUsed[ftpUl.ftpUlQci-1] = true;
    traffic->cmUsed[CMindex] = true;
    this->saveProjectsFile();
    emit currentCustomModelChanged(traffic->customModels[CMindex], traffic->cmUsed);
}

void DataSystem::saveStreamDlData(const QString &projectName, const QString &trafficName, const int &CMindex, const StreamDl &streamDl)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr){
        emit errorInData("Can't find right project.\nData not saved");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        emit errorInData("Can't find right trafficFile");
        return;
    }
    traffic->customModels[CMindex].CMStreamDls.push_back(streamDl);
    traffic->customModels[CMindex].qciUsed[streamDl.streamDlQci-1] = true;
    traffic->cmUsed[CMindex] = true;
    this->saveProjectsFile();
    emit currentCustomModelChanged(traffic->customModels[CMindex], traffic->cmUsed);
}

void DataSystem::saveSyncedPingData(const QString &projectName, const QString &trafficName, const int &CMindex, const SyncedPing &syncedPing)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr){
        emit errorInData("Can't find right project.\nData not saved");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        emit errorInData("Can't find right trafficFile");
        return;
    }
    traffic->customModels[CMindex].CMSyncedPings.push_back(syncedPing);
    for(auto &qci : syncedPing.SyncedPingQciArray) {
        traffic->customModels[CMindex].qciUsed[qci - 1] = true;
    }
    traffic->cmUsed[CMindex] = true;
    this->saveProjectsFile();
    emit currentCustomModelChanged(traffic->customModels[CMindex], traffic->cmUsed);
}

void DataSystem::saveServiceReqData(const QString &projectName, const QString &trafficName, const int &CMindex, const ServiceReq &serviceReq)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr){
        emit errorInData("Can't find right project.\nData not saved");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        emit errorInData("Can't find right trafficFile");
        return;
    }
    traffic->customModels[CMindex].CMServiceReqs.push_back(serviceReq);
    for(auto &qci : serviceReq.ServiceReqQciArray) {
        traffic->customModels[CMindex].qciUsed[qci - 1] = true;
    }
    traffic->cmUsed[CMindex] = true;
    this->saveProjectsFile();
    emit currentCustomModelChanged(traffic->customModels[CMindex], traffic->cmUsed);
}

void DataSystem::deleteCustomModelItem(const QString &projectName, const QString &trafficName, const QString &item, const int &itemIndex, const int &CMindex)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr){
        emit errorInData("Can't find right project.\nData not saved");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        emit errorInData("Can't find right trafficFile");
        return;
    }
    if(item == "Ping") {
        traffic->customModels[CMindex].qciUsed[traffic->customModels[CMindex].CMPings[itemIndex].pingQci-1] = false;
        traffic->customModels[CMindex].CMPings.erase(traffic->customModels[CMindex].CMPings.begin()+itemIndex);
    } else if(item == "Voip") {
        traffic->customModels[CMindex].qciUsed[traffic->customModels[CMindex].CMVoips[itemIndex].voipQci-1] = false;
        traffic->customModels[CMindex].CMVoips.erase(traffic->customModels[CMindex].CMVoips.begin()+itemIndex);
    } else if(item == "FtpDl") {
        traffic->customModels[CMindex].qciUsed[traffic->customModels[CMindex].CMFtpDls[itemIndex].ftpDlQci-1] = false;
        traffic->customModels[CMindex].CMFtpDls.erase(traffic->customModels[CMindex].CMFtpDls.begin()+itemIndex);
    } else if(item == "FtpUl") {
        traffic->customModels[CMindex].qciUsed[traffic->customModels[CMindex].CMFtpUls[itemIndex].ftpUlQci-1] = false;
        traffic->customModels[CMindex].CMFtpUls.erase(traffic->customModels[CMindex].CMFtpUls.begin()+itemIndex);
    } else if(item == "StreamDl") {
        traffic->customModels[CMindex].qciUsed[traffic->customModels[CMindex].CMStreamDls[itemIndex].streamDlQci-1] = false;
        traffic->customModels[CMindex].CMStreamDls.erase(traffic->customModels[CMindex].CMStreamDls.begin()+itemIndex);
    } else if(item == "StreamUl") {
        traffic->customModels[CMindex].qciUsed[traffic->customModels[CMindex].CMStreamUls[itemIndex].streamUlQci-1] = false;
        traffic->customModels[CMindex].CMStreamUls.erase(traffic->customModels[CMindex].CMStreamUls.begin()+itemIndex);
    } else if(item == "SyncedPing") {
        for(auto &qci : traffic->customModels[CMindex].CMSyncedPings[itemIndex].SyncedPingQciArray) {
            traffic->customModels[CMindex].qciUsed[qci-1] = false;
        }
        traffic->customModels[CMindex].CMSyncedPings.erase(traffic->customModels[CMindex].CMSyncedPings.begin()+itemIndex);
    } else if(item == "ServiceReq") {
        for(auto &qci : traffic->customModels[CMindex].CMServiceReqs[itemIndex].ServiceReqQciArray) {
            traffic->customModels[CMindex].qciUsed[qci-1] = false;
        }
        traffic->customModels[CMindex].CMServiceReqs.erase(traffic->customModels[CMindex].CMServiceReqs.begin()+itemIndex);
    }
    bool isUsed = false;
    for(unsigned i =0; i < 9; i++) {
        if(traffic->customModels[CMindex].qciUsed[i] == true) {
            isUsed = true;
        }
    }
    if(isUsed == false) {
        traffic->cmUsed[CMindex] = false;
    }
    emit currentCustomModelChanged(traffic->customModels[CMindex], traffic->cmUsed);
    saveProjectsFile();
}

void DataSystem::saveStreamUlData(const QString &projectName, const QString &trafficName, const int &CMindex, const StreamUl &streamUl)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr){
        emit errorInData("Can't find right project.\nData not saved");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        emit errorInData("Can't find right trafficFile");
        return;
    }
    traffic->customModels[CMindex].CMStreamUls.push_back(streamUl);
    traffic->customModels[CMindex].qciUsed[streamUl.streamUlQci-1] = true;
    traffic->cmUsed[CMindex] = true;
    this->saveProjectsFile();
    emit currentCustomModelChanged(traffic->customModels[CMindex], traffic->cmUsed);
}

void DataSystem::updateCustomModel(const QString &projectName, const QString &trafficName, const int &index)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr){
        emit errorInData("Can't find right project.\nData not saved");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        emit errorInData("Can't find right trafficFile");
        return;
    }
    emit currentCustomModelChanged(traffic->customModels[index], traffic->cmUsed);
}
void DataSystem::updateProjectOnMapCloseEvent(const QString &projectName){
    auto project = findProjectByName(projectName);
    if (project==nullptr){
        emit errorInData("Can't find right project.\nData not saved");
        return;
    }
    emit currentProjectChanged(*project);
    saveProjectsFile();
}
