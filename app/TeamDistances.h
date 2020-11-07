#ifndef TEAMDISTANCES_H
#define TEAMDISTANCES_H

#include <QObject>

class TeamDistances : public QObject
{
    Q_OBJECT

    int     distanceID;
    int     teamID;
    QString teamName;
    QString fromStaium;
    QString toStadium;
    int     milesBetween;

public:
    explicit TeamDistances(QObject *parent = nullptr);

    int     getDistanceID() const;
    int     getTeamID() const;
    QString getTeamName() const;
    QString getFromStaium() const;
    QString getToStadium() const;
    int     getMilesBetween() const;

public slots:
    void setDistanceID(int value);
    void setTeamID(int value);
    void setTeamName(const QString &value);
    void setFromStaium(const QString &value);
    void setToStadium(const QString &value);
    void setMilesBetween(int value);

signals:
    void distanceIDchanged(int newID);
    void teamIDchanged(int newID);
    void teamNameChanged(QString newName);
    void fromStaiumChanged(QString newFromStadium);
    void toStadiumChanged(QString newToStadium);
    void milesBetweenChanged(int newMiles);
};

#endif // TEAMDISTANCES_H
