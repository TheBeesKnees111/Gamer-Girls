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

void Admin::on_UpdatePushButton_clicked()
{

}

void Admin::on_ReadInFromFileButton_clicked()
{

}

void Admin::on_HomePushButton_clicked()
{
    MainWindow *mainWindow;
    mainWindow = new MainWindow(this);

    hide();

    mainWindow -> show();
}

void Admin::on_UpdateStadiumInfoPushButton_clicked()
{

}
