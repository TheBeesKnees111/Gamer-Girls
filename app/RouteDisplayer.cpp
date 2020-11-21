#include "RouteDisplayer.h"
#include "ui_RouteDisplayer.h"
#include "Team.h"


RouteDisplayer::RouteDisplayer(QWidget *parent, QVector<StadiumDistance*> path, QString teamName):
    QDialog(parent),
    ui(new Ui::RouteDisplayer)
 {
    ui->setupUi(this);
    // create the row size for setup
    int rowSize = path.size();
    // setup row & column sizes
    QTableWidget* tableWidget = ui->Route_List_TableWidget;
    tableWidget->setRowCount(rowSize + 1);
    tableWidget->setColumnCount(2);

    int totalDistance = 0;

    // loops thru the vector of StadiumDistances and displays the team name
    // as well as the stadium
    for (int row = 0; row < path.size(); row++)
    {
        // get & display team name
        QString teamName = path[row]->getFromStadium()->getTeams().first()->getTeamName();
        //    Items are created outside the table (with no parent widget) and inserted into the table with setItem():
        QTableWidgetItem *newItem = new QTableWidgetItem(teamName);
        tableWidget->setItem(row, 0, newItem);
        // get & display stadium name
        //    Items are created outside the table (with no parent widget) and inserted into the table with setItem():
        newItem = new QTableWidgetItem(path[row]->getFromStadium()->getStadiumName());
        tableWidget->setItem(row, 1, newItem);
        // calculate total distance
        totalDistance += path[row]->getDistance();
    }

    // calculate last team & stadium name
    QTableWidgetItem *newItem = new QTableWidgetItem(teamName);
    tableWidget->setItem(rowSize, 0, newItem);
    newItem = new QTableWidgetItem(path[rowSize - 1]->getToStadium()->getStadiumName());
    tableWidget->setItem(rowSize, 1, newItem);

    // out put distance
    ui->Total_Distance_Label->setText(QString("%1").arg(totalDistance));

    // resize based on table contents
    ui->Route_List_TableWidget->horizontalHeader()->setSectionResizeMode
            (QHeaderView::ResizeToContents);
}

RouteDisplayer::~RouteDisplayer()
{
    delete ui;
}

