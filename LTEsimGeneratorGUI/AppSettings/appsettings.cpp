#include "appsettings.h"

AppSettings::AppSettings() {

}

AppSettings::~AppSettings() {

}


void AppSettings::write_settings_file(){
    QFile file("settings.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream file_str(&file);

    QString content(defaultNewProjectDir);

    const char* ciphertext = crypt(content.toStdString().c_str(),content.length(),cipher_key.toStdString().c_str(),cipher_key.length() );
    file_str.writeRawData(ciphertext,content.length() );
    file.close();
}

void AppSettings::read_settings_file(){
    QFile file("settings.dat");
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

    dir = (dir == "<default>") ? "projects" : dir;

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

    dir = (dir == "<default>") ? "projects" : dir;

    QFile project_file(dir + "/" + project_name + "/" + project_name + getProFileExt());
    project_file.open(QIODevice::WriteOnly);
    QDataStream project_file_stream(&project_file);

    const char* ciphertext = crypt(project_content.toStdString().c_str(),project_content.length(),cipher_key.toStdString().c_str(),cipher_key.length() );
    project_file_stream.writeRawData(ciphertext,project_content.length());

    project_file.close();
}


void AppSettings::write_projects_file(){
    QFile projects_file("projects.dat");
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
    QFile projects_file("projects.dat");
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

//Loads all the projects and settings
std::vector<QListWidgetItem*> AppSettings::loadSettings() {
    checkIfExistAndCreateSettingsFile();
    checkIfExistAndCreateProjectsFile();
    checkIfExistAndCreateProjectsDir();
    read_settings_file();
    readProjectsFile();
    std::vector<QListWidgetItem*> vector = testProjectsObtainedFromTheFile();
    projects_dir_content=project_dir.entryInfoList(QDir::AllDirs);
    traverseProjectsListAndAddProjectIfNotFound();
    return vector;
}

// check if the settings file exists, create it if it doesn't
void AppSettings::checkIfExistAndCreateSettingsFile() {
    settings_file.setFileName("settings.dat");
    if(!settings_file.exists()){
        setDefaultNewProjectDir("<default>");
        write_settings_file();
        qDebug()<<"settings file did not exist and was created";
    }
}

// check if the projects file exists, create it if it doesn't
void AppSettings::checkIfExistAndCreateProjectsFile() {
    projects_file.setFileName("projects.dat");
    if(!projects_file.exists()){
        projects_file.open(QIODevice::WriteOnly);
        QTextStream str(&projects_file);
        str<<"0";
        projects_file.close();
    }
}

// check if the projects dir exists, create it if it doesn't
void AppSettings::checkIfExistAndCreateProjectsDir() {
    if(!project_dir.exists("projects")){
        project_dir.mkdir("projects");
    }
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
std::vector<QListWidgetItem*> AppSettings::testProjectsObtainedFromTheFile() {

    Project new_project;
    QListWidgetItem *new_widget;
    std::vector<QListWidgetItem*> widget_vector;

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
                widget_vector.push_back(new_widget);
                new_project.widget=new_widget;
                projects.push_back(new_project);
            }
        }
    }
    project_dir.setPath("projects");
    return widget_vector;
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
        projectDir.setPath("projects");
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
    project_content+=itoa(param_template_content.split("\n").size());
    project_content+="\n";
    project_content+=param_template_content;
    project_content+="\n";
    param_template.close();

    if(dir=="<default>"){
        write_project_file(new_item->text(),project_content, getProjectDirectory(new_item->text()));
    } else {
        write_project_file(new_item->text(),project_content,dir);
    }
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
