#ifndef UBSIMSETTINGS_H
#define UBSIMSETTINGS_H

#include "Data/Interfaces/serializeinterface.h"
#include "Data/Interfaces/scriptable.h"

/**
 * @brief The UBSimSettings class contains settings for UBSim module
 */
class UBSimSettings : public SerializeInterface, public Scriptable
{
public:
    UBSimSettings();
    ~UBSimSettings() {}

    QString imsiMapRange;           ///< Map range of IMSI

    QString ueTypesDir;             ///< Directory containing users UE type definitions
    QString csTrafficModelsDir;     ///< Directory containing users CS traffic Models
    QString psTrafficModelsDir;     ///< Directory containing users PS traffic Models
    QString mobilityModelsDir;      ///< Directory containing users Mobility Models
    bool UBSimGui;                  ///< UBsim GUI setting (true/false)

    QStringList ubsim_patches;      ///< Patches to use when starting UBsim

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

#endif // UBSIMSETTINGS_H
