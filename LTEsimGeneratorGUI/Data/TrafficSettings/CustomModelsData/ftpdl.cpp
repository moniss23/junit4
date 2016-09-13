#include "ftpdl.h"

FtpDl::FtpDl()
{

}

QString FtpDl::getElementType() const
{
    return QString("FtpDl");
}

QByteArray FtpDl::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << ftpDlQci << ftpDlFilesize << ftpDlMinThroughput;

    return serializedData.buffer();
}

void FtpDl::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> ftpDlQci >> ftpDlFilesize >> ftpDlMinThroughput;
}
