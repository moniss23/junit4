#include "datatest.h"

DataTest::DataTest(QObject *parent) : QObject(parent)
{

}

void DataTest::test()
{
    QVERIFY(true==true);
}


