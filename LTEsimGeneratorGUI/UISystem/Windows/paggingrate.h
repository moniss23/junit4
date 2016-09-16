#ifndef PAGGINGRATE_H
#define PAGGINGRATE_H

#include <QWidget>
#include <QString>

namespace Ui {
class PaggingRate;
}

class PaggingRate : public QWidget
{
    Q_OBJECT

public:
    explicit PaggingRate(QWidget *parent = 0);
    ~PaggingRate();
signals:
    void updatePaggingRate(QString projectName, int rate);
private slots:
    void loadAndSpawn(const QString &projectName,int &rate);

    void on_OkButton_clicked();

private:
    Ui::PaggingRate *ui;
    QString projectName;
    int rate;
};

#endif // PAGGINGRATE_H
