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

	/***************************************************************************
	 * INITIALIZING COMBO BOXES
	 * -------------------------------------------------------------------------
	 * Initialize comboboxes to hold stadium names and team names
	 **************************************************************************/
	query.exec("SELECT teamName FROM teamInfo");

	if(!query.exec())
		qDebug() << "Error: TRIPS PAGE -> Adding Team Name to ComboBox ";
	else
	{//begin else

		while (query.next())
		{
			QString teamName    = query.value(0).toString();

			ui -> Souvenir_Select_Team_ComboBox       -> addItem(teamName);
			ui -> Green_Bay_Select_Stadium_ComboBox   -> addItem(teamName);
			ui -> Custom_Trip_Select_Stadium_ComboBox -> addItem(teamName);
			ui -> Shortest_Distance_Select_Stadium_ComboBox -> addItem(teamName);

		}

		// Adjust combo box to size of contents
		ui -> Souvenir_Select_Team_ComboBox       -> setSizeAdjustPolicy(QComboBox::AdjustToContents);
		ui -> Green_Bay_Select_Stadium_ComboBox   -> setSizeAdjustPolicy(QComboBox::AdjustToContents);
		ui -> Custom_Trip_Select_Stadium_ComboBox -> setSizeAdjustPolicy(QComboBox::AdjustToContents);
		ui -> Shortest_Distance_Select_Stadium_ComboBox -> setSizeAdjustPolicy(QComboBox::AdjustToContents);

		// sets index to nothing - won't show on dropdown
		ui -> Souvenir_Select_Team_ComboBox             -> setCurrentIndex(0);
		ui -> Green_Bay_Select_Stadium_ComboBox         -> setCurrentIndex(0);
		ui -> Custom_Trip_Select_Stadium_ComboBox       -> setCurrentIndex(0);
		ui -> Shortest_Distance_Select_Stadium_ComboBox -> setCurrentIndex(0);

	}//begin else

	/***************************************************************************
	 * INITIALIZING CHECK BOXES
	 * -------------------------------------------------------------------------
	 * Create check boxes so user can select cities to go to
	 **************************************************************************/
	QStringList  itemLabels;

	query.prepare("SELECT stadiumName FROM teamInfo");

	//Initialize items that will be added to the list view
	if(!query.exec())
	{
		qDebug() << "Chck boxes broke ";
	}
	else
	{
		while(query.next())
		{
			itemLabels.push_back(query.value(0).toString());
			qDebug() << "query.value(0).toString()" << query.value(0).toString();
		}
	}

	QStringListIterator it(itemLabels);
	while (it.hasNext())
	{
		listItem = new QListWidgetItem(it.next(), ui ->
		Select_Cities_ListWidget);

		listItem -> setCheckState(Qt::Unchecked);
		ui->Select_Cities_ListWidget->addItem(listItem);
	}

	ui -> Select_Cities_ListWidget -> sortItems();


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

			/*********************************************
			 ************** CUSTOM TRIP TAB **************
			 *********************************************/
///For CUSTOM TRIP push button clicked
/// Will call rout displayer and show cities the user has selected to travel to
void SouvenirAndTrip::on_Confirm_Custom_Trip_PushButton_clicked()
{
	QStringList listOfStadiums;
	QList<int>  listOfDistances;

	for(int index = 0; index < ui -> Select_Cities_ListWidget -> count(); index++)
	{
		if(ui -> Select_Cities_ListWidget -> item(index) -> checkState() == Qt::Checked)
		{
			listOfStadiums.push_back(ui -> Select_Cities_ListWidget -> item(index) -> text());
		}
	}

	while(!listOfStadiums.isEmpty())
	{
		qDebug() << listOfStadiums.first();
		listOfStadiums.pop_front();
	}

}
