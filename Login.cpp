#include "Login.h"
#include "ui_Login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_HomePushButton_clicked()
{
    MainWindow *mainWindow;
    mainWindow = new MainWindow(this);

    hide();

    mainWindow -> show();
}

/*************************************************************************
 * void Login::on_pushButton_clicked()
 * ----------------------------------------------------------------------
 * This function will read the text from the username and password line edits
 * and check if they are equal to both the administrator's username and
 * password. If both the correct username and password are entered, then
 * the administrator page will open; otherwise an error message will appear
 * telling the user that the username/password is incorrect.
 ************************************************************************/
void Login::on_LoginPushButton_clicked()
{
    Admin   *adminUI;
    QString username = ui -> UsernameLineEdit -> text(); //IN & PROC - Check if text is the same as the username
    QString password = ui -> PasswordLineEdit -> text(); //IN & PROC - Check if text is the same as the password

    /*************************************************************************
     * PROCESSING - Check if correct username and password are entered
     *              Else show an error message.
     ************************************************************************/
    if(username == "" && password == "")
    {//begin if else

        adminUI = new Admin(this);
        adminUI -> setWindowTitle("Administrator Page");

        //Hide Login Page
        hide();

        adminUI -> show();
    }
    //Display error message
    else
    {
        QMessageBox::information(this, "", "Username and/or password is incorrect!");

    }//end if else

}
