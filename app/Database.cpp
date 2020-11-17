#include "Database.h"
#include "Team.h"
#include "Stadium.h"
#include "StadiumDistance.h"
#include <QFileInfo>
#include <QSqlError>
#include <QFileDialog>
#include <QVector>


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
QVector<Stadium*> Database::getStadiums()
{
    QVector<Stadium*> StadiumNodeList;
    QSqlQuery query;
    query.exec("SELECT teamID FROM teamInfo");
    while (query.next())
    {
        // for the value in column 0 of the current row, turn it to a string
        // then create a QString value because it's QtSql
        int teamID = query.value(0).toInt();
        qDebug() << "teamID for getStadiums " << teamID;
        Stadium* stadium = getStadiumByID(teamID);
        // converts Qstring to a standard std::string then builds a city node
        // w/ that & puts it in the vector
        StadiumNodeList.push_back(stadium);
    }
    return StadiumNodeList;
}

QVector<StadiumDistance*> Database::createConnections()
{
    QVector<StadiumDistance*> ConnectionNodeList;
    QSqlQuery query;
    query.exec("SELECT distanceID FROM teamDistances " );
    while (query.next())
    {
        // for the value in column 0 of the current row, turn it to an int
        int distanceID = query.value(0).toInt();
        qDebug() << "DistanceID for createConnections " << distanceID;
        StadiumDistance* stadiumDistance = getStadiumDistanceByID(distanceID);
        ConnectionNodeList.push_back(stadiumDistance);
    }

    return ConnectionNodeList;
}

StadiumGraph Database::createStadiumGraph()
{
    QVector<StadiumDistance*> edgeList = createConnections();
    QMap<Stadium*, QVector<StadiumDistance*>> adjacencyList;

    // Adjacency list from the edge list
    for(auto edge : edgeList)
    {
        Stadium* fromStadium = edge->getFromStadium();
//        Stadium* toStadium = edge->getToStadium();
//        int milesBetween = edge->getDistance();

        // Creates adjacencyList if it doesn't already exist
        adjacencyList[fromStadium].push_back(edge);
// creating the reverse edge
//        adjacencyList[toStadium].push_back(edge);
    }
    // creating graph when returning
    return {getStadiums(), adjacencyList};
}

StadiumDistance *Database::getStadiumDistanceByID(int distanceID)
{
    StadiumDistance *stadiumDistance = nullptr;
    QSqlQuery query;
    query.prepare("SELECT distanceID, fromStadium, toStadium, milesBetween "
                  "FROM teamDistances "
                  "WHERE distanceID = (:distanceID)");
    query.bindValue(":distanceID", distanceID);
    qDebug() << "DistanceID for getStadiumDistanceByID " << distanceID;
    if(query.exec())
    {
        if (!query.next())	// Gets the first row
            qDebug() << "No team found with ID " << distanceID;

//        Team *team = new Team;
        stadiumDistance = new StadiumDistance;

        stadiumDistance->setDistanceID(distanceID);
        stadiumDistance->setFromStadium(getStadiumByName(query.value(1).toString()));
        stadiumDistance->setToStadium(getStadiumByName(query.value(2).toString()));
        stadiumDistance->setDistance(query.value(3).toInt());

//        teamDbMap[teamID] = team;
    }
    else
    {
        qDebug() << "Error " << query.lastError().text()
                 << " while executing query " << query.executedQuery();
    }

//    return teamDbMap[teamID];
    return stadiumDistance;
 }

Team* Database::GetTeamByID(const int &teamID)
{
    query.prepare("SELECT teamID, teamName, stadiumName, seatingCap, location, "
                  "conference, division, surfaceType, roofType, dateOpened "
                  "FROM teamInfo "
                  "WHERE teamID = (:teamID)");
    query.bindValue(":teamID", teamID);
    qDebug() << "teamID for getteambyid " << teamID;

    if(query.exec())
    {
        if (!query.next())	// Gets the first row
            qDebug() << "No team found with ID " << teamID;

        Team *team = new Team;
        Stadium *stadium = new Stadium;

        // FIXME These constants are only valid for this query, they won't be
        // valid for any other queries.
        // Another query might have the columns in a different order, so the
        // #'s in these constants won't correspond to the columns.
        team->setTeamID(query.value(T_ID).toInt());
        team->setTeamName(query.value(T_TEAM_NAME).toString());
        stadium->setStadiumName(query.value(T_STADIUM_NAME).toString());
        stadium->setSeatingCapacity(query.value(T_SEATING_CAP).toInt());
        stadium->setLocation(query.value(T_LOCATION).toString());
        team->setConference(query.value(T_CONFERENCE).toString());
        team->setDivision(query.value(T_DIVISION).toString());
        stadium->setSurfaceType(query.value(T_SURFACE_TYPE).toString());
        stadium->setRoofType(query.value(T_ROOF_TYPE).toString());
        stadium->setDateOpened(query.value(T_DATE_OPENED).toInt());

        team->setStadium(stadium);

        teamDbMap[teamID] = team;
    }
    else
    {
        qDebug() << "Error " << query.lastError().text()
                 << " while executing query " << query.executedQuery();
    }

    return teamDbMap[teamID];
}

// Uber object for use in all display sections. Will overwrite upon return to homepage
QVector<Team*> Database::GetTeams()
{
    query.prepare("SELECT teamID, teamName, stadiumName, seatingCap, location, "
                  "conference, division, surfaceType, roofType, dateOpened "
                  "FROM teamInfo ");
    if(query.exec())
    {
        while(query.next())
        {
            Team *team = new Team;
            Stadium *stadium = new Stadium;

            team->setTeamID(query.value(T_ID).toInt());
            team->setTeamName(query.value(T_TEAM_NAME).toString());
            stadium->setStadiumName(query.value(T_STADIUM_NAME).toString());
            stadium->setSeatingCapacity(query.value(T_SEATING_CAP).toInt());
            stadium->setLocation(query.value(T_LOCATION).toString());
            team->setConference(query.value(T_CONFERENCE).toString());
            team->setDivision(query.value(T_DIVISION).toString());
            stadium->setSurfaceType(query.value(T_SURFACE_TYPE).toString());
            stadium->setRoofType(query.value(T_ROOF_TYPE).toString());
            stadium->setDateOpened(query.value(T_DATE_OPENED).toInt());

            team->setStadium(stadium);

            teamDbMap[team->getTeamID()] = team;
            stadiumDbMapByID[team->getTeamID()] = stadium;
            stadiumDbMapByName[stadium->getStadiumName()] = stadium;
        }
    }
    else
    {
        qDebug() << "Error " << query.lastError().text()
                 << " while executing query " << query.executedQuery();
    }


    return teamDbMap.values().toVector();
}

Stadium* Database::getStadiumByID(const int& teamID)
{
    // TODO check to see if this teamID is already in the map
    // if it's in the map, return what's in the map, otherwise run the query
    // might be possible to create separate function for it so can use for both
    // Also do for one below this (getStadiumByName)
    query.prepare("SELECT stadiumName, seatingCap, location, "
                  "surfaceType, roofType, dateOpened "
                  "FROM teamInfo "
                  "WHERE teamID = (:teamID)");
    query.bindValue(":teamID", teamID);

    if(query.exec())
    {
        if (!query.next())	// Gets the first row
            qDebug() << "No stadium found with ID " << teamID;
        qDebug() << "teamID for getStadiumByID " << teamID;

        Stadium *stadium = new Stadium;

        stadium -> setStadiumName    (query.value(0).toString());
        stadium -> setSeatingCapacity(query.value(1).toInt());
        stadium -> setLocation       (query.value(2).toString());
        stadium -> setSurfaceType    (query.value(3).toString());
        stadium -> setRoofType       (query.value(4).toString());
        stadium -> setDateOpened     (query.value(5).toInt());

        stadiumDbMapByID[teamID] = stadium;
        stadiumDbMapByName[stadium->getStadiumName()] = stadium;
    }
    else
    {
        qDebug() << "Error " << query.lastError().text()
                 << " while executing query " << query.executedQuery();
    }

    return stadiumDbMapByID[teamID];
}

Stadium *Database::getStadiumByName(const QString stadiumName)
{
    query.prepare("SELECT teamID, stadiumName, seatingCap, location, "
                  "surfaceType, roofType, dateOpened "
                  "FROM teamInfo "
                  "WHERE stadiumName = (:stadiumName)");
    query.bindValue(":stadiumName", stadiumName);

    if(query.exec())
    {
        if (!query.next())	// Gets the first row
            qDebug() << "db::getStadiumByName No stadium found with ID " << stadiumName;

        Stadium *stadium = new Stadium;

        int teamID                 = (query.value(0).toInt());
        stadium -> setStadiumName    (query.value(1).toString());
        stadium -> setSeatingCapacity(query.value(2).toInt());
        stadium -> setLocation       (query.value(3).toString());
        stadium -> setSurfaceType    (query.value(4).toString());
        stadium -> setRoofType       (query.value(5).toString());
        stadium -> setDateOpened     (query.value(6).toInt());

        stadiumDbMapByID[teamID] = stadium;
        stadiumDbMapByName[stadiumName] = stadium;
    }
    else
    {
        qDebug() << "Error " << query.lastError().text()
                 << " while executing query " << query.executedQuery();
    }

    return stadiumDbMapByName[stadiumName];
}

// For use in admin section
QVector<Souvenir*> Database::getSouvenirs()
{
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


// TODO
int Database::GetMilesBetweenStadiums(const QString &origin, const QString &destination)
{
    query.prepare("SELECT milesBetween FROM teamDistances "
                  "WHERE fromStadium = (:fromStadium) "
                  "and toStadium = (:toStadium)");

    query.bindValue(":fromStadium", origin);
    query.bindValue(":toStadium", destination);

    if (query.exec())
    {
        if (!query.next())	// Gets the first row
            qDebug() << "No distance found for " << origin << " to " << destination;
        int milesBetween = query.value(0).toInt();
        return milesBetween;
    }
    else
    {
        qDebug() << "Error " << query.lastError().text()
                 << " while executing query " << query.executedQuery();
        return -1;
    }
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

