#ifndef MMEFORM_H
#define MMEFORM_H

#include <QWidget>
#include <QMessageBox>
#include <QString>


#include "Data/ProjectSettings/mmesettings.h"

namespace Ui {
class MmeForm;
}

class MmeForm : public QWidget
{
    Q_OBJECT

public:
    explicit MmeForm(QWidget *parent = 0);
    ~MmeForm();

signals:
    void updateMme(const MmeSettings &mmeSettings, const QString &porjectName);
public slots:
    void loadAndSpawn(const MmeSettings &mmeSettings, const QString &projectName);
private slots:

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_pbReset_clicked();

private:

    void setChanges();
    void setParameters(MmeSettings mmeSettings);
    void setDefaultParameters();

private:
    Ui::MmeForm *ui;
    MmeSettings mmeSettings;
    QMessageBox msg;
    QString projectName;
};

#endif // MMEFORM_H
