#ifndef STATISTICSDATA_H
#define STATISTICSDATA_H

#include <QObject>
#include <QString>
#include <QVector>

#include "Data/Interfaces/serializeinterface.h"

/**
 * @brief The StatisticsData class is responsible for data about statistics that should be provided in LTEsim output.
 */
class StatisticsData : public SerializeInterface
{
public:
    StatisticsData();
    ~StatisticsData();

    const static QStringList NAMESLIST;

    /**********************************************************
     * FIELDS STORING DATA INPUTS FROM STATISTCSFORM
     *********************************************************/
    QString generalUe;
    QString generalDelayBetweenPackets;
    QString generalTotalNumberOfSeconds;
    QString generalMtuSize;
    QString generalMeasurementDelta;

    QString ipexTguImsi;
    QString ipexFileName;
    QString ipexSeconds;
    QString ipexMeasurement;

    QString pdcpuBearerStatusImsi;
    QString pdcpuBearerStatusEpsBearerId;
    QString pdcpuBearerRohcImsi;
    QString pdcpuBearerRohcEpsBearerId;
    QString pdcpuBearerErrorImsi;
    QString pdcpuBearerErrorEpsBearerId;
    QString pdcpuFileName;
    QString pdcpuSeconds;
    QString pdcpuMeasurement;

    /**
     * @brief statisticsMap stores the information about certain statistics to be calculated
     */
    QVector<QPair<QString,bool>> statisticsMap;

    void setStatMapFor(QString key, bool value);
    bool getStatMapFor(QString key) const;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    /**
     * @brief serializeData is an inherited method that serializes this class to QByteArray
     * @return QByteArray with all class members serialized
     */
    virtual QByteArray serializeData();
    /**
     * @brief deserializeData ia an inherited method that deserializes it's parameter to fill the fields in this class' instance
     * @param rawData is QByteArray that contains all the data needed to creata an instance of StatisticsData class
     */
    virtual void deserializeData(const QByteArray &rawData);
    /**
     * @brief getElementType is a API method to recognise the object by QString
     * @return  QString("SettingsData")
     */
    virtual QString getElementType() const;
};

#endif // STATISTICSDATA_H
