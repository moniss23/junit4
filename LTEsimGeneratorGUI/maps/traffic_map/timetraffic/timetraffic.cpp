#include "timetraffic.h"



TimeTraffic::TimeTraffic()
{
    tab1_attachRate = 0;
    tab1_detachRate = 0;
    tab1_statsRate = 0;

    tab1_timeTrafficDuration = 0;


    tab2_attachRate = 0;
    tab2_detachRate = 0;
    tab2_statsRate = 0;

    tab2_timeTrafficDuration = 0;
    tab2_crdelUEPeriod = 0;

    spn_hours1 = 0;
    spn_hours2 = 0;
    spn_minutes1 = 0;
    spn_minutes2 = 0;
    spn_seconds1 = 0;
    spn_seconds2 = 0;
}

TimeTraffic::~TimeTraffic()
{

}

QString TimeTraffic::get_tab1_AttachRate()
{
    return QString::number(tab1_attachRate);
}

void TimeTraffic::set_tab1_AttachRate(QString ar)
{
    tab1_attachRate = ar.toInt();
}

QString TimeTraffic::get_tab1_DetachRate()
{
    return QString::number(tab1_detachRate);
}

void TimeTraffic::set_tab1_DetachRate(QString dr)
{
    tab1_detachRate = dr.toInt();
}

QString TimeTraffic::get_tab1_StatsRate()
{
    return QString::number(tab1_statsRate);
}

void TimeTraffic::set_tab1_StatsRate(QString sr)
{
    tab1_statsRate = sr.toInt();
}


QString TimeTraffic::get_tab2_AttachRate()
{
    return QString::number(tab2_attachRate);
}

void TimeTraffic::set_tab2_AttachRate(QString ar)
{
    tab2_attachRate = ar.toInt();
}

QString TimeTraffic::get_tab2_DetachRate()
{
    return QString::number(tab2_detachRate);
}

void TimeTraffic::set_tab2_DetachRate(QString dr)
{
    tab2_detachRate = dr.toInt();
}

QString TimeTraffic::get_tab2_StatsRate()
{
    return QString::number(tab2_statsRate);
}

void TimeTraffic::set_tab2_StatsRate(QString sr)
{
    tab2_statsRate = sr.toInt();
}

QString TimeTraffic::get_tab2_CrDrUEPeriod()
{
    return QString::number(tab2_crdelUEPeriod);
}

void TimeTraffic::set_tab2_CrDrUEPeriod(QString uep)
{
    tab2_crdelUEPeriod = uep.toInt();
}

int TimeTraffic::getSpn_hours1() const
{
    return spn_hours1;
}

void TimeTraffic::setSpn_hours1(int value)
{
    spn_hours1 = value;
}

int TimeTraffic::getSpn_minutes1() const
{
    return spn_minutes1;
}

void TimeTraffic::setSpn_minutes1(int value)
{
    spn_minutes1 = value;
}

int TimeTraffic::getSpn_seconds1() const
{
    return spn_seconds1;
}

void TimeTraffic::setSpn_seconds1(int value)
{
    spn_seconds1 = value;
}

int TimeTraffic::getSpn_hours2() const
{
    return spn_hours2;
}

int TimeTraffic::getSpn_minutes2() const
{
    return spn_minutes2;
}

void TimeTraffic::setSpn_minutes2(int value)
{
    spn_minutes2 = value;
}

int TimeTraffic::getSpn_seconds2() const
{
    return spn_seconds2;
}

void TimeTraffic::setSpn_seconds2(int value)
{
    spn_seconds2 = value;
}

int TimeTraffic::get_tab2_TimeTrafficDuration() const
{
    return tab2_timeTrafficDuration;
}

void TimeTraffic::set_tab2_TimeTrafficDuration(int value)
{
    tab2_timeTrafficDuration = value;
}

void TimeTraffic::setSpn_hours2(int value)
{
    spn_hours2 = value;
}

int TimeTraffic::get_tab1_TimeTrafficDuration() const
{
    return tab1_timeTrafficDuration;
}

void TimeTraffic::set_tab1_TimeTrafficDuration(int value)
{
    tab1_timeTrafficDuration = value;
}


