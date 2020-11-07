#ifndef DATABASE_H
#define DATABASE_H

#include "Header.h"
#include <QSqlDatabase>
#include <QObject>

class Database : public QSqlDatabase
{
    Q_OBJECT

public:

    Database();
};

#endif // DATABASE_H
