#include "mainwindow.h"
#include "Admin.h"
#include "ui_Admin.h"

#include <QMap>

Admin::Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
}


// Initializes souvenir table to blank
void InitializeSouvenirTable (QTableView* table)
{

}

// Populates souvenir table with relevant information
void PopulateSouvenirTable (QTableView* table, QSqlQueryModel* model)
{

}

// Intializes stadium table to blank
void InitializeStadiumTable (QTableView* table)
{

}

// Populates stadium table with relevant information
void PopulateStadiumTable (QTableView* table, QSqlQueryModel* model)
{

}

Admin::~Admin()
{
    delete ui;
}

///This function will create a pointer to the MainWindow UI. The admin page will be
/// hidden before showing the Main Window
void Admin::on_Home_PushButton_clicked()
{
    MainWindow *mainWindow;
    mainWindow = new MainWindow(this);

    hide();

    mainWindow -> show();
}
