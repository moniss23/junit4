#include "renamedialog.h"
#include "ui_renamedialog.h"


RenameDialog::RenameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenameDialog),
    fileNameRegExp(fileNamePattern),
    fileNameValidator(fileNameRegExp)
{
    ui->setupUi(this);
    this->setModal(Qt::WindowModal);
    ui->fileNameInput->setValidator(&fileNameValidator);
    fileNameValidator.setParent(ui->fileNameInput);
}

RenameDialog::~RenameDialog()
{
    delete ui;
}

void RenameDialog::on_buttonBox_accepted()
{
    QString newFilename = ui->fileNameInput->text();
    QString oldFilename = ui->filenameLabel->text();

    if(!newFilename.endsWith(getRbFileExt())) {
        newFilename.append(getRbFileExt());
    }

    emit changedFilename(newFilename, oldFilename, currentProjectName);
}

QString RenameDialog::getRbFileExt() const
{
    return rbFileExt;
}

void RenameDialog::on_buttonBox_rejected()
{
    this->close();
}

void RenameDialog::initWindow(const QString& filename, const QString &projectName)
{
    currentProjectName = projectName;
    ui->filenameLabel->setText(filename);
    ui->fileNameInput->clear();
    ui->fileNameInput->setPlaceholderText(filename);
    ui->fileNameInput->setFocus();
    this->show();
}

void RenameDialog::accept() {
    this->on_buttonBox_accepted();
}

