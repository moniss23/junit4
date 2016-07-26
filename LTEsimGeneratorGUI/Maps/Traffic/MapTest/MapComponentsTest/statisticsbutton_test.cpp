#include "statisticsbutton_test.h"

void StatisticsButton_Test::testConstructor()
{
    myStatisticsButtonPtr = new StatisticsButton;
}

void StatisticsButton_Test::testDestructor()
{
    delete myStatisticsButtonPtr;
}

void StatisticsButton_Test::testPressEvent()
{
}
