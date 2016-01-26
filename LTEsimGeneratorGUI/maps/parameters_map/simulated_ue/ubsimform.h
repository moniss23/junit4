#ifndef UBSIMFORM_H
#define UBSIMFORM_H

#include <QWidget>
#include "maps/traffic_map/ue_param/ue.h"
#include <QMessageBox>
namespace Ui {
class UBsimForm;
}

class UBsimForm : public QWidget
{
    Q_OBJECT

public:
    explicit UBsimForm(QWidget *parent = 0);
    void set_checkboxactive(bool check);
    bool get_checkboxactive();
    ~UBsimForm();
    void setParameters(Ue *ue);
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_tet_name_returnPressed();
    void on_tet_l1l2_managers_returnPressed();
    void on_tet_rrc_pluginFilterPath_returnPressed();
    void on_tet_ue_network_capability_returnPressed();
    void on_tet_ue_keyDerivationAlgorithm_returnPressed();
    void on_tet_ue_key_returnPressed();
    void on_tet_ue_op_returnPressed();

    void on_tet_imsiMapRange_returnPressed();

    void on_tet_ueTypesDir_returnPressed();

    void on_tet_csTrafficModelsDir_returnPressed();

    void on_tet_psTrafficModelsDir_returnPressed();

    void on_tet_mobilityModelsDir_returnPressed();

    void on_tet_ubsim_patches_returnPressed();

    void on_checkBox_Visualization_clicked();

    void on_pbReset_clicked();
    bool wasChangesBeforeAccept();
    void setChanges();

private:
    Ui::UBsimForm *ui;
    Ue *ue;
    QMessageBox msg,msgBox;
    bool flagConfirmNewValue;
    bool checkboxactive;
    bool wasThereChanges;

};

#endif // UBSIMFORM_H
