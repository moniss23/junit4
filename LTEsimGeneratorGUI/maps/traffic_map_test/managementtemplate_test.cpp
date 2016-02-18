#include "managementtemplate_test.h"

ManagementTemplate_Test::ManagementTemplate_Test(ManagementTemplate &managementTemplate)
{
    p_managementTemplate = &managementTemplate;
}

void ManagementTemplate_Test::testConstructor()
{
    ManagementTemplate *p_managementTemplate2 = new ManagementTemplate;
    delete p_managementTemplate2;
    ManagementTemplate p_managementTemplate3;
}
