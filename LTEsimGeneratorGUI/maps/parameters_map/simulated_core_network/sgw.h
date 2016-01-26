#ifndef SGW_H
#define SGW_H

#include <QString>
#include <QList>

class Sgw
{
public:
    Sgw();
    QString getNames();
    QString getIpAddresses();
    QString getApnLists();
    QString getLDIs();
    bool getCore_network_gateway();

    void setNames(QString n);
    void setIpAddresses(QString ip);
    void setApn_lists(QString a);
    void setLDIs(QString Ldi);
    void setCore_network_gateway(bool cn);

    void resetParams();

private:
    QString names;               // Name of the Serving GWs
    QString ipAddresses;
    QString apn_lists;
    QString LDIs;

    bool core_network_gateway;

    QList <QString> fileParameters;
    void openFile();
    QString searchParameter(QString name);
    QString searchDefaultParameter(QString name);
    void setParameters();
    bool toBool(QString t);
};

#endif // SGW_H
