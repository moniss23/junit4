#include "scale_test.h"

double const myPositionX[2][4] = {{ 7000, 14000, 21000, 28000 }, {10500, 17500, 24500, 31500}};
double const myPositionY[6] = { 7000, 13000, 19000, 25000, 31000, 37000};
double const eastHorizon = 37000;
double const northHorizon = 43000;
double const westHorizon = 0;
double const southHorizon = 0;

const int eheigth = 930;
const int ewidth =  eheigth * (eastHorizon - westHorizon) / (northHorizon - southHorizon);
const int xe0 = 10;
const int ye0 = 940;

void Scale_Test::testConstructor()
{
    int eX0 = 0;
    int eY0 = 0;
    int eWidth = 100;
    int eHeigth = 100;
    double rX0 = 0;
    double rY0 = 0;
    double rWidth = 2000;
    double rHeigth = 2000;

    myScalePtr = new Scale<double, int>(eX0, eY0, eWidth, eHeigth, rX0, rY0, rWidth, rHeigth);
    my2ndScalePtr = new Scale<double, int>( xe0, ye0, ewidth, eheigth, westHorizon, southHorizon,
                                            (eastHorizon - westHorizon), (northHorizon - southHorizon));//(eX0, eY0, eWidth, eHeigth, rX0, rY0, rWidth, rHeigth);
    Scale<double, double> myScale_d_d(rX0, rY0, rWidth, rHeigth, rX0, rY0, rWidth, rHeigth);
    Scale<int, int> myScale_i_i(eX0, eY0, eWidth, eHeigth, eX0, eY0, eWidth, eHeigth);
    Scale<int, double> myScale_i_d(rX0, rY0, rWidth, rHeigth, eX0, eY0, eWidth, eHeigth);
}

void Scale_Test::testDestructor()
{
    delete myScalePtr;
}


void Scale_Test::testGetRealX()
{
    QVERIFY(round(my2ndScalePtr->getRealX(33)*100)/100 == 1063.75);
}

void Scale_Test::testGetRealY()
{
    QVERIFY(round(my2ndScalePtr->getRealY(50)*10)/10 == 41150.5);
}

void Scale_Test::testGetDisplayX()
{
    QVERIFY(my2ndScalePtr->getDisplayX(423.3) == 19);
}

void Scale_Test::testGetDisplayY()
{
    QVERIFY(my2ndScalePtr->getDisplayY(23.3) == 939);
}

void Scale_Test::testGetLengthOX()
{
    QVERIFY(my2ndScalePtr->getDislpayLengthOX(345) == 7);
}

void Scale_Test::testGetLengthOY()
{
    QVERIFY(my2ndScalePtr->getDisplayLengthOY(593) == 12);
}
