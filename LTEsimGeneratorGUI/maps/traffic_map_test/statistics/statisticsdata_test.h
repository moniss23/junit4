#ifndef STATISTICSDATA_TEST_H
#define STATISTICSDATA_TEST_H

#include <QObject>
#include <maps/traffic_map/statistics/statisticsdata.h>
#include <QtTest/QtTest>

class StatisticsData_Test : public QObject
{
    Q_OBJECT
public:
    explicit StatisticsData_Test(QObject *parent = 0);
    QString mapIndexTest = "mapa";
    bool valueTest = true;

private Q_SLOTS:
    void setGetStatisticsParamTest();
};

#endif // STATISTICSDATA_TEST_H
