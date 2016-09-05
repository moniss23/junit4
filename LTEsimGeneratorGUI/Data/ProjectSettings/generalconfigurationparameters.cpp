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

    QString generalParameters = "\tdef Parameters.getGeneralParameters() \n\
    \t# Define and return default values\n\
    \t\tdefault = {}\n\
    \n";
                         // log dir
    generalParameters.append("\t\tlog_dir");
    generalParameters.append(logDir);
    generalParameters.append("\n");
                         // core Parameters
    generalParameters.append("\t\tdefault[:");
    generalParameters.append("coreParameters] = ");
    generalParameters.append(coreParameters);
    generalParameters.append("\t# String containing start parameters for ltesim core \n");
    generalParameters.append("\t\t\t\t\t# See ltesim core -help for details\n");
                        // jvm parameters
    generalParameters.append("\t\tdefault[:");
    generalParameters.append("jvm_parameters] = ");
    generalParameters.append(jvmParameters);
    generalParameters.append(" \t\t# Specify additional JVM parameters\n");
                        // logger handlerSet
    generalParameters.append("\t\tdefault[:");
    generalParameters.append("logger_handlersSet] = ");
    generalParameters.append(loggerHandlerSet);
    generalParameters.append("\n");
                        // logger file count
    generalParameters.append("\t\tdefault[:");
    generalParameters.append("logger_file_count] = ");
    generalParameters.append(QString::number(loggerFileCount));
    generalParameters.append("\n");
                        // logger file size limit
    generalParameters.append("\t\tdefault[:");
    generalParameters.append("logger_file_sizeLimit] = ");
    generalParameters.append(QString::number(loggerFileSizeLimit.first));
    generalParameters.append("**");
    generalParameters.append(QString::number(loggerFileSizeLimit.second));
    generalParameters.append("\n");
                        // logger file gzipEnabled
    generalParameters.append("\t\tdefault[:");
    generalParameters.append("logger_file_count] = ");
    if (loggerFileCount) {
        generalParameters.append("true");
    }
    else {
        generalParameters.append("false");
    }
    generalParameters.append("\n");

    generalParameters.append("\t\treturn default\n");
    generalParameters.append("\tend\n\n");

    return generalParameters;
}
