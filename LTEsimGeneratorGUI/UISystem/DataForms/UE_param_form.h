#ifndef UE_PARAM_FORM_H
#define UE_PARAM_FORM_H

#include <QWidget>
class QLineEdit;
class QComboBox;

namespace Ui {
class Form;
}

class Form : public QWidget
        //TODO: Refactor that class, name, functions, members with similar name, etc
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    QLineEdit* area1;
    QLineEdit* area2;
    QComboBox* pointerPS;
    QWidget* pointerWinTitle;
    QComboBox* combo;

    QString get_currentCSBehavior();
    QString get_currentPSBehavior();

    static int getUEPairs();
    static void resetUEPairsCount();
    void resetAccept();
    QString get_currentArea();
    void set_currentArea(QString value);

    bool is_Accepted();

    QString getWindowTitle();

    void getAllValues();
    QComboBox setAllValues();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    void countUEPairs();

private:
    Ui::Form  *ui;
    int        tempPairsCount;
    static int uePairsCount;
    bool       accept;
    bool       accepted;
};

#endif // UE_PARAM_FORM_H
