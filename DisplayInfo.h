#ifndef DISPLAYINFO_H
#define DISPLAYINFO_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class DisplayInfo;
}

class DisplayInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayInfo(QWidget *parent = nullptr);
    ~DisplayInfo();

private slots:
    void on_PrintAllTeamsPushButton_clicked();

    void on_PrintAFCTeamsPushButton_clicked();

    void on_PrintNFCTeamsPushButton_clicked();

    void on_PrintNorthNFCTeamsPushButton_clicked();

    void on_PrintTeamInforByConferencePushButton_clicked();

    void on_PrintStadiumPushButton_clicked();

    void on_PrintStadiumByDatePushButton_clicked();

    void on_ShowOpenRoofStadiumsPushButton_clicked();

    void on_ShowBermudaGrassStadiumsPushButton_clicked();

    void on_HomePushButton_clicked();

private:
    Ui::DisplayInfo *ui;
};

#endif // DISPLAYINFO_H
