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
QString GeneralConfigurationParameters::ParseToScript(){

    QString generalParameters = " def Parameters.getGeneralParameters() \n\
     # Define and return default values\n\
       default = {}\n\
    \n";
                         // log dir
    generalParameters.append("  log_dir = ");
    generalParameters.append(logDir);
    generalParameters.append("\n");
                         // core Parameters
    generalParameters.append("  default[:");
    generalParameters.append("coreParameters] = ");
    generalParameters.append(coreParameters);
    generalParameters.append("\t# String containing start parameters for ltesim core \n");
    generalParameters.append("\t\t\t\t\t\t\t# See ltesim core -help for details\n");
                        // jvm parameters
    generalParameters.append("  default[:");
    generalParameters.append("jvm_parameters] = ");
    generalParameters.append(jvmParameters);
    generalParameters.append(" \t\t# Specify additional JVM parameters\n");
                        // logger handlerSet
    generalParameters.append("  default[:");
    generalParameters.append("logger_handlersSet] = \"");
    generalParameters.append(loggerHandlerSet);
    generalParameters.append("\"\n");
                        // logger file count
    generalParameters.append("  default[:");
    generalParameters.append("logger_file_count] = ");
    generalParameters.append(QString::number(loggerFileCount));
    generalParameters.append("\n");
                        // logger file size limit
    generalParameters.append("  default[:");
    generalParameters.append("logger_file_sizeLimit] = ");
    generalParameters.append(QString::number(loggerFileSizeLimit.first));
    generalParameters.append("**");
    generalParameters.append(QString::number(loggerFileSizeLimit.second));
    generalParameters.append("\n");
                        // logger file gzipEnabled
    generalParameters.append("  default[:");
    generalParameters.append("logger_file_count] = ");
    if (loggerFileCount) {
        generalParameters.append("true");
    }
    else {
        generalParameters.append("false");
    }
    generalParameters.append("\n");

    generalParameters.append("  return default\n");
    generalParameters.append(" end\n\n");

    return generalParameters;
}
