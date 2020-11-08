#include "Souvenir.h"

Souvenir::Souvenir(QObject *parent) : QObject(parent){}

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
{   souvenirID = value; }

void Souvenir::setTeamID(int value)
{    teamID = value;    }

void Souvenir::setItemName(const QString &value)
{    itemName = value;  }

void Souvenir::setItemPrice(float value)
{    itemPrice = value; }

void Souvenir::setQtyPurchased(int value)
{    qtyPurchased = value;    }

