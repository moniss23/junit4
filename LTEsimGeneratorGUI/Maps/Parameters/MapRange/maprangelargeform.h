#ifndef MAPRANGELARGEFORM_H
#define MAPRANGELARGEFORM_H
#include <Maps/Parameters/MapRange/maprange.h>
#include <QWidget>

namespace Ui {
class MapRangeLargeForm;
}

class MapRangeLargeForm : public QWidget
{
    Q_OBJECT

public:
    explicit MapRangeLargeForm(QWidget *parent = 0);
    ~MapRangeLargeForm();
    void setParameters(MapRange *mapRange, bool destination);
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_tet_northBoundMap_valueChanged(double arg1);
    void on_tet_eastBoundMap_valueChanged(double arg1);
    void on_tet_southBoundMap_valueChanged(double arg1);
    void on_tet_westBoundMap_valueChanged(double arg1);

private:
    Ui::MapRangeLargeForm *ui;
    MapRange *mapRange;
    bool flagConfirmNewValue;
};

#endif // MAPRANGELARGEFORM_H
