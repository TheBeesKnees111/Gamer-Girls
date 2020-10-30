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

void DisplayInfo::on_PrintAllTeamsPushButton_clicked()
{

}

void DisplayInfo::on_PrintAFCTeamsPushButton_clicked()
{

}

void DisplayInfo::on_PrintNFCTeamsPushButton_clicked()
{

}

void DisplayInfo::on_PrintNorthNFCTeamsPushButton_clicked()
{

}

void DisplayInfo::on_PrintTeamInforByConferencePushButton_clicked()
{

}

void DisplayInfo::on_PrintStadiumPushButton_clicked()
{

}

void DisplayInfo::on_PrintStadiumByDatePushButton_clicked()
{

}

void DisplayInfo::on_ShowOpenRoofStadiumsPushButton_clicked()
{

}


void DisplayInfo::on_ShowBermudaGrassStadiumsPushButton_clicked()
{

}

void DisplayInfo::on_HomePushButton_clicked()
{
    MainWindow *mainWindow;
    mainWindow = new MainWindow(this);

    hide();

    mainWindow -> show();

}
