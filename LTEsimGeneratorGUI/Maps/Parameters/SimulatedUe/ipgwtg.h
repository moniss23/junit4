#ifndef IPGWTG_H
#define IPGWTG_H
#include <QString>
#include <QMessageBox>
#include <QStringList>

class Ipgwtg
{
public:
    Ipgwtg();

    QString getDataGenerator();
    void setDataGenerator(QString value);

    QString getUserDataGen();
    void setUserDataGen( QString value);

    bool getStart_isp_simulator() const;
    void setStart_isp_simulator(bool value);

    QString getIpgwtg_ipAddress() ;
    void setIpgwtg_ipAddress( QString value);

    bool getIpgwtg_inband_signaling() const;
    void setIpgwtg_inband_signaling(bool value);

    QString getIpgwtg_port() const;
    void setIpgwtg_port(QString value);

    bool getIpgwtg_ftp_sender_connect_put() const;
    void setIpgwtg_ftp_sender_connect_put(bool value);

    void resetParams();


private:
    QString dataGenerator;
    QString userDataGen;
    bool start_isp_simulator;
    QString ipgwtg_ipAddress;           // IP address of the interface that can reach the PGW
    bool ipgwtg_inband_signaling;
    int ipgwtg_port;
    bool ipgwtg_ftp_sender_connect_put;

    QList<QString> fileParameters;

    void openFile();
    QString searchParameters(QString name);
    QString searchParametersList(QString name);
    QString searchDefaultParameters(QString name);
    QString searchDefaultParametersList(QString name);
    void setParams();
    bool toBool(QString t);

};

#endif // IPGWTG_H
