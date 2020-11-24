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

    // Imports Team data from any trip. Populates purchase table
    explicit RouteDisplayer(QWidget *parent, QVector<Team*>* teamList);

    ~RouteDisplayer();

private:
    Ui::RouteDisplayer *ui;
};

#endif // ROUTEDISPLAYER_H
