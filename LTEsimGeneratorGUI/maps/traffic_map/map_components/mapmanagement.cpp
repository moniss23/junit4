#include "mapmanagement.h"

//-------MapManagement Constructor (either large or standard size of the map)------
MapManagement::MapManagement(bool large /*= false*/ ) : ManagementTemplate()
{
    this->setWindowTitle("Map management");
    setMaximumSize(1100, 950);
    resize(maximumWidth(), maximumHeight());

    initialiseTheView(large);
}

//------Facade used to hide the complexity of a window structure creation-----
void MapManagement::initialiseTheView(bool large)
{
    scrollArea = new QScrollArea(this);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    saveButton->setVisible(false);
    cancelButton->setVisible(false);

    scrollAreaWidgetContents = new MyScrollAreaWidget(large);
    scrollAreaWidgetContents->resize(maximumWidth()-10, maximumHeight()-10);
    scrollArea->setWidget(scrollAreaWidgetContents);
}

//-------Adjust scrollArea features according to size of the window------
void MapManagement::resizeEvent(QResizeEvent *event )
{
    scrollArea->verticalScrollBar()->setPageStep(this->height());
    scrollArea->horizontalScrollBar()->setPageStep(this->width());
    scrollArea->verticalScrollBar()->setRange(0, maximumHeight() - this->height());
    scrollArea->horizontalScrollBar()->setRange(0, maximumWidth() - this->width());
    scrollArea->resize(this->width(), this->height());
}

MapManagement::~MapManagement()
{
    delete scrollArea;
}
