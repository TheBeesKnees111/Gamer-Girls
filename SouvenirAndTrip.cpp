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


///This function will create a pointer to the main window. It will then hide the
///travel page before showing the main window
void SouvenirAndTrip::on_Home_PushButton_clicked()
{
    MainWindow *mainWindow;
    mainWindow = new MainWindow(this);

    hide();

    mainWindow -> show();
}
