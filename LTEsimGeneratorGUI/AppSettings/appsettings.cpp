#include "appsettings.h"

AppSettings::AppSettings() {

}

AppSettings::~AppSettings() {

}

void AppSettings::LoadAppData() {
    checkIfExistAndCreateSettingsFile();
    checkIfExistAndCreateProjectsFile();
    createProjectDirIfNotExist();
    read_settings_file();
    readProjectsFile();
    testProjectsObtainedFromTheFile();
    projects_dir_content=project_dir.entryInfoList(QDir::AllDirs);
    traverseProjectsListAndAddProjectIfNotFound();
    emit currentProjects(projects);
}


void AppSettings::write_settings_file(){
    QFile file(settingsFile);
    file.open(QIODevice::WriteOnly);
    QDataStream file_str(&file);

    QString content(defaultNewProjectDir);

    const char* ciphertext = crypt(content.toStdString().c_str(),content.length(),cipher_key.toStdString().c_str(),cipher_key.length() );
    file_str.writeRawData(ciphertext,content.length() );
    file.close();
}

void AppSettings::read_settings_file(){
    QFile file(settingsFile);
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


// Read the content of the project file, decrypt it and split into a list
QStringList AppSettings::read_project_file(QString project_name, QString dir){

    dir = (dir == "<default>") ? projectsDirectory : dir;

    QFile project_file(dir + "/" + project_name + "/" + project_name + getProFileExt());
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

    dir = (dir == "<default>") ? projectsDirectory : dir;

    QFile project_file(dir + "/" + project_name + "/" + project_name + getProFileExt());
    project_file.open(QIODevice::WriteOnly);
    QDataStream project_file_stream(&project_file);

    const char* ciphertext = crypt(project_content.toStdString().c_str(),project_content.length(),cipher_key.toStdString().c_str(),cipher_key.length() );
    project_file_stream.writeRawData(ciphertext,project_content.length());

    project_file.close();
}

QString AppSettings::get_project_dir(QListWidgetItem *item)
{
    for(unsigned int i = 0; i < projects.size(); i++) {
        if(projects[i].widget == item) {
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
    QFile projects_file(projectsFile);
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
    QFile projects_file(projectsFile);
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
void AppSettings::checkIfExistAndCreateSettingsFile() {
    settings_file.setFileName(settingsFile);
    if(!settings_file.exists()){
        setDefaultNewProjectDir("<default>");
        write_settings_file();
    }
}

// check if the projects file exists, create it if it doesn't
void AppSettings::checkIfExistAndCreateProjectsFile() {
    projects_file.setFileName(projectsFile);
    if(!projects_file.exists()){
        projects_file.open(QIODevice::WriteOnly);
        QTextStream str(&projects_file);
        str<<"0";
        projects_file.close();
    }
}

// create project dir if doesn't exist
void AppSettings::createProjectDirIfNotExist() {
        project_dir.mkdir(projectsDirectory);
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
    QListWidgetItem *new_widget;

    for(int i=1; i<=projectC_file*2; i+=2){
        QDir d;
        if(projects_file_content[i+1]!="<default>"){
            d.setPath(projects_file_content[i+1]+"/"+projects_file_content[i]);
        }
        else{
            d.setPath("projects/"+projects_file_content[i]);
        }
        if(d.exists()){
            QFile f(d.absolutePath()+"/"+projects_file_content[i] + getProFileExt());
            if(f.exists()){
                new_project.name=projects_file_content[i];
                new_project.fullpath=projects_file_content[i+1];
                new_widget = new QListWidgetItem(new_project.name+"\t("+new_project.fullpath+")");
                new_project.widget=new_widget;
                projects.push_back(new_project);
            }
        }
    }
    project_dir.setPath(projectsDirectory);
}

// traverse the list of projects dir contents
void AppSettings::traverseProjectsListAndAddProjectIfNotFound() {
    for(int i=0; i<projects_dir_content.size(); i++){

        project_dir.setPath(projects_dir_content[i].fileName());

        // check if the project file exists inside the project dir and its name is the same as project dir
        project_file.setFileName("projects/"+projects_dir_content[i].fileName()+"/"+projects_dir_content[i].fileName()+ getProFileExt());
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
                QListWidgetItem *new_widget = new QListWidgetItem(new_project.name+"\t("+new_project.fullpath+")");
                new_project.widget=new_widget;
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

void AppSettings::addProject(QListWidgetItem* new_item,QString dir){

    Project new_project;
    new_project.name=new_item->text();
    new_project.fullpath=dir;
    new_project.widget=new_item;
    projects.push_back(new_project);

    QDir projectDir;

    // if the project is to be saved in default directory
    if(dir=="<default>"){
        projectDir.setPath(projectsDirectory);
    } else {
        projectDir.setPath(dir);
    }

    projectDir.mkdir(getProjectName());

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
        write_project_file(new_item->text(),project_content, getProjectDirectory(new_item->text()));
    } else {
        write_project_file(new_item->text(),project_content,dir);
    }
    emit currentProjects(projects);
}

// recursively remove entire directory and its content
void AppSettings::removeDirectoryRecursively(QString dir_name){
    QDir directory("projects/"+dir_name);
    directory.removeRecursively();
}

QString AppSettings::readParametersFile()
{
    QFile param_template(parameterFile);
    param_template.open(QIODevice::ReadOnly);
    QTextStream param_template_str(&param_template);
    param_template.close();

    return param_template_str.readAll();
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
    return defaultNewProjectDir;
}

void AppSettings::setDefaultNewProjectDir(const QString &value)
{
    defaultNewProjectDir = value;
}

QString AppSettings::getProFileExt() const
{
    return proFileExt;
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
