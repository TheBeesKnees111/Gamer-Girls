#ifndef ADMIN_H
#define ADMIN_H

#include "Header.h"
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

    void on_ReadInFromFileButton_clicked();

    ///This function will create a pointer to the MainWindow UI. The admin page will be
    /// hidden before showing the Main Window
    void on_HomePushButton_clicked();

    void on_UpdateSouvenirPushButton_clicked();

    void on_UpdateStadiumPushButton_clicked();

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
