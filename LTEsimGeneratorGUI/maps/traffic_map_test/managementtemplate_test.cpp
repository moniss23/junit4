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

void ManagementTemplate_Test::testDestructor()
{
    p_managementTemplate2 = new ManagementTemplate;
    delete p_managementTemplate2;

    ManagementTemplate *p_mngTmpl1 = new ManagementTemplate;
    ManagementTemplate &p_mngTmpl2 = *p_mngTmpl1;
    delete &p_mngTmpl2;

    ManagementTemplate *p_mngTmpl3 = new ManagementTemplate;
    delete p_mngTmpl3;
}
