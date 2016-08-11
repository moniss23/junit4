#ifndef RENAMEDIALOG_H
#define RENAMEDIALOG_H

#include <QDialog>
#include <QRegExp>
#include <QRegExpValidator>

#include "Data/project.h"

/**
 * It's a UI which asks user for new name for RB file
 */

namespace Ui {
class RenameDialog;
}

class RenameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RenameDialog(QWidget *parent = 0);
    ~RenameDialog();

    virtual void accept();

    QString getRbFileExt() const;

signals:
    void changedFilename(const QString& newFilename, const QString& oldFilename);

public slots:
    void initWindow(const QString &filename);

private slots:
    void on_buttonBox_rejected();

private:
    void on_buttonBox_accepted();

private:
    Ui::RenameDialog *ui;

    const QString rbFileExt = ".rb"; ///< Extension for rb files.

    const QString         fileNamePattern = "^[\\w\\s-.]{1,50}$"; ///< Regular expression rules
    QRegExp               fileNameRegExp;    ///< Regular expression used in name validator
    QRegExpValidator      fileNameValidator; ///< Validator used to check project names
};

#endif // RENAMEDIALOG_H
