#ifndef SYNCEDPINGFORM_H
#define SYNCEDPINGFORM_H

#include <QDialog>

namespace Ui {
class SyncedPingForm;
}

class SyncedPingForm : public QDialog
{
    Q_OBJECT

public:
    explicit SyncedPingForm(QWidget *parent = 0);
    ~SyncedPingForm();

private:
    Ui::SyncedPingForm *ui;
};

#endif // SYNCEDPINGFORM_H

