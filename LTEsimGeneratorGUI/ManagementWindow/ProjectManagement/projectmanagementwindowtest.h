#ifndef PROJECTMANAGEMENTWINDOWTEST_H
#define PROJECTMANAGEMENTWINDOWTEST_H

#include <QObject>
#include <QtTest>
#include <QSignalSpy>
#include <QPushButton>

#include "AppSettings/appsettings.h"
#include "ManagementWindow/ProjectManagement/projectmanagement.h"

class ProjectManagementWindowTest : public QObject
{
    Q_OBJECT

public:
    ProjectManagementWindowTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void ProjectManagementTest1_checkNewProjectSignal();
    void ProjectManagementTest2_checkOpenProjectSignal();
    void ProjectManagementTest3_checkImportProjectSignal();
    void ProjectManagementTest4_checkDeleteProjectSignal();
    void ProjectManagementTest5_checkSettingsSignal();
};

#endif // PROJECTMANAGEMENTWINDOWTEST_H
