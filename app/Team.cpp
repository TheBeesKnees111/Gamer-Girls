#include "Team.h"

Team::Team(QObject *parent) : QObject(parent){}

/****************************************************
 * - GETTERS -                                      *
 ****************************************************/
int Team::getTeamID() const
{    return teamID; }

QString Team::getTeamName() const
{    return teamName;   }

QString Team::getConference() const
{    return conference; }

QString Team::getDivision() const
{    return division;   }

// Souvenir is a list so needs setup for that.  Didn't get to it yet.
//QVector<Souvenir *> Team::getSouvenirList() const
//{    return souvenirList;   }


Stadium *Team::getStadium() const
{    return stadium; }

/****************************************************
 * - SETTERS -                                      *
 ****************************************************/
void Team::setTeamID(int value)
{
    if (value != teamID)
    {
        teamID = value;
        emit teamIDChanged(value);
    }
}

void Team::setTeamName(const QString &value)
{
    if (value != teamName)
    {
        teamName = value;
        emit teamNameChanged(value);
    }
}

void Team::setConference(const QString &value)
{
    if (value != conference)
    {
        conference = value;
        emit conferenceChanged(value);
    }
}

void Team::setDivision(const QString &value)
{
    if (value != division)
    {
        division = value;
        emit divisionChanged(value);
    }
}

// Souvenir is a list so needs setup for that.  Didn't get to it yet.
//void Team::setSouvenirList(const QVector<Souvenir *> &value)
//{
//    if (value != souvenirList)
//    {
//        souvenirList = value;
//        emit souvenirListChanged(value);
//    }
//}


void Team::setStadium(Stadium *value)
{
    if (value != stadium)
    {
        stadium = value;
        emit stadiumChanged(value);
    }
}


