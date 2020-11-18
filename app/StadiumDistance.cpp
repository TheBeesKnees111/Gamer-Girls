#include "StadiumDistance.h"

StadiumDistance::StadiumDistance()
{

}

Stadium *StadiumDistance::getFromStadium() const
{
    return fromStadium;
}

void StadiumDistance::setFromStadium(Stadium *value)
{
    fromStadium = value;
}

Stadium *StadiumDistance::getToStadium() const
{
    return toStadium;
}

void StadiumDistance::setToStadium(Stadium *value)
{
    if (value != toStadium)
    {
        toStadium = value;
    }
}

int StadiumDistance::getDistance() const
{
    return distance;
}

void StadiumDistance::setDistance(int value)
{
    distance = value;
}

int StadiumDistance::getDistanceID() const
{
    return distanceID;
}

void StadiumDistance::setDistanceID(int value)
{
    distanceID = value;
}
