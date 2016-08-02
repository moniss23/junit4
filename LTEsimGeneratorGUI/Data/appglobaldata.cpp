#include "appglobaldata.h"

AppGlobalData::AppGlobalData()
{

}

/*
 *
 * Getters and Setters
 *
 */

QString AppGlobalData::getParameterFile() const
{
    return parameterFile;
}

QString AppGlobalData::getProjectsDirectory() const
{
    return projectsDirectory;
}

QString AppGlobalData::getProjectsFile() const
{
    return projectsFile;
}

QString AppGlobalData::getSettingsFile() const
{
    return settingsFile;
}

QString AppGlobalData::getProFileExt() const
{
    return proFileExt;
}
