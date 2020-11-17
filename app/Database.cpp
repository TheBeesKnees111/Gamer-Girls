#include "Database.h"
#include "Team.h"
#include "Stadium.h"
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
vector<StadiumNode> Database::GetStadiums()
{
    vector<StadiumNode> StadiumNodeList;
    QSqlQuery query;
    query.exec("SELECT teamName FROM teamInfo");
    while (query.next())
    {
        // for the value in column 0 of the current row, turn it to a string
        // then create a QString value because it's QtSql
        QString team = query.value(0).toString();
        // converts Qstring to a standard std::string then builds a city node
        // w/ that & puts it in the vector
        StadiumNodeList.push_back({team.toStdString()});
    }

    return StadiumNodeList;

}

vector<StadiumConnection> Database::createConnections()
{
    vector<StadiumConnection> ConnectionNodeList;
    QSqlQuery query;
    query.exec("SELECT fromStadium, toStadium, milesBetween FROM teamDistances " );
    while (query.next())
    {
        // for the value in column 0 of the current row, turn it to an int
        QString fromStadiumID = query.value(0).toString();
        QString toStadiumID = query.value(1).toString();
        int milesBetween = query.value(2).toInt();

        QSqlQuery query;
        query.prepare("SELECT teamName FROM teamInfo "
                  "WHERE stadiumName = (:sName)");
        query.bindValue(":sName", fromStadiumID);
        if(!query.exec())
            qDebug() << "Failed: " << query.lastError();
        if (!query.next())	// Gets the first row
            qDebug() << "No record found for " << fromStadiumID;
        string fromStadium = query.value(0).toString().toStdString();

        query.prepare("SELECT teamName FROM teamInfo "
                  "WHERE stadiumName = (:sName)");
        query.bindValue(":sName", toStadiumID);
        if(!query.exec())
            qDebug() << "Failed: " << query.lastError();
        if (!query.next())	// Gets the first row
            qDebug() << "No record found for " << toStadiumID;
        string toStadium = query.value(0).toString().toStdString();

        // Creating the CityConnection and adding it to the vector
        ConnectionNodeList.push_back({{fromStadium},	// Creating StadiumNode fromStadium
                                      {toStadium},		// crating StadiumNode toStadium
                                      milesBetween });	// creating milesBetween
    }

    return ConnectionNodeList;
}

StadiumGraph Database::createStadiumGraph()
{
    vector<StadiumConnection> edgeList = createConnections();
    map<StadiumNode, vector<StadiumConnection>> adjacencyList;

    // Adjacency list from the edge list
    for(auto edge : edgeList)
    {
        string fromStadium = edge.fromStadium.name;
        string toStadium = edge.toStadium.name;
        int milesBetween = edge.milesBetween;

        // Creates adjacencyList if it doesn't already exist
        adjacencyList[{fromStadium}].push_back(edge);
        // creating the reverse edge
        adjacencyList[{toStadium}].push_back({
                              {toStadium},		// crating StadiumNode toStadium
                              {fromStadium},	// Creating StadiumNode fromStadium
                              milesBetween });
    }
    return {GetStadiums(), adjacencyList};
}

Team* Database::GetTeamByID(const int &teamID)
{
    query.prepare("SELECT teamID, teamName, stadiumName, seatingCap, location, "
                  "conference, division, surfaceType, roofType, dateOpened "
                  "FROM teamInfo "
                  "WHERE teamID = (:teamID)");
    query.bindValue(":teamID", teamID);

    if(query.exec())
    {
        if (!query.next())	// Gets the first row
            qDebug() << "No team found with ID " << teamID;

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
            stadiumDbMap[team->getTeamID()] = stadium;
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
    query.prepare("SELECT stadiumName, seatingCap, location, "
                  "surfaceType, roofType, dateOpened "
                  "FROM teamInfo "
                  "WHERE teamID = (:teamID)");
    query.bindValue(":teamID", teamID);

    if(query.exec())
    {
        if (!query.next())	// Gets the first row
            qDebug() << "No stadium found with ID " << teamID;

        Stadium *stadium = new Stadium;

        stadium -> setStadiumName    (query.value(T_STADIUM_NAME).toString());
        stadium -> setSeatingCapacity(query.value(T_SEATING_CAP).toInt());
        stadium -> setLocation       (query.value(T_LOCATION).toString());
        stadium -> setSurfaceType    (query.value(T_SURFACE_TYPE).toString());
        stadium -> setRoofType       (query.value(T_ROOF_TYPE).toString());
        stadium -> setDateOpened     (query.value(T_DATE_OPENED).toInt());

        stadiumDbMap[teamID] = stadium;
    }
    else
    {
        qDebug() << "Error " << query.lastError().text()
                 << " while executing query " << query.executedQuery();
    }

    return stadiumDbMap[teamID];
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

