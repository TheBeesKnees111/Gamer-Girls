#include "Database.h"
#include "SouvenirAndTrip.h"
#include "ui_SouvenirAndTrip.h"
#include "mainwindow.h"
#include "Team.h"
#include "Souvenir.h"
#include "Stadium.h"
#include "PurchaseTable.h"
#include "StadiumGraph.h"
#include "Dijkstra.h"
#include "BFS.h"
#include "AdjacencyList.h"
#include "kruskals.h"

SouvenirAndTrip::SouvenirAndTrip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SouvenirAndTrip)
{
    ui->setupUi(this);

    // TODO DEBUG This database is opened here because I can't find it opened anywhere else
    database = Database::getInstance();

    adjList = database->GetAdjacencyList();

    // Retrieving combobox labels for 'display souvenirs for one team'
    souvenirComboBoxLabels = database->GetTeamNames();
    ui->Souvenir_Select_Team_ComboBox->addItems(souvenirComboBoxLabels);


    QSqlQuery query;

    /***************************************************************************
     * INITIALIZING COMBO BOXES
     * -------------------------------------------------------------------------
     * Initialize comboboxes to hold stadium names and team names
     **************************************************************************/
    query.exec("SELECT teamName, stadiumName FROM teamInfo");

    if(!query.exec())
        qDebug() << "Error: TRIPS PAGE -> Adding Team Name to ComboBox ";
    else
    {//begin else

        while (query.next())
        {
            QString teamName    = query.value(0).toString();
            QString stadiumName = query.value(1).toString();

            ui -> Souvenir_Select_Team_ComboBox       -> addItem(teamName);
            ui -> Green_Bay_Select_Stadium_ComboBox   -> addItem(teamName);
            ui -> Custom_Trip_Select_Stadium_ComboBox -> addItem(teamName);
            ui -> Shortest_Distance_Select_Stadium_ComboBox -> addItem(teamName);

        }

        // Adjust combo box to size of contents
        ui -> Souvenir_Select_Team_ComboBox       -> setSizeAdjustPolicy(QComboBox::AdjustToContents);
        ui -> Green_Bay_Select_Stadium_ComboBox   -> setSizeAdjustPolicy(QComboBox::AdjustToContents);
        ui -> Custom_Trip_Select_Stadium_ComboBox -> setSizeAdjustPolicy(QComboBox::AdjustToContents);
        ui -> Shortest_Distance_Select_Stadium_ComboBox -> setSizeAdjustPolicy(QComboBox::AdjustToContents);

        // sets index to nothing - won't show on dropdown
        ui -> Souvenir_Select_Team_ComboBox             -> setCurrentIndex(0);
        ui -> Green_Bay_Select_Stadium_ComboBox         -> setCurrentIndex(0);
        ui -> Custom_Trip_Select_Stadium_ComboBox       -> setCurrentIndex(0);
        ui -> Shortest_Distance_Select_Stadium_ComboBox -> setCurrentIndex(0);

    }//begin else

    /***************************************************************************
     * INITIALIZING CHECK BOXES
     * -------------------------------------------------------------------------
     * Create check boxes so user can select cities to go to
     **************************************************************************/
    QStringList  itemLabels;

    query.prepare("SELECT stadiumName FROM teamInfo");

    //Initialize items that will be added to the list view
    if(!query.exec())
    {
        qDebug() << "Chck boxes broke ";
    }
    else
    {
        while(query.next())
        {
            itemLabels.push_back(query.value(0).toString());
            //qDebug() << "query.value(0).toString()" << query.value(0).toString();
        }
    }

    QStringListIterator it(itemLabels);
    while (it.hasNext())
    {
        listItem = new QListWidgetItem(it.next(), ui ->
        Select_Cities_ListWidget);

        listItem -> setCheckState(Qt::Unchecked);
        ui->Select_Cities_ListWidget->addItem(listItem);
    }

    ui -> Select_Cities_ListWidget -> sortItems();

    // Disable "Go to Cart" buttons (Enabled by pressing "Confirm Trip" on each page)
    ui->greenBay_cart_button->setDisabled(true);
    ui->customTrip_cart_button->setDisabled(true);
    ui->newEngland_cart_button->setDisabled(true);
    ui->shortestCustomTrip_cart_button->setDisabled(true);
    //Took this line out because the mst does not need to access the shopping cart per Jerry's requirements
    //ui->mst_cart_button->setDisabled(true);
    ui->minnesota_cart_button->setDisabled(true);
    ui->losAngeles_cart_button->setDisabled(true);

    // Set distance travelled to 0
    distanceTraveled = 0;

}

SouvenirAndTrip::~SouvenirAndTrip()
{
    delete ui;
}

///This function will create a pointer to the main window. It will then hide the
///travel page before showing the main window
void SouvenirAndTrip::on_Home_PushButton_clicked()
{
    MainWindow *mainWindow;
    mainWindow = new MainWindow(this);

    hide();

    mainWindow -> show();
}

/*********************************************
 ************** GREEN BAY TRIP **************
 *********************************************/
///For GREEN BAY TRIP push button clicked
/// Will call rout displayer and show the dijkstra path to the city
/// the traveler has selected to travel to
void SouvenirAndTrip::on_Green_Bay_Confirmation_PushButton_clicked()
{
    QString teamName = ui->Green_Bay_Select_Stadium_ComboBox->currentText();

//    qDebug() << "Building path from Green Bay to: " << teamName;

    // Create Database
    Database* db = Database::getInstance();

    // CALL SHORTEST PATH HERE?
    // get stadium origin
    Stadium* origin {db->getStadiumByName("Lambeau Field")};
    // get city selected
    Stadium *destination = db->GetTeamByName(teamName)->getStadium();
//    Stadium* destination{db->getStadiumByName(stadiumName)};

    // create graph
    StadiumGraph graph = StadiumGraph::createStadiumGraph(db);

    // create spanning tree for all destinations
    QHash<QString, StadiumDistance*> spanningTree = Dijkstra(graph, origin);

    // get path for destination location
    QVector<StadiumDistance*> path = buildPath(spanningTree, destination);

    /***********************************************
    // PRINTING TO DISPLAY ON SOUVENIRANDTRIP PAGE
    ***********************************************/
    // create the row size for setup
    int rowSize = path.size();
    // setup row & column sizes
    QTableWidget* tableWidget = ui->greenBay_tableWidget;
    tableWidget->setRowCount(rowSize + 1);
    tableWidget->setColumnCount(2);

    int totalDistance = 0;

    // loops thru the vector of StadiumDistances and displays the team name
    // as well as the stadium
    for (int row = 0; row < path.size(); row++)
    {
        // get & display team name
        QString teamName = path[row]->getFromStadium()->getTeams().first()->getTeamName();
        //    Items are created outside the table (with no parent widget) and inserted into the table with setItem():
        QTableWidgetItem *newItem = new QTableWidgetItem(teamName);
        tableWidget->setItem(row, 0, newItem);
        // get & display stadium name
        //    Items are created outside the table (with no parent widget) and inserted into the table with setItem():
        newItem = new QTableWidgetItem(path[row]->getFromStadium()->getStadiumName());
        tableWidget->setItem(row, 1, newItem);
        // calculate total distance
        totalDistance += path[row]->getDistance();
    }

    // calculate last team & stadium name
    QTableWidgetItem *newItem = new QTableWidgetItem(teamName);
    tableWidget->setItem(rowSize, 0, newItem);
    newItem = new QTableWidgetItem(path[rowSize - 1]->getToStadium()->getStadiumName());
    tableWidget->setItem(rowSize, 1, newItem);

    // output distance
    ui->Total_Distance_Label->setText(QString("%1").arg(totalDistance));

    // resize based on table contents
    tableWidget->horizontalHeader()->setSectionResizeMode
            (QHeaderView::ResizeToContents);

    /***********************************************
    // SETUP FOR PURCHASE TABLE
    ***********************************************/
//    qDebug() << "Calling Purchase Table from Green Bay to: " << teamName;

    // Create QStringList for Shopping List
    QStringList stadiumNames;
    stadiumNames.append("Lambeau Field");
    stadiumNames.append(destination->getStadiumName());
//    qDebug() << "stadiumNames list: " << stadiumNames;

    // Create Shopping List
    teamList = db->CreateShoppingList(stadiumNames);
//    qDebug() << "QVector teamList size: " << teamList->size();
//    qDebug() << "CreateShoppingList info: ";
//    for(int i = 0; i < teamList->size(); i++)
//    {
//        qDebug() << teamList->at(i)->getTeamName();
//    }

    ui->greenBay_cart_button->setEnabled(true);
}

void SouvenirAndTrip::on_greenBay_cart_button_clicked()
{
    // FIXME: Needs to re-grey if we close the window without clicking on "Okay!"

    // Create new PurchaseTable
    PurchaseTable * purchaseTable = new PurchaseTable(this, teamList);
    // set window title
//    purchaseTable->setWindowTitle(QString("Trip from Green Bay Packers in %1").arg(origin->getStadiumName()));
    // open window
    purchaseTable->show();
}

            /*********************************************
             ************** CUSTOM TRIP TAB **************
             *********************************************/
///For CUSTOM TRIP push button clicked
/// Will call rout displayer and show cities the user has selected to travel to
void SouvenirAndTrip::on_Confirm_Custom_Trip_PushButton_clicked()
{
    QStringList listOfStadiums;
    QList<int>  listOfDistances;

    for(int index = 0; index < ui -> Select_Cities_ListWidget -> count(); index++)
    {
        if(ui -> Select_Cities_ListWidget -> item(index) -> checkState() == Qt::Checked)
        {
            listOfStadiums.push_back(ui -> Select_Cities_ListWidget -> item(index) -> text());
        }
    }

    while(!listOfStadiums.isEmpty())
    {
        qDebug() << listOfStadiums.first();
        listOfStadiums.pop_front();
    }

}

// Will activate pulling souvenirs for this team
void SouvenirAndTrip::on_Souvenir_Select_Team_ComboBox_activated(const QString &arg1)
{
    Team* team = database->GetSingleTeamSouvenirs(arg1);

    // Pull souvenir data from database
    InitializeSouvenirTable(ui->Souvenir_TableWidget, SOUVENIR_COL_COUNT, souvenirHeaders);

    // Display in table
    PopulateSouvenirTable(team);
}

//---------- END NAVIGATION

// ------- START HELPER METHODS

void SouvenirAndTrip::InitializeSouvenirTable(QTableWidget* table, const int &cols, const QStringList &headers)
{
    table->clearContents();
    table->setColumnCount(cols);
    table->setHorizontalHeaderLabels(headers);
    table->setEditTriggers(QTableView::NoEditTriggers);
    table->verticalHeader()->hide();

    DeleteAllTableRows(table);
}

void SouvenirAndTrip::PopulateSouvenirTable(Team* team)
{
    // Date opened item
    QTableWidgetItem* priceItem;
    for(int index = 0; index < team->getSouvenirList().size(); index++)
    {
        // Set date opened item
        priceItem = new QTableWidgetItem(QString::number(team->getSouvenirList().at(index)->getItemPrice(), 'f', 2));
        // Create Row
        ui->Souvenir_TableWidget->insertRow(ui->Souvenir_TableWidget->rowCount());
        // Populate Team Name Column
        ui->Souvenir_TableWidget->setItem(ui->Souvenir_TableWidget->rowCount() -1, TEAM_NAME, new QTableWidgetItem(team->getTeamName()));
        // Populate Stadium Name Column
        ui->Souvenir_TableWidget->setItem(ui->Souvenir_TableWidget->rowCount() -1, SOUVENIR_NAME, new QTableWidgetItem(team->getSouvenirList().at(index)->getItemName()));
        // Populate Date Opened Column
        ui->Souvenir_TableWidget->setItem(ui->Souvenir_TableWidget->rowCount() -1, SOUVENIR_PRICE, priceItem);
    }
}

// Deletes contents of passed in table
void SouvenirAndTrip::DeleteAllTableRows(QTableWidget *table)
{
    const int ROW_COUNT = table->rowCount();

    for(int index = 0; index < ROW_COUNT; index++)
    {
        table->removeRow(0);
    }
}

void SouvenirAndTrip::InitializeTripTable(QTableWidget* table, const int &cols, const QStringList &headers)
{
    table->clearContents();
    table->setColumnCount(cols);
    table->setHorizontalHeaderLabels(headers);
    table->setEditTriggers(QTableView::NoEditTriggers);
    table->verticalHeader()->hide();

    DeleteAllTableRows(table);
}

void SouvenirAndTrip::PopulateTripTable(QTableWidget* table, const QVector<Team*>* teams)
{
    // Date opened item
    for(int index = 0; index < teams->size(); index++)
    {
        // Create Row
        table->insertRow(table->rowCount());
        // Populate Team Name Column
        table->setItem(table->rowCount() -1, T_TEAM, new QTableWidgetItem(teams->at(index)->getTeamName()));
        // Populate Stadium Name Column
        table->setItem(table->rowCount() -1, T_STADIUM, new QTableWidgetItem(teams->at(index)->getStadium()->getStadiumName()));
    }
}

// END HELPER METHODS

// Los Angeles BFS Trip
void SouvenirAndTrip::on_Confirm_Lo_sAngeles_Rams_Trip_PushButton_clicked()
{
    QStringList stadiumNames;
    QString distanceOutput = "Total Distance Traveled: ";
    BFS bfs(adjList);

    // Perform BFS
    bfs.Traverse();
    stadiumNames = bfs.GetTraversalList();

//    // DEBUG output teamNames
//    qDebug() << "Printing stadiumNames from BFS";
//    qDebug() << stadiumNames;
//    qDebug() << "---";

    // Store distance traveled
    distanceTraveled = bfs.GetDistanceTraveled();

    // Get BFS team objects
    teamList = database->CreateShoppingList(stadiumNames);

//    // DEBUG
//    qDebug() << "Printing teams and stadium names from CreateShoppingList";
//    for(int index = 0; index < teamList->size(); index++)
//    {
//        qDebug() << "Team Name: " << teamList->at(index)->getTeamName();
//        qDebug() << "Stadium Name: " << teamList->at(index)->getStadium()->getStadiumName();
//    }

    // Enable cart button
    ui->losAngeles_cart_button->setEnabled(true);

    // Populate label
    distanceOutput = distanceOutput + QVariant(distanceTraveled).toString();
    ui->losAngeles_distance_label->setText(distanceOutput);

    // Initialize Table
    InitializeTripTable(ui->losAngeles_tableWidget, TRIP_TABLE_COL_COUNT, tripTableHeaders);

    // Populate Table
    PopulateTripTable(ui->losAngeles_tableWidget, teamList);
}

void SouvenirAndTrip::on_losAngeles_cart_button_clicked()
{
    PurchaseTable *purchaseTable = new PurchaseTable(this, teamList);

    purchaseTable->show();
}

			/*********************************************
			 **************     MST TRIP    **************
			 *********************************************/

void SouvenirAndTrip::on_Confirm_MST_Trip_clicked()
{
    //a qstringlist to hold the stadium naes
    QStringList stadiumNames;
	QStringList verticalHeader;
    QString distanceOutput = "Total Cost: ";
    //instantiate our kruskals graph
    kruskals g(10000);
    //read from db from prechosen starting spot
    g.readDb("Sofi Stadium");
    //solve kruskals algorithm
    g.solve();
    //get the cost of the trip
    g.calcCost();
    //set the cost to the distance traveled
    int totalCost = g.getDistanceTraveled();
    //print the distance traveled
    distanceOutput = distanceOutput + QVariant(totalCost).toString();
    ui->mst_distance_label->setText(distanceOutput);
    //inintialize the table

    InitializeTripTable(ui->mst_tableWidget, TRIP_TABLE_COL_COUNT, tripTableHeaders);
    //get the list of traversal
   stadiumNames = g.getList();
   //create the list needed to populate the db
    teamList = database->CreateShoppingList(stadiumNames);
    //print to the db
   PopulateTripTable(ui->mst_tableWidget, teamList);

   for(int index = ui -> mst_tableWidget -> rowCount(); index > -1 ; index--)
   {
	   if(index%2 ==1)
		   ui -> mst_tableWidget -> insertRow(index + 1);
   }

   //Set vertical Header
   for(int index = 0; index < ui -> mst_tableWidget -> rowCount(); index++)
   {
	   switch(index % 3 + 1)
	   {
		   case 1: verticalHeader.push_back("From City");
		   break;

		   case 2: verticalHeader.push_back("To City");
		   break;

		   default: verticalHeader.push_back("");
	   }
   }

   ui -> mst_tableWidget -> setVerticalHeaderLabels(verticalHeader);
   ui -> mst_tableWidget -> verticalHeader() -> show();
   ui -> mst_tableWidget -> setColumnWidth(0,200);
   ui -> mst_tableWidget -> setColumnWidth(1,200);


}
