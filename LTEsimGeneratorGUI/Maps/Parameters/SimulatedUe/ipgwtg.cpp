#include "ipgwtg.h"
#include "QFile"
#include "QTextStream"
#include "qdebug.h"

extern QString parametersFileContent;
extern QStringList parametersFileContentList;
extern QString savedParametersFileContent;
extern std::vector<QString> trafficFilesContent;
extern std::vector<QString> savedTrafficFilesContent;
extern bool paramFileChanged;
extern bool paramFileModified;
extern std::vector<bool> trafficFilesChanged;
extern std::vector<bool> trafficFilesModified;

Ipgwtg::Ipgwtg()
{
    //openFile();
    setParams();
}
QString Ipgwtg::getUserDataGen()
{
    return userDataGen.remove("\\n");
}

void Ipgwtg::setUserDataGen(QString value)
{
    userDataGen = value;
     qDebug() <<userDataGen;
}
bool Ipgwtg::getStart_isp_simulator() const
{
    return start_isp_simulator;
}

void Ipgwtg::setStart_isp_simulator(bool value)
{
    start_isp_simulator = value;
}
QString Ipgwtg::getIpgwtg_ipAddress()
{
    return ipgwtg_ipAddress.remove("\"");
}

void Ipgwtg::setIpgwtg_ipAddress( QString value)
{
    ipgwtg_ipAddress = "\"" + value + "\"";
    qDebug() <<ipgwtg_ipAddress;
}
bool Ipgwtg::getIpgwtg_inband_signaling() const
{
    return ipgwtg_inband_signaling;
}

void Ipgwtg::setIpgwtg_inband_signaling(bool value)
{
    ipgwtg_inband_signaling = value;
}
QString Ipgwtg::getIpgwtg_port() const
{
    return QString::number(ipgwtg_port);
}

void Ipgwtg::setIpgwtg_port(QString value)
{
    ipgwtg_port = value.toInt();
}
bool Ipgwtg::getIpgwtg_ftp_sender_connect_put() const
{
    return ipgwtg_ftp_sender_connect_put;
}

void Ipgwtg::setIpgwtg_ftp_sender_connect_put(bool value)
{
    ipgwtg_ftp_sender_connect_put = value;
}
QString Ipgwtg::getDataGenerator()
{
    return dataGenerator.remove("\"");
}

void Ipgwtg::setDataGenerator( QString value)
{
    dataGenerator = value;
}

void Ipgwtg::resetParams()
{
    openFile();
    dataGenerator = searchDefaultParameters(("dataGenerator"));
    userDataGen = searchDefaultParametersList("userDataGen");
    start_isp_simulator  =toBool(searchDefaultParameters("start_isp_simulator").trimmed());
    ipgwtg_ipAddress = searchDefaultParameters("ipgwtg_ipAddress").trimmed();
    ipgwtg_inband_signaling = toBool(searchDefaultParameters("ipgwtg_inband_signaling").trimmed());
    ipgwtg_port = searchDefaultParameters("ipgwtg_port").toInt();
    ipgwtg_ftp_sender_connect_put = toBool(searchDefaultParameters("ipgwtg_ftp_sender_connect_put").trimmed());
}



void Ipgwtg::openFile()
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

QString Ipgwtg::searchParameters(QString name)
{
    QStringList list;
    QString text1= "";
    for (int i=0; i<parametersFileContentList.size();i++)
    {
        if (parametersFileContentList[i].contains(name)){
            text1 = parametersFileContentList[i].trimmed();
            if (text1.left(1) != "#"){
                list = text1.split("#");
                text1 = list[0];
                list = text1.split("=");
                return list[1];
            }
        }
    }
    return NULL;
}

QString Ipgwtg::searchParametersList(QString name)
{
    QStringList list;
    QString date="", tmp;
    bool isPlus = false;
    QString text1= "";
    for (int i=0; i<parametersFileContentList.size(); i++)
    {
        if (parametersFileContentList[i].contains(name) || isPlus){
            text1 = parametersFileContentList[i].trimmed();
            if (text1.contains("start_isp_simulator"))
                break;
            list = text1.split("#");
            text1 = list[0].trimmed();
            if (text1.contains("\" +")){
                isPlus = true;
            }else isPlus = false;
            list = text1.split("\"");
            date += list[1] + "\n";
      }
    }
    return date;
}

QString Ipgwtg::searchDefaultParameters(QString name)
{
    QStringList list;
    QString text1= "";
    for (int i=0; i<fileParameters.size();i++)
    {
        if (fileParameters[i].contains(name)){
            text1 = fileParameters[i].trimmed();
            if (text1.left(1) != "#"){
                list = text1.split("#");
                text1 = list[0];
                list = text1.split("=");
                return list[1];
            }
        }
    }
    return NULL;
}

QString Ipgwtg::searchDefaultParametersList(QString name)
{
    QStringList list;
    QString date="";
    bool isPlus = false;
    QString text1= "";
    for (int i=0; i<fileParameters.size(); i++)
    {
        if (fileParameters[i].contains(name) || isPlus){
            text1 = fileParameters[i].trimmed();
            if (text1.contains("start_isp_simulator"))
                break;
            list = text1.split("#");
            text1 = list[0].trimmed();
            if (text1.contains("\" +")){
                isPlus = true;
            }else isPlus = false;
            list = text1.split("\"");
            date += list[1] + "\n";
        }
    }
    return date;
}

void Ipgwtg::setParams()
{
    dataGenerator = searchParameters("dataGenerator").trimmed();
    userDataGen = searchParametersList("userDataGen").trimmed();
    start_isp_simulator  =toBool(searchParameters("start_isp_simulator").trimmed());
    ipgwtg_ipAddress = searchParameters("ipgwtg_ipAddress").trimmed();
    ipgwtg_inband_signaling = toBool(searchParameters("ipgwtg_inband_signaling").trimmed());
    ipgwtg_port = searchParameters("ipgwtg_port").toInt();
    ipgwtg_ftp_sender_connect_put = toBool(searchParameters("ipgwtg_ftp_sender_connect_put").trimmed());
}
bool Ipgwtg::toBool(QString t){
    if (t.trimmed() == "true" || t.trimmed() == "True" || t.trimmed()=="TRUE" || t.trimmed()=="1")
        return true;
    if (t.trimmed() == "false" || t.trimmed() == "False" || t.trimmed()=="FALSE" || t.trimmed()=="0")
        return false;
    return NULL;
}

