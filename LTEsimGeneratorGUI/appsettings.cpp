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
    for(int i = 1; i <= projects.size(); i++)
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

