#include "RouteDisplayer.h"
#include "ui_RouteDisplayer.h"

RouteDisplayer::RouteDisplayer(QWidget *parent, QStringList cities, QList<int> distances) :
	QDialog(parent),
	ui(new Ui::RouteDisplayer),
	route(distances),
	totalDistance(totalDistance)
{
	ui->setupUi(this);

	QSqlQuery query;
	query.prepare("SELECT location FROM teamInfo");

	while(query.next())
	{
		QString cityName = query.value(Database::T_LOCATION).toString();

		ui -> Route_List_TableWidget -> insertRow (ui -> Route_List_TableWidget -> rowCount());
		ui -> Route_List_TableWidget -> setItem   (ui -> Route_List_TableWidget -> rowCount()-1, 0,
								 new QTableWidgetItem(cityName));

	}

}

RouteDisplayer::~RouteDisplayer()
{
	delete ui;
}

