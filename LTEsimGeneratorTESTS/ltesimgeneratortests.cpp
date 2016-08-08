#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <vector>
#include <QApplication>
#include <QFile>
#include <QListWidgetItem>

#include "ManagementWindow/ParametersWindow/parameterswindow.h"
#include "Maps/Parameters/MapWindow/mapwindow.h"
#include "Maps/Traffic/map_traffic.h"
#include "ManagementWindow/ProjectManagement/projectmanagementwindowtest.h"
#include "ManagementWindow/AddProjectWindow/addprojectwindowtest.h"


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
    AddProjectWindowTest addProjectWindowTest;

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void appSetttingsTest1_checkDefaultProjectDir();
};

LTEsimGeneratorTESTS::LTEsimGeneratorTESTS()
{
    QTest::qExec(&projectManagementWindowTest);
    QTest::qExec(&addProjectWindowTest);
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
