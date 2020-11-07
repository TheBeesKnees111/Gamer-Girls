#ifndef TEAMINFO_H
#define TEAMINFO_H

#include <QObject>

class TeamInfo : public QObject
{
    Q_OBJECT

    int     teamID;
    QString teamName;
    QString stadiumName;
    int     seatingCap;
    QString location;
    QString conference;
    QString division;
    QString surfaceType;
    QString roofType;
    int     dateOpened;

public:
    explicit TeamInfo(QObject *parent = nullptr);

    int     getTeamID() const;
    QString getTeamName() const;
    QString getStadiumName() const;
    int     getSeatingCap() const;
    QString getLocation() const;
    QString getConference() const;
    QString getDivision() const;
    QString getSurfaceType() const;
    QString getRoofType() const;
    int     getDateOpened() const;

public slots:
    void setTeamID(int value);
    void setTeamName(const QString &value);
    void setStadiumName(const QString &value);
    void setSeatingCap(int value);
    void setLocation(const QString &value);
    void setConference(const QString &value);
    void setDivision(const QString &value);
    void setSurfaceType(const QString &value);
    void setRoofType(const QString &value);
    void setDateOpened(int value);

signals:
    void teamIDchanged(int value);
    void teamNameChanged(const QString value);
    void stadiumNameChanged(const QString value);
    void seatingCapChanged(int value);
    void locationChanged(const QString value);
    void conferenceChanged(const QString value);
    void divisionChanged(const QString value);
    void surfaceTypeChanged(const QString value);
    void roofTypeChanged(const QString value);
    void dateOpenedChanged(int value);

};

#endif // TEAMINFO_H
