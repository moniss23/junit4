#ifndef IMPORTPROJECTWINDOW_H
#define IMPORTPROJECTWINDOW_H

#include <QObject>

class ImportProjectWindow : public QObject
{
    Q_OBJECT

public:
    ImportProjectWindow();
    virtual ~ImportProjectWindow();

signals:
    void selectedProjectDirectory(const QString &ProjectDirectory);

public slots:
    void getProjectDirectory();
};

#endif // IMPORTPROJECTWINDOW_H
