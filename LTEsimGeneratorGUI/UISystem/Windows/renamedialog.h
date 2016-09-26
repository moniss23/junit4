#ifndef RENAMEDIALOG_H
#define RENAMEDIALOG_H

#include <QDialog>
#include <QRegExp>
#include <QRegExpValidator>

#include "Data/project.h"

namespace Ui {
class RenameDialog;
}

/**
 * @brief The RenameDialog class is an UI which asks user for new name for RB file
 */
class RenameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RenameDialog(QWidget *parent = 0);
    ~RenameDialog();

    virtual void accept();
    QString getRbFileExt() const;

    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
signals:
    /**
     * @brief changedFilename is emited when new filename for script has been chosen
     * @param newFilename new filename
     * @param oldFilename old filename
     * @param projectName name of a project that holds modified file
     */
    void changedFilename(const QString& newFilename, const QString& oldFilename, const QString& projectName);

public slots:
    /**
     * @brief initWindow initializes RenameDialog with current filename and project's name
     * @param filename current (old) filename
     * @param projectName name of a project that holds file to be modified
     */
    void initWindow(const QString &filename, const QString& projectName);

    /***********************************************
     *  BINDINGS TO UI BUTTONS                     *
     ***********************************************/
private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
    Ui::RenameDialog    *ui;                                    ///< RenameDialog's UI
    QString             currentProjectName;                     ///< Current project name

    const QString       rbFileExt = ".rb";                      ///< Extension for Ruby files.

    const QString       fileNamePattern = "^[\\w\\s-.]{1,50}$"; ///< Regular expression rules
    QRegExp             fileNameRegExp;                         ///< RegExp used in name validator
    QRegExpValidator    fileNameValidator;                      ///< Validator used to check filenames
};

#endif // RENAMEDIALOG_H
