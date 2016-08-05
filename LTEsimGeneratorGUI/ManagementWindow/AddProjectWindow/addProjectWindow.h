#ifndef ADDPROJECTWINDOW_H
#define ADDPROJECTWINDOW_H

#include <QDialog>
#include <QString>
#include <QObject>
#include <QRegExpValidator>
#include <QRegExp>

namespace Ui {
class AddProjectWindow;
}

class AddProjectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddProjectWindow(QWidget *parent = 0);
    ~AddProjectWindow();

signals:

    void createNewProject(const QString& projectName, const QString& directory);

public slots:
    void showErrorWindow(const QString& errorMessage);
    void closeWindow();

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_browseDirectoryButton_clicked();

    void on_defaultLocationRadioButton_toggled(bool checked);

private:
    const QString fileNamePattern = "^[\\w\\s-]{1,50}$";
    Ui::AddProjectWindow *ui;
    QRegExp fileNameRegExp;
    QRegExpValidator fileNameValidator;
};

#endif // ADDPROJECTWINDOW_H
