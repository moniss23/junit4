#include "parametersfiledatatest.h"
#include "Data/parametersfiledata.h"

#include <QtTest>
#include <QString>
#include <QByteArray>

ParametersFileDataTest::ParametersFileDataTest()
{

}

void ParametersFileDataTest::initTestCase(){
}

void ParametersFileDataTest::cleanupTestCase(){
}

void ParametersFileDataTest::ParametersFileDataTest1_getElementTypeTest() {

    qInfo() << "TEST FOR getElementType METHOD.";

    const QString projectType = "ParametersFileData";

    ParametersFileData parametersFileData;
    QString returnedProjectType = parametersFileData.getElementType();

    QCOMPARE(returnedProjectType, projectType);
}

void ParametersFileDataTest::ParametersFileDataTest2_serializeDataTest() {

    qInfo() << "TEST FOR serializeData METHOD.";

    ParametersFileData parametersFileData;
    parametersFileData.fileName = "simple data";
    parametersFileData.content = "simple data";

    QByteArray byteArray = parametersFileData.serializeData();

    QVERIFY(byteArray.size() > 0);
}
