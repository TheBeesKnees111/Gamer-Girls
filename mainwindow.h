#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private slots:
    void on_AdminPagePushButton_clicked();

    void on_DisplayTeamStadiumInfo_clicked();

    void on_SouvenirAndTripPushButton_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
