#include "projecttest.h"
#include "Data/project.h"

#include <QString>
#include <QtTest>
#include <QByteArray>


ProjectTest::ProjectTest()
{

}

void ProjectTest::initTestCase()
{
}

void ProjectTest::cleanupTestCase()
{
}

void ProjectTest::ProjectTest1_getElementTypeTest() {

    qInfo() << "TEST FOR getElementType METHOD.";

    const QString projectType = "Project";

    Project project;
    QString returnedProjectType = project.getElementType();

    QCOMPARE(returnedProjectType, projectType);
}

void ProjectTest::ProjectTest2_serializeDataTest() {

    qInfo() << "TEST FOR serializeData METHOD.";

    Project project;
    project.name = "simple data";
    project.fullpath = "simple data";

    QByteArray byteArray = project.serializeData();

    QVERIFY(byteArray.size() > 0);
}
