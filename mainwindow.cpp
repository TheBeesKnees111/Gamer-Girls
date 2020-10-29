#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_AdminPagePushButton_clicked()
{
    Login *loginUi;

    loginUi = new Login(this);

    hide();

    loginUi -> show();
}

void MainWindow::on_DisplayTeamStadiumInfo_clicked()
{
    DisplayInfo *displayUI;

    displayUI = new DisplayInfo(this);

    hide();

    displayUI -> show();
}

void MainWindow::on_SouvenirAndTripPushButton_clicked()
{
    SouvenirAndTrip *ui;
    ui = new SouvenirAndTrip(this);

    hide();

    ui -> show();
}
