#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QObject>
#include <QDebug>

class Team;
class Souvenir;
class Stadium;
class Purchases;

class Database : public QSqlDatabase
{

public:

    Database();

    // TEAM METHODS
    Team* getTeamByID(int teamID);
    QVector<Team*> getTeams();

    // STADIUM METHODS
    QVector<Stadium*> getStadiums();
    Stadium* getStadiumByID(int stadiumID);

    // SOUVENIR METHODS
    QVector<Souvenir*> getSouvenirs();
    Souvenir* getSouvenierByID(int souvenirID);

    // PURCHASES METHODS
    QVector<Purchases*> getPurchases();
    Purchases* getPurchasesByID(int purchaseID);

    // DISTANCE METHODS
    int getMilesBetweenStadiums(Stadium* from, Stadium* to);

    // TODO
    // should dijk call get miles from db
    // or create adjacency list & pass to dijk
    // creating the list will make dijk's algo run faster

private:
    QMap<int, Team*> teamDbMap;
    QMap<int, Stadium*> stadiumDbMap;
    QMap<int, Souvenir*> souvenirDbMap;
    QMap<int, Purchases*> purchasesDbMap;

    void runGetTeamAndStadiumByIDQry(int teamID);
    void runGetAllTeamsAndStadiums();
};

#endif // DATABASE_H