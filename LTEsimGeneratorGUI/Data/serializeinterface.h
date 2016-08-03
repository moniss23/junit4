#ifndef SERIALIZEINTERFACE
#define SERIALIZEINTERFACE

#include <QByteArray>
#include <QString>
#include <QStringList>

class SerializeInterface
{
public:
    SerializeInterface(){}
    virtual ~SerializeInterface(){}

public:
    virtual QString getElementType() const = 0;
    virtual QByteArray serializeData() = 0;
    virtual void deserializeData(const QByteArray &rawData) = 0;
};


#endif // SERIALIZEINTERFACE

