#ifndef TIMETRAFFIC_H
#define TIMETRAFFIC_H
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

    int getSpn_hours1() const;
    void setSpn_hours1(int);

    int getSpn_minutes1() const;
    void setSpn_minutes1(int);

    int getSpn_seconds1() const;
    void setSpn_seconds1(int);

    int getSpn_hours2() const;
    void setSpn_hours2(int);

    int getSpn_minutes2() const;
    void setSpn_minutes2(int);

    int getSpn_seconds2() const;
    void setSpn_seconds2(int);

    int get_tab1_TimeTrafficDuration() const;
    void set_tab1_TimeTrafficDuration(int);

    int get_tab2_TimeTrafficDuration() const;
    void set_tab2_TimeTrafficDuration(int);

private:
    int tab1_attachRate, tab1_detachRate, tab1_statsRate;
    int tab2_attachRate, tab2_detachRate, tab2_statsRate;

    int tab2_crdelUEPeriod;

    int spn_hours1, spn_minutes1, spn_seconds1;
    int spn_hours2, spn_minutes2, spn_seconds2;
    int tab1_timeTrafficDuration, tab2_timeTrafficDuration;
};

#endif // TIMETRAFFIC_H
