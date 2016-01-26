#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QString>
#include <QStringList>
#include <QListWidgetItem>
#include <maps/object_map/cell.h>
#include <maps/object_map/handover.h>
#include <maps/object_map/center.h>

struct Project{
    QString name;
    QString fullpath;
    QListWidgetItem* widget;
    QString rbOutputDir;
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
QStringList read_project_file(QString project_name,QString dir);
void write_project_file(QString project_name,QString project_content,QString dir);
void write_projects_file();
void read_projects_file();
QString get_project_name(QListWidgetItem* item);
QString itoa(int i);

QString get_project_name(QListWidgetItem* item);
QString get_project_dir(QListWidgetItem* item);
QString get_project_dir(QString project_name);

void write_settings_file();
void read_settings_file();

void setCenterOfApplication(QWidget* widget);

#endif // ENCRYPTION_H
