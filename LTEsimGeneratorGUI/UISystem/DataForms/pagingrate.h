#ifndef PAGGINGRATE_H
#define PAGGINGRATE_H

#include <QWidget>
#include <QString>
#include <QListWidgetItem>

namespace Ui {
class PagingRate;
}
/**
 * @brief The PagingRate class is responsible for showing and managing PagingSettings.rate and PagingSettings.name
 */
class PagingRate : public QWidget
{
    Q_OBJECT

public:
    explicit PagingRate(QWidget *parent = 0);
    ~PagingRate();

    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
signals:
    /**
     * @brief updatePagingRate is used to save pagingRate in trafficFile
     * @param projectName is current project name
     * @param generators QStringList with generators names
     * @param rates QVector of rates
     */
    void updatePagingRate(QString &projectName, QStringList generators, QVector<int> rates);
    /**
     * @brief restoreDefaults signal is used to replace local PagingSettings data with global PagingSettings data
     * @param projectName is current project name
     */
    void restoreDefaults(const QString &projectName);

public slots:
    /**
     * @brief loadAndSpawn is used to load data and show window
     * @param projectName is current project name
     * @param generators QStringList with generators names
     * @param rates QVector of rates
     */
    void loadAndSpawn(const QString &projectName, QStringList generators, QVector<int> rates);
    /**
     * @brief enablePagingRate is used to set enabled ui items.
     * @param value is flag that represent if ui should be enabled, true = enabled
     */
    void enablePagingRate(bool value);
    /**
     * @brief restoreDefaults slot is used to replace local PagingSettings data with global PagingSettings data
     * @param names QStringList with generators names
     * @param rates QVector of rates
     */
    void restoreDefaults(QStringList names, QVector<int> rates);

    /***********************************************
     *  BINDINGS TO UI BUTTONS                     *
     ***********************************************/
private slots:
    void on_OkButton_clicked();
    void on_listWidget_currentItemChanged(QListWidgetItem *current);
    void on_AcceptButton_clicked();
    void on_CancelButton_clicked();
    void on_RestoreButton_clicked();

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
    Ui::PagingRate *ui;             ///< Pointer to GUI FORM
    QString projectName;            ///< Current project name
    QVector<int> rates;             ///< Container of rates
    QStringList generators;         ///< Generator names List
};

#endif // PAGGINGRATE_H
