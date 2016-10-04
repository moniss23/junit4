#ifndef APPGLOBALDATA_H
#define APPGLOBALDATA_H

#include <QString>
#include <QStringList>

/**
 * @brief The AppGlobalData class contains global data
 */
class AppGlobalData
{
public:
    /**
     * @brief AppGlobalData default constructor
     */
    AppGlobalData();

    /**
     * @brief setDefaultNewProjectsPath is setting new default project path
     * @param value is new project path
     */
    void setDefaultNewProjectsPath(const QString &value);
    /**
     * @brief getDefaultNewProjectsPath is used to get default project path
     * @return QString default project path
     */
    const QString getDefaultNewProjectsPath() const;
    /**
     * @brief getParameterFile is used to get parameter files path
     * @return QString ":/RbFiles/ParametersTemplate.rb"
     */
    QString getParameterFile() const;
    /**
     * @brief getTrafficFile is used to get traffic files path
     * @return QString ":/RbFiles/TrafficTemplate.rb"
     */
    QString getTrafficFile() const;
    /**
     * @brief getProjectsDirectory is used to get projects directory
     * @return QString "projects"
     */
    QString getProjectsDirectory() const;
    /**
     * @brief getProjectsFile is used to get projects file
     * @return QString "projects.dat"
     */
    QString getProjectsFile() const;
    /**
     * @brief getSettingsFile is used to get settings file
     * @return QString "settings.dat"
     */
    QString getSettingsFile() const;
    /**
     * @brief getProFileExt is used to get projects extension
     * @return QString ".proj"
     */
    QString getProFileExt() const;
    /**
     * @brief getRbFileExt is used to get scripts extension
     * @return QString ".rb"
     */
    QString getRbFileExt() const;

private:

    QString defaultNewProjectsPath;
    const QString proFileExt = ".proj";
    const QString rbFileExt = ".rb";
    const QString settingsFile = "settings.dat";
    const QString projectsFile = "projects.dat";
    const QString projectsDirectory = "projects";
    const QString parameterFile = ":/RbFiles/ParametersTemplate.rb";
    const QString trafficFile = ":/RbFiles/TrafficTemplate.rb";
};

#endif // APPGLOBALDATA_H
