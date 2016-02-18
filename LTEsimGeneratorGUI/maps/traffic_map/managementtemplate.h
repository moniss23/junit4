#ifndef MANAGEMENTTEMPLATE_H
#define MANAGEMENTTEMPLATE_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class ManagementTemplate;
}

class ManagementTemplate : public QDialog
{
    Q_OBJECT

public:
    explicit ManagementTemplate(QWidget *parent = 0);

protected:
    QPushButton *m_saveButton, *m_cancelButton;
public:
    Ui::ManagementTemplate *ui;
};

#endif // MANAGEMENTTEMPLATE_H
