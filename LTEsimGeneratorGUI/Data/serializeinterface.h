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
    virtual QByteArray serializeToFile() = 0;
    virtual void serializeFromFile(QByteArray rawData) = 0;
};


#endif // SERIALIZEINTERFACE

