#ifndef STADIUMDISTANCE_H
#define STADIUMDISTANCE_H

#include "Stadium.h"

#include <QObject>

// Edge class - creates an object with:
// an  origin stadium
// a destination stadium,
// the distance between,
// and the distanceID (might not be needed)

/*!
 * @class StadiumDistance
 * @brief The StadiumDistance class serves as an Edge class for use in graph traversals
 */
class StadiumDistance : public QObject
{
    Q_OBJECT
public:

    /*!
     * @brief Constructor
     */
    StadiumDistance();

    /*!
     * @brief Accessor returns pointer to origin's edge
     * @return Stadium*; Pointer to origin's edge
     */
    Stadium *getFromStadium() const;

    /*!
     * @brief Mutator sets an origin edge for this object
     * @param value; Destination edge
     */
    void setFromStadium(Stadium *value);

    /*!
     * @brief Accessor returns pointer to destination's edge
     * @return Stadium*; Pointer to destination's edge
     */
    Stadium *getToStadium() const;

    /*!
     * @brief Mutator sets a destination edge for this object
     * @param value; Destination edge
     */
    void setToStadium(Stadium *value);

    /*!
     * @brief Accessor returns distance of this edge
     * @return int; distance of this edge
     */
    int getDistance() const;

    /*!
     * @brief Mutator sets a weight of this edge
     * @param value; Weight of this edge
     */
    void setDistance(int value);

    /*!
     * @brief Accessor returns database ID of this object's distance attribute
     * @return int; Database ID of this object's distance attribute
     */
    int getDistanceID() const;

    /*!
     * @brief Mutator sets the database ID of this object's distance attribute
     * @param value; Database ID of this object's distance attribute
     */
    void setDistanceID(int value);

private:
    Stadium *fromStadium;       /// Pointer to origin Stadium
    Stadium *toStadium;         /// Pointer to destination Stadium
    int     distance;           /// Weight of edge
    int     distanceID;         /// Database ID of this edge
};

#endif // STADIUMDISTANCE_H
