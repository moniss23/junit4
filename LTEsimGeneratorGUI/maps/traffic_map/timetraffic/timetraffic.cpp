#include "timetraffic.h"

TimeTraffic::TimeTraffic()
{
    tab1_attachRate = tab1_detachRate = tab1_statsRate = 0;
    tab2_attachRate = tab2_detachRate = tab2_statsRate = 0;
    tab1_timeTrafficDuration = tab2_timeTrafficDuration = 0;

    tab2_crdelUEPeriod = 0;

    spn_hours1 = spn_minutes1 = spn_seconds1 = 0;
    spn_hours2 = spn_minutes2 = spn_seconds2 = 0;
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

int TimeTraffic::getSpn_hours1() const {return spn_hours1;}
void TimeTraffic::setSpn_hours1(int hours) {spn_hours1 = hours;}

int TimeTraffic::getSpn_minutes1() const {return spn_minutes1;}
void TimeTraffic::setSpn_minutes1(int minutes) {spn_minutes1 = minutes;}

int TimeTraffic::getSpn_seconds1() const {return spn_seconds1;}
void TimeTraffic::setSpn_seconds1(int seconds) {spn_seconds1 = seconds;}

int TimeTraffic::getSpn_hours2() const {return spn_hours2;}
void TimeTraffic::setSpn_hours2(int hours) {spn_hours2 = hours;}

int TimeTraffic::getSpn_minutes2() const {return spn_minutes2;}
void TimeTraffic::setSpn_minutes2(int minutes) {spn_minutes2 = minutes;}

int TimeTraffic::getSpn_seconds2() const {return spn_seconds2;}
void TimeTraffic::setSpn_seconds2(int seconds) {spn_seconds2 = seconds;}

int TimeTraffic::get_tab1_TimeTrafficDuration() const {return tab1_timeTrafficDuration;}
void TimeTraffic::set_tab1_TimeTrafficDuration(int duration) {tab1_timeTrafficDuration = duration;}

int TimeTraffic::get_tab2_TimeTrafficDuration() const {return tab2_timeTrafficDuration;}
void TimeTraffic::set_tab2_TimeTrafficDuration(int duration) {tab2_timeTrafficDuration = duration;}
