#include <vector>
#include <QApplication>
#include <QString>

#include "AppSettings/appsettings.h"
#include "Maps/Parameters/MapWindow/mapwindow.h"
#include "Maps/Traffic/map_traffic.h"
#include "Data/appglobaldata.h"
#include "UISystem/uisystem.h"


ParametersWindow *p;
std::vector<QString*> trafficFilesNames;
unsigned int project_index;
bool paramFilePresent = true;
MapWindow* map_w          = NULL;
Map_traffic* map_t        = NULL;
bool changesPresent = false;
void msg(QString content);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppSettings appSettings;


    /************************************
     *       SETUP   ALL   WINDOWS      *
     *       BINDING SIGNALS&SLOTS      *
     *           LOAD APP DATA          *
     ************************************/
    UISystem UiSystem(&appSettings);

    return a.exec();
}

// wrapper for displaying an alert/information message
void msg(QString content){
    QMessageBox(QMessageBox::Information,"",content,QMessageBox::Yes).exec();
}

