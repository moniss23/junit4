#ifndef SCRIPTPARSERMANAGERTEST_H
#define SCRIPTPARSERMANAGERTEST_H

#include <QObject>
#include <QtTest>
#include <QString>

#include "Data/Managers/scriptparsermanager.h"
#include "Data/ProjectSettings/datageneratorsettings.h"
#include "Data/ProjectSettings/sgwsettings.h"

class ScriptParserManagerTest : public QObject
{
    Q_OBJECT

public:
    ScriptParserManagerTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void scriptParserManagerTest1_getDataGeneratorSettingsFromScript();
    void scriptParserManagerTest2_getDataGeneratorSettingsFromScript();
    void scriptParserManagerTest3_getSgwSettingsFromScript();
    void scriptParserManagerTest4_getSgwSettingsFromScript();
};

#endif // SCRIPTPARSERMANAGERTEST_H
