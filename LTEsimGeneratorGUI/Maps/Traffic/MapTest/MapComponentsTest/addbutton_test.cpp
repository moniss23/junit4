#include "addbutton_test.h"

void AddButton_Test::testConstructor()
{
    myAddButtonPtr = new AddButton;
    QCOMPARE(myAddButtonPtr->text(), QString("+"));
    QVERIFY(myAddButtonPtr->created == false);
}

void AddButton_Test::testDestructor()
{
    delete myAddButtonPtr;
}

void AddButton_Test::testPressEvent()
{
    AddButton addButton;
    AddButton::created = true;
    QTest::mousePress(&addButton, Qt::LeftButton);
    QVERIFY(AddButton::created == true);
    QVERIFY(addButton.pointer == NULL);
}
