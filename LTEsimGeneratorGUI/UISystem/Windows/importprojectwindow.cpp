#include "importprojectwindow.h"
#include <QFileDialog>

ImportProjectWindow::ImportProjectWindow()
{

}

ImportProjectWindow::~ImportProjectWindow()
{

}

void ImportProjectWindow::getProjectDirectory()
{
    QWidget widget;
    QString fileName = QFileDialog::getOpenFileName(&widget,QString("Open File"),
                                                    QString("/home"),
                                                    QString("Ruby Scripts (*.rb)"));
    emit selectedProjectDirectory(fileName);
}
