#include "SouvenirAndTrip.h"
#include "ui_SouvenirAndTrip.h"

SouvenirAndTrip::SouvenirAndTrip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SouvenirAndTrip)
{
    ui->setupUi(this);
}

SouvenirAndTrip::~SouvenirAndTrip()
{
    delete ui;
}

void SouvenirAndTrip::on_SearchTeamSouvenirPushButton_clicked()
{

}

void SouvenirAndTrip::on_ConfirmationPushButton_clicked()
{

}

void SouvenirAndTrip::on_ConfirmCustomTripPushButton_clicked()
{

}

void SouvenirAndTrip::on_ConfirmNewEnglandTripPushButton_clicked()
{

}

void SouvenirAndTrip::on_ConfirmCustomShortestTripPushButton_clicked()
{

}

void SouvenirAndTrip::on_ConfirmMSTTrip_clicked()
{

}

void SouvenirAndTrip::on_ConfirmMinnesotaTripPushButton_clicked()
{

}

void SouvenirAndTrip::on_ConfirmLosAngelesRamsTripPushButton_clicked()
{

}

///This function will create a pointer to the main window. It will then hide the
///travel page before showing the main window
void SouvenirAndTrip::on_HomePushButton_clicked()
{
    MainWindow *mainWindow;
    mainWindow = new MainWindow(this);

    hide();

    mainWindow -> show();
}
