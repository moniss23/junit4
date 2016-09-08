#ifndef UEPARAMETERSPARSER_H
#define UEPARAMETERSPARSER_H
#include "Data/ProjectSettings/uctoolsettings.h"
#include "Data/ProjectSettings/ueparameters.h"

class UeParametersParser
{
public:
    UeParametersParser();
    ~UeParametersParser(){}

    static QString ParseToScript(UCToolSettings &ucTool, UeParameters &ue);

};

#endif // UEPARAMETERSPARSER_H
