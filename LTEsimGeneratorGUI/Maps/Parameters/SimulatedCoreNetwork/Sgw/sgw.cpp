#include "sgw.h"
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <qdebug.h>

extern QStringList parametersFileContentList;
extern QString savedParametersFileContent;
extern std::vector<QString> trafficFilesContent;

Sgw::Sgw()
{
  setParameters();
}

QString Sgw::getNames()
{
    names.remove(QChar('"'));
    names.remove(QChar('['));
    names.remove(QChar(']'));
    return names;
}

QString Sgw::getIpAddresses()
{
    ipAddresses.remove(QChar('"'));
    ipAddresses.remove(QChar('['));
    ipAddresses.remove(QChar(']'));
    return ipAddresses;
}

QString Sgw::getApnLists()
{
    apn_lists.remove(QChar('"'));
    apn_lists.remove(QChar('['));
    apn_lists.remove(QChar(']'));
    return apn_lists;
}

QString Sgw::getLDIs()
{
    LDIs.remove(QChar('"'));
    LDIs.remove(QChar('['));
    LDIs.remove(QChar(']'));
    return LDIs;
}

bool Sgw::getCore_network_gateway()
{
    return core_network_gateway;
}

void Sgw::setNames(QString n)
{
    names = "[\"" + n + "\"]";
    qDebug() << names;
}

void Sgw::setIpAddresses(QString ip)
{
    ipAddresses = "[\"" + ip + "\"]";
    qDebug() << ipAddresses;
}

void Sgw::setApn_lists(QString a)
{
    apn_lists = "[\"" + a + "\"]";
    qDebug() << apn_lists;
}

void Sgw::setLDIs(QString Ldi)
{
    LDIs =  "[\"" + Ldi + "\"]";
    qDebug() << LDIs;
}

void Sgw::setCore_network_gateway(bool cn)
{
    core_network_gateway = cn;
}

void Sgw::resetParams()
{
    openFile();
    names = searchDefaultParameter(":sgw_names").trimmed();
    ipAddresses = searchDefaultParameter(":sgw_ipAddresses").trimmed();
    apn_lists = searchDefaultParameter(":apn_lists").trimmed();
    LDIs = searchDefaultParameter(":sgw_LDIs").trimmed();
    core_network_gateway = toBool(searchDefaultParameter(":core_network_gateway").trimmed());
}

void Sgw::openFile()
{
    QString fileName = ":/RbFiles/parameters.rb";
    QFile file1(fileName);

    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
        return;              // if coudn't open file: stop loading file

    QString text1="";
    QTextStream stream(&file1);

    while(!stream.atEnd()){
        text1 = stream.readLine();
        fileParameters << text1.trimmed();
   }
}

QString Sgw::searchParameter(QString name)
{
    QStringList list;
    QString text1= "";
    for (int i=0; i<parametersFileContentList.size();i++)
    {
        if (parametersFileContentList[i].contains(name)){
            text1 = parametersFileContentList[i];
            list = text1.split("#");
            text1 = list[0];
            list = text1.split("=");
            return list[1];
        }
    }
    return NULL;
}

QString Sgw::searchDefaultParameter(QString name)
{
    QStringList list;
    QString text1= "";
    for (int i=0; i<fileParameters.size();i++)
    {
        if (fileParameters[i].contains(name)){
            text1 = fileParameters[i];
            list = text1.split("#");
            text1 = list[0];
            list = text1.split("=");
            return list[1];
        }
    }
    return NULL;
}

void Sgw::setParameters()
{
    names = searchParameter(":sgw_names").trimmed();
    ipAddresses = searchParameter(":sgw_ipAddresses").trimmed();
    apn_lists = searchParameter(":apn_lists").trimmed();
    LDIs = searchParameter(":sgw_LDIs").trimmed();
    core_network_gateway = toBool(searchParameter(":core_network_gateway").trimmed());
}

bool Sgw::toBool(QString t)
{
    if (t.trimmed() == "true" || t.trimmed() == "True" || t.trimmed()=="TRUE")
        return true;
    if (t.trimmed() == "false" || t.trimmed() == "False" || t.trimmed()=="FALSE")
        return false;
    return NULL;
}

