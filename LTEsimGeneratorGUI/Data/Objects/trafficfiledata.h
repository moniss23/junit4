#ifndef TRAFFICFILEDATA_H
#define TRAFFICFILEDATA_H

#include <QVector>

#include "Data/TrafficSettings/uedata.h"
#include "Data/Interfaces/serializeinterface.h"
#include "Data/TrafficSettings/statisticsData.h"
#include "Data/TrafficSettings/custommodelsettings.h"
#include "Data/TrafficSettings/tuningTrafficData.h"
#include "Data/TrafficSettings/timeData.h"

/**
 * @brief The TrafficFileData class contains data that is needed to generate traffic script
 */
class TrafficFileData : public SerializeInterface
{
public:
    /**
     * @brief TrafficFileData default constructor
     */
    TrafficFileData();

    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/

    QString content;                            ///< traffic script content
    QString filename;                           ///< traffic file name
    StatisticsData statisticsData;              ///< local copy of statistics Data
    QVector<UEData> userEquipments;             ///< vector of ue (default 0)
    QVector<CustomModelSettings> customModels;  ///< vector of customModels (default 10)
    TuningTrafficData tuningTrafficData;        ///< local copy of tunningtraffic data
    TimeData timeData;                          ///< local copy of time data
    static const int cmAmount = 10;             ///< Amount of custom models
    bool cmUsed[cmAmount];                      ///< table of used customModels

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
public:
    ~TrafficFileData() {}

    /**
     * @brief getElementType is a API method to recognise the object by QString
     * @return QString("TrafficFileData")
     */
    virtual QString getElementType() const;
    /**
     * @brief serializeData is an inherited method that serializes this class to QByteArray
     * @return QByteArray with serialized object of the class
     */
    virtual QByteArray serializeData();
    /**
     * @brief deserializeData ia an inherited method that deserializes it's parameter to fill the fields in this class' instance
     * @param rawData is QByteArray that contains all the data needed to creata an instance of trafficFileData class
     */
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // TRAFFICFILEDATA_H
