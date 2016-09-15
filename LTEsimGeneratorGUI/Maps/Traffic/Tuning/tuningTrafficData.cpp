#include "tuningTrafficData.h"

TuningTrafficData::TuningTrafficData()
{
    psBehaviorIndex = csBehaviorIndex = mobilityIndex = 0;

    csParamGroup = QVector<CSParameters* >();
    psParamGroup = QVector<PSParameters* >();
    mobilityGroup = QVector<Mobility* >();

    csParamGroup.push_back(new CSParameters());
    psParamGroup.push_back(new PSParameters());
    mobilityGroup.push_back(new Mobility());
}

TuningTrafficData::~TuningTrafficData()
{
    for (int i = 0; i < csParamGroup.size(); ++i){
        delete csParamGroup[i];
    }
    csParamGroup.clear();

    for (int i = 0; i < psParamGroup.size(); ++i){
        delete psParamGroup[i];
    }
    psParamGroup.clear();

    for (int i = 0; i < mobilityGroup.size(); ++i){
        delete mobilityGroup[i];
    }
    mobilityGroup.clear();
}

QString TuningTrafficData::getSpeed(int index) const { return mobilityGroup[index]->speed; }
void TuningTrafficData::setSpeed(QString speed, int index) { mobilityGroup[index]->speed = speed;}

QString TuningTrafficData::getGranularity(int index) const { return mobilityGroup[index]->granularity; }
void TuningTrafficData::setGranularity(QString granularity, int index) { mobilityGroup[index]->granularity = granularity; }

QString TuningTrafficData::getCall_intensity(int index) const { return csParamGroup[index]->callIntensity; }
void TuningTrafficData::setCall_intensity(QString intensity, int index) { csParamGroup[index]->callIntensity = intensity;}

QString TuningTrafficData::getCall_duration(int index) const { return csParamGroup[index]->callDuration; }
void TuningTrafficData::setCall_duration(QString duration, int index) { csParamGroup[index]->callDuration = duration; }

QString TuningTrafficData::getPS_intensity(int index) const { return psParamGroup[index]->psIntensity; }
void TuningTrafficData::setPs_intensity(QString intensity, int index) { psParamGroup[index]->psIntensity = intensity; }

QString TuningTrafficData::getPs_duration(int index) const {return psParamGroup[index]->psDuration; }
void TuningTrafficData::setPs_duration(QString duration, int index) { psParamGroup[index]->psDuration = duration; }

QString TuningTrafficData::getRecovery_start_interval(int index) const { return csParamGroup[index]->recoveryStartInterval; }
void TuningTrafficData::setRecovery_start_interval(QString value, int index) { csParamGroup[index]->recoveryStartInterval = value; }

QString TuningTrafficData::getCs_Name(int index) const { return csParamGroup[index]->csName; }
void TuningTrafficData::setCs_Name(QString value, int index) { csParamGroup[index]->csName = value; }

QString TuningTrafficData::getPs_Name(int index) const { return psParamGroup[index]->psName; }
void TuningTrafficData::setPs_Name(QString value, int index) { psParamGroup[index]->psName = value; }

QString TuningTrafficData::getMobility_name(int index) const { return mobilityGroup[index]->mobilityName; }
void TuningTrafficData::setMobility_Name(QString value, int index) { mobilityGroup[index]->mobilityName = value; }

int TuningTrafficData::get_csBehaviorIndex() const { return csBehaviorIndex; }
void TuningTrafficData::set_csBehaviorIndex(int value) { csBehaviorIndex = value; }

int TuningTrafficData::get_MobilityIndex() const { return mobilityIndex; }
void TuningTrafficData::set_MobilityIndex(int value) { mobilityIndex = value; }

//--------Group Getters-------------------
QVector<TuningTrafficData::CSParameters *> TuningTrafficData::getCSParamGroup() const { return csParamGroup; }
QVector<TuningTrafficData::PSParameters *> TuningTrafficData::getPSParamGroup() const { return psParamGroup; }
QVector<TuningTrafficData::Mobility *> TuningTrafficData::getMobilityGroup() const { return mobilityGroup; }



void TuningTrafficData::pushCSModel() { csParamGroup.push_back(new TuningTrafficData::CSParameters()); }
void TuningTrafficData::popCSModel() { csParamGroup.pop_back();}

void TuningTrafficData::pushPSModel() { psParamGroup.push_back(new TuningTrafficData::PSParameters()); }
void TuningTrafficData::popPSModel() { psParamGroup.pop_back(); }

void TuningTrafficData::pushMobilityModel() { mobilityGroup.push_back(new Mobility()); }
void TuningTrafficData::popMobilityModel() { mobilityGroup.pop_back(); }

void TuningTrafficData::setCSParamGroup(const QVector<CSParameters *> &value) { csParamGroup = value; }

void TuningTrafficData::setPSParamGroup(const QVector<PSParameters *> &value) { psParamGroup = value; }

void TuningTrafficData::setMobilityGroup(const QVector<Mobility *> &value) { mobilityGroup = value; }

void TuningTrafficData::csInitialize(int size_value)
{
    csParamGroup.resize(0);
    for (int i = 0; i < size_value; ++i){
        csParamGroup.push_back(new TuningTrafficData::CSParameters());
    }
}

void TuningTrafficData::psInitialize(int size_value)
{
    psParamGroup.resize(0);
    for (int i = 0; i < size_value; ++i){
        psParamGroup.push_back(new TuningTrafficData::PSParameters());
    }
}

void TuningTrafficData::mobilityInitialize(int size_value)
{
    mobilityGroup.resize(0);
    for (int i = 0; i < size_value; ++i){
        mobilityGroup.push_back(new TuningTrafficData::Mobility());
    }
}

int TuningTrafficData::get_psBehaviorIndex() const { return psBehaviorIndex; }
void TuningTrafficData::set_psBehaviorIndex(int value) { psBehaviorIndex = value; }
