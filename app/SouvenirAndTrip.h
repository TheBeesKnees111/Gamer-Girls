#ifndef SOUVENIRANDTRIP_H
#define SOUVENIRANDTRIP_H

#include "Database.h"
#include <QSqlQueryModel>
#include <QSpinBox>
#include <QDialog>
#include <QListWidgetItem>
#include <QTableWidget>

class Team;
class Stadium;
class Souvenir;

namespace Ui {
class SouvenirAndTrip;
}

class SouvenirAndTrip : public QDialog
{
    Q_OBJECT

public:


    const int SOUVENIR_COL_COUNT = 3;
    enum SouvenirColPositions { TEAM_NAME, SOUVENIR_NAME, SOUVENIR_PRICE };
    QStringList souvenirComboBoxLabels;
    QStringList souvenirHeaders { "Team Name", "Souvenir Name", "Souvenir Price" };

    void InitializeSouvenirTable(QTableWidget* table, const int &cols, const QStringList &headers);

    void PopulateSouvenirTable(Team* team);

    void DeleteAllTableRows(QTableWidget *table);


    explicit SouvenirAndTrip(QWidget *parent = nullptr);
    ~SouvenirAndTrip();

private slots:

    ///This function will create a pointer to the main window. It will then hide the
    ///travel page before showing the main window
	void on_Home_PushButton_clicked();

	void on_Confirm_Custom_Trip_PushButton_clicked();

    void on_Souvenir_Select_Team_ComboBox_activated(const QString &arg1);

private:
	Database            *database;
	QSqlQueryModel      *queryModel;
    Ui::SouvenirAndTrip *ui;
	QListWidgetItem     *listItem;
};

#endif // SOUVENIRANDTRIP_H
