#include "Database.h"
#include "Team.h"
#include "Stadium.h"
#include "StadiumDistance.h"
#include "Souvenir.h"
#include <QFileInfo>
#include <QSqlError>
#include <QFileDialog>
#include <QVector>
#include "AdjacencyList.h"

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
		QString windowsPathFile =  "/db/NFLdb.db";
		setDatabaseName(QDir::currentPath() + windowsPathFile);
//    QString macPathFile = "/db";
//    setDatabaseName(QDir::currentPath() + macPathFile);
//    qDebug() << QDir::currentPath() + macPathFile;

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

int GetTeamIDByCityName(QString location)
{
    QSqlQuery query;

    query.prepare("SELECT teamID FROM teamInfo WHERE location = :location");
    query.bindValue(":location", location);

    if(!query.exec())
        qDebug() << query.lastError();

    return query.value(0).toInt();
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

//Return team name by ID
QString Database::GetTeamNameByID(const int& teamID)
{

	query.prepare("SELECT teamName FROM teamInfo "
				  "WHERE teamID = (:teamID)");
	query.bindValue(":teamID", teamID);

	if(!query.exec())
		qDebug() << "ERROR - Database::GetTeamNameByID " << query.lastError();

	return query.value(0).toString();
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
void Database::AddSouvenir(const QString &team, const QString &souvenirName, const QString &price)
{

}

// Change price of souvenir in database
void Database::UpdateSouvenirPrice(const QString &SouvenirName, const QString teamName, const QString &price)
{

}

// Remove souvenir from database
void Database::DeleteSouvenir(const QString &SouvenirName, const QString &teamName)
{

}

// Get all team names (for use in comboboxes)
QStringList Database::GetTeamNames()
{
    QSqlQuery query;
    QStringList teamNames;
    query.prepare("SELECT teamName from teaminfo order by teamName");

    if(query.exec())
    {
        while(query.next())
        {
            // Add name to stringlist
            teamNames.append(query.value(0).toString());
        }
    }
    else
    {
        qDebug() << "GetTeamNames() failed";
    }

    return teamNames;
}

// Get Info for one team (Requirement 2)
Team* Database::GetSingleTeam(const QString &teamName)
{
    QSqlQuery query;
    Team* team = new Team;
    Stadium* stadium = new Stadium;
    query.prepare("select * from teaminfo where teamname = :teamName");
    query.bindValue(":teamName", teamName);

    // Execute
    if(query.exec())
    {
        while(query.next())
        {
            team->setTeamName(query.value(1).toString());
            stadium->setStadiumName(query.value(2).toString());
            stadium->setSeatingCapacity(query.value(3).toInt());
            stadium->setLocation(query.value(4).toString());
            team->setConference(query.value(5).toString());
            team->setDivision(query.value(6).toString());
            stadium->setSurfaceType(query.value(7).toString());
            stadium->setRoofType(query.value(8).toString());
            stadium->setDateOpened(query.value(9).toInt());
            team->setStadium(stadium);
        }
    }
    else
    {
        qDebug() << "GetSingleTeam failed";
    }

    return team;
}

// TODO, USED COMBOBOX LABELS FOR THIS ONE. MIGHT NOT NEED THIS METHOD
// Get all teams ordered by team name (Requirement 3)
QVector<Team*>* Database::GetTeamsOrderByName()
{
    QVector<Team*> *v(NULL);

    return v;
}

// Get all teams and stadiums ordered by stadium name (Requirement 4)
QVector<Team*>* Database::GetTeamsOrderByStadium()
{
    QSqlQuery query;
    QVector<Team*>* teams = new QVector<Team*>;
    Team* team = nullptr;
    Stadium* stadium = nullptr;

    query.prepare("SELECT stadiumName, teamName FROM teamInfo order by stadiumName");

    if(query.exec())
    {
        while(query.next())
        {
            team = new Team;
            stadium = new Stadium;
            stadium->setStadiumName(query.value(0).toString());
            team->setTeamName(query.value(1).toString());
            team->setStadium(stadium);
            teams->push_back(team);
        }
    }

    return teams;
}

// Get all AFC Teams sorted by team name (Requirement 5)
QVector<Team*>* Database::GetAFCTeamsOrderByTeamName()
{
    QSqlQuery query;
    QVector<Team*>* teams = new QVector<Team*>;
    Team* team = nullptr;

    query.prepare("SELECT teamName, conference FROM teamInfo WHERE conference = 'American Football Conference' ORDER BY teamName");

    if(query.exec())
    {
        while(query.next())
        {
            team = new Team;
            team->setTeamName(query.value(0).toString());
            team->setConference(query.value(1).toString());
            teams->push_back(team);
        }
    }
    else
    {
        qDebug() << "GetAFCTeamsOrderByTeamName Failed";
    }

    return teams;
}

// Get all NFC teams sorted by team name (Requirement 6)
QVector<Team*>* Database::GetNFCTeamsOrderByTeamName()
{
    QSqlQuery query;
    QVector<Team*>* teams = new QVector<Team*>;
    Team* team = nullptr;

    query.prepare("SELECT teamName, conference FROM teamInfo WHERE conference = 'National Football Conference' ORDER BY teamName");

    if(query.exec())
    {
        while(query.next())
        {
            team = new Team;
            team->setTeamName(query.value(0).toString());
            team->setConference(query.value(1).toString());
            teams->push_back(team);
        }
    }
    else
    {
        qDebug() << "GetNFCTeamsOrderByTeamName Failed";
    }

    return teams;
}

// Get all NFC North teams ordered by team name (Requirement 7)
QVector<Team*>* Database::GetNorthNFCTeamsOrderByTeamName()
{
    QSqlQuery query;
    QVector<Team*>* teams = new QVector<Team*>;
    Team* team = nullptr;

    query.prepare("SELECT teamName, division FROM teamInfo WHERE division = 'NFC North' ORDER BY teamName;");

    if(query.exec())
    {
        while(query.next())
        {
            team = new Team;
            team->setTeamName(query.value(0).toString());
            team->setConference(query.value(1).toString());
            teams->push_back(team);
        }
    }
    else
    {
        qDebug() << "GetNFCNORTHTeamsOrderByTeamName Failed";
    }

    return teams;
}

// Get all stadiums sorted by date opened (Requirement 8)
QVector<Team*>* Database::GetStadiumsOrderByDateOpened()
{
    QSqlQuery query;
    QVector<Team*>* teams = new QVector<Team*>;
    Team* team = nullptr;
    Stadium* stadium = nullptr;

    query.prepare("SELECT stadiumName, teamName, dateOpened FROM teaminfo ORDER BY dateOpened;");

    if(query.exec())
    {
        while(query.next())
        {
            team = new Team;
            stadium = new Stadium;
            stadium->setStadiumName(query.value(0).toString());
            team->setTeamName(query.value(1).toString());
            stadium->setDateOpened(query.value(2).toInt());
            team->setStadium(stadium);
            teams->push_back(team);
        }
    }
    else
    {
        qDebug() << "GetStadiumsOrderByDateOpened Failed";
    }

    return teams;
}

// Get all open roof stadiums (Requirement 9)
QVector<Team*>* Database::GetOpenRoofStadiums()
{
    QVector<Team*>* teams = new QVector<Team*>;
    Team* team = nullptr;
    Stadium* stadium = nullptr;

    query.prepare("SELECT stadiumName, teamName, roofType FROM teamInfo WHERE roofType = 'Open'");

    if(query.exec())
    {
        while(query.next())
        {
            team = new Team;
            stadium = new Stadium;
            stadium->setStadiumName(query.value(0).toString());
            team->setTeamName(query.value(1).toString());
            stadium->setRoofType(query.value(2).toString());
            team->setStadium(stadium);
            teams->push_back(team);
        }
    }
    else
    {
        qDebug() << "GetOpenRoofStadiums Failed";
    }

    return teams;
}

// Get number of open roof stadiums (Requirement 9)
int Database::GetOpenStadiumCount()
{
    int count = 0;

    query.prepare("SELECT DISTINCT stadiumName FROM teaminfo WHERE roofType = 'Open'");

    if(query.exec())
    {
        while(query.next())
        {
            count++;
        }
    }
    else
    {
        qDebug() << "GetOpenStadiumsCount Failed";
    }

    return count;
}

// Get stadiums ordered by seating capacity (Requirement 10)
QVector<Team*>* Database::GetStadiumsOrderBySeatingCap()
{
    QVector<Team*>* teams = new QVector<Team*>;
    Team* team = nullptr;
    Stadium* stadium = nullptr;

    query.prepare("SELECT stadiumName, teamName, seatingCap FROM teamInfo ORDER BY seatingCap;");

    if(query.exec())
    {
        while(query.next())
        {
            team = new Team;
            stadium = new Stadium;
            stadium->setStadiumName(query.value(0).toString());
            team->setTeamName(query.value(1).toString());
            stadium->setSeatingCapacity(query.value(2).toInt());
            team->setStadium(stadium);
            teams->push_back(team);
        }
    }
    else
    {
        qDebug() << "GetStadiumsOrderBySeatingCap Failed";
    }

    return teams;
}

// Get total seating capacity of entire NFL (Requirement 10)
int Database::GetTotalSeatingCapacity()
{
    int count = 0;

    query.prepare("SELECT DISTINCT seatingCap FROM teamInfo");

    if(query.exec())
    {
        while(query.next())
        {
            count = count + query.value(0).toInt();
        }
    }
    else
    {
        qDebug() << "GetOpenStadiumsCount Failed";
    }

    return count;
}


// Get teams ordered by conference (Requirement 11)
QVector<Team*>* Database::GetTeamsOrderByConference()
{
    QVector<Team*>* teams = new QVector<Team*>;
    Team* team = nullptr;
    Stadium* stadium = nullptr;

    query.prepare("SELECT teamName, stadiumName, conference, location from teamInfo order by conference");

    if(query.exec())
    {
        while(query.next())
        {
            team = new Team;
            stadium = new Stadium;
            team->setTeamName(query.value(0).toString());
            stadium->setStadiumName(query.value(1).toString());
            team->setConference(query.value(2).toString());
            stadium->setLocation(query.value(3).toString());
            team->setStadium(stadium);
            teams->push_back(team);
        }
    }
    else
    {
        qDebug() << "GetTeamsOrderByConference Failed";
    }

    return teams;
}

// Get teams with bermuda grass surface type (Requirement 12)
QVector<Team*>* Database::GetBermudaGrassTeams()
{
    QVector<Team*>* teams = new QVector<Team*>;
    Team* team = nullptr;
    Stadium* stadium = nullptr;

    query.prepare("SELECT teamName, surfaceType FROM teamInfo WHERE surfaceType = 'Bermuda Grass'");

    if(query.exec())
    {
        while(query.next())
        {
            team = new Team;
            stadium = new Stadium;
            team->setTeamName(query.value(0).toString());
            stadium->setSurfaceType(query.value(1).toString());
            team->setStadium(stadium);
            teams->push_back(team);
        }
    }
    else
    {
        qDebug() << "GetBermudaGrassTeams";
    }

    return teams;
}

// Get total bermuda grass stadiums (Requirement 12)
int Database::GetBermudaGrassTeamCount()
{
    int count = 0;

    query.prepare("SELECT teamName, surfaceType FROM teamInfo WHERE surfaceType = 'Bermuda Grass'");

    if(query.exec())
    {
        while(query.next())
        {
            count++;
        }
    }
    else
    {
        qDebug() << "GetBermudaGrassStadiumCount Failed";
    }

    return count;
}

// Get all souvenirs for one team (Requirement 13)
Team* Database::GetSingleTeamSouvenirs(const QString &teamName)
{
    QSqlQuery query;
    Team* team = new Team;
    QVector<Souvenir*> souvenirs;
    Souvenir* souvenir = nullptr;

    query.prepare("select teamInfo.teamName, souvenirs.itemName, souvenirs.itemPrice from teamInfo, souvenirs where teamInfo.teamName = :teamName and teamInfo.teamID = souvenirs.teamID");

    query.bindValue(":teamName", teamName);
    if(query.exec())
    {
        while(query.next())
        {
            if(team->getTeamName() != query.value(0).toString())
            {
                team->setTeamName(query.value(0).toString());
            }

            souvenir = new Souvenir;
            souvenir->setItemName(query.value(1).toString());
            souvenir->setItemPrice(query.value(2).toFloat());

            souvenirs.push_back(souvenir);
        }

        team->setSouvenirList(souvenirs);
    }
    else
    {
        qDebug() << "GetSingleTeamSouvenirs Failed!";
    }

    return team;
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

            team->setTeamID(teamID);
            team->setTeamName(teamName);
            team->setConference(conference);
            team->setDivision(division);

            // TODO set object parents for these so they get cleaned up
            Stadium *stadium = nullptr;
            if (stadiumDbCacheByName.contains(stadiumName))
            {
                stadium = stadiumDbCacheByName[stadiumName];
            }
            else
            {
                stadium = new Stadium;
                stadium->setStadiumName(stadiumName);
                stadium->setSeatingCapacity(seatingCap);
                stadium->setLocation(location);
                stadium->setSurfaceType(surfaceType);
                stadium->setRoofType(roofType);
                stadium->setDateOpened(dateOpened);
                stadiumDbCacheByID[teamID] = stadium;
                stadiumDbCacheByName[stadium->getStadiumName()] = stadium;
            }

            team->setStadium(stadium);

            teamDbCache[teamID] = team;
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

// Get adjacency list for algorithms
AdjacencyList* Database::GetAdjacencyList()
{
    QSqlQuery vertexQuery;
    QSqlQuery edgeQuery;
    AdjacencyList* list = nullptr;

    vertexQuery.prepare("SELECT DISTINCT stadiumName from teamInfo");

    // If query executes
    if(vertexQuery.exec())
    {
//        // DEBUG
//        qDebug() << "---- POPULATE ADJACENCY LIST START -----";

        // Create adjacencylist pointer
        list = new AdjacencyList;

        // Create Edge pointer
        AdjacencyList::Edge* destination = nullptr;

        // Create Vertex pointer
        AdjacencyList::Vertex* origin = nullptr;


        // While query has stadium names left on list
        while(vertexQuery.next())
        {
            // Create new Vertex Item
            origin = new AdjacencyList::Vertex;

            // Populate Vertex Item with origin stadium
            origin->origin = vertexQuery.value(0).toString();

            // Run query to pull that stadium's destination stadiums and their distances
            edgeQuery.prepare("SELECT DISTINCT toStadium, milesBetween FROM teamDistances, teamInfo "
                              "WHERE teamdistances.fromStadium = teamInfo.stadiumName "
                              "AND teamInfo.stadiumName = :origin order by milesBetween");

            // Bind origin stadium name to query
            edgeQuery.bindValue(":origin", origin->origin);

            // If query executes,
            if(edgeQuery.exec())
            {
                // While query has destination stadiums left on list
                while(edgeQuery.next())
                {
                    // Create new Edge item
                    destination = new AdjacencyList::Edge;

                    // Populate edge item with destination stadium
                    destination->destination = edgeQuery.value(0).toString();

                    // Populate edge item with destination stadium's distance
                    destination->distance = edgeQuery.value(1).toInt();

//                    // DEBUG
//                    qDebug() << "Destination City Name: " << destination->endCity;
//                    qDebug() << "Destination City Distance: " << destination->distance;

                    // Insert Edge into Vertex
                    origin->destinations.push_back(*destination);

                }// End While Edge
            }
            else
            {
                qDebug() << "GetAdjacencyList failed at Edge Query";
            }

            // Insert completed vertex into adjacency list
            list->list.push_back(*origin);

        } // End While Vertex

//        // DEBUG: PRINT ENTIRE LIST
//        qDebug() << "Starting final print!";
//        for(int originsIndex = 0; originsIndex < list->list.size(); originsIndex++)
//        {
//            qDebug() << "Arriving at: " << list->list.at(originsIndex).origin;
//            for(int destinationsIndex = 0; destinationsIndex < list->list.at(originsIndex).destinations.size(); destinationsIndex ++)
//            {
//                qDebug() << "-Destination #" << destinationsIndex+1;
//                qDebug() << "--Name: " << list->list.at(originsIndex).destinations.at(destinationsIndex).destination;
//                qDebug() << "--Distance: " << list->list.at(originsIndex).destinations.at(destinationsIndex).distance;
//            }

//            qDebug() << "-------";
//        }

    }
    else
    {
        qDebug() << "GetAdjacencyList failed at Vertex Query";
    }

    return list;
}



// Populate Shopping Cart List
QVector<Team*>* Database::CreateShoppingList(const QStringList &stadiumNames)
{
    QVector<Team*>* shoppingList = new QVector<Team*>;
    QVector<Souvenir*>* souvenirList = new QVector<Souvenir*>;
    Team* team = nullptr;
    Stadium* stadium = nullptr;
    Souvenir* souvenir = nullptr;

    qDebug() << "--SHOPPING CART CREATION START--";

    // Populate stadium name for each team
    for(int index = 0; index < stadiumNames.size(); index++)
    {
        // Create team and stadium
        team = new Team;
        stadium = new Stadium;

        // Name stadium from stadium names
        stadium->setStadiumName(stadiumNames.at(index));

        // Add to team
        team->setStadium(stadium);

        team->setTeamName(stadiumNames.at(index));


        // TODO  LEFT OFF HEREEEEEE
        // DEBUG
        qDebug() << "Stadium Name Added: " << team->getStadium()->getStadiumName();

        // Prep query
        query.prepare("SELECT teamName FROM teamInfo WHERE stadiumName = :stadiumName");

        // Bind value
        query.bindValue(":stadiumName", stadiumNames.at(index));

        // Execute
        if(query.exec())
        {
            // Create new stadium object
            stadium = new Stadium;

            while(query.next())
            {
                // Populate stadium name
                stadium->setStadiumName(query.value(0).toString());
            }

            // Add stadium to team
            shoppingList->at(index)->setStadium(stadium);

            // DEBUG
            qDebug() << "Team Name: " << shoppingList->at(index)->getTeamName()
                     << "Stadium Name: " << shoppingList->at(index)->getStadium()->getStadiumName();
        }
        else
        {
            qDebug() << "CreateShoppingList() failed at creating teams from stadium names";
        }

        // Add team to shopping list
        shoppingList->push_back(team);
    }

    // Populate souvnirs for each team
    for(int index = 0; index < stadiumNames.size(); index++)
    {
        // Prep query
        query.prepare("SELECT itemName, itemPrice FROM souvenirs, teamInfo WHERE teamInfo.teamID = souvenirs.teamID AND teamInfo.teamName = :teamName");

        // Bind value
        query.bindValue(":teamName", stadiumNames.at(index));

        // Execute
        if(query.exec())
        {
            // Populate team with souvenirs
            while(query.next())
            {
                // Populate souvenir
                souvenir = new Souvenir;
                souvenir->setItemName(query.value(0).toString());
                souvenir->setItemPrice(query.value(0).toFloat());

                // Insert souvenir into list
                souvenirList->push_back(souvenir);

                // DEBUG
                qDebug() << "Souvenir Name: " << souvenir->getItemName();
                qDebug() << "Souvenir Price: " << souvenir->getItemPrice();
            }

            // Insert list into team
            shoppingList->at(index)->setSouvenirList(*souvenirList);
        }
        else
        {
            qDebug() << "CreateShoppingList() failed at adding souvenirs to team";
        }
    }

    qDebug() << "--SHOPPING CART CREATION END--";
    qDebug() << "----";
    qDebug() << "----";
    qDebug() << "--PRINTING SHOPPING CART START --";

    for(int index = 0; index < shoppingList->size(); index++)
    {
        qDebug() << "Team #" << index+1;
        qDebug() << "Name: ";
        qDebug() << "Stadium: ";
        qDebug() << "Souvenir List: ";

        for(int sIndex = 0; sIndex < shoppingList->at(index)->getSouvenirList().size(); sIndex++)
        {
            qDebug() << "-Name: " << shoppingList->at(index)->getSouvenirList().at(sIndex)->getItemName();
            qDebug() << "-Price: " << shoppingList->at(index)->getSouvenirList().at(sIndex)->getItemPrice();
        }
    }

    qDebug() << "--PRINTING SHOPPING CART END --";

    return shoppingList;

}
