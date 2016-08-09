#include "mme.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVector>

extern QStringList parametersFileContentList;
extern QString savedParametersFileContent;

Mme::Mme()
{
    setMmeParameters();
}

Mme::~Mme()
{
}

QString Mme::getMme_names()
{
    mme_names.remove(QChar('['));
    mme_names.remove(QChar(']'));
    mme_names.remove(QChar('"'));
    return mme_names;
}

QString Mme::getMme_tais()
{
    mme_tais.remove(QChar('['));
    mme_tais.remove(QChar(']'));
    mme_tais.remove(QChar('"'));
    return mme_tais;
}

QString Mme::getMmes()
{
    return QString::number(mmes);
}

QString Mme::getMme_s1ap_uris()
{
    mme_s1ap_uris.remove(QChar('['));
    mme_s1ap_uris.remove(QChar(']'));
    mme_s1ap_uris.remove(QChar('"'));
    return mme_s1ap_uris;
}

QString Mme::getS1ap_pluginFilterPath()
{
    s1ap_pluginFilterPath.remove(QChar('"'));
    return s1ap_pluginFilterPath;
}

bool Mme::getSimulate_core()
{
    return simulate_core;
}

void Mme::setMme_names(QString mme_n)
{
    mme_names = "[\"" + mme_n + "\"]";
}

void Mme::setMme_tais(QString mme_t)
{
    mme_tais = "[\"" + mme_t +"\"]";
}

void Mme::setMmes(QString mmes)
{
    this->mmes = mmes.toInt();
}

void Mme::setMme_s1ap_uris(QString s1ap_uris)
{
    mme_s1ap_uris = "\""+ s1ap_uris +"\"";
}

void Mme::setS1ap_pluginFilterPath(QString s1ap_plugin)
{
    s1ap_pluginFilterPath = "\"" + s1ap_plugin + "\"";
}

void Mme::setSimulate_core(bool sc)
{
    simulate_core = sc;
}
QString Mme::getPaging_generator_names()
{
    paging_generator_names.remove(QChar('['));
    paging_generator_names.remove(QChar(']'));
    paging_generator_names.remove(QChar('"'));
    return paging_generator_names;
}

void Mme::setPaging_generator_names( QString value)
{
    paging_generator_names = "[\"" + value.replace(", ","\", \"") + "\"]";
}
QString Mme::getImsi_ranges()
{
    imsi_ranges.remove(QChar('['));
    imsi_ranges.remove(QChar(']'));
    imsi_ranges.remove(QChar('"'));
    return imsi_ranges;
}

void Mme::setImsi_ranges(QString value)
{
    imsi_ranges = "[\"" + value.replace(", ","\", \"") + "\"]";
}
QString Mme::getMme_codes()
{
    mme_codes.remove(QChar('['));
    mme_codes.remove(QChar(']'));
    mme_codes.remove(QChar('"'));
    return mme_codes;
}

void Mme::setMme_codes(QString value)
{
    mme_codes = "[\"" + value.replace(", ","\", \"") + "\"]";
}
QString Mme::getUe_paging_identity()
{
    return ue_paging_identity.remove(QChar('"'));
}

void Mme::setUe_paging_identity(QString value)
{
    ue_paging_identity = "\""+ value + "\"";
}
QString Mme::getPaging_s1ap_uris()
{
    paging_s1ap_uris.remove(QChar('['));
    paging_s1ap_uris.remove(QChar(']'));
    paging_s1ap_uris.remove(QChar('"'));
    return paging_s1ap_uris;
}

void Mme::setPaging_s1ap_uris( QString value)
{
    paging_s1ap_uris = "[\"" + value.replace(", ","\", \"") + "\"]";
}
bool Mme::getS1ap_checkASN1_constraints() const
{
    return s1ap_checkASN1_constraints;
}

void Mme::setS1ap_checkASN1_constraints(bool value)
{
    s1ap_checkASN1_constraints = value;
}
bool Mme::getBundle_paging() const
{
    return bundle_paging;
}

void Mme::setBundle_paging(bool value)
{
    bundle_paging = value;
}
bool Mme::getGenerate_pagings() const
{
    return generate_pagings;
}

void Mme::setGenerate_pagings(bool value)
{
    generate_pagings = value;
}
QString Mme::getGenerators() const
{
    return QString::number(generators);
}

void Mme::setGenerators(QString value)
{
    generators = value.toInt();
}

void Mme::resetParams()
{
    openFile();

    //-----------------mme parameters---------------------------------------
    simulate_core = toBool(searchDefaultParameter((":simulate_core")));
    mme_names =  searchDefaultParameter(":mme_names").trimmed();
    mme_tais =  searchDefaultParameter(":mme_tais").trimmed();
    mmes = searchDefaultParameter(":mmes").toInt();
    mme_s1ap_uris =  searchDefaultParameter(":mme_s1ap_uris").trimmed();
    s1ap_pluginFilterPath = searchDefaultParameter(":s1ap_pluginFilterPath").trimmed();

     //-----------------paging Parameters--------------------------------------
    generate_pagings = toBool(searchDefaultParameter((":generate_pagings")));
    generators = searchDefaultParameter((":generators")).toInt();
    paging_generator_names = searchDefaultParameter((":paging_generator_names")).trimmed();
    imsi_ranges = searchDefaultParameter((":imsi_ranges")).trimmed();
    mme_codes = searchDefaultParameter((":mme_codes")).trimmed();
    ue_paging_identity = searchDefaultParameter((":ue_paging_identity")).trimmed();
    paging_s1ap_uris = searchDefaultParameter((":paging_s1ap_uris")).trimmed();
    s1ap_checkASN1_constraints = toBool(searchDefaultParameter((":s1ap_checkASN1_constraints")));
    bundle_paging = toBool(searchDefaultParameter((":bundle_paging")));

}

bool Mme::toBool(QString t){
    if (t.trimmed() == "true" || t.trimmed() == "True" || t.trimmed()=="TRUE" || t.trimmed()=="1")
        return true;
    if (t.trimmed() == "false" || t.trimmed() == "False" || t.trimmed()=="FALSE" || t.trimmed()=="0")
        return false;
    return NULL;
}

void Mme::openFile()
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

QString Mme::searchParameter(QString name)
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

QString Mme::searchDefaultParameter(QString name)
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

void Mme::setMmeParameters(){

   //-----------------mme parameters---------------------------------------
   simulate_core = toBool(searchParameter((":simulate_core")));
   mme_names =  searchParameter(":mme_names").trimmed();
   mme_tais =  searchParameter(":mme_tais").trimmed();
   mmes = searchParameter(":mmes").toInt();
   mme_s1ap_uris =  searchParameter(":mme_s1ap_uris").trimmed();
   s1ap_pluginFilterPath = searchParameter(":s1ap_pluginFilterPath").trimmed();
    //-----------------paging Parameters--------------------------------------
   generate_pagings = toBool(searchParameter((":generate_pagings")));
   generators = searchParameter((":generators")).toInt();
   paging_generator_names = searchParameter((":paging_generator_names")).trimmed();
   imsi_ranges = searchParameter((":imsi_ranges")).trimmed();
   mme_codes = searchParameter((":mme_codes")).trimmed();
   ue_paging_identity = searchParameter((":ue_paging_identity")).trimmed();
   paging_s1ap_uris = searchParameter((":paging_s1ap_uris")).trimmed();
   s1ap_checkASN1_constraints = toBool(searchParameter((":s1ap_checkASN1_constraints")));
   bundle_paging = toBool(searchParameter((":bundle_paging")));
}

