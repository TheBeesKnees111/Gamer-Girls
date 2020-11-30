#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class Login;
class DisplayInfo;
class SouvenirAndTrip;
class Team;
class Database;
class BFS;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * @class MainWindow
 * @brief The MainWindow class contains all objects necessary to control main window of program
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * @brief Constructor
     * @param *parent; Pointer to parent object
     */
	MainWindow(QWidget *parent = nullptr);

    /*!
     * @brief Destructor
     */
    ~MainWindow();

private slots:
    /*!
     * @brief Navigate to administrator login screen
     */
    void on_Admin_Page_PushButton_clicked();

    /*!
     * @brief Navigate to Display Team Info section
     */
	void on_Display_Team_Stadium_Info_clicked();

    ///This function will create a pointer to the Travel UI. The mainwindow will be
    /// hidden before showing the Travel page

    /*!
     * @brief Navigate to Trip Section
     */
    void on_Souvenir_And_Trip_PushButton_clicked();

private:
    Ui::MainWindow *ui; /// Pointer to ui object
    Database*       db; /// Pointer to database object

};
#endif // MAINWINDOW_H
