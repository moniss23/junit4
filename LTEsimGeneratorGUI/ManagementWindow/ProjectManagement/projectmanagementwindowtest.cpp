#include "ManagementWindow/ProjectManagement/projectmanagementwindowtest.h"

ProjectManagementWindowTest::ProjectManagementWindowTest(){

}

void ProjectManagementWindowTest::initTestCase()
{
}

void ProjectManagementWindowTest::cleanupTestCase()
{
}

void ProjectManagementWindowTest::ProjectManagementTest1_checkNewProjectSignal()
{
    qInfo() << "TEST FOR NEW PROJECT WINDOW SPAWN SIGNAL";

    AppSettings appSettings;
    ProjectManagement projectManagement(&appSettings);

    QPushButton* newProjectButton = projectManagement.findChild<QPushButton *>("newProject_Button");
    QSignalSpy spy(&projectManagement, SIGNAL(SpawnWindow_NewProject()));

    newProjectButton->click();

    QCOMPARE(spy.count(), 1);
}

void ProjectManagementWindowTest::ProjectManagementTest2_checkOpenProjectSignal()
{
    qInfo() << "TEST FOR OPEN PROJECT WINDOW SPAWN SIGNAL";
    qInfo() << "TRYING TO OPEN PROJECT FROM EMPTY LIST, EXPECTING SIGNAL WILL NOT BE INVOKED";

    AppSettings appSettings;
    ProjectManagement projectManagement(&appSettings);

    QPushButton* newProjectButton = projectManagement.findChild<QPushButton *>("openProject_Button");
    QSignalSpy spy(&projectManagement, SIGNAL(SpawnWindow_OpenProject(const QString)));

    newProjectButton->click();

    QCOMPARE(spy.count(), 0);
}

void ProjectManagementWindowTest::ProjectManagementTest3_checkImportProjectSignal()
{
    qInfo() << "TEST FOR IMPORT PROJECT WINDOW SPAWN SIGNAL";

    AppSettings appSettings;
    ProjectManagement projectManagement(&appSettings);

    QPushButton* newProjectButton = projectManagement.findChild<QPushButton *>("importProject_Button");
    QSignalSpy spy(&projectManagement, SIGNAL(SpawnWindow_ImportProject()));

    newProjectButton->click();

    QCOMPARE(spy.count(), 1);
}

void ProjectManagementWindowTest::ProjectManagementTest4_checkDeleteProjectSignal()
{
    qInfo() << "TEST FOR DELETE PROJECT SIGNAL";
    qInfo() << "TRYING TO DELETE PROJECT FROM EMPTY LIST, EXPECTING SIGNAL WILL NOT BE INVOKED";

    AppSettings appSettings;
    ProjectManagement projectManagement(&appSettings);

    QPushButton* newProjectButton = projectManagement.findChild<QPushButton *>("deleteProject_Button");
    QSignalSpy spy(&projectManagement, SIGNAL(deleteProject(const QString)));

    newProjectButton->click();

    QCOMPARE(spy.count(), 0);
}

void ProjectManagementWindowTest::ProjectManagementTest5_checkSettingsSignal()
{
    qInfo() << "TEST FOR SETTINGS WINDOW SPAWN SIGNAL";

    AppSettings appSettings;
    ProjectManagement projectManagement(&appSettings);

    QPushButton* newProjectButton = projectManagement.findChild<QPushButton *>("settings_Button");
    QSignalSpy spy(&projectManagement, SIGNAL(SpawnWindow_Settings()));

    newProjectButton->click();

    QCOMPARE(spy.count(), 1);
}
