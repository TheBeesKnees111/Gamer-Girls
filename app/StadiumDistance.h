#ifndef STADIUMDISTANCE_H
#define STADIUMDISTANCE_H

#include "Stadium.h"

#include <QObject>

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
    Stadium *fromStadium;
    Stadium *toStadium;
    int     distance;
    int     distanceID;
};

#endif // STADIUMDISTANCE_H
