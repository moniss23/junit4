#ifndef TuningTrafficData_H
#define TuningTrafficData_H
#include <QString>
#include <QComboBox>
class TuningTrafficData
{
public:
    TuningTrafficData();
    ~TuningTrafficData();

    //Public structs representing CS/PS/Area parameters
    struct CSParameters
    {
        QString cs_name;
        QString call_intensity;
        QString call_duration;
        QString recovery_start_interval;

        CSParameters(){cs_name = ""; call_intensity = "0"; call_duration = "0"; recovery_start_interval = "0";}
    };

    struct PSParameters
    {
        QString ps_name;
        QString ps_duration;
        QString ps_intensity;

        PSParameters() {ps_name = ""; ps_duration = "0"; ps_intensity = "0";}
    };

    struct Areas
    {
        QString area_name;
        QString speed;
        QString granularity;

        Areas(){area_name = ""; speed = "0"; granularity = "0";}
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

    void setArea_Name(QString value, int index);
    QString getArea_name(int index) const;

    int get_psBehaviorIndex() const;
    void set_psBehaviorIndex(int value);

    int get_csBehaviorIndex() const;
    void set_csBehaviorIndex(int value);

    int get_AreaIndex() const;
    void set_AreaIndex(int value);


    QVector<CSParameters *> getCSParamGroup() const;
    void setCSParamGroup(const QVector<CSParameters *> &value);
    QVector<PSParameters *> getPSParamGroup() const;
    void setPSParamGroup(const QVector<PSParameters *> &value);
    QVector<Areas *> getAreaGroup() const;
    void setAreaGroup(const QVector<Areas *> &value);

    void csInitialize(int size_value);
    void psInitialize(int size_value);
    void areaInitialize(int size_value);

    void pushCSModel();
    void popCSModel();

    void pushPSModel();
    void popPSModel();

    void pushAreaModel();
    void popAreaModel();

private:
    //Vectors for temporary saved/set model parameters
    QVector<CSParameters* > CSParamGroup;
    QVector<PSParameters* > PSParamGroup;
    QVector<Areas*> areaGroup;

    int psBehaviorIndex;
    int csBehaviorIndex;
    int areaIndex;
    QComboBox *combo;
};

#endif // TuningTrafficData_H
