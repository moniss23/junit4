#include "trafficfiledatatest.h"
#include "Data/trafficfiledata.h"

#include <QtTest>
#include <QString>
#include <QByteArray>

TrafficFileDataTest::TrafficFileDataTest()
{

}



void TrafficFileDataTest::initTestCase(){
}

void TrafficFileDataTest::cleanupTestCase(){
}

void TrafficFileDataTest::TrafficFileDataTest1_getElementTypeTest() {

    qInfo() << "TEST FOR getElementType METHOD.";

    const QString projectType = "TrafficFileData";

    TrafficFileData trafficFileData;
    QString returnedProjectType = trafficFileData.getElementType();

    QCOMPARE(returnedProjectType, projectType);
}

void TrafficFileDataTest::TrafficFileDataTest2_serializeDataTest() {

    qInfo() << "TEST FOR serializeData METHOD.";

    TrafficFileData trafficFileData;
    trafficFileData.fileName = "simple data";
    trafficFileData.content = "simple data";

    QByteArray byteArray = trafficFileData.serializeData();

    QVERIFY(byteArray.size() > 0);
}
