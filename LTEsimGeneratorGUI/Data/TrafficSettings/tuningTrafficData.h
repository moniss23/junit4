#ifndef TuningTrafficData_H
#define TuningTrafficData_H
#include <QString>
#include <QVector>

#include "Data/Interfaces/serializeinterface.h"

/**
 * @brief The StatisticsData class is responsible for data about statistics that should be provided in LTEsim output.
 */
class TuningTrafficData : public SerializeInterface
{
public:
    TuningTrafficData();
    ~TuningTrafficData();

    /**
     * @brief The CSParameters struct represents CS parameters
     */
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

    /**
     * @brief The PSParameters struct represents PS parameters
     */
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

    /**
     * @brief The Mobility struct represents  mobility parameters
     */
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

    /**************************************************************************
     * STATIC QSTRINGLISTS WITH NAMES OF CS/PS/MOBILITY PAREAMETERS
     **************************************************************************/
    const static QStringList CSSTRINGLIST;
    const static QStringList PSSTRINGLIST;
    const static QStringList MOBILITYSTRINGLIST;

    /**********************************************
     * VECTORS FOR SAVED MODEL PARAMETERS
     **********************************************/
    QVector<CSParameters*> csParamGroup;
    QVector<PSParameters*> psParamGroup;
    QVector<Mobility*> mobilityGroup;

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

#endif // TuningTrafficData_H
