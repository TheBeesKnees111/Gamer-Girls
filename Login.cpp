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

///This function will create a pointer to the MainWindow UI. The Login
/// page will be hidden before showing the Main Window
void Login::on_Home_PushButton_clicked()
{
    MainWindow *mainWindow;
    mainWindow = new MainWindow(this);

    hide();

    mainWindow -> show();
}


///This function will read the text from the username and password line edits
///and check if they are equal to both the administrator's username and
///password. If both the correct username and password are entered, then
///the administrator page will open; otherwise an error message will appear
///telling the user that the username/password is incorrect.
void Login::on_Login_PushButton_clicked()
{
    Admin   *adminUI;
	QString username = ui -> Username_LineEdit -> text(); //IN & PROC - Check if text is the same as the username
	QString password = ui -> Password_LineEdit -> text(); //IN & PROC - Check if text is the same as the password

     //Check if correct username and password are entered
     //Else show an error message.
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
