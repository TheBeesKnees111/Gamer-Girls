#include "Database.h"

#include <QFileInfo>
#include <QSqlError>
#include <QSqlQuery>

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

Team* Database::getTeamByID(int teamID)
{
    // if the dabase map doesn't contain the team object, add it
    if (!teamDbMap.contains(teamID))
    {
        runGetTeamAndStadiumByIDQry(teamID);
    }
    return teamDbMap[teamID];
}

QVector<Team*> Database::getTeams()
{
    runGetAllTeamsAndStadiums();
    return teamDbMap.values().toVector();
}

QVector<Stadium*> Database::getStadiums()
{
    runGetAllTeamsAndStadiums();
    return stadiumDbMap.values().toVector();
}

Stadium* Database::getStadiumByID(int stadiumID)
{

}

QVector<Souvenir*> Database::getSouvenirs()
{

}

Souvenir* Database::getSouvenierByID(int souvenirID)
{

}

QVector<Purchases*> Database::getPurchases()
{

}

Purchases* Database::getPurchasesByID(int purchaseID)
{

}

int Database::getMilesBetweenStadiums(Stadium *from, Stadium *to)
{
    QSqlQuery query;
    query.prepare("SELECT milesBetween FROM teamDistances "
                  "WHERE fromStadium = (:fromStadium) "
                  "and toStadium = (:toStadium)");

    query.bindValue(":fromStadium", from->getStadiumName());
    query.bindValue(":toStadium", to->getStadiumName());

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

void Database::runGetTeamAndStadiumByIDQry(int teamID)
{
    QSqlQuery query;
    query.prepare("SELECT teamID, teamName, stadiumName, seatingCap, location, "
                  "conference, division, surfaceType, roofType, dateOpened "
                  "FROM teamInfo "
                  "WHERE teamID = (:teamID)");
    query.bindValue(":teamID", teamID);
    if(query.exec())
    {
        query.next();

        // for the value in column 0 of the current row, turn it to a string
        // then create a QString value because it's QtSql
        //    int teamID = query.value(0).toInt();
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
        //    stadium->setTeamID(teamID);
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
        //    stadium->setTeam(team);

        teamDbMap[teamID] = team;
        stadiumDbMap[teamID] = stadium;
    }
    else
    {
        qDebug() << "Error " << query.lastError().text()
                 << " while executing query " << query.executedQuery();
    }
}

void Database::runGetAllTeamsAndStadiums()
{
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
}
