#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class Login;
class DisplayInfo;
class SouvenirAndTrip;
class Team;
class Database;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    ///This function will create a pointer to the login UI. The mainwindow will be
    /// hidden before showing the login page
	void on_Admin_Page_PushButton_clicked();

    ///This function will create a pointer to the DisplayInfo UI. The mainwindow
    /// will be hidden before showing the DisplayInfo page
	void on_Display_Team_Stadium_Info_clicked();

    ///This function will create a pointer to the Travel UI. The mainwindow will be
    /// hidden before showing the Travel page
	void on_Souvenir_And_Trip_PushButton_clicked();

private:
	Ui::MainWindow *ui;
    Database* db;

};
#endif // MAINWINDOW_H
