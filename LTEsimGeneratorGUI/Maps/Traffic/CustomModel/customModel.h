#ifndef customModel_H
#define customModel_H

#include <QMainWindow>

namespace Ui {
class newCustomModel;
}

class customModel : public QMainWindow
{
    Q_OBJECT

public:
    explicit customModel(QWidget *parent = 0);
    ~customModel();

    void set_custom_name(QString name);

private:
    Ui::newCustomModel *ui;
    QString name;
};

#endif // customModel_H
