#ifndef IMPORTPROJECTWINDOW_H
#define IMPORTPROJECTWINDOW_H

#include <QObject>

/**
 * @brief The ImportProjectWindow class is responsible for showing FileDialog and importing project
 */
class ImportProjectWindow : public QObject
{
    Q_OBJECT

public:
    ImportProjectWindow();
    virtual ~ImportProjectWindow();

    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
signals:
    /**
     * @brief importProject is used to import project from .rb script
     * @param ProjectDirectory is .rb script directory
     */
    void importProject(const QString &ProjectDirectory);

public slots:
    /**
     * @brief spawnWindowFileDialog is used to spawn window FileDialog
     */
    void spawnWindowFileDialog();
};

#endif // IMPORTPROJECTWINDOW_H
