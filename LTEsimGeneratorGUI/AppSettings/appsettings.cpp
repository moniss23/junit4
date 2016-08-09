#include "appsettings.h"

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
    for(size_t i=0; i<projects.size(); i++){
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

    unsigned int length = project_file.bytesAvailable();
    char* ciphertext = new char[length];

    project_file_stream.readRawData(ciphertext,length);
    const char* plaintext = crypt(ciphertext,length,cipher_key.toStdString().c_str(),cipher_key.length());

    project_file.close();
    return QString(plaintext).split('\n');
}

// encrypt the project data and write it into the file
void AppSettings::write_project_file(QString project_name, QString project_content, QString dir){

    dir = (dir == "<default>") ? appGlobalData.getProjectsDirectory() : dir;

    QFile project_file(dir + "/" + project_name + "/" + project_name + appGlobalData.getProFileExt());
    project_file.open(QIODevice::WriteOnly);
    QDataStream project_file_stream(&project_file);

    const char* ciphertext = crypt(project_content.toStdString().c_str(),project_content.length(),cipher_key.toStdString().c_str(),cipher_key.length() );
    project_file_stream.writeRawData(ciphertext,project_content.length());

    project_file.close();
}


void AppSettings::write_settings_file(){
    QFile file(appGlobalData.getSettingsFile());
    file.open(QIODevice::WriteOnly);
    QDataStream file_str(&file);

    QString content(defaultNewProjectDir);

    const char* ciphertext = crypt(content.toStdString().c_str(),content.length(),cipher_key.toStdString().c_str(),cipher_key.length() );
    file_str.writeRawData(ciphertext,content.length() );
    file.close();
}

void AppSettings::read_settings_file(){
    QFile file(appGlobalData.getSettingsFile());
    unsigned int length = file.bytesAvailable();
    file.open(QIODevice::ReadOnly);
    char* ciphertext = new char[length];
    QDataStream file_str(&file);
    file_str.readRawData(ciphertext,length);
    const char* plaintext = crypt(ciphertext,length,cipher_key.toStdString().c_str(),cipher_key.length(),true);
    file.close();

    QString content(plaintext);
    QStringList content_list(content.split("\n") );

    defaultNewProjectDir = content_list[0];

}

QString AppSettings::get_project_dir(QListWidgetItem *item)
{
    for(unsigned int i = 0; i < projects.size(); i++) {
        if(projects[i].name == item->text()) {
            return projects[i].fullpath;
        }
    }

    return QString();
}

QString AppSettings::get_project_dir(QString project_name)
{
    for(unsigned int i = 0; i < projects.size(); i++) {
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
    for(size_t i = 0; i < projects.size(); i++) {
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
    for(unsigned i=1; i<=projects.size(); i++)
    {
        new_project.name = content[2 * i - 1];
        new_project.fullpath = content[2 * i];
        projects.push_back(new_project);
    }
}

//Moved from projectManagement
bool AppSettings::projectNameTaken(QString projectName){
    bool taken=false;
    for(unsigned i=0; i<projects.size(); i++){
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
                new_project.name=projects_file_content[i];
                new_project.fullpath=projects_file_content[i+1];
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
            unsigned int j;
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

void AppSettings::setMapType(const QString& projectName, const QString& mapType) {
    for(auto &&it : projects) {
        if(it.name == projectName) {
            it.chosenMapType = mapType;
        }
    }
}

/*
 * Slots
 *
 */

void AppSettings::createNewProject(const QString &projectName, const QString & directory) {

    if(projectNameTaken(projectName)) {
        emit errorInData("Name already in use. Choose another one.");
        return;
    }

    QString dir;
    if(directory.isEmpty()){
       dir = getDefaultNewProjectDir();
    } else {
       dir = directory;
    }


    Project new_project;
    new_project.name=projectName;
    new_project.fullpath=dir;

    projects.push_back(new_project);

    QDir projectDir;

    // if the project is to be saved in default directory
    if(dir=="<default>"){
        projectDir.setPath(appGlobalData.getProjectsDirectory());
    } else {
        projectDir.setPath(dir);
    }

    projectDir.mkdir(projectName);

    // append the settings, the name and content of parameters.rb template to project file
    QString project_content("<default>\nnormal\nParameters.rb\n0\n");
    QFile param_template(":/RbFiles/parameters.rb");
    param_template.open(QIODevice::ReadOnly);
    QTextStream param_template_str(&param_template);
    QString param_template_content=param_template_str.readAll();
    project_content+=QString::number(param_template_content.split("\n").size());
    project_content+="\n";
    project_content+=param_template_content;
    project_content+="\n";
    param_template.close();

    if(dir=="<default>"){
        write_project_file(projectName,project_content, getProjectDirectory(projectName));
    } else {
        write_project_file(projectName,project_content,dir);
    }

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

QString AppSettings::getParametersFile() const
{
    return parametersFile;
}

void AppSettings::setParametersFile(const QString &value)
{
    parametersFile = value;
}

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

void AppSettings::addToProject_TrafficFile(const QString &ProjectName)
{
    (void) ProjectName;
    //find project
    //add new traffic file
    //emit signal currentProjectChanged(const Project &current);
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
