#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QDialog>
#include <QString>
#include <AppSettings/appsettings.h>

namespace Ui {
class FileDialog;
}

class FileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileDialog(QWidget *parent = 0);
    ~FileDialog();

    void clearInputArea();

    void setDefaultDir(QString dir);

    void setAppSettings(AppSettings *value);

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_browseDirectoryButton_clicked();

    void on_defaultLocationRadioButton_toggled(bool checked);

private:
    Ui::FileDialog *ui;
    AppSettings* appSettings;
};

#endif // FILEDIALOG_H
