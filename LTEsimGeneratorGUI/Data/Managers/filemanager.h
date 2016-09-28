#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QByteArray>

#include "Data/project.h"

/**
 * @brief The FileManager class is responsible for I/O on files
 */
class FileManager {
public:
    /**
     * @brief FileManager default constructor
     */
    FileManager();

    /***********************************************
     *   PUBLIC API
     ***********************************************/
    /**
     * @brief readFromFile reads binary data from a file
     * @param fileFullPath QString with full path to the file
     * @return QByteArray with file content
     */
    QByteArray readFromFile(const QString &fileFullPath);
    /**
     * @brief writeToFile writes binary data to file
     * @param fileFullPath QString with full path to the file
     * @param rawData QByteArray with binary data
     */
    void writeToFile(const QString &fileFullPath, const QByteArray &locationFileContent);
    /**
     * @brief redProjectFromFile
     * @param fullFilePath
     * @return
     */
    QByteArray readProjectFromFile(QString fullFilePath);
    /**
     * @brief writeProjectToFile
     * @param location
     * @param projectName
     * @param rawData
     */
    void writeProjectToFile(QString location, QString projectName, QByteArray rawData);
    /**
     * @brief removeProjectDirectory
     * @param directory
     */
    void removeProjectDirectory(QString directory);
    /**
     * @brief removeTrafficFile
     * @param fullpath
     */
    void removeTrafficFile(QString fullpath);
    /**
     * @brief generateParametersScript is used to write parametersFileData content to file
     * @param location is path to file
     * @param projectName is current Project name
     * @param content is content that will be write to file
     */
    void generateParametersScript(QString location, QString projectName,QString fileName, QString content);
    /**
     * @brief generateTrafficScript is used to write trafficFileData content to file
     * @param location is path to file
     * @param projectName is current Project name
     * @param content is content that will be write to file
     * @param fileName is current traffic file name
     */
    void generateTrafficScript(QString location, QString projectName, QString content, QString fileName);
    /**
     * @brief readFileToQString is used to read content of the file
     * @param filename is file name
     * @return QString with file content
     */
    QString readFileToQString(const QString &filename);
    /**
     * @brief projectsFileSetup is used to check if projects file exist, and create it if doesn't
     * @param projectsFilename is projec's file name
     */
    void projectsFileSetup(const QString &projectsFilename);
};

#endif // FILEMANAGER_H
