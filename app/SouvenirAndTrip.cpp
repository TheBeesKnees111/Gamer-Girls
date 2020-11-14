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
	query.exec("SELECT teamName, stadiumName FROM teamInfo");

	if(!query.exec())
		qDebug() << "Error: TRIPS PAGE -> Adding Team Name to ComboBox ";
	else
	{//begin else

		while (query.next())
		{
			QString teamName    = query.value(0).toString();
			QString stadiumName = query.value(1).toString();

			ui -> Souvenir_Select_Team_ComboBox       -> addItem(teamName);
			ui -> Green_Bay_Select_Stadium_ComboBox   -> addItem(stadiumName);
			ui -> Custom_Trip_Select_Stadium_ComboBox -> addItem(stadiumName);
			ui -> Shortest_Distance_Select_Stadium_ComboBox -> addItem(stadiumName);

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
		  QListWidgetItem *listItem = new QListWidgetItem(it.next(), ui -> Select_Cities_ListWidget);
		  listItem->setCheckState(Qt::Unchecked);
		  ui->Select_Cities_ListWidget->addItem(listItem);
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

void SouvenirAndTrip::on_Souvenir_Select_Team_ComboBox_currentIndexChanged(int teamID)
{
	teamID++;
	QSqlQuery query;

	query.prepare("SELECT souvenirID, itemName, itemPrice FROM souvenirs "
				  "WHERE teamID = :teamID");

	query.bindValue(":teamID", teamID);

	if(!query.exec())
		qDebug() << "Failed: " << teamID;

	else
	{
		for(int index = 0; index <=12; index++)
		{
			query.next();
			int souvenirID       = query.value(index++).toInt();
			QString souvenirName = query.value(index++).toString();
			double souvenirPrice = query.value(index++).toDouble();

			query.next();
			qDebug() << "souvenirID   : " << souvenirID;
			qDebug() << "souvenirName : " << souvenirName;
			qDebug() << "souvenirPrice: " << souvenirPrice;
			qDebug() << "";
		}

	}

}
