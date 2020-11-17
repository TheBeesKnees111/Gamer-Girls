#ifndef SOUVENIRANDTRIP_H
#define SOUVENIRANDTRIP_H

#include "Database.h"
#include <QSqlQueryModel>
#include <QSpinBox>
#include <QDialog>
#include <QListWidgetItem>

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

	void on_Confirm_Custom_Trip_PushButton_clicked();

	private:
	Database            *database;
	QSqlQueryModel      *queryModel;
    Ui::SouvenirAndTrip *ui;
	QListWidgetItem     *listItem;
};

#endif // SOUVENIRANDTRIP_H
