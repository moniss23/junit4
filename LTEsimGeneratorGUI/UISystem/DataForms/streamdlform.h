#ifndef STREAMDLFORM_H
#define STREAMDLFORM_H

#include <QDialog>

namespace Ui {
class StreamDlForm;
}

class StreamDlForm : public QDialog
{
    Q_OBJECT

public:
    explicit StreamDlForm(QWidget *parent = 0);
    ~StreamDlForm();

private:
    Ui::StreamDlForm *ui;
};

#endif // STREAMDLFORM_H
