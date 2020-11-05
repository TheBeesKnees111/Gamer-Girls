#include "Admin.h"
#include "ui_Admin.h"

Admin::Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_AddSouvenirPushButton_clicked()
{

}

void Admin::on_DeleteSouvenirPushButton_clicked()
{

}

void Admin::on_ReadInFromFileButton_clicked()
{

}

///This function will create a pointer to the MainWindow UI. The admin page will be
/// hidden before showing the Main Window
void Admin::on_HomePushButton_clicked()
{
    MainWindow *mainWindow;
    mainWindow = new MainWindow(this);

    hide();

    mainWindow -> show();
}

void Admin::on_UpdateSouvenirPushButton_clicked()
{

}

void Admin::on_UpdateStadiumPushButton_clicked()
{

}
