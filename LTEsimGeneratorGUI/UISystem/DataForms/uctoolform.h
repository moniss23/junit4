#ifndef UCTOOLFORM_H
#define UCTOOLFORM_H

#include <QWidget>
#include <QMessageBox>

#include "Data/ProjectSettings/uctoolsettings.h"

namespace Ui {
class UCtoolForm;
}

class UCtoolForm : public QWidget
{
    Q_OBJECT

public:
    explicit UCtoolForm(QWidget *parent = 0);
    ~UCtoolForm();

public slots:
    void loadAndOpen(const UCToolSettings &ucToolSettings, const QString &projectName);

private slots:

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_pbReset_clicked();

private:
    void setDefaultParameters();

private:
    Ui::UCtoolForm *ui;
    UCToolSettings ucToolSettings;
    QString projectName;
};

#endif // UCTOOLFORM_H
