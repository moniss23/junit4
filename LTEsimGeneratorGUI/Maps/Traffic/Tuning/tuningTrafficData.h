#ifndef TuningTrafficData_H
#define TuningTrafficData_H
#include <QString>
#include <QVector>

class TuningTrafficData
{
public:
    TuningTrafficData();
    ~TuningTrafficData();

    //Public structs representing CS/PS/Mobility parameters
    struct CSParameters
    {
        QString csName;
        QString callIntensity;
        QString callDuration;
        QString recoveryStartInterval;

        CSParameters(){csName = ""; callIntensity = "0"; callDuration = "0"; recoveryStartInterval = "0";}
    };

    struct PSParameters
    {
        QString psName;
        QString psDuration;
        QString psIntensity;

        PSParameters() {psName = ""; psDuration = "0"; psIntensity = "0";}
    };

    struct Mobility
    {
        QString mobilityName;
        QString speed;
        QString granularity;

        Mobility(){mobilityName = ""; speed = "0"; granularity = "0";}
    };

    void setSpeed(QString value, int index);
    QString getSpeed(int index) const;

    void setGranularity(QString value, int index);
    QString getGranularity(int index) const;

    void setCall_intensity(QString value, int index);
    QString getCall_intensity(int index) const;

    void setCall_duration(QString value, int index);
    QString getCall_duration(int index) const;

    void setPs_intensity(QString value, int index);
    QString getPS_intensity(int index) const;

    void setPs_duration(QString value, int index);
    QString getPs_duration(int index) const;

    void setRecovery_start_interval(QString value, int index);
    QString getRecovery_start_interval(int index) const;

    void setCs_Name(QString value, int index);
    QString getCs_Name(int index) const;

    void setPs_Name(QString value, int index);
    QString getPs_Name(int index) const;

    void setMobility_Name(QString value, int index);
    QString getMobility_name(int index) const;

    int get_psBehaviorIndex() const;
    void set_psBehaviorIndex(int value);

    int get_csBehaviorIndex() const;
    void set_csBehaviorIndex(int value);

    int get_MobilityIndex() const;
    void set_MobilityIndex(int value);


    QVector<CSParameters *> getCSParamGroup() const;
    void setCSParamGroup(const QVector<CSParameters *> &value);
    QVector<PSParameters *> getPSParamGroup() const;
    void setPSParamGroup(const QVector<PSParameters *> &value);
    QVector<Mobility *> getMobilityGroup() const;
    void setMobilityGroup(const QVector<Mobility *> &value);

    void csInitialize(int size_value);
    void psInitialize(int size_value);
    void mobilityInitialize(int size_value);

    void pushCSModel();
    void popCSModel();

    void pushPSModel();
    void popPSModel();

    void pushMobilityModel();
    void popMobilityModel();

private:
    //Vectors for temporary saved/set model parameters
    QVector<CSParameters*> csParamGroup;
    QVector<PSParameters*> psParamGroup;
    QVector<Mobility*> mobilityGroup;

    int psBehaviorIndex;
    int csBehaviorIndex;
    int mobilityIndex;
};

#endif // TuningTrafficData_H
