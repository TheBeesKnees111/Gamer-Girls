#ifndef ROUTEDISPLAYER_H
#define ROUTEDISPLAYER_H

#include "Database.h"

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class RouteDisplayer;
}

class RouteDisplayer : public QDialog
{
    Q_OBJECT

public:

    // Displays the route for a trip from origin stadium to the end of the path
    // list, and the total distance for the trip.
    explicit RouteDisplayer(QWidget *parent, QVector<StadiumDistance*> path, QString teamName);

    ~RouteDisplayer();

private:
    Ui::RouteDisplayer *ui;
};

#endif // ROUTEDISPLAYER_H
