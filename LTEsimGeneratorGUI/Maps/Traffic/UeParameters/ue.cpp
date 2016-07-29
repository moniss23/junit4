#include "ue.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <qdebug.h>

extern QStringList parametersFileContentList;
extern QString savedParametersFileContent;
extern std::vector<QString> trafficFilesContent;

Ue::Ue()
{
    //openFile();
    setParameters();
}
QString Ue::getName()
{
    return name.remove("\"");
}

void Ue::setName( QString value)
{
    name = "\""+value +"\"";
    qDebug() << name;
}
QString Ue::getL1l2_managers()
{
    return l1l2_managers.remove("\"");
}

void Ue::setL1l2_managers( QString value)
{
    l1l2_managers = "\"" + value + "\"";
    qDebug() << l1l2_managers;
}
QString Ue::getRrc_pluginFilterPath()
{
    return rrc_pluginFilterPath.remove("\"");
}

void Ue::setRrc_pluginFilterPath(QString value)
{
    rrc_pluginFilterPath = "\"" + value + "\"";
    qDebug() << rrc_pluginFilterPath;
}
QString Ue::getUctool_ip()
{
    uctool_ip.remove("{");
    uctool_ip.remove("}");
    return uctool_ip.remove("\"");
}

void Ue::setUctool_ip( QString value)
{
    uctool_ip = "\"{" + value + "}\"";
    qDebug() << uctool_ip;
}
QString Ue::getUctool_cIds()
{
    uctool_cIds.remove("{");
    uctool_cIds.remove("}");
    return uctool_cIds.remove("\"");
}

void Ue::setUctool_cIds(QString value)
{
    uctool_cIds = "\"{" + value + "}\"";
    qDebug() << uctool_cIds;
}
QString Ue::getUctool_service_ip()
{
    uctool_service_ip.remove("{");
    uctool_service_ip.remove("}");
    return uctool_service_ip.remove("\"");
}

void Ue::setUctool_service_ip(QString value)
{
    uctool_service_ip = "\"{" + value + "}\"";
    qDebug() << uctool_service_ip;
}
QString Ue::getUe_network_capability()
{
    return ue_network_capability.remove("\"");
}

void Ue::setUe_network_capability(QString value)
{
    ue_network_capability = "\"" + value + "\"";
    qDebug() << ue_network_capability;
}
QString Ue::getUe_keyDerivationAlgorithm()
{
    return ue_keyDerivationAlgorithm.remove("\"");
}

void Ue::setUe_keyDerivationAlgorithm( QString value)
{
    ue_keyDerivationAlgorithm = "\"" + value + "\"";
    qDebug() << ue_keyDerivationAlgorithm;
}
QString Ue::getUe_key()
{
    return ue_key.remove("\"");
}

void Ue::setUe_key(QString value)
{
    ue_key = "\"" + value + "\"";
    qDebug() << ue_key;
}
QString Ue::getUe_op()
{
    return ue_op.remove("\"");
}

void Ue::setUe_op( QString value)
{
    ue_op = "\"" + value + "\"";
    qDebug() << ue_op;
}
QString Ue::getImsiMapRange()
{
    return imsiMapRange.remove("\"");
}

void Ue::setImsiMapRange( QString value)
{
    imsiMapRange = "\"" + value + "\"";;
    qDebug() << imsiMapRange;
}
QString Ue::getUeTypesDir()
{
    return ueTypesDir.remove("\"");
}

void Ue::setUeTypesDir( QString value)
{
    ueTypesDir = "\"" + value + "\"";
    qDebug() << ueTypesDir;
}
QString Ue::getCsTrafficModelsDir()
{
    return csTrafficModelsDir.remove("\"");
}

void Ue::setCsTrafficModelsDir( QString value)
{
    csTrafficModelsDir = "\"" + value + "\"";;
    qDebug() << csTrafficModelsDir;
}
QString Ue::getPsTrafficModelsDir()
{
    return psTrafficModelsDir.remove("\"");
}

void Ue::setPsTrafficModelsDir( QString value)
{
    psTrafficModelsDir = "\"" + value + "\"";;
    qDebug() << psTrafficModelsDir;
}
QString Ue::getMobilityModelsDir()
{
    return mobilityModelsDir.remove("\"");
}

void Ue::setMobilityModelsDir( QString value)
{
    mobilityModelsDir = "\"" + value + "\"";;
    qDebug() << mobilityModelsDir;
}
QString Ue::getUbsim_patches()
{
    return ubsim_patches.remove("\"");
}

void Ue::setUbsim_patches( QString value)
{
    ubsim_patches = "\"" + value + "\"";;
    qDebug() << ubsim_patches;
}
bool Ue::getVisualization() const
{
    return visualization;
}

void Ue::setVisualization(const bool &value)
{
    visualization = value;
}
bool Ue::getStart_ue_component() const
{
    return start_ue_component;
}

void Ue::setStart_ue_component(bool value)
{
    start_ue_component = value;
}

void Ue::resetParamsUBSIM()
{
    openFile();
    start_ue_component = toBool(searchDefaultParameter(":start_ue_component").trimmed());
    name = searchDefaultParameter(":name").trimmed();
    l1l2_managers = searchDefaultParameter(":l1l2_managers").trimmed();
    rrc_pluginFilterPath = searchDefaultParameter(":rrc_pluginFilterPath").trimmed();
    ue_network_capability = searchDefaultParameter(":ue_network_capability").trimmed();
    ue_keyDerivationAlgorithm = searchDefaultParameter(":ue_keyDerivationAlgorithm").trimmed();
    ue_key = searchDefaultParameter("ue_key]").trimmed();
    ue_op = searchDefaultParameter(":ue_op]").trimmed();

    imsiMapRange = searchDefaultParameter("imsiMapRange").trimmed();
    ueTypesDir = searchDefaultParameter("ueTypesDir").trimmed();
    csTrafficModelsDir = searchDefaultParameter("csTrafficModelsDir").trimmed();
    psTrafficModelsDir = searchDefaultParameter("psTrafficModelsDir").trimmed();
    mobilityModelsDir  =searchDefaultParameter("mobilityModelsDir").trimmed();
    visualization = toBool(searchDefaultParameter("visualization"));
    ubsim_patches = searchDefaultParameter(":ubsim_patches").trimmed();
}

void Ue::resetParamsUCTOOL()
{
    openFile();
    uctool_ip = searchDefaultParameter(":uctool_ip").trimmed();
    uctool_cIds = searchDefaultParameter(":uctool_cIds").trimmed();
    uctool_service_ip = searchDefaultParameter(":uctool_service_ip").trimmed();
}


bool Ue::toBool(QString t){
    if (t.trimmed() == "true" || t.trimmed() == "True" || t.trimmed()=="TRUE" || t.trimmed()=="1")
        return true;
    if (t.trimmed() == "false" || t.trimmed() == "False" || t.trimmed()=="FALSE" || t.trimmed()=="0")
        return false;
    return NULL;
}
void Ue::openFile()
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

QString Ue::searchDefaultParameter(QString name)
{
    QStringList list;
    QString text1= "";
    for (int i=0; i<fileParameters.size();i++)
    {
        if (fileParameters[i].contains(name)){
            text1 = fileParameters[i].trimmed();

            if(text1.left(1)!="#"){
                list = text1.split("#");
                text1 = list[0];
                list = text1.split("=");
                return list[1];
            }
        }
    }
    return NULL;
}

QString Ue::searchParameter(QString name)
{
    QStringList list;
    QString text1= "";
    for (int i=0; i<parametersFileContentList.size();i++)
    {
        if (parametersFileContentList[i].contains(name)){
            text1 = parametersFileContentList[i].trimmed();
            qDebug()<<"ONE LINE AHEAD:   \n"<<parametersFileContentList[i+1];
            if(text1.left(1)!="#"){
                list = text1.split("#");
                text1 = list[0];
                list = text1.split("=");
                qDebug()<<"Moj element: "<<parametersFileContentList[i];
                qDebug()<<"Moj element: "<<parametersFileContentList[i];
                qDebug() << "THIS IS IT!!!:  \n" <<list;

                return list[1];
            }
        }
    }
    return NULL;
}

void Ue::setParameters()
{
    start_ue_component = toBool(searchParameter(":start_ue_component").trimmed());
    name = searchParameter(":name").trimmed();
    l1l2_managers = searchParameter(":l1l2_managers").trimmed();
    rrc_pluginFilterPath = searchParameter(":rrc_pluginFilterPath").trimmed();
    uctool_ip = searchParameter(":uctool_ip").trimmed();
    uctool_cIds = searchParameter(":uctool_cIds").trimmed();
    uctool_service_ip = searchParameter(":uctool_service_ip").trimmed();
    ue_network_capability = searchParameter(":ue_network_capability").trimmed();
    ue_keyDerivationAlgorithm = searchParameter(":ue_keyDerivationAlgorithm").trimmed();
    ue_key = searchParameter("ue_key]").trimmed();
    ue_op = searchParameter(":ue_op]").trimmed();

    imsiMapRange = searchParameter("imsiMapRange").trimmed();
    ueTypesDir = searchParameter("ueTypesDir").trimmed();
    csTrafficModelsDir = searchParameter("csTrafficModelsDir").trimmed();
    psTrafficModelsDir = searchParameter("psTrafficModelsDir").trimmed();
    mobilityModelsDir  =searchParameter("mobilityModelsDir").trimmed();
    visualization = toBool(searchParameter("visualization"));
    ubsim_patches = searchParameter(":ubsim_patches").trimmed();
}

