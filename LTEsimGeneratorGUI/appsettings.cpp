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

