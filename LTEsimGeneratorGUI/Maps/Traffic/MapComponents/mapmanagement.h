#ifndef MAPMANAGEMENT_H
#define MAPMANAGEMENT_H

#include <QScrollArea>
#include <QScrollBar>
#include <Maps/Traffic/ManagementTemplate/managementtemplate.h>
#include <Maps/Traffic/MapComponents/myscrollareawidget.h>


class MapManagement : public ManagementTemplate
{
    Q_OBJECT
public:
    explicit MapManagement( bool large = 0 );
    ~MapManagement();
    void initialiseTheView( bool large );
    void resizeEvent(QResizeEvent* event)Q_DECL_OVERRIDE;

private:
    QScrollArea *scrollArea;
    MyScrollAreaWidget *scrollAreaWidgetContents;
};
#endif // MAPMANAGEMENT_H