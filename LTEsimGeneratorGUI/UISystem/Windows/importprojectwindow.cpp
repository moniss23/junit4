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
    QString ImportDir = QFileDialog::getExistingDirectory(NULL,
                                                          ("Find project directory"),
                                                          "/",
                                                           QFileDialog::ShowDirsOnly);

    emit selectedProjectDirectory(ImportDir);
}
