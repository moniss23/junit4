#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "Data/project.h"
#include "UISystem/Widgets/uerepresentation.h"
#include "UISystem/Widgets/cellrepresentation.h"
#include "UISystem/Widgets/handoverrepresentation.h"

/**
 * @brief The MapView class is our map representation
 */
class MapView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MapView(const Project& project, QWidget *parent = 0, QString trafficName = "");

    /***********************************************
     *  WIDGET PUBLIC API
     ***********************************************/
public slots:
    /**
     * @brief spawnWindow_MapRange is used to spawn MapRange window
     */
    void spawnWindow_MapRange();
    /**
     * @brief spawnWindow_HandoverParams is used to show handover parameters
     * @param hoRep is pointer to current clicked handover representation
     * @param ho is current clicked handover data
     */
    void spawnWindow_HandoverParams(HandoverRepresentation* hoRep, const Handover& ho);
    /**
     * @brief spawnWindow_CellParams is used to show cell and center parameters
     * @param cellRep is pointer to current clicked cell representation
     * @param cellInfo is current clicked cellInfo data
     */
    void spawnWindow_CellParams(CellRepresentation* cellRep, const QPair<Cell,Center>& cellInfo);
    /**
     * @brief updateUe is used to update ue data
     * @param ueRep is pointer to current clicked ue representation
     * @param ueData is current clicked ue data
     */
    void updateUe(UeRepresentation* ueRep, const UEData &ueData);
    /**
     * @brief spawnWindow_UeParams is used to show ue parameters window
     * @param ueRepresentation is pointer to double-clicked ue representation
     * @param ueDataName is current double-clicked ue name
     */
    void spawnWindow_UeParams(UeRepresentation* ueRepresentation, const QString &ueDataName);

signals:
    /**
     * @brief spawnWindow_mapRange signal is used to spawn MapRange window
     */
    void spawnWindow_mapRange();
    /**
     * @brief spawnWindow_MapView_HandoverParams is used to show handover parameters
     * @param hoRep is pointer to current clicked handover representation
     * @param ho is current clicked ho data
     */
    void spawnWindow_MapView_HandoverParams(HandoverRepresentation* hoRep, const Handover& ho);
    /**
     * @brief spawnWindow_MapView_CellParams is used to show cellInfo parameters
     * @param cellRep is pointer to current clicked cell representation
     * @param cellInfo is current clicked cellInfo data
     */
    void spawnWindow_MapView_CellParams(CellRepresentation* cellRep, const QPair<Cell,Center>& cellInfo);
    /**
     * @brief updateUe_MapView is used to update ue data
     * @param projectName is current project name
     * @param trafficName is current trafficfile name
     * @param ueData is ue data to be saved
     */
    void updateUe_MapView(UeRepresentation*, const QString &projectName, const QString &trafficName, const UEData &ueData);
    /**
     * @brief spawnWindow_ueParams is used to spawn ue parameters window
     * @param ueRepresentation is pointer to current double-clicked ue representation
     * @param ueDataName is current double-clicked ue data
     */
    void spawnWindow_ueParams(UeRepresentation* ueRepresentation, const QString &ueDataName);
    /**
     * @brief addUeToScene is used to add ue representation to scene
     * @param ueData is the data of the new ue object
     * @param ueDataIndex is index of ue pair
     */
    void addUeToScene(UEData &ueData, int ueDataIndex);
    /**
     * @brief addCelltoScene is used to add cell representation to scene
     * @param cell is the data of the new cell object
     */
    void addCelltoScene (Cell &cell);
    /**
     * @brief addHandoverToScene is used to add handover representation to scene
     * @param handover is the data of the new handover object
     */
    void addHandoverToScene (Handover &handover);

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
public:
    /**
     * @brief printNewMap is used to print map
     */
    void printNewMap();
    void resizeEvent(QResizeEvent* event);
    /**
     * @brief generateColorForUe is used to generate unique ue colors
     * @param ueDataIndex is index of ue
     * @return QColor that is unique
     */
    QColor generateColorForUe(int ueDataIndex);

private:
    /**
     * @brief drawMapLines is used to draw grid lines
     */
    void drawMapLines();
    /**
     * @brief drawAxisAndButtons is used to draw x,y axis and add buttons on them
     */
    void drawAxisAndButtons();
    /**
     * @brief drawUeRepresentations is used to draw ue representations
     */
    void drawUeRepresentations();
    /**
     * @brief drawCellRepresentations is used to draw cell representations
     */
    void drawCellRepresentations();
    /**
     * @brief drawHandoverRepresentations is used to draw handover representations
     */
    void drawHandoverRepresentations();


public:
    QGraphicsScene *scene;                              ///< pointer to scene

private:
    Project project;                                    ///< local copy of project
    QString trafficName;                                ///< current traffic file name

    QLineF x_AxisLine, y_AxisLine;                      ///< x,y axis lines
    QPen solidPen, solid2, dotPen;                      ///< Pens
    QPointF gridLineStart, gridLineEnd, textPoint;      ///< grid lines start, end point, text start point
};

#endif // MAPVIEW_H
