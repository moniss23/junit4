#ifndef TUNINGTRAFFICMANAGER_H
#define TUNINGTRAFFICMANAGER_H

#include <QWidget>
#include "tuningTrafficData.h"
#include <UISystem/DataForms/UE_param_form.h>

namespace Ui {
class TuningTrafficForm;
}

class TuningTrafficManager : public QWidget
{
    Q_OBJECT

public:
    explicit TuningTrafficManager(QWidget *parent = 0);
    ~TuningTrafficManager();
    void setParameters();
    void readTemporaryParameters(TuningTrafficData* tuningTrafficData);
    void clearCSCombobox();
    void clearPSCombobox();
    void clearAreaCombobox();
    void setUEGroup(Form* form);
    void setCSCombobox();
    void setPSCombobox();
    void setAreaCombobox();
    void initialize(TuningTrafficData* tuningTrafficData);
    void pushModel(TuningTrafficData* tuningTrafficData);
    void popCSModel(TuningTrafficData* tuningTrafficData);
    void popPSModel(TuningTrafficData* tuningTrafficData);
    void popArea(TuningTrafficData *tuningTrafficData);
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

public slots:
    void open(const QString &projectName, const QString &trafficName);

private:
    Ui::TuningTrafficForm *ui;
    TuningTrafficData *tuningTrafficData;
    //Vectors for overall saved model parameters
    QVector<TuningTrafficData::CSParameters* > CSSaveParameters;
    QVector<TuningTrafficData::PSParameters* > PSSaveParameters;
    QVector<TuningTrafficData::Areas* > areaSaveParameters;

    bool saveClicked;
    bool cancelClicked;

    QString projectName;
    QString trafficFileName;

    struct TuningTrafficUEModel
    {
        QString cs;
        QString ps;
        QString area;
    } UEGroup;

    void SaveAll();
    void setParametersValidation();
    void copyCSParams(const QVector<TuningTrafficData::CSParameters*>& value);
    void copyPSParams(const QVector<TuningTrafficData::PSParameters*>& value);
    void copyAreaParams(const QVector<TuningTrafficData::Areas*>& value);
    QString saveToString();
};

#endif // TUNINGTRAFFICMANAGER_H
