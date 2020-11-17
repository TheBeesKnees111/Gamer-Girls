#ifndef STADIUM_H
#define STADIUM_H

#include <QObject>

class Team;
class Stadium : public QObject
{
    Q_OBJECT

    QString stadiumName;
    int     stadiumID;
    QString seatingCapacity;
    QString location;
    QString surfaceType;
    QString roofType;
    int     dateOpened;

public:
    explicit Stadium(QObject *parent = nullptr);

    QString getStadiumName() const;
    QString getSeatingCapacity() const;
    QString getLocation() const;
    QString getSurfaceType() const;
    QString getRoofType() const;
    int     getDateOpened() const;

public slots:
    void setStadiumName(const QString &value);
    void setSeatingCapacity(const QString value);
    void setLocation(const QString &value);
    void setSurfaceType(const QString &value);
    void setRoofType(const QString &value);
    void setDateOpened(int value);

signals:
    void stadiumNameChanged(QString value);
    void seatingCapacityChanged(QString value);
    void locationChanged(QString value);
    void surfaceTypeChanged(QString value);
    void roofTypeChanged(QString value);
    void dateOpenedChanged(int value);

};

#endif // STADIUM_H
