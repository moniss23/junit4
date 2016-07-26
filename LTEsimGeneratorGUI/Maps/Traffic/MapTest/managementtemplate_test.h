#ifndef TST_H
#define TST_H

#include <QtWidgets>
#include <QtTest/QtTest>
#include <Maps/Traffic/ManagementTemplate/managementtemplate.h>
class ManagementTemplate_Test : public QObject
{
    Q_OBJECT
public:
    ManagementTemplate_Test(ManagementTemplate &argManagementTemplate);
    ManagementTemplate *managementTemplate;
    ManagementTemplate *managementTemplate2;

private slots:
    void testConstructor();
    void testDestructor();
};
#endif // TST_H
