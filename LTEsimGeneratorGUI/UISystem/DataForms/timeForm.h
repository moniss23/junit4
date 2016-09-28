#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <QDialog>

#include "Data/TrafficSettings/timeData.h"

namespace Ui {
class TimeForm;
}

/**
 * @brief The TimeForm class is responsible for showing and managing TimeData data.
 */

class TimeForm : public QDialog
{
    Q_OBJECT

public:
    explicit TimeForm(QWidget *parent = 0);
    ~TimeForm();

    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
public slots:
    /**
     * @brief loadAndOpen used to load data and show window
     * @param projectName name of current project
     * @param trafficName name of current traffic
     * @param timeData data that will be changed
     */
    void loadAndOpen(const QString& projectName, const QString& trafficName, const TimeData& timeData);

signals:
    /**
     * @brief saveTimeData is used to save Time data in traffic
     * @param projectName name of current project
     * @param trafficName name of current traffic
     * @param timeData data that will be changed
     */
    void saveTimeData(const QString& projectName, const QString& trafficName, const TimeData& timeData);

    /***********************************************
     *  BINDINGS TO UI BUTTONS                     *
     ***********************************************/
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_btn_restore_clicked();
    void on_gb_attdetRate1_toggled();
    void on_gb_attdetRate2_toggled();
    void on_txt_attachRate1_textChanged(QString);
    void on_txt_attachRate2_textChanged(QString);
    void on_tab1_printStatisticsWithRate_toggled(bool checked);
    void on_tab2_statisticsWithRate_toggled(bool checked);

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
    /**
     * @brief refreshUi is used when window needs to refresh state
     */
    void refreshUi();
    /**
     * @brief setParametersValidation is used to set data validators in Time UI
     */
    void setParametersValidation();
    /**
     * @brief getParameters is used to set Time data from ui fields
     */
    void getParameters();

private:
    Ui::TimeForm *ui;                   ///< GUI form pointer

    TimeData timeData;                  ///< Time data
    QString projectName;                ///< Current project name
    QString trafficName;                ///< Current traffic file name
};

#endif // TIMEMANAGER_H
