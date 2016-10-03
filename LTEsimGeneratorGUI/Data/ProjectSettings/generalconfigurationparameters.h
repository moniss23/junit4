#ifndef GENERALCONFIGURATIONPARAMETERS_H
#define GENERALCONFIGURATIONPARAMETERS_H

#include <QPair>

#include "Data/Interfaces/serializeinterface.h"
#include "Data/Interfaces/scriptable.h"

/**
 * @brief The GeneralConfigurationParameters class contains general configuration parameters
 */
class GeneralConfigurationParameters: public SerializeInterface, public Scriptable
{
public:
    GeneralConfigurationParameters();
    ~GeneralConfigurationParameters() {}

    QString logDir;                     ///< Directory to save logs
    QString coreParameters;             ///< Core parameters
    QString jvmParameters;              ///< JVM parameters
    QString loggerHandlerSet;           ///< Logger handler setting
    int loggerFileCount;                ///< Logger file count
    QPair<int,int> loggerFileSizeLimit; ///< Logger file size limitation
    bool loggerFileGzipEnabled;         ///< Logger file GZip setting (true/false)

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);

    /****************************
    *   PARSING INTERFACE       *
    ****************************/
    virtual QString ParseToScript();
};

#endif // GENERALCONFIGURATIONPARAMETERS_H
