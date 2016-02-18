#ifndef TST_H
#define TST_H

#include <QtWidgets>
#include <QtTest/QtTest>
#include <maps/traffic_map/managementtemplate.h>

class ManagementTemplate_Test: public QObject
{
    Q_OBJECT
public:
    ManagementTemplate_Test(ManagementTemplate &managementTemplate);
    ManagementTemplate *p_managementTemplate;
    ManagementTemplate *p_managementTemplate2;

private slots:
    void testConstructor();
};
#endif // TST_H
