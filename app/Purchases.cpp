#include "Purchases.h"

Purchases::Purchases(QObject *parent) : QObject(parent) {}

/****************************************************
 * - GETTERS -                                      *
 ****************************************************/
int Purchases::getPurchaseID() const
{    return purchaseID; }

int Purchases::getTeamID() const
{    return teamID; }

int Purchases::getSouvenirID() const
{    return souvenirID; }

int Purchases::getQtyPurchased() const
{    return qtyPurchased;   }

/****************************************************
 * - SETTERS -                                      *
 ****************************************************/
void Purchases::setPurchaseID(int value)
{
    if (value != purchaseID)
    {
        purchaseID = value;
        emit purchaseIDChanged(value);
    }
}

void Purchases::setTeamID(int value)
{
    if (value != teamID)
    {
        teamID = value;
        emit teamIDChanged(value);
    }
}

void Purchases::setSouvenirID(int value)
{
    if (value != souvenirID)
    {
        souvenirID = value;
        emit souvenirIDChanged(value);
    }
}

void Purchases::setQtyPurchased(int value)
{
    if (value != qtyPurchased)
    {
        qtyPurchased = value;
        emit qtyPurchasedChanged(value);
    }
}
