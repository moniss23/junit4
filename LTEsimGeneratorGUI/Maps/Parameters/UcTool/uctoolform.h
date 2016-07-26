#ifndef UCTOOLFORM_H
#define UCTOOLFORM_H

#include <QWidget>
#include <Maps/Traffic/UeParameters/ue.h>
#include <QMessageBox>

namespace Ui {
class UCtoolForm;
}

class UCtoolForm : public QWidget
{
    Q_OBJECT

public:
    explicit UCtoolForm(QWidget *parent = 0);
    void set_checkboxactive(bool check);
    bool get_checkboxactive();
    ~UCtoolForm();
    void setParameters(Ue *ue);
private slots:
    void on_tet_uctool_ip_returnPressed();
    void on_tet_uctool_cIds_returnPressed();
    void on_tet_uctool_service_ip_returnPressed();

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_pbReset_clicked();
    bool wasChangesBeforeAccept();
    void setChanges();

private:
    Ui::UCtoolForm *ui;
    Ue *ue;
    QMessageBox msg,msgBox;
    bool flagConfirmNewValue;
    bool checkboxactive;
    bool wasThereChanges;

};

#endif // UCTOOLFORM_H
