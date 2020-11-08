#ifndef TEAM_H
#define TEAM_H

#include <QObject>
#include "Stadium.h"
#include "Souvenir.h"

class Stadium;
class Team : public QObject
{
    Q_OBJECT

    int         teamID;
    QString     teamName;
    QString     conference;
    QString     division;
    QVector<Souvenir*> souvenirList;
    Stadium     *stadium;

public:
    explicit Team(QObject *parent = nullptr);

    int         getTeamID() const;
    QString     getTeamName() const;
    QString     getConference() const;
    QString     getDivision() const;
//    Souvenir    getSouvenirObj() const;
    Stadium     *getStadium() const;

public slots:
    void setTeamID(int value);
    void setTeamName(const QString &value);
    void setConference(const QString &value);
    void setDivision(const QString &value);
//    void setSouvenirObj(const Souvenir &value);
    void setStadium(Stadium *value);

signals:
    void teamIDChanged(int value);
    void teamNameChanged(QString value);
    void conferenceChanged(QString value);
    void divisionChanged(QString value);
//    void souvenirObjChanged(Souvenir value);
    void stadiumChanged(Stadium *value);

};

#endif // TEAM_H
