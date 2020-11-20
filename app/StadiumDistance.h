#ifndef STADIUMDISTANCE_H
#define STADIUMDISTANCE_H

#include "Stadium.h"

#include <QObject>

// Edge class - creates an object with:
// an  origin stadium
// a destination stadium,
// the distance between,
// and the distanceID (might not be needed)
class StadiumDistance : public QObject
{
    Q_OBJECT
public:
    StadiumDistance();

    Stadium *getFromStadium() const;
    void setFromStadium(Stadium *value);

    Stadium *getToStadium() const;
    void setToStadium(Stadium *value);

    int getDistance() const;
    void setDistance(int value);

    int getDistanceID() const;
    void setDistanceID(int value);

private:
    Stadium *fromStadium;       // origin Stadium *
    Stadium *toStadium;         // destination Stadium *
    int     distance;           // milesBetween
    int     distanceID;         // distanceID
};

#endif // STADIUMDISTANCE_H
