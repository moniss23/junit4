#ifndef PAGGINGRATE_H
#define PAGGINGRATE_H

#include <QWidget>
#include <QString>

namespace Ui {
class PagingRate;
}

class PagingRate : public QWidget
{
    Q_OBJECT

public:
    explicit PagingRate(QWidget *parent = 0);
    ~PagingRate();
signals:
    void updatePagingRate(QString projectName, int rate);
private slots:
    void loadAndSpawn(const QString &projectName,int &rate);
    void enablePagingRate(bool value);
    void on_OkButton_clicked();

private:
    Ui::PagingRate *ui;
    QString projectName;
    int rate;
};

#endif // PAGGINGRATE_H
