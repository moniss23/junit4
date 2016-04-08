#include "tuningtrafficbutton_test.h"

void TuningTrafficButton_Test::testConstructor()
{
    myTuningTrafficButtonPtr = new TuningTrafficButton;
}

void TuningTrafficButton_Test::testDestructor()
{
    delete myTuningTrafficButtonPtr;
}

void TuningTrafficButton_Test::testPressEvent()
{
}
