#ifndef SOUVENIRANDTRIP_H
#define SOUVENIRANDTRIP_H

#include <QDialog>

namespace Ui {
class SouvenirAndTrip;
}

class SouvenirAndTrip : public QDialog
{
    Q_OBJECT

public:
    explicit SouvenirAndTrip(QWidget *parent = nullptr);
    ~SouvenirAndTrip();

private slots:
    void on_SearchTeamSouvenirPushButton_clicked();

    void on_ConfirmationPushButton_clicked();

    void on_ConfirmCustomTripPushButton_clicked();

    void on_ConfirmNewEnglandTripPushButton_clicked();

    void on_ConfirmCustomShortestTripPushButton_clicked();

    void on_ConfirmMSTTrip_clicked();

    void on_ConfirmMinnesotaTripPushButton_clicked();

    void on_ConfirmLosAngelesRamsTripPushButton_clicked();

    ///This function will create a pointer to the main window. It will then hide the
    ///travel page before showing the main window
    void on_HomePushButton_clicked();

private:
    Ui::SouvenirAndTrip *ui;
};

#endif // SOUVENIRANDTRIP_H
