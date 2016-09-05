#ifndef NEWMAPWINDOW_H
#define NEWMAPWINDOW_H

#include <QMainWindow>
#include "UISystem/Widgets/mapview.h"
#include <QHBoxLayout>

namespace Ui {
class NewMapWindow;
}

class NewMapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewMapWindow(QWidget *parent = 0);
    ~NewMapWindow();

public slots:
    void loadAndOpen(const Project &project);
    void spawnWindow_MapView_handoverParams(HandoverRepresentation*, const Handover&);

signals:
    void spawnWindow_Mme(const QString& projectName);
    void spawnWindow_Sgw(const QString& projectName);
    void spawnWindow_Ipex(const QString& projectName);
    void spawnWindow_UBSim(const QString& projectName);
    void spawnWindow_ucTool(const QString &projectName);
    void spawnWindow_ChannelModel(const QString& projectName);

    void updateUEsimulated(const QString& projectName, const bool& checked);
    void updateCoreNetwork(const QString& projectName, const bool& checked);

    void updateHandover(const Handover &handover, const QString &projectName);

private slots:
    void on_mmeButton_pressed();
    void on_sgwButton_pressed();
    void on_ipexButton_pressed();
    void on_ubSimButton_pressed();
    void on_ucToolButton_pressed();
    void on_channelModelsButton_pressed();
    void on_setHandoverParamsBtn_clicked();
    void on_ueCheckbox_toggled(bool checked);
    void on_coreNetworkCheckbox_toggled(bool checked);

private:
    Ui::NewMapWindow *ui;
    QHBoxLayout *hBoxLayout;
    QVBoxLayout *vBoxLayout;
    MapView *mapView;
    Project project;

    HandoverRepresentation* clickedHandover;
};

#endif // NEWMAPWINDOW_H
