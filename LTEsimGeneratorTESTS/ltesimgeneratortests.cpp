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
#include "ManagementWindow/ProjectManagement/projectmanagementwindowtest.h"


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

    ProjectManagementWindowTest projectManagementWindowTest;

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void appSetttingsTest1_checkDefaultProjectDir();
};

LTEsimGeneratorTESTS::LTEsimGeneratorTESTS()
{
    QTest::qExec(&projectManagementWindowTest);
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

// wrapper for displaying an alert/information message
void msg(QString content){
    QMessageBox(QMessageBox::Information,"",content,QMessageBox::Yes).exec();
}


QTEST_MAIN(LTEsimGeneratorTESTS)

#include "ltesimgeneratortests.moc"
