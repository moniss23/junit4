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
    QString header = "\t#\n\
\t# Retrieve default parameters for UBsim configuration\n\
\t#\n\
\tdef Parameters.getUbsimConfigParameters()\n\
\n\
\t\t# Define and return default values\n\
\t\tdefault = {}\n\n";
    outputString.append(header);
    // UE TYPES DIR
    outputString.append("\t\tdefault[:ueTypesDir] = \"");
    outputString.append(ueTypesDir);
    outputString.append("\"");
    outputString.append("\t\t# Directory containing users UE type definitions\n");
    // CS TRAFFIC MODELS DIR
    outputString.append("\t\tdefault[:csTrafficModelsDir] = \"");
    outputString.append(csTrafficModelsDir);
    outputString.append("\"");
    outputString.append("\t# Directory containing users CS traffic Models\n");
    // PS TRAFFIC MODELS DIR
    outputString.append("\t\tdefault[:psTrafficModelsDir] = \"");
    outputString.append(psTrafficModelsDir);
    outputString.append("\"");
    outputString.append("\t# Directory containing users PS traffic Models\n");
    // MOBILITY MODELS
    outputString.append("\t\tdefault[:mobilityModelsDir] = \"");
    outputString.append(mobilityModelsDir);
    outputString.append("\"");
    outputString.append("\t# Directory containing users Mobility Models\n");
    // VISUALISATION
    outputString.append("\t\tdefault[:visualization] = ");
    if (UBSimGui){
        outputString.append("true");
    }
    else{
        outputString.append("false");
    }
    outputString.append("\t\t# UBsim GUI\n");

    // PATCHES
    outputString.append("\t\t# patches to use when starting UBsim\n");
    outputString.append("\t\t# Given as a Java classpath, multiple element separated by ':'\n");
    outputString.append("\t\tdefault[:ubsim_patches] = ");
    for (int i=0;i<ubsim_patches.size();i++){
        outputString.append(ubsim_patches[i]);
        if (ubsim_patches[i]!=ubsim_patches.back()){
            outputString.append(":");
        }
    }
    outputString.append("\t\t# UBsim code in UBsim project (ubsim.jar)\n");
    outputString.append("\t\treturn default\n");
    outputString.append("\tend\n\n");

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
