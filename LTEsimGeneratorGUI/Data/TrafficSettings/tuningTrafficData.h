#ifndef TuningTrafficData_H
#define TuningTrafficData_H
#include <QString>
#include <QVector>

#include "Data/Interfaces/serializeinterface.h"

class TuningTrafficData : public SerializeInterface
{
public:
    TuningTrafficData();
    ~TuningTrafficData();

    //Public structs representing CS/PS/Mobility parameters
    struct CSParameters
    {
        QString csName;
        double callIntensity;
        double callDuration;
        double recoveryStartInterval;

        CSParameters (const QString &name, const double &callIntensity = 1, const double &callDuration = 1, const double &recoveryStartInterval = 1 ){
            csName = name;
            this->callIntensity = callIntensity;
            this->callDuration = callDuration;
            this->recoveryStartInterval = recoveryStartInterval;
        }
    };

    struct PSParameters
    {
        QString psName;
        double psDuration;
        double psIntensity;

        PSParameters (const QString &name, const double &psIntensity = 1, const double &psDuration = 1) {
            this->psName = name;
            this->psDuration = psDuration;
            this->psIntensity = psIntensity;
        }
    };

    struct Mobility
    {
        QString mobilityName;
        double speed;
        double granularity;

        Mobility (const QString &name, const double &speed = 1, const double &granularity = 1) {
            this->mobilityName = name;
            this->speed = speed;
            this->granularity = granularity;
        }
    };

    const static QStringList CSSTRINGLIST;
    const static QStringList PSSTRINGLIST;
    const static QStringList MOBILITYSTRINGLIST;

    //Vectors for temporary saved/set model parameters
    QVector<CSParameters*> csParamGroup;
    QVector<PSParameters*> psParamGroup;
    QVector<Mobility*> mobilityGroup;

    // SerializeInterface interface
public:
    QString getElementType() const;
    QByteArray serializeData();
    void deserializeData(const QByteArray &rawData);
};

#endif // TuningTrafficData_H
