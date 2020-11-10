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


///This function will create a pointer to the MainWindow UI. The admin page will be
/// hidden before showing the Main Window
void Admin::on_Home_PushButton_clicked()
{
    MainWindow *mainWindow;
    mainWindow = new MainWindow(this);

    hide();

    mainWindow -> show();
}
