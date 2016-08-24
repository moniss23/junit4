#ifndef SCRIPTPARSERMANAGERTEST_H
#define SCRIPTPARSERMANAGERTEST_H

#include <QObject>
#include <QtTest>
#include <QString>

#include "Data/Managers/scriptparsermanager.h"
#include "Data/ProjectSettings/datageneratorsettings.h"

class ScriptParserManagerTest : public QObject
{
    Q_OBJECT

public:
    ScriptParserManagerTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void scriptParserManagerTest1_getDataGeneratorSettingsFromScript();
};

#endif // SCRIPTPARSERMANAGERTEST_H
