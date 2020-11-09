#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DisplayInfo.h"
#include "Login.h"
#include "SouvenirAndTrip.h"
#include "Database.h"
#include "Team.h"

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
    QPixmap homePageBackground (":/new/Images/FootballPic3.jpg");

    int ImageLabelW = ui -> ImageLabel -> width();
    int ImageLabelH = ui -> ImageLabel -> height();


    ///PROCESSING - Set the label to hold the image specified and align center
    ui -> ImageLabel -> setAlignment(Qt::AlignCenter);
    ui -> ImageLabel -> setPixmap(homePageBackground.scaled
                                 (ImageLabelW, ImageLabelH,
                                  Qt::KeepAspectRatio));

    // Create Database
    db = new Database;
}

MainWindow::~MainWindow()
{
    delete ui;
}


///This function will create a pointer to the login UI. The mainwindow will be
/// hidden before showing the login page
void MainWindow::on_AdminPagePushButton_clicked()
{
    Login *loginUi;
    loginUi = new Login(this);

    hide();

    loginUi -> show();
}

///This function will create a pointer to the DisplayInfo UI. The mainwindow
/// will be hidden before showing the DisplayInfo page
void MainWindow::on_DisplayTeamStadiumInfo_clicked()
{
    DisplayInfo *displayUI;
    displayUI = new DisplayInfo(this);

    hide();

    displayUI -> show();
}

///This function will create a pointer to the Travel UI. The mainwindow will be
/// hidden before showing the Travel page
void MainWindow::on_SouvenirAndTripPushButton_clicked()
{
    SouvenirAndTrip *ui;
    ui = new SouvenirAndTrip(this);

    hide();

    ui -> show();
}

///This function will return the ui
Ui::MainWindow* MainWindow::GetUI() const
{
    return ui;
}
