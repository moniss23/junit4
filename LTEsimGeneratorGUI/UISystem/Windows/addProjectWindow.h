#ifndef ADDPROJECTWINDOW_H
#define ADDPROJECTWINDOW_H

#include <QDialog>
#include <QRegExpValidator>
#include <QRegExp>

namespace Ui {
class AddProjectWindow;
}

/**
 * @brief The AddProjectWindow class is responsible for drawing UI form
 *        for adding new project to application.
 */
class AddProjectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddProjectWindow(QWidget *parent = 0);
    ~AddProjectWindow();


    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
public slots:
    void loadAndOpen();

signals:
    /**
     * @brief createNewProject signal used to notify application of new project request
     * @param projectName QString with new project name
     * @param directory QString with new project directory
     * @param isCustomLocation flag that represent custom or default location, true if custom
     */
    void createNewProject(const QString& projectName, const QString& directory, bool isCustomLocation);


    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_browseDirectoryButton_clicked();
    void on_defaultLocationRadioButton_toggled(bool checked);


    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
    Ui::AddProjectWindow *ui;                ///< GUI form pointer
    const QString         fileNamePattern = "^[\\w\\s-]{1,50}$"; ///< Regular expression rules
    QRegExp               fileNameRegExp;    ///< Regular expression used in name validator
    QRegExpValidator      fileNameValidator; ///< Validator used to check project names
};

#endif // ADDPROJECTWINDOW_H
