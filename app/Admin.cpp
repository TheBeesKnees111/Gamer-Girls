#include "mainwindow.h"
#include "Database.h"
#include "Admin.h"
#include "ui_Admin.h"

#include <QMap>

Admin::Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin)
{
	QSqlQueryModel *queryModel = nullptr;

    ui->setupUi(this);

	//Populate Souvenir table with related data and increase column width
	//so team name is not cut off
	PopulateSouvenirTable(queryModel);

	//Populate Stadium table with related data
	PopulateStadiumTable(queryModel);
}


// Initializes souvenir table to blank
void InitializeSouvenirTable (QTableView* table)
{

}

/// Populates souvenir table in the admin section with all data
/// related to souvenirs
void Admin::PopulateSouvenirTable (QSqlQueryModel* model)
{
	QSqlQuery query;

	model = new QSqlQueryModel;

	//Select all souvenir data from database and display it
	//on the datatable (Will Print team names instead of teamID)
	model -> setQuery("SELECT teamName, itemName, itemPrice FROM teamInfo, souvenirs WHERE teamInfo.teamID = souvenirs.teamID");
	ui    -> Update_Souvenir_Datatable -> setModel(model);

	//Resize rows and columns
	ui -> Update_Souvenir_Datatable -> setColumnWidth(0, 200);
	ui -> Update_Souvenir_Datatable -> setColumnWidth(1, 200);
}

// Intializes stadium table to blank
void InitializeStadiumTable (QTableView* table)
{

}

// Populates stadium table with relevant information
void Admin::PopulateStadiumTable (QSqlQueryModel* model)
{
	model = new QSqlQueryModel;

	//Set query to display all data related to the teams
	model -> setQuery("SELECT * FROM teamInfo");
	ui    -> Admin_Datatable        -> setModel(model);
	ui    -> Edit_Stadium_TableView -> setModel(model);

	//Format table boxes to fit data so there is no cut off and
	//it is easily read
	ui -> Admin_Datatable -> setColumnWidth(1, 170);
	ui -> Admin_Datatable -> setColumnWidth(2, 240);
	ui -> Admin_Datatable -> setColumnWidth(4, 240);
	ui -> Admin_Datatable -> setColumnWidth(5, 200);
	ui -> Admin_Datatable -> setColumnWidth(7, 200);

	ui -> Edit_Stadium_TableView -> setColumnWidth(1, 170);
	ui -> Edit_Stadium_TableView -> setColumnWidth(2, 240);
	ui -> Edit_Stadium_TableView -> setColumnWidth(4, 240);
	ui -> Edit_Stadium_TableView -> setColumnWidth(5, 200);
	ui -> Edit_Stadium_TableView -> setColumnWidth(7, 200);

}

Admin::~Admin()
{
    delete ui;
}

///This function will create a pointer to the MainWindow UI. The admin page will be
/// hidden before showing the Main Window
void Admin::on_Home_PushButton_clicked()
{
	MainWindow *mainWindow = new MainWindow(this);

    hide();

	mainWindow -> show();

}
