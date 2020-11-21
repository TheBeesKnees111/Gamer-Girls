#include "RouteDisplayer.h"
#include "ui_RouteDisplayer.h"


RouteDisplayer::RouteDisplayer(QWidget *parent, QVector<StadiumDistance*> path ):
    QDialog(parent),
    ui(new Ui::RouteDisplayer),
    route(path)
{
    ui->setupUi(this);

    int rowSize = path.size();
    QTableWidget* tableWidget = ui->Route_List_TableWidget;
     tableWidget->setRowCount(rowSize);
     tableWidget->setColumnCount(2);
//    Items are created outside the table (with no parent widget) and inserted into the table with setItem():
         QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(
             (row+1)*(column+1)));
         tableWidget->setItem(row, column, newItem);
//    If you want to enable sorting in your table widget, do so after you have populated it with items, otherwise sorting may interfere with the insertion order (see setItem() for details).
//    Tables can be given both horizontal and vertical headers. The simplest way to create the headers is to supply a list of strings to the setHorizontalHeaderLabels() and setVerticalHeaderLabels() functions. These will provide simple textual headers for the table's columns and rows. More sophisticated headers can be created from existing table items that are usually constructed outside the table. For example, we can construct a table item with an icon and aligned text, and use it as the header for a particular column:
         QTableWidgetItem *cubesHeaderItem = new QTableWidgetItem(tr("Cubes"));
         cubesHeaderItem->setIcon(QIcon(QPixmap(":/Images/cubed.png")));
         cubesHeaderItem->setTextAlignment(Qt::AlignVCenter);

    // Display trip team name & stadium

    // display total distance traveled

 }

//RouteDisplayer::RouteDisplayer(QWidget *parent, QStringList cities, QList<int> distances) :
//    QDialog(parent),
//    ui(new Ui::RouteDisplayer),
//    route(distances),
//    totalDistance(totalDistance)
//{
//    ui->setupUi(this);

//    QSqlQuery query;
//    query.prepare("SELECT location FROM teamInfo");

//    while(query.next())
//    {
//        QString cityName = query.value(0).toString();

//        ui -> Route_List_TableWidget -> insertRow (ui -> Route_List_TableWidget -> rowCount());
//        ui -> Route_List_TableWidget -> setItem   (ui -> Route_List_TableWidget -> rowCount()-1, 0,
//                                 new QTableWidgetItem(cityName));
//    }
//}

RouteDisplayer::~RouteDisplayer()
{
    delete ui;
}

