#include "tuningtraffic.h"

Tuningtraffic::Tuningtraffic()
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

Tuningtraffic::~Tuningtraffic()
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

QString Tuningtraffic::getSpeed(int index) const { return areaGroup[index]->speed; }
void Tuningtraffic::setSpeed(QString speed, int index) { areaGroup[index]->speed = speed;}

QString Tuningtraffic::getGranularity(int index) const { return areaGroup[index]->granularity; }
void Tuningtraffic::setGranularity(QString granularity, int index) { areaGroup[index]->granularity = granularity; }

QString Tuningtraffic::getCall_intensity(int index) const { return CSParamGroup[index]->call_intensity; }
void Tuningtraffic::setCall_intensity(QString intensity, int index) { CSParamGroup[index]->call_intensity = intensity;}

QString Tuningtraffic::getCall_duration(int index) const { return CSParamGroup[index]->call_duration; }
void Tuningtraffic::setCall_duration(QString duration, int index) { CSParamGroup[index]->call_duration = duration; }

QString Tuningtraffic::getPS_intensity(int index) const { return PSParamGroup[index]->ps_intensity; }
void Tuningtraffic::setPs_intensity(QString intensity, int index) { PSParamGroup[index]->ps_intensity = intensity; }

QString Tuningtraffic::getPs_duration(int index) const {return PSParamGroup[index]->ps_duration; }
void Tuningtraffic::setPs_duration(QString duration, int index) { PSParamGroup[index]->ps_duration = duration; }

QString Tuningtraffic::getRecovery_start_interval(int index) const { return CSParamGroup[index]->recovery_start_interval; }
void Tuningtraffic::setRecovery_start_interval(QString value, int index) { CSParamGroup[index]->recovery_start_interval = value; }

QString Tuningtraffic::getCs_Name(int index) const { return CSParamGroup[index]->cs_name; }
void Tuningtraffic::setCs_Name(QString value, int index) { CSParamGroup[index]->cs_name = value; }

QString Tuningtraffic::getPs_Name(int index) const { return PSParamGroup[index]->ps_name; }
void Tuningtraffic::setPs_Name(QString value, int index) { PSParamGroup[index]->ps_name = value; }

QString Tuningtraffic::getArea_name(int index) const { return areaGroup[index]->area_name; }
void Tuningtraffic::setArea_Name(QString value, int index) { areaGroup[index]->area_name = value; }

int Tuningtraffic::get_csBehaviorIndex() const { return csBehaviorIndex; }
void Tuningtraffic::set_csBehaviorIndex(int value) { csBehaviorIndex = value; }

int Tuningtraffic::get_AreaIndex() const { return areaIndex; }
void Tuningtraffic::set_AreaIndex(int value) { areaIndex = value; }

//--------Group Getters-------------------
QVector<Tuningtraffic::CSParameters *> Tuningtraffic::getCSParamGroup() const { return CSParamGroup; }
QVector<Tuningtraffic::PSParameters *> Tuningtraffic::getPSParamGroup() const { return PSParamGroup; }
QVector<Tuningtraffic::Areas *> Tuningtraffic::getAreaGroup() const { return areaGroup; }



void Tuningtraffic::pushCSModel() { CSParamGroup.push_back(new Tuningtraffic::CSParameters()); }
void Tuningtraffic::popCSModel() { CSParamGroup.pop_back();}

void Tuningtraffic::pushPSModel() { PSParamGroup.push_back(new Tuningtraffic::PSParameters()); }
void Tuningtraffic::popPSModel() { PSParamGroup.pop_back(); }

void Tuningtraffic::pushAreaModel() { areaGroup.push_back(new Areas()); }
void Tuningtraffic::popAreaModel() { areaGroup.pop_back(); }

void Tuningtraffic::setCSParamGroup(const QVector<CSParameters *> &value) { CSParamGroup = value; }

void Tuningtraffic::setPSParamGroup(const QVector<PSParameters *> &value) { PSParamGroup = value; }

void Tuningtraffic::setAreaGroup(const QVector<Areas *> &value) { areaGroup = value; }

void Tuningtraffic::csInitialize(int size_value)
{
    CSParamGroup.resize(0);
    for (int i = 0; i < size_value; ++i){
        CSParamGroup.push_back(new Tuningtraffic::CSParameters());
    }
}

void Tuningtraffic::psInitialize(int size_value)
{
    PSParamGroup.resize(0);
    for (int i = 0; i < size_value; ++i){
        PSParamGroup.push_back(new Tuningtraffic::PSParameters());
    }
}

void Tuningtraffic::areaInitialize(int size_value)
{
    areaGroup.resize(0);
    for (int i = 0; i < size_value; ++i){
        areaGroup.push_back(new Tuningtraffic::Areas());
    }
}

int Tuningtraffic::get_psBehaviorIndex() const { return psBehaviorIndex; }
void Tuningtraffic::set_psBehaviorIndex(int value) { psBehaviorIndex = value; }
