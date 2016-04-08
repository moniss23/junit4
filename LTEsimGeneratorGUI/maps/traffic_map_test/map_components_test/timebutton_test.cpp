#include "timebutton_test.h"

void TimeButton_Test::testConstructor()
{
    myTimeButtonPtr = new TimeButton;
}

void TimeButton_Test::testDestructor()
{
    delete myTimeButtonPtr;
}

void TimeButton_Test::testPressEvent()
{
}
