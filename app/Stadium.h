#ifndef STADIUM_H
#define STADIUM_H

#include <QObject>
#include <QVector>

class Team;

/*!
 * @class Stadium
 * @brief The Stadium class represents stadiums available to travel to and from
 */
class Stadium : public QObject
{
    Q_OBJECT

    /// Name of stadium
    QString stadiumName;
    /// Stadium's ID in database
    int     stadiumID;
    /// Seating capacity of stadium
    int seatingCapacity;
    /// Location (city) of stadium
    QString location;
    /// Surface type of stadium
    QString surfaceType;
    /// Roof type of stadium
    QString roofType;
    /// Date stadium opened
    int     dateOpened;
    /// List of teams that play from this stadium
    QVector<Team*> teams;

public:
    /*!
     * @brief Constructor
     * @param *parent; Pointer to parent object
     */
    explicit Stadium(QObject *parent = nullptr);

    /*!
     * @brief Accessor returns stadium's name
     * @return QString; Stadium's name
     */
    QString getStadiumName() const;

    /*!
     * @brief Accessor returns stadium's seating capacity
     * @return int; Stadium's seating capacity
     */
    int getSeatingCapacity() const;

    /*!
     * @brief Accessor returns stadium's location (city)
     * @return QString; Stadium's location (city)
     */
    QString getLocation() const;

    /*!
     * @brief Accessor returns stadium's surface type
     * @return QString; Stadium's surface type
     */
    QString getSurfaceType() const;

    /*!
     * @brief Accessor returns stadium's roof type
     * @return QString; Stadium's roof type
     */
    QString getRoofType() const;

    /*!
     * @brief Accessor returns stadium's opening date
     * @return int; Stadium's opening date
     */
    int     getDateOpened() const;

    /*!
     * @brief Accessor returns teams that play out of this stadium
     * @return Qvector<Team*>; Teams that play out of this stadium
     */
    QVector<Team*> getTeams() const;

public slots:

    /*!
     * @brief Mutator alters stadium's name
     * @param value; Stadium's
     */
    void setStadiumName(const QString &value);

    /*!
     * @brief Mutator alters stadium's seating capacity
     * @param value; Stadium's seating capacity
     */
    void setSeatingCapacity(const int value);

    /*!
     * @brief Mutator alters stadium's location (city)
     * @param value; Stadium's location (city)
     */
    void setLocation(const QString &value);

    /*!
     * @brief Mutator alters stadium's surface type
     * @param value; Stadium's surface type
     */
    void setSurfaceType(const QString &value);

    /*!
     * @brief Mutator alters stadium's roof type
     * @param value; Stadium's roof type
     */
    void setRoofType(const QString &value);

    /*!
     * @brief Mutator alters stadium's opening date
     * @param value; Stadium's opening date
     */
    void setDateOpened(int value);

    /*!
     * @brief Mutator adds team that plays out of this stadium
     * @param newTeam; Team that plays out of this stadium
     */
    void addTeam(Team* newTeam);

signals:
    /*!
     * @brief Takes action when stadium's name is changed
     * @param value; Stadium's name
     */
    void stadiumNameChanged(QString value);

    /*!
     * @brief Takes action when stadium's seating capacity is changed
     * @param value; Stadium's seating capacity
     */
    void seatingCapacityChanged(int value);

    /*!
     * @brief Takes action when stadium's location is changed
     * @param value; Stadium's location
     */
    void locationChanged(QString value);

    /*!
     * @brief Takes action when stadium's surface type is changed
     * @param value; Stadium's surface type
     */
    void surfaceTypeChanged(QString value);

    /*!
     * @brief Takes action when stadium's roof type is changed
     * @param value; Stadium's roof type
     */
    void roofTypeChanged(QString value);

    /*!
     * @brief Takes action when stadium's opening date is changed
     * @param value; Stadium's opening date
     */
    void dateOpenedChanged(int value);
};

#endif // STADIUM_H
