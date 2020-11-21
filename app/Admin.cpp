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
	InitializeSouvenirTable();

	//Populate Stadium table with related data
	PopulateStadiumTable(queryModel);

	//Populate ComboBoxes with realted information
	PopulateComboBoxes("SELECT conference FROM teamInfo" , ui -> Conference_Combo_Box);
	PopulateComboBoxes("SELECT division FROM teamInfo"   , ui -> Division_Combo_Box);
	PopulateComboBoxes("SELECT surfaceType FROM teamInfo", ui -> Surface_Type_ComboBox);
	PopulateComboBoxes("SELECT roofType FROM teamInfo"   , ui -> Roof_Type_ComboBox);
	PopulateComboBoxes("SELECT teamName FROM teamInfo"   , ui -> Team_Name_ComboBox);

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
			list.push_back(query.value(0).toString());
		}
	}

	//Add values to the combobox
	for(int index = 0; index < list.size(); index++)
	{
		comboBox -> addItem(list[index]);
	}

	comboBox -> setCurrentIndex(-1);
}

// Initializes souvenir table to blank
void Admin::InitializeSouvenirTable ()
{
	QSqlQuery query;
	int       row = 0;

	ui -> Update_Souvenir_Datatable -> setColumnCount(3);
	ui -> Update_Souvenir_Datatable -> setHorizontalHeaderLabels({"Team Name", "Souvenir Name", "Souvenir Price"});

	//Select all souvenir data from database and display it
	//on the datatable (Will Print team names instead of teamID)
	query.exec("SELECT teamName, itemName, itemPrice FROM teamInfo, souvenirs WHERE teamInfo.teamID = souvenirs.teamID");

	//Add items while there are more rows in the database
	while(query.next())
	{//begin while

		ui -> Update_Souvenir_Datatable -> insertRow(ui -> Update_Souvenir_Datatable -> rowCount());

		for(int col = 0; col < ui -> Update_Souvenir_Datatable -> model() -> columnCount(); col++)
		{

			switch(col)
			{   case 0:
				case 1: ui -> Update_Souvenir_Datatable -> setItem  (row, col, new QTableWidgetItem(query.value(col).toString()));
						qDebug()<< "col " << col << "query.value(col).toString() " << query.value(col).toString();
				break;
				case 2: ui -> Update_Souvenir_Datatable -> setItem  (row, col, new QTableWidgetItem(query.value(col).toString()));
					qDebug()<< "col " << col << "query.value(col).toDouble() " << query.value(col).toDouble();

				break;
			}

		}

		row++;

	}//end while
}

/// Populates souvenir table in the admin section with all data
/// related to souvenirs
void Admin::PopulateSouvenirTable()
{
	int       row = 0;
	QSqlQuery query;

	//Select all souvenir data from database and display it
	//on the datatable (Will Print team names instead of teamID)
	query.exec("SELECT teamName, itemName, itemPrice FROM teamInfo, souvenirs WHERE teamInfo.teamID = souvenirs.teamID");

	//Add items while there are more rows in the database
	while(query.next())
	{//begin while

		for(int col = 0; col < ui -> Update_Souvenir_Datatable -> model() -> columnCount(); col++)
		{

			switch(col)
			{   case 0:
				case 1: ui -> Update_Souvenir_Datatable -> setItem  (row, col, new QTableWidgetItem(query.value(col).toString()));
						qDebug()<< "col " << col << "query.value(col).toString() " << query.value(col).toString();
				break;
				case 2: ui -> Update_Souvenir_Datatable -> setItem  (row, col, new QTableWidgetItem(query.value(col).toString()));
					qDebug()<< "col " << col << "query.value(col).toDouble() " << query.value(col).toDouble();

				break;
			}

		}

		row++;

	}//end while
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
void Admin::on_Read_In_From_File_Button_clicked()
{
	QFile           file(":/Input/Input.txt");
	QTextStream     inFile(&file);
	file.open(QIODevice::ReadOnly);

	//Only run if the file is opened
	if(file.isOpen())
	{//begin if(file.isOpen())

		QSqlQuery       query;
		QSqlQueryModel *model = nullptr;
		int             teamID = 33;
		int             souvenirID = (teamID - 1) * 5;
		QStringList     otherStadiums;
		QVector <int>   miles;

		qDebug() << "FILE OPENED";

		/***********************************************************************
		 * ADDING TO TEAM TABLE
		 **********************************************************************/
		//Read int each line as text
		QString teamName        = file.readLine().trimmed();
		QString stadiumName     = file.readLine().trimmed();
		int     seatingCapacity = file.readLine().toInt();
		QString location        = file.readLine().trimmed();
		QString conference      = file.readLine().trimmed();
		QString division        = file.readLine().trimmed();
		QString surfaceType     = file.readLine().trimmed();
		QString roofType        = file.readLine().trimmed();
		int     dateOpened      = file.readLine().toInt();

		while(!file.atEnd())
		{
			otherStadiums.push_back(file.readLine().trimmed());
			miles.push_back(file.readLine().toInt());
		}

		qDebug() << "ui -> Team_Name_ComboBox -> findText(teamName) "
				 << ui -> Team_Name_ComboBox -> findText(teamName);

		if(ui -> Team_Name_ComboBox -> findText(teamName) == -1)
		{
			//Add team to table for teamInfo
			query.prepare("INSERT OR IGNORE INTO"
						  " teamInfo(teamID,     teamName,    stadiumName, "
						  "         seatingCap,  location,    conference,  "
						  "			division,    surfaceType, roofType,"
						  "         dateOpened) "
						  " VALUES(:teamID,    :teamName,   :stadiumName, "
						  "        :seatingCap,:location,   :conference,  "
						  "        :division,  :surfaceType,:roofType,    "
						  "        :dateOpened)");

			//Bind query values
			query.bindValue(":teamID"     , teamID);
			query.bindValue(":teamName"   , teamName);
			query.bindValue(":stadiumName", stadiumName);
			query.bindValue(":seatingCap" , seatingCapacity);
			query.bindValue(":location"   , location);
			query.bindValue(":conference" , conference);
			query.bindValue(":division"   , division);
			query.bindValue(":surfaceType", surfaceType);
			query.bindValue(":roofType"   , roofType);
			query.bindValue(":dateOpened" , dateOpened);

			if(!query.exec())
				qDebug() << query.lastError();

			//Populate datatable with new info
			PopulateStadiumTable(model);
			PopulateComboBoxes("SELECT teamName FROM teamInfo"   , ui -> Team_Name_ComboBox);

		/***********************************************************************
		 * ADDING TO SOUVENIR TABLE
		 **********************************************************************/
			Database::getInstance() -> AddDefaultSouvenirsToDatabase
					(souvenirID, teamID, defaultSouvenirs, souvenirPrices);

			PopulateSouvenirTable();
		/***********************************************************************
		 * ADDING TO DISTANCES TABLE
		 **********************************************************************/
			Database::getInstance()->AddDistancesToDataBaseFromFile(stadiumName, otherStadiums, miles);
		}

	}//end if(file.isOpen())

}

//Add souvenir to database and datatable
void Admin::on_Add_Souvenir_PushButton_clicked()
{
	QString        souvenirName = ui -> Souvenir_Name_LineEdit -> text();
	double         price        = ui -> Price_Double_SpinBox   -> text().toDouble();
	int			   teamID       = ui -> Team_Name_ComboBox     -> currentIndex() + 1;
	QSqlQuery      query;

	//Set definition of blank data
	bool    blankData    = (souvenirName == "" || price == 0.00 ||
							teamID       == 0);

	if(blankData)
		QMessageBox::information(this,"ERROR", "***** Data left blank *****");

	else
	{
		ui -> Update_Souvenir_Datatable -> insertRow(ui -> Update_Souvenir_Datatable -> rowCount());

		//Pull teamId from team name selected by the user
		query.prepare("INSERT OR IGNORE INTO "
					  "souvenirs(teamID,  itemName,  itemPrice) "
					  "VALUES   (:teamID, :itemName, :itemPrice)");

		query.bindValue(":teamID",    teamID);
		query.bindValue(":itemName",  souvenirName);
		query.bindValue(":itemPrice", price);

		if(!query.exec())
			qDebug() << query.lastError();

		//Repopulate the souvenir table
		PopulateSouvenirTable();

		ui -> Souvenir_Name_LineEdit -> clear();
		ui -> Price_Double_SpinBox   -> clear();
		ui -> Team_Name_ComboBox     -> setCurrentIndex(-1);
	}
}

///This will delete an item from the database with the name and team selected
///by the user
void Admin::on_Delete_Souvenir_PushButton_clicked()
{

}

void Admin::on_Update_Souvenir_Datatable_clicked(const QModelIndex &index)
{
	if(index.isValid())
	{
		qDebug() << "index.row() " << index.row();
		qDebug() << "index.col() " << index.column();
		qDebug() << " ";

		int rowIndex = ui -> Update_Souvenir_Datatable -> selectionModel() -> currentIndex().row();

		ui -> Souvenir_Name_LineEdit -> text()        = index.data(0).toString();
		ui -> Price_Double_SpinBox   -> text()        = index.data(1).toDouble();
		ui -> Team_Name_ComboBox     -> currentText() = index.data(2).toString();

		qDebug() << "rowIndex " << rowIndex;
		qDebug() << " ";

//		ui -> Souvenir_Name_LineEdit -> setText (model -> index(rowIndex , 0).data().toString());
		QItemSelectionModel *select = ui -> Update_Souvenir_Datatable->selectionModel();
		qDebug()<<select->selectedRows(0).value(0).data().toString();
		qDebug()<<select->selectedRows(1).value(0).data().toString();
		qDebug()<<select->selectedRows(2).value(0).data().toString();
		qDebug()<<select->selectedRows(3).value(0).data().toString();

	}
}
