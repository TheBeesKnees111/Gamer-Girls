#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

private slots:
    void on_AddSouvenirPushButton_clicked();

    void on_DeleteSouvenirPushButton_clicked();

    void on_UpdatePushButton_clicked();

    void on_ReadInFromFileButton_clicked();

    void on_HomePushButton_clicked();

    void on_UpdateStadiumInfoPushButton_clicked();

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
