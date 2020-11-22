#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DisplayInfo.h"
#include "Login.h"
#include "SouvenirAndTrip.h"
#include "Database.h"
#include "Team.h"
#include "TestAlgos.h"

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

    //TEST DIJKSTRA & DFS
//    testDijkstra();
    testDFS();

    // Create Database
    db = Database::getInstance();

    // Populating Adjacency List. This may belong in the souvenir and trip section
    AdjacencyList* aList = db->GetAdjacencyList();

//    // DEBUG: Testing BFS
//    BFS bfs(aList);
//    bfs.Traverse();

    // TEST DIJKSTRA
    testDijkstra();
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
