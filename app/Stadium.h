#ifndef STADIUM_H
#define STADIUM_H

#include "Team.h"
#include <QObject>

class Team;
class Stadium : public QObject
{
    Q_OBJECT

    QString stadiumName;
    int     stadiumID;
    Team    *team;
    int     seatingCapacity;
    QString location;
    QString surfaceType;
    QString roofType;
    int     dateOpened;

public:
    explicit Stadium(QObject *parent = nullptr);

    QString getStadiumName() const;
    void setStadiumName(const QString &value);

    int getSeatingCapacity() const;
    void setSeatingCapacity(int value);

    QString getLocation() const;
    void setLocation(const QString &value);

    QString getSurfaceType() const;
    void setSurfaceType(const QString &value);

    QString getRoofType() const;
    void setRoofType(const QString &value);

    int getDateOpened() const;
    void setDateOpened(int value);

public slots:


signals:

};

#endif // STADIUM_H
