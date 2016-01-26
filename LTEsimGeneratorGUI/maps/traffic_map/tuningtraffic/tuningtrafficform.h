#ifndef TUNINGTRAFFICFORM_H
#define TUNINGTRAFFICFORM_H

#include <QWidget>
#include "tuningtraffic.h"
#include "maps/traffic_map/ue_param/UE_param_form.h"

namespace Ui {
class TuningTrafficForm;
}

class TuningTrafficForm : public QWidget
{
    Q_OBJECT

public:
    explicit TuningTrafficForm(QWidget *parent = 0);
    ~TuningTrafficForm();
    void setParameters();
    void readTemporaryParameters(Tuningtraffic* tuningtraffic);
    void clearCSCombobox();
    void clearPSCombobox();
    void clearAreaCombobox();
    void setUEGroup(Form* form);
    void setCSCombobox();
    void setPSCombobox();
    void setAreaCombobox();
    void initialize(Tuningtraffic* tuningtraffic);
    void pushModel(Tuningtraffic* tuningtraffic);
    void popCSModel(Tuningtraffic* tuningtraffic);
    void popPSModel(Tuningtraffic* tuningtraffic);
    void popArea(Tuningtraffic* tuningtraffic);
    int get_csComboboxCount();
    int get_psComboboxCount();
    bool isinCsCombobox(QString value);
    bool isInPsCombobox(QString value);
    bool isInAreaCombobox(QString value);

private slots:
    void on_bt_save_clicked();
    void on_bt_cancel_clicked();
    void on_bt_restore_clicked();
    void on_cs_combobox_activated(const QString &arg1);
    void on_ps_combobox_activated(const QString & arg1);
    void on_area_combobox_activated();
    void on_chb_area_toggled();
    void on_btn_csMiniSave_clicked();
    void on_btn_psMiniSave_clicked();
    void on_btn_areaMiniSave_clicked();

private:
    Ui::TuningTrafficForm *ui;
    Tuningtraffic *tuningtraffic;
    //Vectors for overall saved model parameters
    QVector<Tuningtraffic::CSParameters* > CSSaveParameters;
    QVector<Tuningtraffic::PSParameters* > PSSaveParameters;
    QVector<Tuningtraffic::Areas* > areaSaveParameters;

    bool saveClicked;
    bool cancelClicked;

    struct TuningTrafficUEModel
    {
        QString cs;
        QString ps;
        QString area;
    } UEGroup;

    void SaveAll();
    void setParametersValidation();
    void copyCSParams(const QVector<Tuningtraffic::CSParameters*>& value);
    void copyPSParams(const QVector<Tuningtraffic::PSParameters*>& value);
    void copyAreaParams(const QVector<Tuningtraffic::Areas*>& value);
    QString saveToString();
};

#endif // TUNINGTRAFFICFORM_H
