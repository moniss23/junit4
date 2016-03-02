#include "managementtemplate_test.h"

ManagementTemplate_Test::ManagementTemplate_Test(ManagementTemplate &argManagementTemplate)
{
    managementTemplate = &argManagementTemplate;
}

void ManagementTemplate_Test::testConstructor()
{
    ManagementTemplate *managementTemplate2 = new ManagementTemplate;
    delete managementTemplate2;
    ManagementTemplate managementTemplate3;
}

void ManagementTemplate_Test::testDestructor()
{
    managementTemplate2 = new ManagementTemplate;
    delete managementTemplate2;

    ManagementTemplate *mngTmpl1 = new ManagementTemplate;
    ManagementTemplate &mngTmpl2 = *mngTmpl1;
    delete &mngTmpl2;

    ManagementTemplate *mngTmpl3 = new ManagementTemplate;
    delete mngTmpl3;
}
