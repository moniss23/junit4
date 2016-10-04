#include "importprojectwindow.h"
#include <QFileDialog>

ImportProjectWindow::ImportProjectWindow()
{

}

ImportProjectWindow::~ImportProjectWindow()
{

}

void ImportProjectWindow::spawnWindowFileDialog()
{
    QWidget widget;
    QString fileName = QFileDialog::getOpenFileName(&widget,QString("Open File"),
                                                    QString("/home"),
                                                    QString("Ruby Scripts (*.rb)"));
    if (!fileName.isEmpty()){
        emit importProject(fileName);
    }
}
