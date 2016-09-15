#ifndef MAPRANGEFORM_H
#define MAPRANGEFORM_H

#include <QWidget>
#include "Data/ProjectSettings/maprange.h"
#include "ui_maprangeform.h"

namespace Ui {
class MapRangeForm;
}

class MapRangeForm : public QWidget
{
    Q_OBJECT

public:
    explicit MapRangeForm(QWidget *parent = 0);
    ~MapRangeForm();

signals:
    /**
     * @brief updateMapRange signal used to get information from Window and update it in project
     * @param MapRange with MapRange configuration from Ui
     * @param QString with current project name
     */
    void updateMapRange(const MapRange &mapRange, const QString &projectName);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();


public slots:
    /**
     * @brief loadAndSpawn slot is called by spawnWindow_MapRange in MapWindow
     * copy MapRange configuration class from project and spawn MapRange window
     *
     */
    void loadAndSpawn(const MapRange &mapRange,const QString &projectName);


private:
    /**
     * @brief updateUi function to update ui data from Maprage configuration class
     *
     */
    void updateUi();

    /**
     * @brief setMapRangeParameters method to copy configuration to from MapRange gived as argument
     *
     */
    void setMapRangeParameters(MapRange mapRange);

    /**
     * @brief setMapRangeChanges method to override changes from ui to Map Range configuration class
     *
     */
    void setMapRangeChanges();

private:
    Ui::MapRangeForm *ui;           //< GUI form pointer
    MapRange mapRange;              //< MapRange class to store MapRange configuration
    QString projectName;            //< Current project name
};

#endif // MAPRANGEFORM_H
