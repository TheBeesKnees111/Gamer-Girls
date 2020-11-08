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

//Souvenir Team::getSouvenirObj() const
//{    return souvenirObj;    }

Stadium *Team::getStadium() const
{    return stadium; }

/****************************************************
 * - SETTERS -                                      *
 ****************************************************/
void Team::setTeamID(int value)
{    teamID = value;    }

void Team::setTeamName(const QString &value)
{    teamName = value;  }

void Team::setConference(const QString &value)
{    conference = value;    }

void Team::setDivision(const QString &value)
{    division = value;  }

//void Team::setSouvenirObj(const Souvenir &value)
//{    souvenirObj = value;   }

void Team::setStadium(Stadium *value)
{    stadium = value;    }

