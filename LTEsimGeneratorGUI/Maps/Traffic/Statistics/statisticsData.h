#ifndef STATISTICSDATA_H
#define STATISTICSDATA_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QVector>

class StatisticsData
{
public:
    StatisticsData();
    StatisticsData(const StatisticsData& statisticsData);

    /**
     * @brief operator = is used to copy StatisticsData to a local object
     * @param data is being coppied
     */
    StatisticsData& operator =(const StatisticsData& data);

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
    QVector<std::tuple<QString,bool>> statisticsMap;
};

#endif // STATISTICSDATA_H
