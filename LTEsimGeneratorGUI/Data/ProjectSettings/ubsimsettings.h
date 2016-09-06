#ifndef UBSIMSETTINGS_H
#define UBSIMSETTINGS_H

#include "Data/Interfaces/serializeinterface.h"

class UBSimSettings : public SerializeInterface
{
public:
    UBSimSettings();
    ~UBSimSettings() {}

    QString imsiMapRange;

    //-------------------------Retrieve default parameters for UBsim configuration------------------------------------------
    QString ueTypesDir;                 // Directory containing users UE type definitions
    QString csTrafficModelsDir;         // Directory containing users CS traffic Models
    QString psTrafficModelsDir;         // Directory containing users PS traffic Models
    QString mobilityModelsDir;          // Directory containing users Mobility Models
    bool UBSimGui;                      // UBsim GUI

    QStringList ubsim_patches;              // patches to use when starting UBsim
                                        // Given as a Java classpath, multiple element separated by ':'

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // UBSIMSETTINGS_H
