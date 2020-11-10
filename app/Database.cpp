#include "Database.h"
#include "Team.h"
#include "Stadium.h"

#include <QFileInfo>
#include <QSqlError>

#include <QFileDialog>

Database::Database(): QSqlDatabase(addDatabase("QSQLITE"))
{
    // Set path
    setDatabaseName(QDir::currentPath() + "/db/NFLdb.db");

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

Team* Database::GetTeamByID(const int &teamID)
{
    query.prepare("SELECT teamID, teamName, stadiumName, seatingCap, location, "
                  "conference, division, surfaceType, roofType, dateOpened "
                  "FROM teamInfo "
                  "WHERE teamID = (:teamID)");
    query.bindValue(":teamID", teamID);

    if(query.exec())
    {
        // TODO change these to direct assignment
        query.next();

        // for the value in column 0 of the current row, turn it to a string
        // then create a QString value because it's QtSql
        int teamID = query.value(0).toInt();
        QString teamName = query.value(T_NAME).toString();
        QString stadiumName = query.value(2).toString();
        int seatingCap = query.value(3).toInt();
        QString location = query.value(4).toString();
        QString conference = query.value(5).toString();
        QString division = query.value(6).toString();
        QString surfaceType = query.value(7).toString();
        QString roofType = query.value(8).toString();
        int dateOpened = query.value(9).toInt();

        Team *team = new Team;
        Stadium *stadium = new Stadium;


        team->setTeamID(teamID);
        team->setTeamName(query.value(T_NAME).toString());
        stadium->setStadiumName(stadiumName);
        stadium->setSeatingCapacity(seatingCap);
        stadium->setLocation(location);
        team->setConference(conference);
        team->setDivision(division);
        stadium->setSurfaceType(surfaceType);
        stadium->setRoofType(roofType);
        stadium->setDateOpened(dateOpened);

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

// Uber object for use in all display sections. Will overwrite upon return
// to home page
QVector<Team*> Database::GetTeams()
{
    query.prepare("SELECT teamID, teamName, stadiumName, seatingCap, location, "
                  "conference, division, surfaceType, roofType, dateOpened "
                  "FROM teamInfo ");
    if(query.exec())
    {
        while(query.next())
        {
            // TODO INSERT ENUM AND CONSOLIDATE ASSIGNMENT/DECLARATION
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

            teamDbMap[teamID] = team;
            stadiumDbMap[teamID] = stadium;
        }
    }
    else
    {
        qDebug() << "Error " << query.lastError().text()
                 << " while executing query " << query.executedQuery();
    }


    return teamDbMap.values().toVector();
}

Stadium* Database::getStadiumByID(int stadiumID)
{

}

// For use in admin section
QVector<Souvenir*> Database::getSouvenirs()
{

}

//
Souvenir* Database::getSouvenierByID(int souvenirID)
{

}

QVector<Purchases*> Database::getPurchases()
{

}

Purchases* Database::getPurchasesByID(int purchaseID)
{

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
