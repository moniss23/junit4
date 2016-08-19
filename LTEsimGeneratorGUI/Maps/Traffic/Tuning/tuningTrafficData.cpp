#include "tuningTrafficData.h"

TuningTrafficData::TuningTrafficData()
{
    psBehaviorIndex = csBehaviorIndex = areaIndex = 0;

    combo = new QComboBox();
    CSParamGroup = QVector<CSParameters* >();
    PSParamGroup = QVector<PSParameters* >();
    areaGroup = QVector<Areas* >();

    CSParamGroup.push_back(new CSParameters());
    PSParamGroup.push_back(new PSParameters());
    areaGroup.push_back(new Areas());
}

TuningTrafficData::~TuningTrafficData()
{
    for (int i = 0; i < CSParamGroup.size(); ++i){
        delete CSParamGroup[i];
    }
    CSParamGroup.clear();

    for (int i = 0; i < PSParamGroup.size(); ++i){
        delete PSParamGroup[i];
    }
    PSParamGroup.clear();

    for (int i = 0; i < areaGroup.size(); ++i){
        delete areaGroup[i];
    }
    areaGroup.clear();
}

QString TuningTrafficData::getSpeed(int index) const { return areaGroup[index]->speed; }
void TuningTrafficData::setSpeed(QString speed, int index) { areaGroup[index]->speed = speed;}

QString TuningTrafficData::getGranularity(int index) const { return areaGroup[index]->granularity; }
void TuningTrafficData::setGranularity(QString granularity, int index) { areaGroup[index]->granularity = granularity; }

QString TuningTrafficData::getCall_intensity(int index) const { return CSParamGroup[index]->call_intensity; }
void TuningTrafficData::setCall_intensity(QString intensity, int index) { CSParamGroup[index]->call_intensity = intensity;}

QString TuningTrafficData::getCall_duration(int index) const { return CSParamGroup[index]->call_duration; }
void TuningTrafficData::setCall_duration(QString duration, int index) { CSParamGroup[index]->call_duration = duration; }

QString TuningTrafficData::getPS_intensity(int index) const { return PSParamGroup[index]->ps_intensity; }
void TuningTrafficData::setPs_intensity(QString intensity, int index) { PSParamGroup[index]->ps_intensity = intensity; }

QString TuningTrafficData::getPs_duration(int index) const {return PSParamGroup[index]->ps_duration; }
void TuningTrafficData::setPs_duration(QString duration, int index) { PSParamGroup[index]->ps_duration = duration; }

QString TuningTrafficData::getRecovery_start_interval(int index) const { return CSParamGroup[index]->recovery_start_interval; }
void TuningTrafficData::setRecovery_start_interval(QString value, int index) { CSParamGroup[index]->recovery_start_interval = value; }

QString TuningTrafficData::getCs_Name(int index) const { return CSParamGroup[index]->cs_name; }
void TuningTrafficData::setCs_Name(QString value, int index) { CSParamGroup[index]->cs_name = value; }

QString TuningTrafficData::getPs_Name(int index) const { return PSParamGroup[index]->ps_name; }
void TuningTrafficData::setPs_Name(QString value, int index) { PSParamGroup[index]->ps_name = value; }

QString TuningTrafficData::getArea_name(int index) const { return areaGroup[index]->area_name; }
void TuningTrafficData::setArea_Name(QString value, int index) { areaGroup[index]->area_name = value; }

int TuningTrafficData::get_csBehaviorIndex() const { return csBehaviorIndex; }
void TuningTrafficData::set_csBehaviorIndex(int value) { csBehaviorIndex = value; }

int TuningTrafficData::get_AreaIndex() const { return areaIndex; }
void TuningTrafficData::set_AreaIndex(int value) { areaIndex = value; }

//--------Group Getters-------------------
QVector<TuningTrafficData::CSParameters *> TuningTrafficData::getCSParamGroup() const { return CSParamGroup; }
QVector<TuningTrafficData::PSParameters *> TuningTrafficData::getPSParamGroup() const { return PSParamGroup; }
QVector<TuningTrafficData::Areas *> TuningTrafficData::getAreaGroup() const { return areaGroup; }



void TuningTrafficData::pushCSModel() { CSParamGroup.push_back(new TuningTrafficData::CSParameters()); }
void TuningTrafficData::popCSModel() { CSParamGroup.pop_back();}

void TuningTrafficData::pushPSModel() { PSParamGroup.push_back(new TuningTrafficData::PSParameters()); }
void TuningTrafficData::popPSModel() { PSParamGroup.pop_back(); }

void TuningTrafficData::pushAreaModel() { areaGroup.push_back(new Areas()); }
void TuningTrafficData::popAreaModel() { areaGroup.pop_back(); }

void TuningTrafficData::setCSParamGroup(const QVector<CSParameters *> &value) { CSParamGroup = value; }

void TuningTrafficData::setPSParamGroup(const QVector<PSParameters *> &value) { PSParamGroup = value; }

void TuningTrafficData::setAreaGroup(const QVector<Areas *> &value) { areaGroup = value; }

void TuningTrafficData::csInitialize(int size_value)
{
    CSParamGroup.resize(0);
    for (int i = 0; i < size_value; ++i){
        CSParamGroup.push_back(new TuningTrafficData::CSParameters());
    }
}

void TuningTrafficData::psInitialize(int size_value)
{
    PSParamGroup.resize(0);
    for (int i = 0; i < size_value; ++i){
        PSParamGroup.push_back(new TuningTrafficData::PSParameters());
    }
}

void TuningTrafficData::areaInitialize(int size_value)
{
    areaGroup.resize(0);
    for (int i = 0; i < size_value; ++i){
        areaGroup.push_back(new TuningTrafficData::Areas());
    }
}

int TuningTrafficData::get_psBehaviorIndex() const { return psBehaviorIndex; }
void TuningTrafficData::set_psBehaviorIndex(int value) { psBehaviorIndex = value; }
