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
{    purchaseID = value;    }

void Purchases::setTeamID(int value)
{    teamID = value;    }

void Purchases::setSouvenirID(int value)
{    souvenirID = value;    }

void Purchases::setQtyPurchased(int value)
{    qtyPurchased = value;  }
