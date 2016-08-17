#ifndef PARAMETERSFILEDATA_H
#define PARAMETERSFILEDATA_H

#include <QString>

#include <Data/serializeinterface.h>

class ParametersFileData : public SerializeInterface
{
public:
    QString fileName;
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
