#ifndef UEPARAMETERSPARSER_H
#define UEPARAMETERSPARSER_H
#include "Data/ProjectSettings/uctoolsettings.h"
#include "Data/ProjectSettings/ueparameters.h"
/**
 * @brief The UeParametersParser class is used to parse information about UEs to Ruby script
 */
class UeParametersParser
{
public:
    UeParametersParser();
    ~UeParametersParser(){}
    /**
     * @brief ParseToScript parses UEs parameters to script
     * @param ucTool holds UCTool settings
     * @param ue holds UE data
     * @return QString with parsed UE data
     */
    static QString ParseToScript(UCToolSettings &ucTool, UeParameters &ue);

};

#endif // UEPARAMETERSPARSER_H
