#ifndef TRAFFICFILEDATATEST_H
#define TRAFFICFILEDATATEST_H

#include <QObject>

class TrafficFileDataTest : public QObject
{
    Q_OBJECT

public:
    TrafficFileDataTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void TrafficFileDataTest1_getElementTypeTest();
    void TrafficFileDataTest2_serializeDataTest();
};

#endif // TRAFFICFILEDATATEST_H
