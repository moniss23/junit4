#ifndef UE_PARAM_FORM_H
#define UE_PARAM_FORM_H

#include <QWidget>
#include <QVector>
#include <QLineEdit>
#include <QComboBox>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    QLineEdit* area1;
    QLineEdit* area2;
    QComboBox* pointerPS;
    QWidget* pointerWinTitle;
    QWidget* pointerWinTitle_large;
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
    Ui::Form *ui;
    int tempPairsCount;
    static int uePairsCount;
    bool accept;
    void countUEPairs();
    bool accepted;
};

#endif // UE_PARAM_FORM_H
