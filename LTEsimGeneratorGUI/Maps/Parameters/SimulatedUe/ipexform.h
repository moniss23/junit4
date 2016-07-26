#ifndef IPEXFORM_H
#define IPEXFORM_H
#include <Maps/Parameters/SimulatedUe/ipgwtg.h>

#include <QWidget>

namespace Ui {
class ipexForm;
}

class ipexForm : public QWidget
{
    Q_OBJECT

public:
    explicit ipexForm(QWidget *parent = 0);
    void set_checkboxactive(bool check);
    bool get_checkboxactive();
    ~ipexForm();
    void setParameters(Ipgwtg *ipex, bool flagUe);
private slots:
    
    void on_tet_ipgwtg_ipAddress_returnPressed();
    void on_tet_ipgwtg_port_returnPressed();
    void on_checkBox_start_isp_simulator_clicked();
    void on_checkBox_ipgwtg_inband_signaling_clicked();
    void on_checkBox_ipgwtg_ftp_sender_connect_put_clicked();
   
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_pbReset_clicked();
    bool wasChangesBeforeAccept();
    void setChanges();

    void on_tet_dataGenerator_returnPressed();

private:
    Ui::ipexForm *ui;
    Ipgwtg *ipex;
    QMessageBox msg,msgBox;
    bool flagUe;
    bool flagConfirmNewValue;
    bool checkboxactive;
    bool wasThereChanges;
    void saveAll();
};

#endif // IPEXFORM_H
