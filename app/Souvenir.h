#ifndef SOUVENIRS_H
#define SOUVENIRS_H

#include <QObject>
#include <QVector>

/*!
 * @class Souvenir
 * @brief The Souvenir class represents souvenirs available for purchase at stadiums
 */
class Souvenir : public QObject
{
    Q_OBJECT

    /// Souvenir ID
    int     souvenirID;
    /// Team ID
    int     teamID;
    /// Souvenir name
    QString itemName;
    /// Souvenir price
    float   itemPrice;
    /// Quantity of souvenir purchased
    int     qtyPurchased;

public:
	explicit Souvenir(QObject *parent = nullptr);
	Souvenir(int sID, int tID, QString iName, float iPrice);

    /*!
     * @brief Constructor
     * @param *parent; Pointer to parent object
     */
    explicit Souvenir(QObject *parent = nullptr);

    /*!
     * @brief Accessor returns souvenir's ID
     * @return int; Souvenir's ID
     */
    int     getSouvenirID() const;

    /*!
     * @brief Accessor returns team's ID
     * @return int; Team's ID
     */
    int     getTeamID() const;

    /*!
     * @brief Accessor returns souvenir's name
     * @return QString; Souvenir's name
     */
    QString getItemName() const;

    /*!
     * @brief Accessor returns souvenir's price
     * @return float; Souvenir's price
     */
    float   getItemPrice() const;

    /*!
     * @brief Accessor returns quantity of souvenir purchased
     * @return int; Quantity of souvenir purchased
     */
    int     getQtyPurchased() const;

public slots:

    /*!
     * @brief Mutator alters souvenir's ID
     * @param value; Souvenir's ID
     */
    void setSouvenirID(int value);

    /*!
     * @brief Mutator alters team's ID
     * @param value; team's ID
     */
    void setTeamID(int value);

    /*!
     * @brief Mutator alters souvenir's name
     * @param value; Souvenir's name
     */
    void setItemName(const QString &value);

    /*!
     * @brief Mutator alters souvenir's price
     * @param value; Souvenir's price
     */
    void setItemPrice(float value);

    /*!
     * @brief Mutator alters quantity of souvenir purchased
     * @param value; Quantity of souvenir purchased
     */
    void setQtyPurchased(int value);

signals:

    /*!
     * @brief Takes action when souvenir ID is changed
     * @param newID; Souvenir's new ID
     */
    void souvenirIDChanged(int newID);

    /*!
     * @brief Takes action when souvenir's team's ID is changed
     * @param newID; Souvenir's team's new ID
     */
    void teamIDChanged(int newID);

    /*!
     * @brief Takes action when souvenir name is changed
     * @param newID; Souvenir's new name
     */
    void itemNameChanged(QString newID);

    /*!
     * @brief Takes action when souvenir price is changed
     * @param num; Souvenir's new price
     */
    void itemPriceChanged(float num);

    /*!
     * @brief Takes action when quantity of souvenirs purchased is changed
     * @param value; Quantity of souvenirs purchased
     */
    void qtyPurchasedChanged(int value);
};

#endif // SOUVENIRS_H
