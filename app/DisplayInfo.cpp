#include "mainwindow.h"
#include <QDialog>
#include "DisplayInfo.h"
#include "ui_DisplayInfo.h"
#include "Team.h"
#include "Stadium.h"
#include "Souvenir.h"

DisplayInfo::DisplayInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayInfo)
{
    ui->setupUi(this);
}


// Intializes viewer table to blank
void InitializeViewTable (QTableWidget* table, const int &cols, const QStringList &headers)
{

}

// Populates viewer table with information
void PopulateViewTable (QTableWidget* table, QVector<Team*> teamList)
{

}

DisplayInfo::~DisplayInfo()
{
    delete ui;
}

///This function will create a pointer to the MainWindow UI. The DisplayInfo
/// page will be hidden before showing the Main Window
void DisplayInfo::on_Home_PushButton_clicked()
{
    MainWindow *mainWindow;
    mainWindow = new MainWindow(this);

    hide();

    mainWindow -> show();

}
