#include "managementtemplate.h"
#include "ui_managementtemplate.h"

ManagementTemplate::ManagementTemplate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManagementTemplate)
{
    ui->setupUi(this);
    resize(450,300);
    saveButton = new QPushButton(this);
    saveButton->setText("Save");
    saveButton->setGeometry(QRect(230, 270, 50, 27) );

    cancelButton = new QPushButton(this);
    cancelButton->setText("Cancel");
    cancelButton->setGeometry(QRect(150, 270, 50, 27) );
}

ManagementTemplate::~ManagementTemplate()
{
    delete ui;
    delete saveButton;
    delete cancelButton;
}
