#include "mainwindow.h"
#include "Database.h"
#include "Admin.h"
#include "ui_Admin.h"

#include <QMap>
#include <QMessageBox>
#include <QSqlError>

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

	//Populate ComboBoxes with realted information
	PopulateComboBoxes("SELECT conference FROM teamInfo" , ui -> Add_Conference_ComboBox);
	PopulateComboBoxes("SELECT division FROM teamInfo"   , ui -> Add_Division_ComboBox);
	PopulateComboBoxes("SELECT surfaceType FROM teamInfo", ui -> Add_Surface_Type_ComboBox);
	PopulateComboBoxes("SELECT roofType FROM teamInfo"   , ui -> Add_Roof_Type_ComboBox);

}

//Populates all combo boxes with relaed information
void Admin::PopulateComboBoxes(QString sqlQuery, QComboBox* comboBox)
{
	//list to hold different string values
	QStringList list;
	QSqlQuery query;

	query.exec(sqlQuery);

	//Output error if query does not work
	if(!query.exec())
		qDebug() << "ERROR reading ADMIN COMBOBOXES";

	//Continue through list while there is still information in the database
	while(query.next())
	{
		//If a value exists in the list do not add it again to prevent repeats
		if(!list.contains(query.value(0).toString()))
		{
			list.push_front(query.value(0).toString());
		}
	}

	//sort list
	list.sort();

	//Add values to the combobox
	for(int index = 0; index < list.size(); index++)
	{
		comboBox -> addItem(list[index]);
	}

	comboBox -> setCurrentIndex(-1);
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
	ui -> Admin_Datatable -> setColumnWidth(2, 200);
	ui -> Admin_Datatable -> setColumnWidth(4, 200);
	ui -> Admin_Datatable -> setColumnWidth(5, 180);
	ui -> Admin_Datatable -> setColumnWidth(7, 200);

	ui -> Edit_Stadium_TableView -> setColumnWidth(1, 170);
	ui -> Edit_Stadium_TableView -> setColumnWidth(2, 200);
	ui -> Edit_Stadium_TableView -> setColumnWidth(4, 200);
	ui -> Edit_Stadium_TableView -> setColumnWidth(5, 180);
	ui -> Edit_Stadium_TableView -> setColumnWidth(7, 200);

	//Hide teamID column
	ui -> Admin_Datatable        -> hideColumn(0);
	ui -> Edit_Stadium_TableView -> hideColumn(0);
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

///Will read in information about a team and add it to the datatable
///and place team in database
void Admin::on_Add_Team_PushButton_clicked()
{

	int teamID = 33;
	QString   teamName    = ui -> Add_Team_Name_LineEdit    -> text();
	QString   stadiumName = ui -> Add_Stadium_Name_LineEdit -> text();
	QString   location    = ui -> Add_Location_LineEdit     -> text();

	bool      blankData   = teamName == "" && stadiumName == "" || location     == "" ||
							ui -> Add_Seating_Capacity_SpinBox -> text()        ==  0 ||
							ui -> Add_Conference_ComboBox      -> currentText() == "" ||
							ui -> Add_Division_ComboBox        -> currentText() == "" ||
							ui -> Add_Roof_Type_ComboBox       -> currentText() == "" ||
							ui -> Add_Surface_Type_ComboBox    -> currentText() == "";

	//Check that all information has been entered and selected
	if(!blankData)
	{//begin if
		QSqlQueryModel *model = nullptr;
		QSqlQuery       query;

		//Add team to table for teamInfo
		query.prepare("INSERT OR IGNORE INTO "
					  "teamInfo(teamName,    stadiumName, seatingCap, "
					  "         location,    conference,  division, "
					  "         surfaceType, roofType,    dateOpened) "
					  "VALUES(:teamName,    :stadiumName, :seatingCap,"
					  "       :location,    :conference,  :division, "
					  "       :surfaceType, :roofType,    :dateOpened)");

		query.bindValue(":teamID"   , teamID);
		query.bindValue(":teamName"   , teamName);
		query.bindValue(":stadiumName", stadiumName);
		query.bindValue(":location"   , location);
		query.bindValue(":seatingCap" , ui -> Add_Seating_Capacity_SpinBox -> text().toInt());
		query.bindValue(":conference" , ui -> Add_Conference_ComboBox      -> currentText());
		query.bindValue(":division"   , ui -> Add_Division_ComboBox        -> currentText());
		query.bindValue(":surfaceType", ui -> Add_Surface_Type_ComboBox    -> currentText());
		query.bindValue(":roofType"   , ui -> Add_Roof_Type_ComboBox       -> currentText());
		query.bindValue(":dateOpened" , ui -> Add_Year_SpinBox             -> text().toInt());

		if(!query.exec())
			qDebug() << query.lastError();

		//
		PopulateStadiumTable(model);



	}//end if
	else
	{
		QMessageBox::information(this, "ERROR Adding Team",
								 "***** Data left blank! *****");
	}
}
