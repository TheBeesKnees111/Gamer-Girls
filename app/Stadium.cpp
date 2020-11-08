#include "Stadium.h"

QString Stadium::getStadiumName() const
{
    return stadiumName;
}

void Stadium::setStadiumName(const QString &value)
{
    stadiumName = value;
}

int Stadium::getSeatingCapacity() const
{
    return seatingCapacity;
}

void Stadium::setSeatingCapacity(int value)
{
    seatingCapacity = value;
}

QString Stadium::getLocation() const
{
    return location;
}

void Stadium::setLocation(const QString &value)
{
    location = value;
}

QString Stadium::getSurfaceType() const
{
    return surfaceType;
}

void Stadium::setSurfaceType(const QString &value)
{
    surfaceType = value;
}

QString Stadium::getRoofType() const
{
    return roofType;
}

void Stadium::setRoofType(const QString &value)
{
    roofType = value;
}

int Stadium::getDateOpened() const
{
    return dateOpened;
}

void Stadium::setDateOpened(int value)
{
    dateOpened = value;
}

Stadium::Stadium(QObject *parent) : QObject(parent){}

/****************************************************
 * - GETTERS -                                      *
 ****************************************************/

/****************************************************
 * - SETTERS -                                      *
 ****************************************************/
