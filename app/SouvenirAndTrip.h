#ifndef SOUVENIRANDTRIP_H
#define SOUVENIRANDTRIP_H

#include "mainwindow.h"

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

    ///This function will create a pointer to the main window. It will then hide the
    ///travel page before showing the main window
	void on_Home_PushButton_clicked();

private:
    Ui::SouvenirAndTrip *ui;
};

#endif // SOUVENIRANDTRIP_H
