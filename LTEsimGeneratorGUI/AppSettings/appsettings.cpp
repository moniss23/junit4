#include "appsettings.h"
#include "Data/appglobaldata.h"
#include "Data/trafficdata.h"

#include <QDebug>

AppSettings::AppSettings()
{
  settingsFileSetup();
  projectsFileSetup();
  projectsDirSetup();
}

AppSettings::~AppSettings() {

}

void AppSettings::LoadAppData() {
    readProjectsFile();
    testProjectsObtainedFromTheFile();
    projects_dir_content=project_dir.entryInfoList(QDir::AllDirs);
    traverseProjectsListAndAddProjectIfNotFound();
    emit currentProjects(projects);
}

void AppSettings::loadProjectsFile() {
    // implemented, not being used yet, 9.08.16
    QByteArray rawData = fileManager.readFromFile(appGlobalData.getProjectsFile());
    QDataStream dataStream(rawData);

    dataStream >> projectC_file;
    for(int i=0; i<projectC_file; ++i) {
        QByteArray singleProjectData;
        dataStream >> singleProjectData;

        Project p;
        p.deserializeData(singleProjectData);
        projects.push_back(p);
    }
}

void AppSettings::saveProjectsFile() {
    // implemented, not being used yet, 9.08.16
    QBuffer rawDataBuff;
    rawDataBuff.open(QBuffer::WriteOnly);
    QDataStream dataStream(&rawDataBuff);

    dataStream << (int)projects.size();

    for(auto &&elem : projects) {
        QByteArray singleProjectData = elem.serializeData();
        dataStream << singleProjectData;
    }

    fileManager.writeToFile(appGlobalData.getProjectsFile(), rawDataBuff.buffer());
}

void AppSettings::importProject(const QString &ProjectDirectory)
{
    if(ProjectDirectory.isEmpty()){
        return;
    }

    // verify validity of the project
    QStringList import_dir_exploded=ProjectDirectory.split("/");
    QString project_name(import_dir_exploded[import_dir_exploded.length()-1]);
    QFile import_file(ProjectDirectory+"/"+project_name + appGlobalData.getProFileExt());

    if(!import_file.exists()){
        emit errorInData("\""+ProjectDirectory+"\" does not seem to be a valid project directory.");
        return;
    }

    // create the project element for the vector
    Project new_project;
    new_project.name=project_name;
    QString vector_dir;

    int i=0;
    for(; i<import_dir_exploded.length()-2; i++){
        vector_dir+=import_dir_exploded[i];
        vector_dir+="/";
    }
    vector_dir+=import_dir_exploded[i];
    new_project.fullpath=vector_dir;

    // check if the project is already on the list
    for(auto i=0; i<projects.size(); i++){
        if(projects[i].name==new_project.name && projects[i].fullpath==new_project.fullpath){
            emit errorInData("Project is already present.");
            return;
        }
    }

    projects.push_back(new_project);

    // update the projects.dat file
    write_projects_file();

    emit currentProjects(projects);
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

QString AppSettings::get_project_dir(QListWidgetItem *item)
{
    for(auto i = 0; i < projects.size(); i++) {
        if(projects[i].name == item->text()) {
            return projects[i].fullpath;
        }
    }

    return QString();
}

QString AppSettings::get_project_dir(QString project_name)
{
    for(auto i = 0; i < projects.size(); i++) {
        if(projects[i].name == project_name) {
            return projects[i].fullpath;
        }
    }
    return QString();

}


void AppSettings::write_projects_file(){
    QFile projects_file(appGlobalData.getProjectsFile());
    projects_file.open(QIODevice::WriteOnly);
    QTextStream projects_file_str(&projects_file);
    projects_file_str << projects.size() << "\n";
    for(auto i = 0; i < projects.size(); i++) {
        projects_file_str << projects[i].name << "\n";
        projects_file_str << projects[i].fullpath << "\n";
    }
    projects_file.close();
}

// currently unused
void AppSettings::read_projects_file(){
    QFile projects_file(appGlobalData.getProjectsFile());
    projects_file.open(QIODevice::ReadOnly);
    QTextStream projects_file_str(&projects_file);
    QStringList content = projects_file_str.readAll().split("\n");
    Project new_project;
    for(auto i=1; i<=projects.size(); i++)
    {
        new_project.name = content[2 * i - 1];
        new_project.fullpath = content[2 * i];
        projects.push_back(new_project);
    }
}

//Moved from projectManagement
bool AppSettings::projectNameTaken(QString projectName){
    bool taken=false;
    for(auto i=0; i<projects.size(); i++){
        if(projects[i].name == projectName)
        {
            taken=true;
            break;
        }
    }
    return taken;
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
    if(!projects_file.exists()){
        projects_file.open(QIODevice::WriteOnly);
        QTextStream str(&projects_file);
        str<<"0";
        projects_file.close();
    }
}

// create project dir if doesn't exist
void AppSettings::projectsDirSetup() {
        project_dir.mkdir(appGlobalData.getProjectsDirectory());
}

// read the content of projects.dat file
void AppSettings::readProjectsFile() {
    projects_file.open(QIODevice::ReadOnly);
    QTextStream projectFileStream(&projects_file);
    QStringList file_content(projectFileStream.readAll().split('\n'));
    projects_file_content = file_content;
    projectC_file=projects_file_content[0].toInt();
}


// test the projects obtained from the file, discard those which don't seem to exist anymore
void AppSettings::testProjectsObtainedFromTheFile() {

    Project new_project;

    for(int i=1; i<=projectC_file*2; i+=2){
        QDir d;
        if(projects_file_content[i+1]!="<default>"){
            d.setPath(projects_file_content[i+1]+"/"+projects_file_content[i]);
        }
        else{
            d.setPath("projects/"+projects_file_content[i]);
        }
        if(d.exists()){
            QFile f(d.absolutePath()+"/"+projects_file_content[i] + appGlobalData.getProFileExt());
            if(f.exists()){
                QFile param_template(":/RbFiles/parameters.rb");
                param_template.open(QIODevice::ReadOnly);
                QTextStream param_template_str(&param_template);
                QString param_template_content = param_template_str.readAll();
                param_template.close();



                new_project.name=projects_file_content[i];
                new_project.fullpath=projects_file_content[i+1];
                new_project.parametersFile.fileName="Parameters.rb";//hack
                new_project.parametersFile.content=param_template_content;//hack
                projects.push_back(new_project);
            }
        }
    }
    project_dir.setPath(appGlobalData.getProjectsDirectory());
}

// traverse the list of projects dir contents
void AppSettings::traverseProjectsListAndAddProjectIfNotFound() {
    for(int i=0; i<projects_dir_content.size(); i++){

        project_dir.setPath(projects_dir_content[i].fileName());

        // check if the project file exists inside the project dir and its name is the same as project dir
        project_file.setFileName("projects/"+projects_dir_content[i].fileName()+"/"+projects_dir_content[i].fileName()+ this->appGlobalData.getProFileExt());
        if(project_file.exists()){

            // here we already verified that an element is a valid project

            // check if the project was already obtained from projects.dat, if not then add it

            //TODO: change the algorithm
            int j;
            for(j=0; j<projects.size(); j++){
                if(projects[j].name==projects_dir_content[i].fileName()){
                    break;
                }
            }

            // if entire vector was traversed, then it means that project was not found, and it shold be added
            if(j==projects.size()){
                Project new_project;

                new_project.name=projects_dir_content[i].fileName();
                new_project.fullpath="<default>";
                projects.push_back(new_project);
            }

        }
    }
}

QString AppSettings::getProjectDirectory(const QString &projectName){
    auto it = std::find_if(projects.begin(), projects.end(), [&projectName](const Project &project) -> bool {
        return (project.name == projectName);
    });

    if(it == std::end(projects)) return QString();
    return it->fullpath;
}

// recursively remove entire directory and its content
void AppSettings::removeDirectoryRecursively(QString dir_name){
    QDir directory("projects/"+dir_name);
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

void AppSettings::createNewProject(const QString &projectName, const QString &directory) {

    if(projectNameTaken(projectName)) {
        emit errorInData("Name already in use. Choose another one.");
        return;
    }

    QString dir = directory.isEmpty() ? getDefaultNewProjectDir() : directory;

    QFile param_template(":/RbFiles/parameters.rb");
    param_template.open(QIODevice::ReadOnly);
    QTextStream param_template_str(&param_template);
    QString param_template_content = param_template_str.readAll();
    param_template.close();

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
    write_projects_file();
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

void AppSettings::setNewDirForProject(const QString &projectName)
{
    (void)projectName;
    //TODO: Implement this slot.
}

void AppSettings::addToProject_TrafficFile(const QString &ProjectName)
{
    auto it = std::find_if(projects.begin(), projects.end(), [&ProjectName](const Project& project)-> bool {
        return (project.name == ProjectName);
    });
    if(it == projects.end()) {
        emit errorInData("Error while adding traffic file");
        return;
    }
    TrafficData trafficData;
    trafficData.fileName = generateUniqueTrafficFilename(*it);
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
    qDebug() << "Traffic name = " << filename;
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
    auto elem = std::find_if(std::begin(projects), std::end(projects), [projectName](const Project &p)->bool {return projectName==p.name;});
    projects.erase(elem);
    emit currentProjects(projects);
}

void AppSettings::findProject(const QString &projectName)
{
    auto it = std::find_if(projects.begin(), projects.end(), [&projectName](const Project& project)-> bool {
       return (projectName == project.name);
    });
    if(it == projects.end()) {
        return;
    }
    emit currentProjectChanged(*it);
}
