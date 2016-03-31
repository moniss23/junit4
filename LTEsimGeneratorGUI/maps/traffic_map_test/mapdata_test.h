#ifndef MAPDATA_TEST_H
#define MAPDATA_TEST_H
#include <maps/traffic_map/mapdata.h>
#include <management_window/projectmanagement.h>
#include <management_window/encryption.h>
#include <QObject>
#include <QDir>
#include <QTest>

extern QString* projectName;
extern ProjectManagement* projectMng;

class MapData_Test : public QObject
{
    Q_OBJECT
public:
    explicit MapData_Test(QObject *parent = 0);
    ~MapData_Test();

    QString testProjectName = "test";
    QString testProjectDir = "projects";
    QString testMapName = "MT1";
    const char* testPhrase = "UG";

private Q_SLOTS:
    void fillActiveCellListTest();
    void fillHandoverListTest();
};

#endif // MAPDATA_TEST_H
