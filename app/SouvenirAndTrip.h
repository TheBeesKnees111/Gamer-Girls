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
class AdjacencyList;

namespace Ui {
class SouvenirAndTrip;
}

class SouvenirAndTrip : public QDialog
{
    Q_OBJECT

public:
    // Souvenir table column count
    const int SOUVENIR_COL_COUNT = 3;
    // Souvenir column positions
    enum SouvenirColPositions { TEAM_NAME, SOUVENIR_NAME, SOUVENIR_PRICE };
    // Souvenir combobox labels
    QStringList souvenirComboBoxLabels;
    // Souvenir column headers
    QStringList souvenirHeaders { "Team Name", "Souvenir Name", "Souvenir Price" };

    // Trip table column count
    const int TRIP_TABLE_COL_COUNT = 2;
    // Trip table column positions
    enum TripTableColPositions { T_TEAM, T_STADIUM };
    // Trip table column headers
    QStringList tripTableHeaders { "Team Name", "Stadium Names"};

    // Total Distance traveled
    int distanceTraveled;

    void InitializeSouvenirTable(QTableWidget* table, const int &cols, const QStringList &headers);

    void PopulateSouvenirTable(Team* team);

    void DeleteAllTableRows(QTableWidget *table);

    void InitializeTripTable(QTableWidget* table, const int &cols, const QStringList &headers);

    void PopulateTripTable(QTableWidget* table, const QVector<Team*>* teams);


    explicit SouvenirAndTrip(QWidget *parent = nullptr);
    ~SouvenirAndTrip();

private slots:

    ///This function will create a pointer to the main window. It will then hide the
    ///travel page before showing the main window
    void on_Home_PushButton_clicked();

    void on_Confirm_Custom_Trip_PushButton_clicked();

    void on_Souvenir_Select_Team_ComboBox_activated(const QString &arg1);

    ///For GREEN BAY TRIP push button clicked
    /// Will call rout displayer and show the dijkstra path to the city
    /// the traveler has selected to travel to
    void on_Green_Bay_Confirmation_PushButton_clicked();

    void on_Confirm_Lo_sAngeles_Rams_Trip_PushButton_clicked();

    void on_losAngeles_cart_button_clicked();

    void on_Confirm_MST_Trip_clicked();
    void on_greenBay_cart_button_clicked();

    void on_Confirm_Minnesota_Trip_PushButton_clicked();

private:
    Database            *database;
    QSqlQueryModel      *queryModel;
    Ui::SouvenirAndTrip *ui;
    QListWidgetItem     *listItem;
    AdjacencyList       *adjList;
    QVector<Team*>      *teamList;

};

#endif // SOUVENIRANDTRIP_H
