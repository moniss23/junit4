#ifndef STATISTICSDATA_H
#define STATISTICSDATA_H

#include <QObject>
#include <QString>
#include <QPair>
#include <QVector>
#include "Data/Interfaces/serializeinterface.h"

class StatisticsData : public SerializeInterface
{
public:
    StatisticsData();
    ~StatisticsData();

    /**
     * @brief getStatMapFor returns bool type value
     * @param key is a "key" in statisticsMap
     */
    bool getStatMapFor(QString key) const;
    /**
     * @brief setStatMapFor sets new value in statisticsMap
     * @param key is a "key" in statisticsMap
     * @param value is a new value for provided key
     */
    void setStatMapFor(QString key, bool value=false);

    // SerializeInterface interface
public:
    /**
     * @brief serializeData is an inherited method that serializes this class to QByteArray
     */
    QByteArray serializeData();
    /**
     * @brief deserializeData ia an inherited method that deserializes it's parameter to fill the fields in this class' instance
     * @param rawData is QByteArray that contains all the data needed to creata an instance of StatisticsData class
     */
    void deserializeData(const QByteArray &rawData);
    /**
     * @brief getElementType is a API method to recognise the object by QString
     */
    QString getElementType() const;


public:

    const static QStringList namesList;

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

private:
    QVector<QPair<QString,bool>> statisticsMap;
};

#endif // STATISTICSDATA_H
