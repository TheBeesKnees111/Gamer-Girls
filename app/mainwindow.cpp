#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DisplayInfo.h"
#include "Login.h"
#include "SouvenirAndTrip.h"
#include "Database.h"
#include "Team.h"
#include "Dijkstra.h"

#include "BFS.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    //PROCESSING - Setting Main Window Title
	this -> setWindowTitle("Let's Play Football");

    /************************************************************
    * PROCESSING - Assign an image into new QPixmap variable
    ************************************************************/
    QPixmap homePageBackground (":/new/Images/FootballPic4.jpg");
    int ImageLabelW = ui -> Image_Label -> width();
    int ImageLabelH = ui -> Image_Label -> height();


    ///PROCESSING - Set the label to hold the image specified and align center
    ui -> Image_Label -> setAlignment(Qt::AlignCenter);
    ui -> Image_Label -> setPixmap(homePageBackground.scaled
                                  (ImageLabelW, ImageLabelH));


    // DEBUG: Populating Adjacency List
    AdjacencyList* aList;

    // Create Database
    db = Database::getInstance();

    // START POPULATE ADJACENCY LIST
    QSqlQuery vertexQuery;
    QSqlQuery edgeQuery;

    vertexQuery.prepare("SELECT DISTINCT stadiumName from teamInfo");

    // If query executes
    if(vertexQuery.exec())
    {
        // DEBUG
        qDebug() << "---- POPULATE ADJACENCY LIST START -----";

        // Create adjacencylist pointer
        AdjacencyList* list = nullptr;

        // Create Edge pointer
        AdjacencyList::Edge* destination = nullptr;

        // Create Vertex pointer
        AdjacencyList::Vertex* origin = nullptr;


        // While query has stadium names left on list
        while(vertexQuery.next())
        {
            // Create new Vertex Item
            origin = new AdjacencyList::Vertex;

            // Populate Vertex Item with origin stadium
            origin->startCity = vertexQuery.value(0).toString();

            // DEBUG
            qDebug() << "Origin City: " << origin->startCity;

            // Run query to pull that stadium's destination stadiums and their distances
            edgeQuery.prepare("SELECT toStadium, milesBetween FROM teamDistances, teamInfo "
                              "WHERE teamdistances.fromStadium = teamInfo.stadiumName "
                              "AND teamInfo.stadiumName = :origin");

            // Bind origin stadium name to query
            edgeQuery.bindValue(":origin", origin->startCity);

            // If query executes,
            if(edgeQuery.exec())
            {
                // While query has destination stadiums left on list
                while(edgeQuery.exec())
                {
                    // Create new Edge item
                    destination = new AdjacencyList::Edge;

                    // Populate edge item with destination stadium
                    destination->endCity = edgeQuery.value(0).toString();

                    // Populate edge item with destination stadium's distance
                    destination->distance = edgeQuery.value(1).toInt();

                    // DEBUG
                    qDebug() << "Destination City Name: " << destination->endCity;
                    qDebug() << "Destination City Distance: " << destination->distance;

                    // Insert Edge into Vertex
                    origin->destinations->push_back(*destination);

                }// End While Edge
            }
            else
            {
                qDebug() << "PopulateAdjList failed at Edge Query";
            }

            // Insert completed vertex into adjacency list
            list->list.push_back(*origin);

        } // End While Vertex

        // DEBUG: PRINT ENTIRE LIST
        qDebug() << "Starting final print!";
        for(int originsIndex = 0; originsIndex < list->list.size(); originsIndex++)
        {
            qDebug() << "Arriving at: " << list->list.at(0).startCity;
            for(int destinationsIndex = 0; destinationsIndex < list->list.at(originsIndex).destinations->size(); destinationsIndex ++)
            {
                qDebug() << "Destination #" << destinationsIndex << ":";
                qDebug() << "Destination Name: " << list->list.at(originsIndex).destinations->at(destinationsIndex).endCity;
                qDebug() << "Destination Distance: " << list->list.at(originsIndex).destinations->at(destinationsIndex).distance;
            }

        }

    }
    else
    {
        qDebug() << "PopulateAdjList failed at Vertex Query";
    }


    // END POPULATE ADJACENCY LIST


    // DEBUG: Testing BFS
    //BFS bfs(aList);

}

MainWindow::~MainWindow()
{
	delete ui;
}


///This function will create a pointer to the login UI. The mainwindow will be
/// hidden before showing the login page
void MainWindow::on_Admin_Page_PushButton_clicked()
{
    Login *loginUi;
    loginUi = new Login(this);

	hide();

    loginUi -> show();
}

///This function will create a pointer to the DisplayInfo UI. The mainwindow
/// will be hidden before showing the DisplayInfo page
void MainWindow::on_Display_Team_Stadium_Info_clicked()
{
    DisplayInfo *displayUI;
    displayUI = new DisplayInfo(this);

	hide();

    displayUI -> show();
}

///This function will create a pointer to the Travel UI. The mainwindow will be
/// hidden before showing the Travel page
void MainWindow::on_Souvenir_And_Trip_PushButton_clicked()
{
	SouvenirAndTrip *ui;
	ui = new SouvenirAndTrip(this);

	hide();

	ui -> show();
}
