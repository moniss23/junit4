#ifndef SCRIPTPARSERMANAGERTEST_H
#define SCRIPTPARSERMANAGERTEST_H

#include <QObject>
#include <QtTest>
#include <QString>

#include "Data/ProjectSettings/sgwsettings.h"
#include "Data/Managers/scriptparsermanager.h"
#include "Data/ProjectSettings/datageneratorsettings.h"
#include "Data/ProjectSettings/channelmodelsettings.h"

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
    void scriptParserManagerTest5_getChannelModelSettingsFromScript();
    void scriptParserManagerTest6_getMmeSettingsFromScript();
    void scriptParserManagerTest7_getMmeSettingsFromScript();

};

#endif // SCRIPTPARSERMANAGERTEST_H
