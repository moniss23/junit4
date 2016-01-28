#include <QString>
#include <QtTest>
#include</home/tomad1/Documents/gerrit1/Internal.LTEsimGenerator/LTEsimGeneratorGUI/maps/traffic_map/timetraffic/timetraffic.cpp>

class TimeTrafficTest : public QObject
{
    Q_OBJECT

public:
    TimeTrafficTest();

private Q_SLOTS:
    void setHours();
};

TimeTrafficTest::TimeTrafficTest()
{

}


void TimeTrafficTest::setHours()
{

    QVERIFY2(true, "Failure");
    TimeTraffic timetest;
    timetest.setSpn_hours1(12);
    timetest.setSpn_hours2(13);
    QCOMPARE(timetest.getSpn_hours1(),12);
    QCOMPARE(timetest.getSpn_hours2(),13);

}

QTEST_APPLESS_MAIN(TimeTrafficTest)

#include "time_trafficTest.moc"
