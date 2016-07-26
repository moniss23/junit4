#ifndef UE_H
#define UE_H
#include <QString>
#include <QList>
class Ue
{
public:
    Ue();
    QString getName();
    void setName(QString value);

    QString getL1l2_managers();
    void setL1l2_managers(QString value);

    QString getRrc_pluginFilterPath();
    void setRrc_pluginFilterPath( QString value);

    QString getUctool_ip();
    void setUctool_ip( QString value);

    QString getUctool_cIds();
    void setUctool_cIds( QString value);

    QString getUctool_service_ip();
    void setUctool_service_ip( QString value);

    QString getUe_network_capability() ;
    void setUe_network_capability( QString value);

    QString getUe_keyDerivationAlgorithm() ;
    void setUe_keyDerivationAlgorithm( QString value);

    QString getUe_key();
    void setUe_key( QString value);

    QString getUe_op();
    void setUe_op( QString value);

    QString getImsiMapRange() ;
    void setImsiMapRange( QString value);

    QString getUeTypesDir() ;
    void setUeTypesDir( QString value);

    QString getCsTrafficModelsDir() ;
    void setCsTrafficModelsDir( QString value);

    QString getPsTrafficModelsDir() ;
    void setPsTrafficModelsDir( QString value);

    QString getMobilityModelsDir() ;
    void setMobilityModelsDir( QString value);

    QString getUbsim_patches();
    void setUbsim_patches(QString value);

    bool getVisualization() const;
    void setVisualization(const bool &value);

    bool getStart_ue_component() const;
    void setStart_ue_component(bool value);

    void resetParamsUBSIM();
    void resetParamsUCTOOL();

private:
    bool start_ue_component;             // Decide if the UE component should be started
    QString name;                        // Name of the UE component
    QString l1l2_managers;               // Space separated string with TYPE;instance tuples where allowed values of TYPE is UCTOOL.
    QString rrc_pluginFilterPath;

    // UCTool specific parameters
    QString uctool_ip;                  // UCTOOL device name the IP address of the UCtool.
                                        // NOTE! If only IP address is given then the IP address will be
                                        // applicable for all UCTOOL managers.
    QString uctool_cIds;                // UCTOOL device name and cell names used to map.
                                        // the UCTOOL cells to corresponding cells in the REC.
    QString uctool_service_ip;          // UCTOOL device name and the IP address of the service requested.
                                        // NOTE! If only IP address is given then the IP address will be
                                        // applicable for all UCTOOLs.

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
    //######################################################################################################################
    QString imsiMapRange;

    //-------------------------Retrieve default parameters for UBsim configuration------------------------------------------
    QString ueTypesDir;                 // Directory containing users UE type definitions
    QString csTrafficModelsDir;         // Directory containing users CS traffic Models
    QString psTrafficModelsDir;         // Directory containing users PS traffic Models
    QString mobilityModelsDir;          // Directory containing users Mobility Models
    bool visualization;                 // UBsim GUI

    // patches to use when starting UBsim
    // Given as a Java classpath, multiple element separated by ':'
    QString ubsim_patches;

    QList <QString> fileParameters;
    void openFile();
    QString searchParameter (QString name);
    QString searchDefaultParameter(QString name);
    void setParameters();
    bool toBool(QString t);

};

#endif // UE_H
