#include "TeamDistances.h"

TeamDistances::TeamDistances(QObject *parent) : QObject(parent){}

/****************************************************
 * - GETTERS -                                      *
 ****************************************************/
int TeamDistances::getDistanceID() const
{    return distanceID; }

int TeamDistances::getTeamID() const
{    return teamID; }

QString TeamDistances::getTeamName() const
{    return teamName;   }

QString TeamDistances::getFromStaium() const
{    return fromStaium; }

QString TeamDistances::getToStadium() const
{    return toStadium;  }

int TeamDistances::getMilesBetween() const
{    return milesBetween;   }

/****************************************************
 * - SETTERS -                                      *
 ****************************************************/
void TeamDistances::setDistanceID(int value)
{    distanceID = value;    }

void TeamDistances::setTeamID(int value)
{    teamID = value;    }

void TeamDistances::setTeamName(const QString &value)
{    teamName = value;  }

void TeamDistances::setFromStaium(const QString &value)
{    fromStaium = value;    }

void TeamDistances::setToStadium(const QString &value)
{    toStadium = value; }

void TeamDistances::setMilesBetween(int value)
{    milesBetween = value;  }
