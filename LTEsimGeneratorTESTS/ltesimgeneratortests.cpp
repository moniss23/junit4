#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <vector>
#include <QApplication>
#include <QFile>
#include <QListWidgetItem>
#include <QPushButton>
#include <QSignalSpy>

#include "AppSettings/appsettings.h"
#include "ManagementWindow/Settings/settings.h"
#include "ManagementWindow/ParametersWindow/parameterswindow.h"
#include "ManagementWindow/ProjectManagement/projectmanagement.h"
#include "ManagementWindow/ProjectManagement/importprojectwindow.h"
#include "Maps/Parameters/MapWindow/mapwindow.h"
#include "Maps/Traffic/map_traffic.h"
#include "Data/appglobaldata.h"

const unsigned int cellCount = 12;
const unsigned int handoverCount = 21;
const unsigned int centerCount = 12;

ParametersWindow *p;
ProjectManagement *projectMng;
std::vector<QString*> trafficFilesNames;
unsigned int project_index;
bool paramFilePresent;

MapWindow* map_w          = NULL;
Map_traffic* map_t        = NULL;

bool changesPresent = false;

void msg(QString content);

class LTEsimGeneratorTESTS : public QObject
{
    Q_OBJECT

public:
    LTEsimGeneratorTESTS();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void appSetttingsTest1_checkDefaultProjectDir();
    void ProjectManagementTest1_checkNewProjectSignal();
    void ProjectManagementTest2_checkOpenProjectSignal();
    void ProjectManagementTest3_checkImportProjectSignal();
    void ProjectManagementTest4_checkDeleteProjectSignal();
    void ProjectManagementTest5_checkSettingsSignal();
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
    QCOMPARE(dir, QString("<default>"));

}

void LTEsimGeneratorTESTS::ProjectManagementTest1_checkNewProjectSignal()
{
    qInfo() << "TEST FOR NEW PROJECT WINDOW SPAWN SIGNAL";

    AppSettings appSettings;
    ProjectManagement projectManagement(&appSettings);

    QPushButton* newProjectButton = projectManagement.findChild<QPushButton *>("newProject_Button");
    QSignalSpy spy(&projectManagement, SIGNAL(SpawnWindow_NewProject()));

    newProjectButton->click();

    QCOMPARE(spy.count(), 1);
}

void LTEsimGeneratorTESTS::ProjectManagementTest2_checkOpenProjectSignal()
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

void LTEsimGeneratorTESTS::ProjectManagementTest3_checkImportProjectSignal()
{
    qInfo() << "TEST FOR IMPORT PROJECT WINDOW SPAWN SIGNAL";

    AppSettings appSettings;
    ProjectManagement projectManagement(&appSettings);

    QPushButton* newProjectButton = projectManagement.findChild<QPushButton *>("importProject_Button");
    QSignalSpy spy(&projectManagement, SIGNAL(SpawnWindow_ImportProject()));

    newProjectButton->click();

    QCOMPARE(spy.count(), 1);
}

void LTEsimGeneratorTESTS::ProjectManagementTest4_checkDeleteProjectSignal()
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

void LTEsimGeneratorTESTS::ProjectManagementTest5_checkSettingsSignal()
{
    qInfo() << "TEST FOR SETTINGS WINDOW SPAWN SIGNAL";

    AppSettings appSettings;
    ProjectManagement projectManagement(&appSettings);

    QPushButton* newProjectButton = projectManagement.findChild<QPushButton *>("settings_Button");
    QSignalSpy spy(&projectManagement, SIGNAL(SpawnWindow_Settings()));

    newProjectButton->click();

    QCOMPARE(spy.count(), 1);
}


// wrapper for displaying an alert/information message
void msg(QString content){
    QMessageBox(QMessageBox::Information,"",content,QMessageBox::Yes).exec();
}


QTEST_MAIN(LTEsimGeneratorTESTS)

#include "ltesimgeneratortests.moc"
