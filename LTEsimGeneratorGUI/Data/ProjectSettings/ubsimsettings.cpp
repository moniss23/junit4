#include "ubsimsettings.h"

#include <QBuffer>
#include <QDataStream>

UBSimSettings::UBSimSettings()
{

}

QString UBSimSettings::getElementType() const {
    return QString("UBSimSettings");
}

QByteArray UBSimSettings::serializeData() {
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << ueTypesDir << csTrafficModelsDir << psTrafficModelsDir
           << mobilityModelsDir << UBSimGui << ubsim_patches;

    return serializedData.buffer();
}

void UBSimSettings::deserializeData(const QByteArray &rawData) {
    QDataStream stream(rawData);
    stream >> ueTypesDir >> csTrafficModelsDir >> psTrafficModelsDir
            >> mobilityModelsDir >> UBSimGui >> ubsim_patches;
}
QString UBSimSettings::ParseToScript() {
    QString outputString;
    QString header = " #\n\
 # Retrieve default parameters for UBsim configuration\n\
 #\n\
 def Parameters.getUbsimConfigParameters()\n\
\n\
  # Define and return default values\n\
  default = {}\n\n";
    outputString.append(header);
    // UE TYPES DIR
    outputString.append("  default[:ueTypesDir] = \"");
    outputString.append(ueTypesDir);
    outputString.append("\"");
    outputString.append("  # Directory containing users UE type definitions\n");
    // CS TRAFFIC MODELS DIR
    outputString.append("  default[:csTrafficModelsDir] = \"");
    outputString.append(csTrafficModelsDir);
    outputString.append("\"");
    outputString.append("\t# Directory containing users CS traffic Models\n");
    // PS TRAFFIC MODELS DIR
    outputString.append("  default[:psTrafficModelsDir] = \"");
    outputString.append(psTrafficModelsDir);
    outputString.append("\"");
    outputString.append("\t# Directory containing users PS traffic Models\n");
    // MOBILITY MODELS
    outputString.append("  default[:mobilityModelsDir] = \"");
    outputString.append(mobilityModelsDir);
    outputString.append("\"");
    outputString.append("\t# Directory containing users Mobility Models\n");
    // VISUALISATION
    outputString.append("  default[:visualization] = ");
    if (UBSimGui){
        outputString.append("true");
    }
    else{
        outputString.append("false");
    }
    outputString.append("\t\t# UBsim GUI\n");

    // PATCHES
    outputString.append("  # patches to use when starting UBsim\n");
    outputString.append("  # Given as a Java classpath, multiple element separated by ':'\n");
    outputString.append("  default[:ubsim_patches] = ");
    for (int i=0;i<ubsim_patches.size();i++){
        outputString.append(ubsim_patches[i]);
        if (ubsim_patches[i]!=ubsim_patches.back()){
            outputString.append(":");
        }
    }
    outputString.append("  # UBsim code in UBsim project (ubsim.jar)\n");
    outputString.append("  return default\n");
    outputString.append(" end\n\n");

    /************ SAMPLE OUTPUT ******************/

    //  def Parameters.getUbsimConfigParameters()
    //
    //      # Define and return default values
    //      default = {}
    //
    //      default[:ueTypesDir] = ""
    //      default[:csTrafficModelsDir] = ""
    //      default[:psTrafficModelsDir] = ""
    //      default[:mobilityModelsDir] = ""
    //      default[:visualization] = false

    //      default[:ubsim_patches] = ""
    //      return default
    //  end




    return outputString;
}
