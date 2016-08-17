#ifndef PARAMETERSFILEMANAGEMENT_H
#define PARAMETERSFILEMANAGEMENT_H
#include "Data/project.h"

class ParametersFileManagement
{
public:
    ParametersFileManagement();
private:
    Project project;

signals:
    void updateProject();

public slots:

    /** UPDATE ELEMENTS **/
    void updateCells();
    void updateHandovers();
    void updateSimulatedCoreNetwork();
    void updateChannelModel();
    void updateUcTool();
    void updateSimulatedUe();

    /** RESTORE ELEMENTS **/

    void restoreCells();
    void restoreHandovers();
    void restoreSimulatedCoreNetwork();
    void restoreChannelModel();
    void restoreUcTool();
    void restoreSimulatedUe();

    void restoreFile();
};

#endif // PARAMETERSFILEMANAGEMENT_H
