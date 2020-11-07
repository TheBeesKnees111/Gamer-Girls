#include "Database.h"

#include <QFileInfo>

Database::Database(): QSqlDatabase(addDatabase("QSQLITE"))
{
    // creating the db file
    QFileInfo db(":/db/nfldb.db");
    // getting the path as a string
    QString DB_PATH = db.absoluteFilePath();
    // printing debug output onto console
    qDebug() << DB_PATH;
    // tell sqlite to use the file
    setDatabaseName(DB_PATH);
    // open the db
    open();
}

