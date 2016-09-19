#ifndef pagingFORM_H
#define pagingFORM_H

#include <QWidget>
#include "Data/ProjectSettings/pagingsettings.h"
namespace Ui {
class PagingForm;
}

class PagingForm : public QWidget
{
    Q_OBJECT

public:
    explicit PagingForm(QWidget *parent = 0);
    ~PagingForm();
    void setDefaultParameters();

signals:
    /**
     * @brief updatePaging signal used to get information from Window and update it in project
     * @param pagingSettings with Paging configuration from Ui
     * @param QString with current project name
     */
    void updatePaging(const PagingSettings &pagingSettings, const QString &projectName);
public slots:
    void loadAndSpawn(const PagingSettings &pagingSettings, const QString &projectName, bool enable);

private slots:
    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/

    void on_RestoreButton_clicked();

    void on_OkButton_clicked();

    void on_CancelButton_clicked();


    void on_checkBox_generate_pagings_stateChanged(int arg1);

private:
    /**
     * @brief setChanges function to override changes from ui to PagingSettings configuration class
     *
     */
    void setChanges();
    /**
     * @brief setPagingParameters function to copy configuration to from pagingSettings gived as argument
     *
     */
    void setPagingParameters(PagingSettings pagingSettings);

    void setReadOnly(bool value);

private:
    Ui::PagingForm *ui;             //< GUI form pointer
    PagingSettings pagingSettings;  //< PagingSettings class to store Paging configuration
    QString projectName;            //< Current project name
};

#endif // pagingFORM_H
