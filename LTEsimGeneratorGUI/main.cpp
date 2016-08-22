#include <QVector>
#include <QApplication>
#include <QString>

#include "Data/datasystem.h"
#include "UISystem/uisystem.h"

#include "Maps/Parameters/MapWindow/mapwindow.h"
#include "Maps/Traffic/map_traffic.h"
MapWindow* map_w          = NULL;
Map_traffic* map_t        = NULL;
bool changesPresent = false;

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
