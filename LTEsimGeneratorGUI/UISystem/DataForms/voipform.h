#ifndef VOIPFORM_H
#define VOIPFORM_H

#include <QDialog>

namespace Ui {
class VoipForm;
}

class VoipForm : public QDialog
{
    Q_OBJECT

public:
    explicit VoipForm(QWidget *parent = 0);
    ~VoipForm();

private:
    Ui::VoipForm *ui;
};

#endif // VOIPFORM_H
