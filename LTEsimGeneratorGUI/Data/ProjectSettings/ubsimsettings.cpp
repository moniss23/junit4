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
