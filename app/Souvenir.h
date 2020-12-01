#ifndef SOUVENIRS_H
#define SOUVENIRS_H

#include <QObject>
#include <QVector>

class Souvenir : public QObject
{
    Q_OBJECT

    int     souvenirID;
    int     teamID;
    QString itemName;
    float   itemPrice;
    int     qtyPurchased;

public:
	explicit Souvenir(QObject *parent = nullptr);
	Souvenir(int sID, int tID, QString iName, float iPrice);

    int     getSouvenirID() const;
    int     getTeamID() const;
    QString getItemName() const;
    float   getItemPrice() const;
    int     getQtyPurchased() const;

public slots:
    void setSouvenirID(int value);
    void setTeamID(int value);
    void setItemName(const QString &value);
    void setItemPrice(float value);
    void setQtyPurchased(int value);

signals:
    void souvenirIDChanged(int newID);
    void teamIDChanged(int newID);
    void itemNameChanged(QString newID);
    void itemPriceChanged(float num);
    void qtyPurchasedChanged(int value);
};

#endif // SOUVENIRS_H
