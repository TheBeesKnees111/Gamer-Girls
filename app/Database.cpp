#include "Database.h"
#include "Team.h"
#include "Stadium.h"
#include "StadiumDistance.h"
#include <QFileInfo>
#include <QSqlError>
#include <QFileDialog>
#include <QVector>

// singleton design pattern
// ensures that there's only ever 1 instance of this class
// If we create multiple instances of the db, then it will close the connection
// to the db file & can break the queries.  This also allows us to share the
// caches across the entire application.  Without it, creating a new instance
// will create new (empty) caches.

// The adjacency list relies on pointers to our types.  In order for it to work
// properly, we can only have one object for a given stadium (ex: there should
// only be one object with stadiumName "AT&T Field").  The caches help to ensure
// this.
// this gets rid of the terminal error messages:
// QSqlDatabasePrivate::removeDatabase: connection 'qt_sql_default_connection' is still in use, all queries will cease to work.
// QSqlDatabasePrivate::addDatabase: duplicate connection name 'qt_sql_default_connection', old connection removed.
Database *Database::instance = nullptr;

Database *Database::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Database;
    }
    return instance;
}

Database::Database(): QSqlDatabase(addDatabase("QSQLITE"))
{
    // Set path
    //NOTE IF YOU ARE ON WINDOWS USE WINDOWSPATHFILE, IF YOU ARE ON MAC USE MACPATHFILE
    //    QString windowsPathFile =  "/db/NFLdb.db";
    //    setDatabaseName(QDir::currentPath() + windowsPathFile);
    QString macPathFile = "/db";
    setDatabaseName(QDir::currentPath() + macPathFile);

    qDebug() << QDir::currentPath() + "/db/nfldb.db";

    // Print error if database does not open
    if (!open())
    {
        qDebug() << "Connection to database failed";
    }
    else
    {
        qDebug() << "Connection to database succeeded";
    }
}

// DIJKSTRA ALGO
// Creates a vector of Stadiums if they don't already exist.
QVector<Stadium*> Database::getStadiums()
{
    if (stadiumDbCacheByID.isEmpty())
        runGetAllTeamsAndStadiums();
    return stadiumDbCacheByID.values().toVector();
}

// Creates a StadiumDistance node and
// adds it to a vector of all edges (the edgelist of StadiumDistance)
QVector<StadiumDistance*> Database::getStadiumDistances()
{
    if (stadiumDistanceCache.isEmpty())
        runGetAllStadiumDistances();
    return stadiumDistanceCache.values().toVector();

}


StadiumDistance *Database::getStadiumDistanceByID(int distanceID)
{
    if (!stadiumDistanceCache.contains(distanceID))
    {
        runGetAllStadiumDistances();
    }
    return stadiumDistanceCache[distanceID];
}

Team* Database::GetTeamByID(const int &teamID)
{
    if (!teamDbCache.contains(teamID))
    {
        runGetAllTeamsAndStadiums();
    }
    return teamDbCache[teamID];
}

// Uber object for use in all display sections. Will overwrite upon return to homepage
QVector<Team*> Database::GetTeams()
{
    if (teamDbCache.isEmpty())
        runGetAllTeamsAndStadiums();
    return teamDbCache.values().toVector();
}

Stadium* Database::getStadiumByID(const int& teamID)
{
    if (!stadiumDbCacheByID.contains(teamID))
        runGetAllTeamsAndStadiums();
    return stadiumDbCacheByID[teamID];
}

Stadium *Database::getStadiumByName(const QString stadiumName)
{
    if (!stadiumDbCacheByName.contains(stadiumName))
        runGetAllTeamsAndStadiums();

    return stadiumDbCacheByName[stadiumName];
}

// For use in admin section
QVector<Souvenir*> Database::getSouvenirs()
{
    // look at the teams & stadiums setup if you want to cache your
    // data for easier reference & better integration w/ the QMap & QHash
    QVector<Souvenir*> v(NULL);

    return v;
}

//
Souvenir* Database::getSouvenierByID(int souvenirID)
{
    return nullptr;
}

QVector<Purchases*> Database::getPurchases()
{
    QVector<Purchases*> v(NULL);

    return v;
}

Purchases* Database::getPurchasesByID(int purchaseID)
{
    return nullptr;
}

// Add souvenir to database
void AddSouvenir(const QString &team, const QString &souvenirName, const QString &price)
{

}

// Change price of souvenir in database
void UpdateSouvenirPrice(const QString &SouvenirName, const QString teamName, const QString &price)
{

}

// Remove souvenir from database
void DeleteSouvenir(const QString &SouvenirName, const QString &teamName)
{

}

// Get Info for one team (Requirement 2)
Team* GetSingleTeam(const QString &teamName);

// Get all teams ordered by team name (Requirement 3)
QVector<Team*> GetTeamsOrderByName()
{
    QVector<Team*> v(NULL);

    return v;
}

// Get all teams and stadiums ordered by stadium name (Requirement 4)
QVector<Team*> GetTeamsOrderByStadium()
{
    QVector<Team*> v(NULL);

    return v;
}

// Get all AFC Teams sorted by team name (Requirement 5)
QVector<Team*> GetAFCTeamsOrderByTeamName()
{
    QVector<Team*> v(NULL);

    return v;
}

// Get all NFC teams sorted by team name (Requirement 6)
QVector<Team*> GetNFCTeamsOrderByTeamName()
{
    QVector<Team*> v(NULL);

    return v;
}

// Get all NFC North teams ordered by team name (Requirement 7)
QVector<Team*> GetNorthNFCTeamsOrderByTeamName()
{
    QVector<Team*> v(NULL);

    return v;
}

// Get all stadiums sorted by date opened (Requirement 8)
QVector<Team*> GetStadiumsOrderByDateOpened()
{
    QVector<Team*> v(NULL);

    return v;
}

// Get all open roof stadiums (Requirement 9)
QVector<Team*> GetOpenRoofStadiums()
{
    QVector<Team*> v(NULL);

    return v;
}

// Get stadiums ordered by seating capacity (Requirement 10)
QVector<Team*> GetStadiumsOrderBySeatingCap()
{
    QVector<Team*> v(NULL);

    return v;
}

// Get teams ordered by conference (Requirement 11)
QVector<Team*> GetTeamsOrderByConference()
{
    QVector<Team*> v(NULL);

    return v;
}

// Get teams with bermuda grass surface type (Requirement 12)
QVector<Team*> GetBermudaGrassTeams()
{
    QVector<Team*> v(NULL);

    return v;
}

// Get all souvenirs for one team (Requirement 13)
Team* GetSingleTeamSouvenirs(const QString &teamName)
{
    return nullptr;
}


// Creates QMap caches of team and stadium objects.
// These can then be used thruout the application whenever needed.
void Database::runGetAllTeamsAndStadiums()
{
    // RAII resource aquisition is initialization (constructor/destructor)
    // constructor will aquire resources to run the query,
    // destructor will release those resources
    // query should be declared in the function where it's used so the resources
    // are cleaned up properly, not accidentally reused across methods.
    QSqlQuery query;
    query.prepare("SELECT teamID, teamName, stadiumName, seatingCap, location, "
                  "conference, division, surfaceType, roofType, dateOpened "
                  "FROM teamInfo ");
    if(query.exec())
    {
        while(query.next())
        {
            // for the value in column 0 of the current row, turn it to a string
            // then create a QString value because it's QtSql
            int teamID = query.value(0).toInt();
            QString teamName = query.value(1).toString();
            QString stadiumName = query.value(2).toString();
            int seatingCap = query.value(3).toInt();
            QString location = query.value(4).toString();
            QString conference = query.value(5).toString();
            QString division = query.value(6).toString();
            QString surfaceType = query.value(7).toString();
            QString roofType = query.value(8).toString();
            int dateOpened = query.value(9).toInt();

            // TODO set object parents for these so they get cleaned up
            Team *team = new Team;
            Stadium *stadium = new Stadium;

            team->setTeamID(teamID);
            //    stadium->setTeamID(teamID); //TODO add this method to Stadium
            team->setTeamName(teamName);
            stadium->setStadiumName(stadiumName);
            stadium->setSeatingCapacity(seatingCap);
            stadium->setLocation(location);
            team->setConference(conference);
            team->setDivision(division);
            stadium->setSurfaceType(surfaceType);
            stadium->setRoofType(roofType);
            stadium->setDateOpened(dateOpened);

            team->setStadium(stadium);
            //    stadium->setTeam(team); //TODO add this method to Stadium

            teamDbCache[teamID] = team;
            stadiumDbCacheByID[teamID] = stadium;
            stadiumDbCacheByName[stadium->getStadiumName()] = stadium;
        }
    }
    else
    {
        qDebug() << "Error " << query.lastError().text()
                 << " while executing query " << query.executedQuery();
    }
}

// creates all StadiumDistances if they don't already exist
void Database::runGetAllStadiumDistances()
{
    StadiumDistance *stadiumDistance = nullptr;
    QSqlQuery query;
    query.prepare("SELECT distanceID, fromStadium, toStadium, milesBetween "
                  "FROM teamDistances ");
    //    query.bindValue(":distanceID", distanceID);
    qDebug() << "runGetAllStadiumDistances ";
    if(query.exec())
    {
        while(query.next())
        {
            stadiumDistance = new StadiumDistance;
            int distanceID = query.value(0).toInt();
            stadiumDistance->setDistanceID(distanceID);
            stadiumDistance->setFromStadium(getStadiumByName(query.value(1).toString()));
            stadiumDistance->setToStadium(getStadiumByName(query.value(2).toString()));
            stadiumDistance->setDistance(query.value(3).toInt());

            stadiumDistanceCache[distanceID] = stadiumDistance;
        }
    }
    else
    {
        qDebug() << "Error " << query.lastError().text()
                 << " while executing query " << query.executedQuery();
    }
}
