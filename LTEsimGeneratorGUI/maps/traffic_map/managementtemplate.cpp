#include "managementtemplate.h"
#include "ui_managementtemplate.h"

QString RemoveMeLater;

ManagementTemplate::ManagementTemplate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManagementTemplate)
{
    ui->setupUi(this);
    resize(450,300);
    m_saveButton = new QPushButton(this);
    m_saveButton->setText("Save");
    m_saveButton->setGeometry(QRect(230, 270, 50, 27));

    m_cancelButton = new QPushButton(this);
    m_cancelButton->setText("Cancel");
    m_cancelButton->setGeometry(QRect(150, 270, 50, 27));
}

ManagementTemplate::~ManagementTemplate()
{
    delete ui;
    delete m_saveButton;
    delete m_cancelButton;
}
