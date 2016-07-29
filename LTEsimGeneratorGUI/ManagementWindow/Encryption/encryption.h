#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QString>
#include <QStringList>
#include <QListWidgetItem>
#include <Maps/MapObjects/cell.h>
#include <Maps/MapObjects/handover.h>
#include <Maps/MapObjects/center.h>
struct Project{
    QString name;
    QString fullpath;
    QListWidgetItem* widget;
    QString rbOutputDir;
    QString chosenMapType;
};

struct cellName{
    Cell* obj;
    QString name;
};

struct centerName{
    Center* obj;
    QString name;
};

struct handoverName{
    Handover* obj;
    QString name;
};

const QString cipher_key="myvoiceismypassportverifyme";

const char* crypt(const char* plaintext,int text_len,const char* key,int key_len,bool terminatingZero=false);


QString itoa(int i);

QString get_project_name(QListWidgetItem* item, const std::vector<Project> &projects);
QString get_project_dir(QListWidgetItem* item, const std::vector<Project> &projects);
QString get_project_dir(QString project_name, const std::vector<Project> &projects);


#endif // ENCRYPTION_H
