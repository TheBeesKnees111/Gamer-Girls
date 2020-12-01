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
    ui->setupUi(this);

	//Populate Souvenir table with related data and increase column width
	//so team name is not cut off
	PopulateSouvenirTable();

	//Populate Stadium table with related data
	PopulateStadiumTable();

	//Populate purchase table with data
	PopulatePurchasesTable();

	//Populate ComboBoxes with realted information
	PopulateComboBoxes("SELECT conference FROM teamInfo" , ui -> Conference_Combo_Box);
	PopulateComboBoxes("SELECT division FROM teamInfo"   , ui -> Division_Combo_Box);
	PopulateComboBoxes("SELECT surfaceType FROM teamInfo", ui -> Surface_Type_ComboBox);
	PopulateComboBoxes("SELECT roofType FROM teamInfo"   , ui -> Roof_Type_ComboBox);
	PopulateComboBoxesItems("SELECT teamName, teamID FROM teamInfo"   , ui -> Team_Name_ComboBox);

	//Initialize Map to carry souvenirs
	InitializeMapSouvenirData();

}

///Initialize map to store all souvenir data
void Admin::InitializeMapSouvenirData()
{
	QSqlQuery query;

	//Call query to select souvenir info
	if(!query.exec("SELECT * FROM souvenirs"))
		qDebug() << "INITIALIZE MAP MACHINE BROKE " << query.lastError();
	else
	{
		Souvenir newSouvenir;

		while(query.next())
		{

			//Set souvenir values
			newSouvenir.SetSouvenirID(query.value(SOUVENIR_ID).toInt());
			newSouvenir.SetTeamID    (query.value(TEAM_ID)    .toInt());
			newSouvenir.SetItemName  (query.value(ITEM_NAME)  .toString());
			newSouvenir.SetItemPrice (query.value(ITEM_PRICE) .toDouble());

			souvenirs.Insert(query.value(SOUVENIR_ID).toInt(), newSouvenir);
		}
	}

}

///Give all comboboxes values
void Admin::PopulateComboBoxes(QString sqlQuery, QComboBox* comboBox)
{
	//list to hold different string values
	QSqlQuery   query;
	QStringList list;

	comboBox -> clear();

	query.exec(sqlQuery);

	//Output error if query does not work
	if(!query.exec())
		qDebug() << "ERROR reading ADMIN COMBOBOXES";

	//Continue through list while there is still information in the database
	while(query.next())
	{
		if(!list.contains(query.value(0).toString()))
			list.push_back(query.value(0).toString());
	}

	list.sort();

	comboBox -> addItems(list);

	//set item data to
	//ui -> Team_Name_ComboBox -> setItemData();
	comboBox -> setCurrentIndex(-1);
}


///Populates all combo boxes with relaed information
void Admin::PopulateComboBoxesItems(QString sqlQuery, QComboBox* comboBox)
{
	//list to hold different string values
	QSqlQuery query;
	int       index = 0;

	comboBox -> clear();
	comboBox -> setDuplicatesEnabled(false);

	query.exec(sqlQuery);

	//Output error if query does not work
	if(!query.exec())
		qDebug() << "ERROR reading ADMIN COMBOBOXES";

	//Continue through list while there is still information in the database
	while(query.next())
	{
		comboBox -> addItem(query.value(0).toString());
		comboBox -> setItemData(index, QVariant::fromValue(query.value(1).toInt()));

		index++;
	}

	//set item data to
	//ui -> Team_Name_ComboBox -> setItemData();
	comboBox -> setCurrentIndex(-1);
}

/// Populates souvenir table in the admin section with all data
/// related to souvenirs
void Admin::PopulateSouvenirTable ()
{
	QSqlQuery query;

	QSqlQueryModel* model = new QSqlQueryModel;

	//Select all souvenir data from database and display it
	//on the datatable (Will Print team names instead of teamID)
	model -> setQuery("SELECT teamName, itemName, itemPrice, souvenirID FROM teamInfo, souvenirs WHERE teamInfo.teamID = souvenirs.teamID");
	ui    -> Update_Souvenir_Datatable -> setModel(model);

	//Resize rows and columns
	ui -> Update_Souvenir_Datatable -> setColumnWidth(0, 200);
	ui -> Update_Souvenir_Datatable -> setColumnWidth(1, 200);

	ui -> Update_Souvenir_Datatable -> verticalHeader() -> hide();
}

/// Populates stadium table with relevant information
void Admin::PopulateStadiumTable ()
{
	QSqlQueryModel* model = new QSqlQueryModel;

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

	ui -> Edit_Stadium_TableView -> verticalHeader() -> hide();
	ui -> Edit_Stadium_TableView -> setColumnWidth(0, 50);
	ui -> Edit_Stadium_TableView -> setColumnWidth(1, 170);
	ui -> Edit_Stadium_TableView -> setColumnWidth(2, 200);
	ui -> Edit_Stadium_TableView -> setColumnWidth(4, 200);
	ui -> Edit_Stadium_TableView -> setColumnWidth(5, 180);
	ui -> Edit_Stadium_TableView -> setColumnWidth(7, 200);

	//Hide teamID column
	ui -> Admin_Datatable        -> hideColumn(0);
}

///Populate table of purchases
void Admin::PopulatePurchasesTable()
{
	QSqlQueryModel *model = new QSqlQueryModel;
	QStringList     headers = {"ID", "Team Name", "Souvenir Name", "Quantity"};

	//Set query for model
	model -> setQuery("SELECT purchases.purchaseID, teamInfo.teamName, souvenirs.itemName, "
					  "purchases.qtyPurchased "
					  "FROM purchases, teamInfo, souvenirs "
					  "WHERE teamInfo.teamID = purchases.teamID AND "
					  "souvenirs.souvenirID = purchases.souvenirID");

	//Set model for table
	ui -> Display_Purchases_TableView -> setModel(model);

	//Set horizontal headers
	for(int index = 0; index < headers.size(); index ++)
	{
		ui -> Display_Purchases_TableView -> model() -> setHeaderData(index, Qt::Horizontal, headers[index]);
	}

	ui -> Display_Purchases_TableView -> verticalHeader() -> hide();
	ui -> Display_Purchases_TableView -> setColumnWidth(0, 50);
	ui -> Display_Purchases_TableView -> setColumnWidth(1, 200);
	ui -> Display_Purchases_TableView -> setColumnWidth(2, 200);
	ui -> Display_Purchases_TableView -> setColumnWidth(3, 100);

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
		int             teamID = 33;
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
			PopulateStadiumTable();
			PopulateComboBoxesItems("SELECT teamName, teamID FROM teamInfo"   , ui -> Team_Name_ComboBox);

		/***********************************************************************
		 * ADDING TO SOUVENIR TABLE
		 **********************************************************************/
			Database::getInstance() -> AddDefaultSouvenirsToDatabase
					(teamID, defaultSouvenirs, souvenirPrices);

			PopulateSouvenirTable();
		/***********************************************************************
		 * ADDING TO DISTANCES TABLE
		 **********************************************************************/
			Database::getInstance()->AddDistancesToDataBaseFromFile(stadiumName, otherStadiums, miles);
		}

	}//end if(file.isOpen())

}

///Add souvenir to database and datatable
void Admin::on_Add_Souvenir_PushButton_clicked()
{
	QString   souvenirName = ui -> Souvenir_Name_LineEdit -> text();
	double    price        = ui -> Price_Double_SpinBox   -> text().toDouble();
	int       teamID       = ui -> Team_Name_ComboBox     -> currentData().toInt();
	QSqlQuery query;

	//Set definition of blank data
	bool    blankData    = (souvenirName == "" || price == 0.00 ||
							teamID       == 0  || !IsOnlySpaces(souvenirName));

	if(blankData && !souvenirs.SearchItem(souvenirs[teamID]))
		QMessageBox::information(this,"ERROR", "***** Data left blank *****\n Or Item already added");

	else
	{
		Souvenir newSouvenir;

		query.prepare("INSERT INTO "
					  "souvenirs(teamID,  itemName,  itemPrice) "
					  "VALUES   (:teamID, :itemName, :itemPrice)");

		query.bindValue(":teamID",    teamID);
		query.bindValue(":itemName",  souvenirName);
		query.bindValue(":itemPrice", price);

		if(!query.exec())
			qDebug() << query.lastError();

		PopulateSouvenirTable();
		PopulateComboBoxes("SELECT teamName, teamID FROM teamInfo", ui -> Team_Name_ComboBox);

		//Clear inputs
		ui -> Souvenir_Name_LineEdit -> clear();
		ui -> Price_Double_SpinBox   -> clear();

		//Add to map
		newSouvenir.SetItemName  (souvenirName);
		newSouvenir.SetItemPrice (price);
		newSouvenir.SetSouvenirID(Database::getInstance() -> GetMaxSouvenirID() + 1);
		newSouvenir.SetTeamID    (teamID);

		souvenirs.Insert(teamID, newSouvenir);

	}

}

///Update inormation of item in database
void Admin::on_Update_Souvenir_PushButton_clicked()
{
	QString   souvenirName = ui -> Souvenir_Name_LineEdit -> text();
	double    price        = ui -> Price_Double_SpinBox   -> text().toDouble();
	int       teamID       = ui -> Team_Name_ComboBox     -> currentData().toInt();

	QSqlQuery query;

	//Set definition of blank data
	bool    blankData    = (souvenirName == ""   ||
							price        == 0.00 ||
							teamID       == 0    ||
							!IsOnlySpaces(souvenirName) ||
							souvenirID == 0);

	//Output error message if data is blank
	if(blankData)
		QMessageBox::information(this,"ERROR", "***** Data left blank *****");

	else
	{
		//Prepare table for update
		query.prepare("REPLACE INTO "
					  "souvenirs( souvenirID,  teamID,  itemName,  itemPrice) "
					  "VALUES   (:souvenirID, :teamID, :itemName, :itemPrice)");

		query.bindValue(":souvenirID", souvenirID);
		query.bindValue(":teamID",     teamID);
		query.bindValue(":itemName",   souvenirName);
		query.bindValue(":itemPrice",  price);

		//Output error message if query fails
		if(!query.exec())
			qDebug() << query.lastError();

		//Update souvenir table
		PopulateSouvenirTable();

	}
}

///Pull data from datatable when a cell is selected
void Admin::on_Update_Souvenir_Datatable_clicked(const QModelIndex &index)
{
	//Set values of clicked cells
	souvenirID = index.siblingAtColumn(3).data().toInt();
	ui -> Souvenir_Name_LineEdit -> setText (index.siblingAtColumn(1).data().toString());
	ui -> Price_Double_SpinBox   -> setValue(index.siblingAtColumn(2).data().toDouble());
	ui -> Team_Name_ComboBox     -> setCurrentText(index.siblingAtColumn(0).data().toString());

	qDebug() << "Team Name Combobox item int   : " << ui -> Team_Name_ComboBox -> currentData().toInt();
}

///DELETE item from datatable and from database
void Admin::on_Delete_Souvenir_PushButton_clicked()
{
	QSqlQuery query;

	//Set definition of blank data
	bool    blankData    = (souvenirID == 0);

	if(blankData)
		QMessageBox::information(this,"ERROR", "***** Data left blank *****");

	else
	{
		//prepare query
		query.prepare("DELETE FROM souvenirs WHERE souvenirID = :souvenirID");

		query.bindValue(":souvenirID", souvenirID);

		//Output error message if query fails
		if(!query.exec())
			qDebug() << query.lastError();

		//Update souvenir table so that information will appear
		PopulateSouvenirTable();

		//Reset souvenir ID to zero
		souvenirID = 0;
	}
}

///Check if line edit is only composed of spaces
bool Admin::IsOnlySpaces(QString& value)
{
	int  index = 0;

	while(index < value.length())
	{
		if(value[index] != ' ')
		{
			return true;
		}
		index++;
	}

	return false;
}

///Updating stadium info
void Admin::on_Update_Stadium_PushButton_clicked()
{
	QString teamName        = ui -> Team_Name_LineEdit       -> text();
	QString stadiumName     = ui -> Stadium_Name_LineEdit    -> text();
	int     seatingCapacity = ui -> Seating_Capacity_SpinBox -> value();
	QString location        = ui -> Location_LineEdit        -> text();
	QString conference      = ui -> Conference_Combo_Box     -> currentText();
	QString division        = ui -> Division_Combo_Box       -> currentText();
	QString surfaceType     = ui -> Surface_Type_ComboBox    -> currentText();
	QString roofType        = ui -> Roof_Type_ComboBox       -> currentText();
	int     dateOpened      = ui -> Year_SpinBox             -> value();
	QSqlQuery query;

	if(selectedTeamID == 0)
		QMessageBox::information(this,"ERROR", "***** Data left blank *****");
	else
	{
		query.prepare("REPLACE INTO"
					  " teamInfo(teamID,     teamName,    stadiumName, "
					  "         seatingCap,  location,    conference,  "
					  "			division,    surfaceType, roofType,"
					  "         dateOpened) "
					  " VALUES(:teamID,    :teamName,   :stadiumName, "
					  "        :seatingCap,:location,   :conference,  "
					  "        :division,  :surfaceType,:roofType,    "
					  "        :dateOpened)");

		//Bind query values
		query.bindValue(":teamID"     , selectedTeamID);
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

		PopulateStadiumTable();
	}
}

///Pull data from table when clicked
void Admin::on_Edit_Stadium_TableView_clicked(const QModelIndex &index)
{
	selectedTeamID = index.siblingAtColumn(0).data().toInt();
	ui -> Team_Name_LineEdit	   -> setText(index.siblingAtColumn(1).data().toString());
	ui -> Stadium_Name_LineEdit    -> setText(index.siblingAtColumn(2).data().toString());
	ui -> Seating_Capacity_SpinBox -> setValue(index.siblingAtColumn(3).data().toInt());
	ui -> Location_LineEdit        -> setText(index.siblingAtColumn(4).data().toString());
	ui -> Conference_Combo_Box	   -> setCurrentText(index.siblingAtColumn(5).data().toString());
	ui -> Division_Combo_Box	   -> setCurrentText(index.siblingAtColumn(6).data().toString());
	ui -> Surface_Type_ComboBox	   -> setCurrentText(index.siblingAtColumn(7).data().toString());
	ui -> Roof_Type_ComboBox	   -> setCurrentText(index.siblingAtColumn(8).data().toString());
	ui -> Year_SpinBox			   -> setValue(index.siblingAtColumn(9).data().toInt());
}
