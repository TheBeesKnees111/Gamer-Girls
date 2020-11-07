#include "TeamInfo.h"

TeamInfo::TeamInfo(QObject *parent) : QObject(parent){}

/****************************************************
 * - GETTERS -                                      *
 ****************************************************/
int TeamInfo::getTeamID() const
{    return teamID; }

QString TeamInfo::getTeamName() const
{    return teamName;   }

QString TeamInfo::getStadiumName() const
{    return stadiumName;    }

int TeamInfo::getSeatingCap() const
{    return seatingCap; }

QString TeamInfo::getLocation() const
{    return location;   }

QString TeamInfo::getConference() const
{    return conference; }

QString TeamInfo::getDivision() const
{    return division;   }

QString TeamInfo::getSurfaceType() const
{    return surfaceType;    }

QString TeamInfo::getRoofType() const
{    return roofType;   }

int TeamInfo::getDateOpened() const
{    return dateOpened; }

/****************************************************
 * - SETTERS -                                      *
 ****************************************************/

void TeamInfo::setTeamID(int value)
{    teamID = value;    }

void TeamInfo::setTeamName(const QString &value)
{    teamName = value;  }

void TeamInfo::setStadiumName(const QString &value)
{    stadiumName = value;   }

void TeamInfo::setSeatingCap(int value)
{    seatingCap = value;    }

void TeamInfo::setLocation(const QString &value)
{    location = value;  }

void TeamInfo::setConference(const QString &value)
{    conference = value;    }

void TeamInfo::setDivision(const QString &value)
{    division = value;  }

void TeamInfo::setSurfaceType(const QString &value)
{    surfaceType = value;   }

void TeamInfo::setRoofType(const QString &value)
{    roofType = value;  }

void TeamInfo::setDateOpened(int value)
{    dateOpened = value;    }
