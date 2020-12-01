#include "Souvenir.h"

Souvenir::Souvenir(QObject *parent) : QObject(parent){}

Souvenir::Souvenir(int sID, int tID, QString iName, float iPrice)
{
	souvenirID = sID;
	teamID     = tID;
	itemName   = iName;
	itemPrice  = iPrice;
}

/****************************************************
 * - GETTERS -                                      *
 ****************************************************/
int Souvenir::getSouvenirID() const
{    return souvenirID; }

int Souvenir::getTeamID() const
{    return teamID; }

QString Souvenir::getItemName() const
{    return itemName;   }

float Souvenir::getItemPrice() const
{    return itemPrice;  }

int Souvenir::getQtyPurchased() const
{    return qtyPurchased; }

/****************************************************
 * - SETTERS -                                      *
 ****************************************************/
void Souvenir::setSouvenirID(int value)
{
    if (value != souvenirID)
    {
        souvenirID = value;
        emit souvenirIDChanged(value);
    }
}

void Souvenir::setTeamID(int value)
{
    if (value != teamID)
    {
        teamID = value;
        emit teamIDChanged(value);
    }
}

void Souvenir::setItemName(const QString &value)
{
    if (value != itemName)
    {
        itemName = value;
        emit itemNameChanged(value);
    }
}

void Souvenir::setItemPrice(float value)
{
    if (value != itemPrice)
    {
        itemPrice = value;
        emit itemPriceChanged(value);
    }
}

void Souvenir::setQtyPurchased(int value)
{
    if (value != qtyPurchased)
    {
        qtyPurchased = value;
        emit qtyPurchasedChanged(value);
    }
}

