#include "ftpdl.h"

#include <QByteArray>
#include <QDataStream>
#include <QBuffer>

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
    stream << currentQciTextFtpDl << ftpDlQci << ftpDlFilesize << ftpDlMinThroughput;

    return serializedData.buffer();
}

void FtpDl::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> currentQciTextFtpDl >> ftpDlQci >> ftpDlFilesize >> ftpDlMinThroughput;
}
