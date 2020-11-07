#include "Souvenirs.h"

Souvenirs::Souvenirs(QObject *parent) : QObject(parent){}

/****************************************************
 * - GETTERS -                                      *
 ****************************************************/
int Souvenirs::getSouvenirID() const
{    return souvenirID; }

int Souvenirs::getTeamID() const
{    return teamID; }

QString Souvenirs::getItemName() const
{    return itemName;   }

float Souvenirs::getItemPrice() const
{    return itemPrice;  }

/****************************************************
 * - SETTERS -                                      *
 ****************************************************/
void Souvenirs::setSouvenirID(int value)
{   souvenirID = value; }

void Souvenirs::setTeamID(int value)
{    teamID = value;    }

void Souvenirs::setItemName(const QString &value)
{    itemName = value;  }

void Souvenirs::setItemPrice(float value)
{    itemPrice = value; }

