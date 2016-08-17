#ifndef PROJECTTEST_H
#define PROJECTTEST_H

#include <QObject>

class ProjectTest : public QObject
{
    Q_OBJECT

public:
    ProjectTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void ProjectTest1_getElementTypeTest();
    void ProjectTest2_serializeDataTest();
};

#endif // PROJECTTEST_H
