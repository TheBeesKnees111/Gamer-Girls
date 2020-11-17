#include "Database.h"
#include "Team.h"
#include "Stadium.h"
#include "Souvenir.h"
#include <QFileInfo>
#include <QSqlError>
#include <QFileDialog>
#include <QVector>


Database::Database(): QSqlDatabase(addDatabase("QSQLITE"))
{
    // Set path
    //NOTE IF YOU ARE ON WINDOWS USE WINDOWSPATHFILE, IF YOU ARE ON MAC USE MACPATHFILE
    QString windowsPathFile =  "/db/NFLdb.db";
    QString macPathFile = "/db";
    setDatabaseName(QDir::currentPath() + windowsPathFile);

	qDebug() << QDir::currentPath() + windowsPathFile;

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

Team* Database::GetTeamByID(const int &teamID)
{
    query.prepare("SELECT teamID, teamName, stadiumName, seatingCap, location, "
                  "conference, division, surfaceType, roofType, dateOpened "
                  "FROM teamInfo "
                  "WHERE teamID = (:teamID)");
    query.bindValue(":teamID", teamID);

    if(query.exec())
    {
        query.next();

        Team *team = new Team;
        Stadium *stadium = new Stadium;


        team->setTeamID(query.value(T_ID).toInt());
        team->setTeamName(query.value(T_TEAM_NAME).toString());
        stadium->setStadiumName(query.value(T_STADIUM_NAME).toString());
        stadium->setSeatingCapacity(query.value(T_SEATING_CAP).toString());
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
            stadium->setSeatingCapacity(query.value(T_SEATING_CAP).toString());
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
		query.next();

		Stadium *stadium = new Stadium;

		stadium -> setStadiumName    (query.value(T_STADIUM_NAME).toString());
        stadium -> setSeatingCapacity(query.value(T_SEATING_CAP).toString());
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
        query.next();
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
            stadium->setSeatingCapacity(query.value(3).toString());
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
QVector<Team>* Database::GetTeamsOrderByName()
{
    QVector<Team>* v(NULL);

	return v;
}

// Get all teams and stadiums ordered by stadium name (Requirement 4)
QVector<Team*>* Database::GetTeamsOrderByStadium()
{
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
            stadium->setSeatingCapacity(query.value(2).toString());
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
    QVector<Team*>* teams = nullptr;

    return teams;
}

// Get all souvenirs for one team (Requirement 13)
Team* Database::GetSingleTeamSouvenirs(const QString &teamName)
{
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

