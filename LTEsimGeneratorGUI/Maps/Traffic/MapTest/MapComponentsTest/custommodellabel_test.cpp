#include "custommodellabel_test.h"

void CustomModelLabel_Test::testConstructor()
{
    myCustomModelLabelPtr = new CustomModelLabel("CM");
    QCOMPARE(myCustomModelLabelPtr->text(), QString("CM"));
    QVERIFY( myCustomModelLabelPtr->frameShape() == QFrame::Box );
    QVERIFY(CustomModelLabel::cmWidth == 50);
    QVERIFY(CustomModelLabel::cmHeigth == 27);
    QCOMPARE(myCustomModelLabelPtr->styleSheet(), QString("QLabel { background-color : rgb(193, 193, 193)}"));
}

void CustomModelLabel_Test::testDestructor()
{
    delete myCustomModelLabelPtr;
}

void CustomModelLabel_Test::testDoubleClickEvent()
{
}
