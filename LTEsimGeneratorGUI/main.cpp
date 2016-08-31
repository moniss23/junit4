#include <QApplication>

#include "Data/datasystem.h"
#include "UISystem/uisystem.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataSystem appSettings;


    /************************************
     *       SETUP   ALL   WINDOWS      *
     *       BINDING SIGNALS&SLOTS      *
     *           LOAD APP DATA          *
     ************************************/
    UISystem UiSystem(&appSettings);

    return a.exec();
}
