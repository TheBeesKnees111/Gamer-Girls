#include "Database.h"
#include "SouvenirAndTrip.h"
#include "ui_SouvenirAndTrip.h"
#include "mainwindow.h"

SouvenirAndTrip::SouvenirAndTrip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SouvenirAndTrip)
{
	ui->setupUi(this);

	QSqlQuery query;

	query.exec("SELECT stadiumName FROM teamInfo");

	if(!query.exec())
		qDebug() << "Error: TRIPS PAGE -> Adding Team Name to ComboBox ";
	else
	{
		int i = 0;

		while (query.next())
		{
			QString stadiumName = query.value(0).toString();
			qDebug() << ++i << "stadiumName: " << stadiumName;
			ui -> Souvenir_Select_Stadium_ComboBox    -> addItem(stadiumName);
			ui -> Green_Bay_Select_Stadium_ComboBox   -> addItem(stadiumName);
			ui -> Custom_Trip_Select_Stadium_ComboBox -> addItem(stadiumName);
			ui -> Shortest_Distance_Select_Stadium_ComboBox -> addItem(stadiumName);

		}

		// Adjust combo box to size of contents
		ui -> Souvenir_Select_Stadium_ComboBox    -> setSizeAdjustPolicy(QComboBox::AdjustToContents);
		ui -> Green_Bay_Select_Stadium_ComboBox   -> setSizeAdjustPolicy(QComboBox::AdjustToContents);
		ui -> Custom_Trip_Select_Stadium_ComboBox -> setSizeAdjustPolicy(QComboBox::AdjustToContents);
		ui -> Shortest_Distance_Select_Stadium_ComboBox -> setSizeAdjustPolicy(QComboBox::AdjustToContents);

		// sets index to nothing - won't show on dropdown
		ui -> Souvenir_Select_Stadium_ComboBox          -> setCurrentIndex(-1);
		ui -> Green_Bay_Select_Stadium_ComboBox         -> setCurrentIndex(-1);
		ui -> Custom_Trip_Select_Stadium_ComboBox       -> setCurrentIndex(-1);
		ui -> Shortest_Distance_Select_Stadium_ComboBox -> setCurrentIndex(-1);

	}

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
