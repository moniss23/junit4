#ifndef ADDPROJECTWINDOWTEST_H
#define ADDPROJECTWINDOWTEST_H

#include <QObject>

class AddProjectWindowTest : public QObject
{
    Q_OBJECT

public:
    AddProjectWindowTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void AddProjectWindowTest1_checkCreateNewProjectSignal();
};

#endif // ADDPROJECTWINDOWTEST_H
