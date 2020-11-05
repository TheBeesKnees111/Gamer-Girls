#ifndef LOGIN_H
#define LOGIN_H

#include "Header.h"
#include "mainwindow.h"
#include "Admin.h"

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

    ///This function will create a pointer to the MainWindow UI. The Login
    /// page will be hidden before showing the Main Window
    void on_HomePushButton_clicked();

    ///This function will read the text from the username and password line edits
    ///and check if they are equal to both the administrator's username and
    ///password. If both the correct username and password are entered, then
    ///the administrator page will open; otherwise an error message will appear
    ///telling the user that the username/password is incorrect.
    void on_LoginPushButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
