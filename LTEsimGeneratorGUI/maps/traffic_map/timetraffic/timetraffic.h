#ifndef TIMETRAFFIC_H
#define TIMETRAFFIC_H
#include <QTime>
#include <QString>

class TimeTraffic
{
public:
    TimeTraffic();
    ~TimeTraffic();

    QString get_tab1_AttachRate() const;
    void set_tab1_AttachRate(QString);

    QString get_tab1_DetachRate() const;
    void set_tab1_DetachRate(QString);

    QString get_tab1_StatsRate() const;
    void set_tab1_StatsRate(QString);

    QString get_tab2_AttachRate() const;
    void set_tab2_AttachRate(QString);

    QString get_tab2_DetachRate() const;
    void set_tab2_DetachRate(QString);

    QString get_tab2_StatsRate() const;
    void set_tab2_StatsRate(QString);

    QString get_tab2_CrDrUEPeriod() const;
    void set_tab2_CrDrUEPeriod(QString);

    QTime getSpn_time1() const;
    void setSpn_time1(int, int, int);

    QTime getSpn_time2() const;
    void setSpn_time2(int, int, int);

    int get_tab1_TimeTrafficDuration() const;
    void set_tab1_TimeTrafficDuration(int);

    int get_tab2_TimeTrafficDuration() const;
    void set_tab2_TimeTrafficDuration(int);

private:
    QTime spn_time1, spn_time2;
    int tab1_attachRate, tab1_detachRate, tab1_statsRate;
    int tab2_attachRate, tab2_detachRate, tab2_statsRate;
    int tab1_timeTrafficDuration, tab2_timeTrafficDuration;

    int tab2_crdelUEPeriod;
};

#endif // TIMETRAFFIC_H
