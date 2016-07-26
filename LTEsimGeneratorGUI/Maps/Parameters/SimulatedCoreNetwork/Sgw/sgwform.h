#ifndef SGWFORM_H
#define SGWFORM_H

#include <QWidget>
#include <Maps/Parameters/SimulatedCoreNetwork/Sgw/sgw.h>
#include <QMessageBox>
namespace Ui {
class SGWForm;
}

class SGWForm : public QWidget
{
    Q_OBJECT

public:
    explicit SGWForm(QWidget *parent = 0);
    void setParameters(Sgw *sgw);
    void set_checkboxactive(bool check);
    bool get_checkboxactive();
    ~SGWForm();
private slots:
    void on_tet_sgw_names_returnPressed();
    void on_tet_sgw_ipAddresses_returnPressed();
    void on_tet_sgw_apn_lists_returnPressed();
    void on_tet_sgw_LDIs_returnPressed();

    void on_buttonBox_accepted();

    void on_pbReset_clicked();

    void on_buttonBox_rejected();
    bool wasChangesBeforeAccept();
    void setChanges();

private:
    Ui::SGWForm *ui;
    Sgw *sgw;
    QMessageBox msg,msgBox;
    bool flagConfirmNewValue;
    bool checkboxactive;
    bool wasThereChanges;
    void saveAll();
};

#endif // SGWFORM_H
