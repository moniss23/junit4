#ifndef APPGLOBALDATA_H
#define APPGLOBALDATA_H

#include <QString>
#include <QStringList>

#include "Interfaces/serializeinterface.h"

/**
 * @brief The AppGlobalData class contains global data
 */
class AppGlobalData : public SerializeInterface
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

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    /**
     * @brief getElementType is a API method to recognise the object by QString
     * @return QSting "Project"
     */
    virtual QString getElementType() const;
    /**
     * @brief serializeData is an inherited method that serializes this class to QByteArray
     * @return QByteArray with serialized object of the class
     */
    virtual QByteArray serializeData();
    /**
     * @brief deserializeData deserializeData ia an inherited method that deserializes it's parameter to fill the fields in this class' instance
     * @param rawData rawData is QByteArray that contains all the data needed to creata an instance of trafficFileData class
     */
    virtual void deserializeData(const QByteArray &rawData);

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
