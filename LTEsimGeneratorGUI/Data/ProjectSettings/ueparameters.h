#ifndef UeParameters_H
#define UeParameters_H

#include <QString>
#include <QPair>
#include <QVector>

#include "Data/Interfaces/scriptable.h"
#include "Data/Interfaces/serializeinterface.h"

/**
 * @brief The UeParameters class contains settings for UE component
 */
class UeParameters: public SerializeInterface
{
public:
    UeParameters();
    ~UeParameters();

    //TODO: get rid of that default value after implementing parsing method
    bool startUeComponent;              ///< UE component starting setting (true/false)

    QString name;                       ///< Name of UE component
    QString managers;                   ///< Managers of UE component
    QString pluginFilterPath;           ///< Path to a plugin filter
    QString ucToolIp;                   ///< UCTool IP address
    QString ucToolcIds;                 ///< UCTool Ids
    QString ucToolServiceIp;            ///< UCTool service IP
    QString ueNetworkCapability;        ///< UENetwork capability
    QString ueKeyDerivationAlgorithm;   ///< UE key derivation algorithm
    QString ueKey;                      ///< UE key
    QString ueOp;                       ///< UE op

    /****************************
    * SERIALIZATION INTERFACE  *
    ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // UeParameters_H
