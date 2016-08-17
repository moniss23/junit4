#ifndef TRAFFICWINDOWMANAGEMENT_H
#define TRAFFICWINDOWMANAGEMENT_H
#include "Data/project.h"


class TrafficWindowManagement
{
public:
    TrafficWindowManagement();
private:
    Project project;
    QString currentTrafficFileName;
signals:
    void updateProject();
public slots:

    /** UPDATE ELEMENTS **/
    void updateUe();
    void updateCustomModels();
    void updateTime();
    void updateStatistics();
    void updateTuning();


    /** RESTORE ELEMTS **/
    void restoreUe();
    void restoreCustomModels();
    void restoreTime();
    void restoreStatistics();
    void restoreTuning();



    void showTrafficMap(QString trafficName);
    void closeTrafficMap();

};

#endif // TRAFFICWINDOWMANAGEMENT_H
