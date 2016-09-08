#include "ueparametersmanager.h"
#include "ui_ueparameterswindow.h"

UeParametersWindow::UeParametersWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UeParametersWindow)
{
    ui->setupUi(this);
}

UeParametersWindow::~UeParametersWindow()
{
    delete ui;
}

void UeParametersWindow::on_pairNameLineEdit_editingFinished()
{

}

void UeParametersWindow::on_amountOfPairsSpinBox_editingFinished()
{

}

void UeParametersWindow::on_frstMobilityModelComboBox_currentIndexChanged(int index)
{

}

void UeParametersWindow::on_scndMobilityModelComboBox_currentIndexChanged(int index)
{

}

void UeParametersWindow::on_frstCsModelComboBox_currentIndexChanged(int index)
{

}

void UeParametersWindow::on_scndCsModelComboBox_currentIndexChanged(int index)
{

}

void UeParametersWindow::on_frstPsModelComboBox_currentIndexChanged(int index)
{

}

void UeParametersWindow::on_scndPsModelComboBox_currentIndexChanged(int index)
{

}

void UeParametersWindow::on_frstUeTypeComboBox_currentIndexChanged(int index)
{

}

void UeParametersWindow::on_scndUeTypeComboBox_currentIndexChanged(int index)
{

}
