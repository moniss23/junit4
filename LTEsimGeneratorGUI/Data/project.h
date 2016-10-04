#ifndef PROJECT_H
#define PROJECT_H

#include <QVector>

#include "Data/Interfaces/serializeinterface.h"
#include "Data/Objects/cell.h"
#include "Data/Objects/center.h"
#include "Data/Objects/handover.h"
#include "Data/Objects/trafficfiledata.h"
#include "Data/Objects/parametersfiledata.h"

#include "Data/ProjectSettings/sgwsettings.h"
#include "Data/ProjectSettings/uctoolsettings.h"
#include "Data/ProjectSettings/channelmodelsettings.h"
#include "Data/ProjectSettings/datageneratorsettings.h"
#include "Data/ProjectSettings/mmesettings.h"
#include "Data/ProjectSettings/pagingsettings.h"
#include "Data/ProjectSettings/ubsimsettings.h"
#include "Data/ProjectSettings/generalconfigurationparameters.h"
#include "Data/ProjectSettings/maprange.h"
#include "Data/ProjectSettings/ueparameters.h"

/**
 * @brief The Project class contains projects data
 */
class Project : public SerializeInterface
{
public:
    /**
     * @brief Project default constructor and destructor
     */
    Project();
    ~Project() {}

    //-- Project info --//
    QString name;                                           ///< projects name
    QString fullpath;                                       ///< projects path
    QString genScriptDir;                                   ///< script path

    //-- Project objects  --//
    QVector<Handover> handovers;                            ///< hondovers data
    QVector<QPair<Cell, Center>> cellsInfo;                 ///< cells data

    //-- Project  data --//
    SgwSettings                     sgwSettings;            ///< SGW
    UCToolSettings                  ucToolSettings;         ///< UCTool
    ChannelModelSettings            channelModelSettings;   ///< Channel Model
    DataGeneratorSettings           dataGeneratorSettings;  ///< Data Generator
    MmeSettings                     mmeSettings;            ///< MME

    PagingSettings                  pagingSettings;         ///< Paging
    UBSimSettings                   ubSimSettings;          ///< UBSim
    GeneralConfigurationParameters  generalConfiguration;   ///< General configuration
    MapRange                        mapRange;               ///< Map range
    UeParameters                    ueParameters;           ///< UE parameters

    //-- Project files --//
    ParametersFileData      parametersFile;                 ///< Parameters data
    QVector<TrafficFileData> trafficFilesList;              ///< Traffics data

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

    /**
     * @brief findHandoverByName is finding handover by name
     * @param name wanted handovers name
     * @return pointer to wanted handovers
     */
    Handover* findHandoverByName(const QString &name);
    /**
     * @brief findCellByName is finding cell by name
     * @param name wanted cells name
     * @return pointer to wanted cells
     */
    QPair<Cell,Center>* findCellByName(const QString &name);
    /**
     * @brief findTrafficFileByName is finding traffic file by name
     * @param name wanted traffic files name
     * @return pointer to wanted traffic file
     */
    TrafficFileData* findTrafficFileByName(const QString &name);
};


#endif // PROJECT_H
