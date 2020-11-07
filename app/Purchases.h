#ifndef PURCHASES_H
#define PURCHASES_H

#include <QObject>

class Purchases : public QObject
{
    Q_OBJECT

    int purchaseID;
    int teamID;
    int souvenirID;
    int qtyPurchased;

public:
    explicit Purchases(QObject *parent = nullptr);

    int getPurchaseID() const;
    int getTeamID() const;
    int getSouvenirID() const;
    int getQtyPurchased() const;


public slots:
    void setPurchaseID(int value);
    void setTeamID(int value);
    void setSouvenirID(int value);
    void setQtyPurchased(int value);

signals:
    void purchaseIDchanged(int newID);
    void teamIDchanged(int newID);
    void souvenirIDchange(int newID);
    void qtyPurchasedChanged(int num);
};

#endif // PURCHASES_H
