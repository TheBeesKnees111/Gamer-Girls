#ifndef LOGIN_H
#define LOGIN_H

#include "mainwindow.h"
#include "Admin.h"

/*!
 * @class Login
 * @brief The Login class contains all objects necessary to validate login credentials to administrator section
 */
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    /*!
     * @brief Constructor
     * @param *parent; Pointer to parent object
     */
	explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    /*!
     * @brief Returns to home screen
     */
	void on_Home_PushButton_clicked();

    /*!
     * @brief Validates login credentials. Prints error if incorrect. Navigates to admin section if correct
     */
    void on_Login_PushButton_clicked();


private:
    Ui::Login *ui; /// Pointer to ui object
};

#endif // LOGIN_H
