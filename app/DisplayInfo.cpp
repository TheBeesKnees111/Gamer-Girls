#include "DisplayInfo.h"
#include "ui_DisplayInfo.h"

DisplayInfo::DisplayInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayInfo)
{
    ui->setupUi(this);
}

DisplayInfo::~DisplayInfo()
{
    delete ui;
}

///This function will create a pointer to the MainWindow UI. The DisplayInfo
/// page will be hidden before showing the Main Window
void DisplayInfo::on_Home_PushButton_clicked()
{
    MainWindow *mainWindow;
    mainWindow = new MainWindow(this);

    hide();

    mainWindow -> show();

}
