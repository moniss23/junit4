#ifndef UEPARAMETERSMANAGER_H
#define UEPARAMETERSMANAGER_H

#include <QWidget>

namespace Ui {
class UeParametersWindow;
}

class UeParametersWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UeParametersWindow(QWidget *parent = 0);
    ~UeParametersWindow();

private slots:
    void on_pairNameLineEdit_editingFinished();

    void on_amountOfPairsSpinBox_editingFinished();

    void on_frstMobilityModelComboBox_currentIndexChanged(int index);

    void on_scndMobilityModelComboBox_currentIndexChanged(int index);

    void on_frstCsModelComboBox_currentIndexChanged(int index);

    void on_scndCsModelComboBox_currentIndexChanged(int index);

    void on_frstPsModelComboBox_currentIndexChanged(int index);

    void on_scndPsModelComboBox_currentIndexChanged(int index);

    void on_frstUeTypeComboBox_currentIndexChanged(int index);

    void on_scndUeTypeComboBox_currentIndexChanged(int index);

private:
    Ui::UeParametersWindow *ui;
};

#endif // UEPARAMETERSMANAGER_H
