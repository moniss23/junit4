#ifndef PAGGINGRATE_H
#define PAGGINGRATE_H

#include <QWidget>
#include <QString>
#include <QListWidgetItem>

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
    void updatePagingRate(QString &projectName, QStringList generators, QVector<int> rates);
    void restoreDefaults(const QString &projectName);
private slots:
    void loadAndSpawn(const QString &projectName, QStringList generators, QVector<int> rates);
    void enablePagingRate(bool value);
    void restoreDefaults(QStringList names, QVector<int> rates);

    void on_OkButton_clicked();

    void on_listWidget_currentItemChanged(QListWidgetItem *current);

    void on_AcceptButton_clicked();

    void on_CancelButton_clicked();

    void on_RestoreButton_clicked();

private:
    Ui::PagingRate *ui;
    QString projectName;
    QVector<int> rates;
    QStringList generators;
};

#endif // PAGGINGRATE_H
