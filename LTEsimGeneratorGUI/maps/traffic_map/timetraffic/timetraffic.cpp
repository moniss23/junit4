#include "timetraffic.h"

TimeTraffic::TimeTraffic()
{
    tab1_attachRate = tab1_detachRate = tab1_statsRate = 0;
    tab2_attachRate = tab2_detachRate = tab2_statsRate = 0;
    tab1_timeTrafficDuration = tab2_timeTrafficDuration = 0;

    tab2_crdelUEPeriod = 0;
}

TimeTraffic::~TimeTraffic()
{
}

QString TimeTraffic::get_tab1_AttachRate() const {return QString::number(tab1_attachRate);}
void TimeTraffic::set_tab1_AttachRate(QString rate) {tab1_attachRate = rate.toInt();}

QString TimeTraffic::get_tab1_DetachRate() const {return QString::number(tab1_detachRate);}
void TimeTraffic::set_tab1_DetachRate(QString rate) {tab1_detachRate = rate.toInt();}

QString TimeTraffic::get_tab1_StatsRate() const {return QString::number(tab1_statsRate);}
void TimeTraffic::set_tab1_StatsRate(QString rate) {tab1_statsRate = rate.toInt();}

QString TimeTraffic::get_tab2_AttachRate() const {return QString::number(tab2_attachRate);}
void TimeTraffic::set_tab2_AttachRate(QString rate) {tab2_attachRate = rate.toInt();}

QString TimeTraffic::get_tab2_DetachRate() const {return QString::number(tab2_detachRate);}
void TimeTraffic::set_tab2_DetachRate(QString rate) {tab2_detachRate = rate.toInt();}

QString TimeTraffic::get_tab2_StatsRate() const {return QString::number(tab2_statsRate);}
void TimeTraffic::set_tab2_StatsRate(QString rate) {tab2_statsRate = rate.toInt();}

QString TimeTraffic::get_tab2_CrDrUEPeriod() const {return QString::number(tab2_crdelUEPeriod);}
void TimeTraffic::set_tab2_CrDrUEPeriod(QString period) {tab2_crdelUEPeriod = period.toInt();}


QTime TimeTraffic::getSpn_time1() const {
    return spn_time1;
}
void TimeTraffic::setSpn_time1(int hours, int minutes, int seconds) {
    spn_time1.setHMS(hours, minutes, seconds);
}

QTime TimeTraffic::getSpn_time2() const {
    return spn_time2;
}
void TimeTraffic::setSpn_time2(int hours, int minutes, int seconds) {
    spn_time2.setHMS(hours, minutes, seconds);
}

int TimeTraffic::get_tab1_TimeTrafficDuration() const {return tab1_timeTrafficDuration;}
void TimeTraffic::set_tab1_TimeTrafficDuration(int duration) {tab1_timeTrafficDuration = duration;}

int TimeTraffic::get_tab2_TimeTrafficDuration() const {return tab2_timeTrafficDuration;}
void TimeTraffic::set_tab2_TimeTrafficDuration(int duration) {tab2_timeTrafficDuration = duration;}
