#ifndef MAPRANGEFORM_H
#define MAPRANGEFORM_H

#include <QWidget>
#include "maprange.h"
namespace Ui {
class MapRangeForm;
}

class MapRangeForm : public QWidget
{
    Q_OBJECT

public:
    explicit MapRangeForm(QWidget *parent = 0);
    ~MapRangeForm();
    void setParameters(MapRange *mapRange, bool destination);
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_tet_northBoundMap_valueChanged(double arg1);

    void on_tet_eastBoundMap_valueChanged(double arg1);

    void on_tet_southBoundMap_valueChanged(double arg1);

    void on_tet_westBoundMap_valueChanged(double arg1);

private:
    Ui::MapRangeForm *ui;
    MapRange *mapRange;
    bool flagConfirmNewValue;


};

#endif // MAPRANGEFORM_H
