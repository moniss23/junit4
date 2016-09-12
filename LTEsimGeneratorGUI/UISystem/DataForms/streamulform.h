#ifndef STREAMULFORM_H
#define STREAMULFORM_H

#include <QDialog>

namespace Ui {
class StreamUlForm;
}

class StreamUlForm : public QDialog
{
    Q_OBJECT

public:
    explicit StreamUlForm(QWidget *parent = 0);
    ~StreamUlForm();

private:
    Ui::StreamUlForm *ui;
};

#endif // STREAMULFORM_H
