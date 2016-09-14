#ifndef STATISTICSDATATEST_H
#define STATISTICSDATATEST_H

#include <QObject>

class StatisticsDataTest : public QObject
{
    Q_OBJECT

public:
    StatisticsDataTest();
    ~StatisticsDataTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void StatisticsDataTest1_serializeData();
    void StatisticsDataTest2_deserializeData();
};

#endif // STATISTICSDATATEST_H
