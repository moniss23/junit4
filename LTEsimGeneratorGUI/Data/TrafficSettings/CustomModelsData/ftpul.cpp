#include "ftpul.h"

#include <QByteArray>
#include <QDataStream>
#include <QBuffer>

FtpUl::FtpUl()
{

}

QString FtpUl::getElementType() const
{
    return QString("FtpUl");
}

QByteArray FtpUl::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << currentQciTextFtpUl << ftpUlQci << ftpUlFilesize << ftpUlMinThroughput;

    return serializedData.buffer();
}

void FtpUl::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> currentQciTextFtpUl >> ftpUlQci >> ftpUlFilesize >> ftpUlMinThroughput;
}
