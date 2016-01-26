#ifndef TIMETRAFFIC_H
#define TIMETRAFFIC_H
#include <QString>

class TimeTraffic
{
public:
    TimeTraffic();
    ~TimeTraffic();

    QString get_tab1_AttachRate();
    void set_tab1_AttachRate(QString ar);

    QString get_tab1_DetachRate();
    void set_tab1_DetachRate(QString dr);

    QString get_tab1_StatsRate();
    void set_tab1_StatsRate(QString sr);

    QString get_tab2_AttachRate();
    void set_tab2_AttachRate(QString ar);

    QString get_tab2_DetachRate();
    void set_tab2_DetachRate(QString dr);

    QString get_tab2_StatsRate();
    void set_tab2_StatsRate(QString sr);

    QString get_tab2_CrDrUEPeriod();
    void set_tab2_CrDrUEPeriod(QString uep);


    int getSpn_hours1() const;
    void setSpn_hours1(int value);

    int getSpn_minutes1() const;
    void setSpn_minutes1(int value);

    int getSpn_seconds1() const;
    void setSpn_seconds1(int value);

    int getSpn_hours2() const;
    void setSpn_hours2(int value);

    int getSpn_minutes2() const;
    void setSpn_minutes2(int value);

    int getSpn_seconds2() const;
    void setSpn_seconds2(int value);

    int get_tab1_TimeTrafficDuration() const;
    void set_tab1_TimeTrafficDuration(int value);

    int get_tab2_TimeTrafficDuration() const;
    void set_tab2_TimeTrafficDuration(int value);

private:
    int tab1_attachRate;
    int tab1_detachRate;
    int tab1_statsRate;
    int tab2_attachRate;
    int tab2_detachRate;
    int tab2_statsRate;

    int tab2_crdelUEPeriod;

    int spn_hours1;
    int spn_minutes1;
    int spn_seconds1;
    int spn_hours2;
    int spn_minutes2;
    int spn_seconds2;
    int tab1_timeTrafficDuration;
    int tab2_timeTrafficDuration;
};

#endif // TIMETRAFFIC_H
