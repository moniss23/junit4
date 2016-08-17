#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QApplication>

#include "UITests/projectmanagementwindowtest.h"
#include "UITests/addprojectwindowtest.h"
#include "DataTests/projecttest.h"
#include "DataTests/parametersfiledatatest.h"
#include "DataTests/trafficfiledatatest.h"

#include "DataSystem/datasystem.h"

class LTEsimGeneratorTESTS : public QObject
{
    Q_OBJECT

public:
    LTEsimGeneratorTESTS();

    ProjectManagementWindowTest projectManagementWindowTest;
    AddProjectWindowTest addProjectWindowTest;
    ProjectTest projectTest;
    ParametersFileDataTest parametersFileDataTest;
    TrafficFileDataTest trafficFileDataTest;

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void appSetttingsTest1_checkDefaultProjectDir();
};

LTEsimGeneratorTESTS::LTEsimGeneratorTESTS()
{
    QTest::qExec(&projectManagementWindowTest);
    QTest::qExec(&addProjectWindowTest);
    QTest::qExec(&projectTest);
    QTest::qExec(&parametersFileDataTest);
    QTest::qExec(&trafficFileDataTest);
}

void LTEsimGeneratorTESTS::initTestCase()
{
}

void LTEsimGeneratorTESTS::cleanupTestCase()
{
}

void LTEsimGeneratorTESTS::appSetttingsTest1_checkDefaultProjectDir()
{
    qInfo() << "TEST FOR NEW PROJECT SETTINGS AND <DEFAULT> PROJECT DIR";

    DataSystem appSettings;

    QString dir = appSettings.getDefaultNewProjectDir();
    QCOMPARE(dir, QString("<default>"));

}



QTEST_MAIN(LTEsimGeneratorTESTS)

#include "ltesimgeneratortests.moc"
