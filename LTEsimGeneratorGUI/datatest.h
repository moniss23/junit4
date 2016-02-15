#ifndef DATATEST_H
#define DATATEST_H
#include<QtTest/QTest>
#include <QObject>

class DataTest: public QObject
{
    Q_OBJECT
public:
    explicit DataTest(QObject *parent = 0);
private Q_SLOTS:
    void test();
};
#endif

