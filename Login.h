#ifndef LOGIN_H
#define LOGIN_H

#include "mainwindow.h"
#include "Admin.h"
#include <QMessageBox>
#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_HomePushButton_clicked();

    void on_LoginPushButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
