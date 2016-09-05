#ifndef GENERALCONFIGURATIONPARAMETERS_H
#define GENERALCONFIGURATIONPARAMETERS_H

#include <QString>
#include <QPair>
#include "Data/Interfaces/serializeinterface.h"
#include "Data/Interfaces/scriptable.h"

class GeneralConfigurationParameters: public SerializeInterface, public Scriptable
{
public:
    GeneralConfigurationParameters();
    ~GeneralConfigurationParameters() {}

    QString logDir;
    QString coreParameters;
    QString jvmParameters;
    QString loggerHandlerSet;
    int loggerFileCount;
    QPair<int,int> loggerFileSizeLimit;
    bool loggerFileGzipEnabled;


    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);

    virtual QString ParseToScript();


};

#endif // GENERALCONFIGURATIONPARAMETERS_H
