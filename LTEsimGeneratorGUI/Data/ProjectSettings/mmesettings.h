#ifndef MMESETTINGS_H
#define MMESETTINGS_H

#include "Data/Interfaces/serializeinterface.h"
#include "Data/Interfaces/scriptable.h"

/**
 * @brief The MmeSettings class contains settings of MME
 */
class MmeSettings : public SerializeInterface, public Scriptable
{

public:
    MmeSettings();
    ~MmeSettings();

    QStringList names;          ///< Names of MMEs
    int numberOfMme;            ///< Number of MMEs (should be equal to names.size())

    QString tais;               ///< TAIS
    QString uris;               ///< URIS
    QString pluginFilterPath;   ///< Path to plugin filter
    bool simulatedCoreNetwork;  ///< Simulated CoreNetwork setting (true/false)

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

#endif // MMESETTINGS_H
