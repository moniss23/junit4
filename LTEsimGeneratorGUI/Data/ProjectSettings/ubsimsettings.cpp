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
    stream << name << l1l2_managers << rrc_pluginFilterPath << ue_network_capability
           << ue_keyDerivationAlgorithm << ue_key << ue_op << imsiMapRange << ueTypesDir
           << csTrafficModelsDir << psTrafficModelsDir << mobilityModelsDir << UBSimGui
           << ubsim_patches;

    return serializedData.buffer();
}

void UBSimSettings::deserializeData(const QByteArray &rawData) {
    QDataStream stream(rawData);
    stream >> name >> l1l2_managers >> rrc_pluginFilterPath >> ue_network_capability
           >> ue_keyDerivationAlgorithm >> ue_key >> ue_op >> imsiMapRange >> ueTypesDir
           >> csTrafficModelsDir >> psTrafficModelsDir >> mobilityModelsDir >> UBSimGui
           >> ubsim_patches;
}
