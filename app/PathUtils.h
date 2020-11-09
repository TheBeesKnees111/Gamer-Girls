#ifndef PATHUTILS_H
#define PATHUTILS_H

#include <QtSql>
#include <QtCore>
#include "Dijkstras.h"

vector<cityNode> createCitiesFromDatabase();

vector<cityConnection> createConnectionsFromDatabase();

cityGraph createCityGraphFromDatabase();

#endif // PATHUTILS_H
