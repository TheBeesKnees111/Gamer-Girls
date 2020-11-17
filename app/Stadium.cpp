#include "Stadium.h"
#include "Team.h"

Stadium::Stadium(QObject *parent) : QObject(parent){}

/****************************************************
 * - GETTERS -                                      *
 ****************************************************/
QString Stadium::getStadiumName() const
{    return stadiumName;    }

int Stadium::getSeatingCapacity() const
{    return seatingCapacity;    }

QString Stadium::getLocation() const
{    return location;   }

QString Stadium::getSurfaceType() const
{    return surfaceType;    }

QString Stadium::getRoofType() const
{   return roofType;    }

int Stadium::getDateOpened() const
{    return dateOpened; }

/****************************************************
 * - SETTERS -                                      *
 ****************************************************/
void Stadium::setStadiumName(const QString &value)
{
    if (value != stadiumName)
    {
        stadiumName = value;
        emit stadiumNameChanged(value);
    }
}

void Stadium::setSeatingCapacity(const int value)
{
    if (value != seatingCapacity)
    {
        seatingCapacity = value;
        emit seatingCapacityChanged(value);
    }
}

void Stadium::setLocation(const QString &value)
{
    if (value != location)
    {
        location = value;
        emit locationChanged(value);
    }
}

void Stadium::setSurfaceType(const QString &value)
{
    if (value != surfaceType)
    {
        surfaceType = value;
        emit surfaceTypeChanged(value);
    }
}

void Stadium::setRoofType(const QString &value)
{
    if (value != roofType)
    {
        roofType = value;
        emit roofTypeChanged(value);
    }
}

void Stadium::setDateOpened(int value)
{
    if (value != dateOpened)
    {
        dateOpened = value;
        emit dateOpenedChanged(value);
    }
}
