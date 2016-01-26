#ifndef MMEFORM_H
#define MMEFORM_H

#include <QWidget>
#include "mme.h"
#include <QMessageBox>
namespace Ui {
class MmeForm;
}

class MmeForm : public QWidget
{
    Q_OBJECT

public:
    explicit MmeForm(QWidget *parent = 0);
    void set_checkboxactive(bool check);
    bool get_checkboxactive();
    ~MmeForm();
    void setParameters(Mme *mme);
private slots:
    void on_tetMme_names_returnPressed();
    void on_tetMme_tais_returnPressed();
    void on_tetMme_s1ap_uris_returnPressed();
    void on_tetS1ap_pluginFilterPath_returnPressed();
    void on_tetMmes_returnPressed();
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_tet_generators_returnPressed();
    void on_tet_paging_generator_names_returnPressed();
    void on_tet_imsi_ranges_returnPressed();
    void on_tet_mme_codes_returnPressed();
    void on_tet_ue_paging_identity_returnPressed();
    void on_tet_paging_s1ap_uris_returnPressed();

    void on_checkBox_generate_pagings_clicked();

    void on_checkBox_s1ap_checkASN1_constraints_clicked();

    void on_checkBox_bundle_paging_clicked();

    void on_pbReset_clicked();
    bool wasChangesBeforeAccept();
    void setChanges();



private:
    Ui::MmeForm *ui;
    Mme *mme;
    QMessageBox msg,msgBox;
    bool flagConfirmNewValue;
    bool checkboxactive;
    bool wasThereChanges;

    void saveAll();
};

#endif // MMEFORM_H
