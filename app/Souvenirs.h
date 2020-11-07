#ifndef SOUVENIRS_H
#define SOUVENIRS_H

#include <QObject>
#include "Header.h"

class Souvenirs : public QObject
{
    Q_OBJECT

    int     souvenirID;
    int     teamID;
    QString itemName;
    float   itemPrice;

public:
    explicit Souvenirs(QObject *parent = nullptr);

    int     getSouvenirID() const;
    int     getTeamID() const;
    QString getItemName() const;
    float   getItemPrice() const;

public slots:
    void setSouvenirID(int value);
    void setTeamID(int value);
    void setItemName(const QString &value);
    void setItemPrice(float value);

signals:
    void souvenirIDchanged(int newID);
    void teamIDchanged(int newID);
    void itemNameChanged(QString newID);
    void itemPriceChanged(float num);
};

#endif // SOUVENIRS_H
