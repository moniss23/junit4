#include "pagingsettings.h"
#include <QDataStream>
#include <QBuffer>

PagingSettings::PagingSettings()
{

}
PagingSettings::~PagingSettings()
{

}

QString PagingSettings::getElementType() const
{
    return QString("PagingSettings");
}

QByteArray PagingSettings::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << isUsedInConfiguration << generators << names << imsiRanges << mmeCodes << uePagingIdentity << pagingSlapUris << bundlePaging << rates;
    return serializedData.buffer();
}

void PagingSettings::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> isUsedInConfiguration >> generators >> names >> imsiRanges >> mmeCodes >> uePagingIdentity >> pagingSlapUris >> bundlePaging >> rates;
}
QString PagingSettings::ParseToScript()
{
    QString outputString;
    // HEADER
    outputString.append(" def Parameters.getPagingGeneratorParameters()\n\
                        # Define and return default values\n");
    // GENERATE paging
    outputString.append("  default = {}\n");
    outputString.append("  default[:generate_pagings] = ");
    if (isUsedInConfiguration){
        outputString.append("true");
    }
    else {
        outputString.append("false");
    }    outputString.append("\t\t\t\t\t# Set to true if paging generators are used in the configuration.\n");
    // GENERATORS
    outputString.append("  default[:generators] = ");
    outputString.append(QString::number(generators));
    outputString.append("\t\t\t\t\t\t# Number of paging generators\n");
    // paging GENERATORS NAMES
    outputString.append("  default[:paging_generator_names] = [");
    for (QString &name:names){
        outputString.append("\"");
        outputString.append(name);
        outputString.append("\"");
        if (name == names.back()){
            outputString.append("]");
        }
        else {
            outputString.append(",");
        }
    }
    outputString.append("\t# Name of the paging generators\n");
    // IMSI RANGES
    outputString.append("  default[:imsi_ranges] = [");
    for (QString &range:imsiRanges){
        outputString.append("\"");
        outputString.append(range);
        outputString.append("\"");
        if (range == imsiRanges.back()){
            outputString.append("]");
        }
        else {
            outputString.append(",");
        }
    }
    outputString.append("\t# The IMSI range which pagings are generated by each generator.\n");
    outputString.append("\n  # The IP addresses must be available on the LTEsim server and reachable from the eNB CP interface\n");
    // MME CODES
    outputString.append("  default[:mme_codes] = [");
    if (mmeCodes.empty()){
        outputString.append("]");
    }
    else {
        for (QString &code:mmeCodes){
            outputString.append("\"");
            outputString.append(code);
            outputString.append("\"");
            if (code == mmeCodes.back()){
                outputString.append("]");
            }
            else {
                outputString.append(",");
            }
        }
    }
    outputString.append("  # Used to generate GUMMEI\n");
    // paging IDENTITY
    outputString.append("  default[:ue_paging_identity] = \"");
    outputString.append(uePagingIdentity);
    outputString.append("\"");
    outputString.append(" # Can be IMSI or STMSI\n");
    // paging S1AP URIS
    outputString.append("  default[:paging_s1ap_uris] = [");
    for (QString &uri:pagingSlapUris){
        outputString.append("\"");
        outputString.append(uri);
        outputString.append("\"");
        if (uri == pagingSlapUris.back()){
            outputString.append("]");
        }
        else {
            outputString.append(",");
        }
    }
    outputString.append("\n");
    // S1AP CHECKASN1 CONSTRAINS
    outputString.append("  default[:s1ap_checkASN1_constraints] = ");
    outputString.append(QString(s1apCheckAsn1Contrains));
    outputString.append("\t# Set constraint checks to true to get info of broken ASN.1 messages\n");
    // BUNDLE paging
    outputString.append("  default[:bundle_paging] = ");
    if (bundlePaging){
        outputString.append("true");
    }
    else {
        outputString.append("false");
    }
    outputString.append("  # Set constraint check to true to turn paging bundle.\n");
    outputString.append("  # All JMX parameters can be listed with help :paginggenerator in the ltesim_cli\n");
    outputString.append("  return default\n");
    outputString.append(" end\n\n");
    return outputString;
}
