#include "generalconfigurationparameters.h"

#include <QBuffer>
#include <QDataStream>

GeneralConfigurationParameters::GeneralConfigurationParameters()
{

}

QString GeneralConfigurationParameters::getElementType() const {
    return QString("GeneralConfigurationParameters");
}

QByteArray GeneralConfigurationParameters::serializeData() {
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);

    stream << logDir << coreParameters << jvmParameters << loggerHandlerSet << loggerFileCount
           << loggerFileSizeLimit << loggerFileGzipEnabled;

    return serializedData.buffer();
}

void GeneralConfigurationParameters::deserializeData(const QByteArray &rawData) {
    QDataStream stream(rawData);

    stream >> logDir >> coreParameters >> jvmParameters >> loggerHandlerSet >> loggerFileCount
           >> loggerFileSizeLimit >> loggerFileGzipEnabled;
}
