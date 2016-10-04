#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>

namespace Ui {
class HelpDialog;
}
/**
 * @brief The HelpDialog class is responsible for showing help Window
 */
class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDialog(QWidget *parent = 0);
    ~HelpDialog();

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
    Ui::HelpDialog *ui;         ///< Pointer to GUI FORM
};

#endif // HELPDIALOG_H
