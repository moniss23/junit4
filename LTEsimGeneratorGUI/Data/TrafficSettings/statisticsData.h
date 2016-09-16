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

    const static QStringList NAMESLIST;

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

    QVector<QPair<QString,bool>> statisticsMap;

    void setStatMapFor(QString key, bool value);
    bool getStatMapFor(QString key) const;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    /**
     * @brief serializeData is an inherited method that serializes this class to QByteArray
     */
    virtual QByteArray serializeData();
    /**
     * @brief deserializeData ia an inherited method that deserializes it's parameter to fill the fields in this class' instance
     * @param rawData is QByteArray that contains all the data needed to creata an instance of StatisticsData class
     */
    virtual void deserializeData(const QByteArray &rawData);
    /**
     * @brief getElementType is a API method to recognise the object by QString
     */
    virtual QString getElementType() const;
};

#endif // STATISTICSDATA_H
