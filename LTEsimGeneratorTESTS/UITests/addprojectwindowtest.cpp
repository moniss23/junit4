#include "addprojectwindowtest.h"
#include "UISystem/Windows/addProjectWindow.h"

#include <QtTest>
#include <QSignalSpy>
#include <QPushButton>
#include <QDialogButtonBox>


AddProjectWindowTest::AddProjectWindowTest()
{

}

void AddProjectWindowTest::initTestCase()
{
}

void AddProjectWindowTest::cleanupTestCase()
{
}

void AddProjectWindowTest::AddProjectWindowTest1_checkCreateNewProjectSignal()
{
    qInfo() << "TEST FOR CREATE NEW PROJECT SIGNAL";

    AddProjectWindow addProjectWindow;

    QDialogButtonBox* buttonBox = addProjectWindow.findChild<QDialogButtonBox *>("buttonBox");

    QPushButton* okButton = buttonBox->button(QDialogButtonBox::Ok);

    QSignalSpy spy(&addProjectWindow, SIGNAL(createNewProject(QString,QString,bool)));

    okButton->click();

    QCOMPARE(spy.count(), 1);
}
