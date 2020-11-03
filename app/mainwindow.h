#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Header.h"
#include "Login.h"
#include "DisplayInfo.h"
#include "SouvenirAndTrip.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ///This function will return the ui
    Ui::MainWindow* GetUI() const;

private slots:
    ///This function will create a pointer to the login UI. The mainwindow will be
    /// hidden before showing the login page
    void on_AdminPagePushButton_clicked();

    ///This function will create a pointer to the DisplayInfo UI. The mainwindow
    /// will be hidden before showing the DisplayInfo page
    void on_DisplayTeamStadiumInfo_clicked();

    ///This function will create a pointer to the Travel UI. The mainwindow will be
    /// hidden before showing the Travel page
    void on_SouvenirAndTripPushButton_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
