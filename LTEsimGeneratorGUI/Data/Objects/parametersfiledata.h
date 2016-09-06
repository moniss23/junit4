#ifndef PARAMETERSFILEDATA_H
#define PARAMETERSFILEDATA_H

#include <Data/Interfaces/serializeinterface.h>

class ParametersFileData : public SerializeInterface
{
public:
    QString filename;
    QString content;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
public:
    ~ParametersFileData() {}

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // PARAMETERSFILEDATA_H
