#ifndef UBSIMFORM_H
#define UBSIMFORM_H

#include <QWidget>
#include <QString>

#include "Data/ProjectSettings/ubsimsettings.h"

namespace Ui {
class UBsimForm;
}

class UBsimForm : public QWidget
{
    Q_OBJECT

public:
    explicit UBsimForm(QWidget *parent = 0);
    ~UBsimForm();

public slots:

    void loadAndOpen(const UBSimSettings &ubSimSettings, const QString &projectName);

signals:

    void updateUBSimSettings(const UBSimSettings &ubSimSettings, const QString &projectName);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_pbReset_clicked();

private:

    void setParameters();
    void getParameters();

private:
    Ui::UBsimForm *ui;
    UBSimSettings ubSimSettings;
    QString projectName;
};

#endif // UBSIMFORM_H
