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
	explicit RouteDisplayer(QWidget *parent, QStringList cities, QList <int> distances);
	~RouteDisplayer();

private:
	Ui::RouteDisplayer *ui;
	QList<int> route;
	int totalDistance;
};

#endif // ROUTEDISPLAYER_H
