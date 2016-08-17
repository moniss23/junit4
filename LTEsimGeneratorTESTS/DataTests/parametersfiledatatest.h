#ifndef PARAMETERSFILEDATATEST_H
#define PARAMETERSFILEDATATEST_H

#include <QObject>

class ParametersFileDataTest : public QObject
{
    Q_OBJECT

public:
    ParametersFileDataTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void ParametersFileDataTest1_getElementTypeTest();
    void ParametersFileDataTest2_serializeDataTest();
};

#endif // PARAMETERSFILEDATATEST_H
