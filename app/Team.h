#ifndef TEAM_H
#define TEAM_H

#include <QObject>
#include <QVector>

class Stadium;
class Souvenir;

/*!
 * @class Team
 * @brief The Team class an individual NFL team
 */
class Team : public QObject
{
    Q_OBJECT

    int                 teamID; /// Team's ID
    QString             teamName; /// Team's name
    QString             conference; /// Team's conference
    QString             division; /// Team's division
    QVector<Souvenir*>  souvenirList; /// Team's souvenir list
    Stadium             *stadium; /// Pointer to team's stadium

public:
    /*!
     * @brief Constructor
     * @param *parent; Pointer to parent object
     */
    explicit Team(QObject *parent = nullptr);


    /*!
     * @brief Accessor returns team's ID
     * @return int; Team's ID
     */
    int         getTeamID() const;

    /*!
     * @brief Accessor returns team's name
     * @return QString; Team's name
     */
    QString     getTeamName() const;

    /*!
     * @brief Accessor returns team's conference
     * @return QString; Team's conference
     */
    QString     getConference() const;

    /*!
     * @brief Accessor returns team's division
     * @return QString; Team's division
     */
    QString     getDivision() const;

    /*!
     * @brief Accessor returns team's souvenir list
     * @return QVector<Souvenir*>; Container with souvenirs for one team
     */
    QVector<Souvenir*> getSouvenirList() const;

    /*!
     * @brief Accessor returns pointer to team's stadium
     * @return Stadium*; Pointer to team's stadium
     */
    Stadium*    getStadium() const;

public slots:
    /*!
     * @brief Mutator alters team's ID
     * @param value; Team's ID
     */
    void setTeamID(int value);

    /*!
     * @brief Mutator alters team's name
     * @param value; Team's name
     */
    void setTeamName(const QString &value);

    /*!
     * @brief Mutator alters team's conference
     * @param value; Team's conference
     */
    void setConference(const QString &value);

    /*!
     * @brief Mutator alters team's division
     * @param value; Team's division
     */
    void setDivision(const QString &value);

    /*!
     * @brief Mutator alters team's division
     * @param value; Team's division
     */
    void setSouvenirList(const QVector<Souvenir *> &value);

    /*!
     * @brief Mutator alters team's stadium
     * @param *value; Pointer to team's stadium
     */
    void setStadium(Stadium *value);

signals:
    /*!
     * @brief Takes action when team's ID is changed
     * @param value; Team's new ID
     */
    void teamIDChanged(int value);

    /*!
     * @brief Takes action when team's name is changed
     * @param value; Team's new name
     */
    void teamNameChanged(QString value);

    /*!
     * @brief Takes action when team's conference is changed
     * @param value; Team's new conference
     */
    void conferenceChanged(QString value);

    /*!
     * @brief Takes action when team's division is changed
     * @param value; Team's new division
     */
    void divisionChanged(QString value);

    /*!
     * @brief Takes action when team's souvenir list is changed
     * @param value; Team's new souvenir list
     */
    void souvenirListChanged(const QVector<Souvenir *> &value);

    /*!
     * @brief Takes action when team's stadium is changed
     * @param *value; Team's new stadium
     */
    void stadiumChanged(Stadium *value);
};

#endif // TEAM_H
