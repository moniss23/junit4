#include <QString>
#include <QtTest>
#include <QCoreApplication>


#include "AppSettings/appsettings.h"

class LTEsimGeneratorTESTS : public QObject
{
    Q_OBJECT

public:
    LTEsimGeneratorTESTS();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void appSetttingsTest1_checkDefaultProjectDir();
};

LTEsimGeneratorTESTS::LTEsimGeneratorTESTS()
{
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

    AppSettings appSettings;

    QString dir = appSettings.getDefaultNewProjectDir();
    QCOMPARE(dir, QString());

    appSettings.loadSettings(); //TODO: This should be done in class c-tor
    appSettings.read_settings_file();
    QString LoadedDefaultDir = appSettings.getDefaultNewProjectDir();
    QCOMPARE(LoadedDefaultDir, QString("<default>"));

}


QTEST_MAIN(LTEsimGeneratorTESTS)

#include "ltesimgeneratortests.moc"