#include "timeData.h"

TimeData::TimeData()
{
    tab1_attachRate = tab1_detachRate = tab1_statsRate = 0;
    tab2_attachRate = tab2_detachRate = tab2_statsRate = 0;
    tab1_timeTrafficDuration = tab2_timeTrafficDuration = 0;

    tab2_crdelUEPeriod = 0;
}

TimeData::~TimeData()
{
}

QString TimeData::get_tab1_AttachRate() const {return QString::number(tab1_attachRate);}
void TimeData::set_tab1_AttachRate(QString rate) {tab1_attachRate = rate.toInt();}

QString TimeData::get_tab1_DetachRate() const {return QString::number(tab1_detachRate);}
void TimeData::set_tab1_DetachRate(QString rate) {tab1_detachRate = rate.toInt();}

QString TimeData::get_tab1_StatsRate() const {return QString::number(tab1_statsRate);}
void TimeData::set_tab1_StatsRate(QString rate) {tab1_statsRate = rate.toInt();}

QString TimeData::get_tab2_AttachRate() const {return QString::number(tab2_attachRate);}
void TimeData::set_tab2_AttachRate(QString rate) {tab2_attachRate = rate.toInt();}

QString TimeData::get_tab2_DetachRate() const {return QString::number(tab2_detachRate);}
void TimeData::set_tab2_DetachRate(QString rate) {tab2_detachRate = rate.toInt();}

QString TimeData::get_tab2_StatsRate() const {return QString::number(tab2_statsRate);}
void TimeData::set_tab2_StatsRate(QString rate) {tab2_statsRate = rate.toInt();}

QString TimeData::get_tab2_CrDrUEPeriod() const {return QString::number(tab2_crdelUEPeriod);}
void TimeData::set_tab2_CrDrUEPeriod(QString period) {tab2_crdelUEPeriod = period.toInt();}


QTime TimeData::getSpn_time1() const {
    return spn_time1;
}
void TimeData::setSpn_time1(int hours, int minutes, int seconds) {
    spn_time1.setHMS(hours, minutes, seconds);
}

QTime TimeData::getSpn_time2() const {
    return spn_time2;
}
void TimeData::setSpn_time2(int hours, int minutes, int seconds) {
    spn_time2.setHMS(hours, minutes, seconds);
}

int TimeData::get_tab1_TimeTrafficDuration() const {return tab1_timeTrafficDuration;}
void TimeData::set_tab1_TimeTrafficDuration(int duration) {tab1_timeTrafficDuration = duration;}

int TimeData::get_tab2_TimeTrafficDuration() const {return tab2_timeTrafficDuration;}
void TimeData::set_tab2_TimeTrafficDuration(int duration) {tab2_timeTrafficDuration = duration;}
