#ifndef UBSIMSETTINGS_H
#define UBSIMSETTINGS_H

#include <QString>

#include "Data/Interfaces/serializeinterface.h"

class UBSimSettings : public SerializeInterface
{
public:
    UBSimSettings();
    ~UBSimSettings() {}

    QString name;                        // Name of the UE component
    QString l1l2_managers;               // Space separated string with TYPE;instance tuples where allowed values of TYPE is UCTOOL.
    QString rrc_pluginFilterPath;

    //###### Security related parameters ###################################################################################
    QString ue_network_capability;      // UE network capabilities. See 3GPP 24.008 for more details
                                        // Used to control which integrity protection and ciphering algorithms a UE supports.

    QString ue_keyDerivationAlgorithm;  // The algorithm used during EPS AKA procedure.
                                        // Supported algorithms:
                                        // * TEST_ALGORITHM - The test algorithm defined in TS 34.108.
                                        // * MILENAGE - The milenage algorithm defined in TS 35.205.
                                        // Also used in simulated MME.
    QString ue_key;
    QString ue_op;
    QString imsiMapRange;

    //-------------------------Retrieve default parameters for UBsim configuration------------------------------------------
    QString ueTypesDir;                 // Directory containing users UE type definitions
    QString csTrafficModelsDir;         // Directory containing users CS traffic Models
    QString psTrafficModelsDir;         // Directory containing users PS traffic Models
    QString mobilityModelsDir;          // Directory containing users Mobility Models
    bool UBSimGui;                      // UBsim GUI

    QString ubsim_patches;              // patches to use when starting UBsim
                                        // Given as a Java classpath, multiple element separated by ':'

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // UBSIMSETTINGS_H
