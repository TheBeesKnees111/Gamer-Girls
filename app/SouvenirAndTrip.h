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

/*!
 * @class SouvenirAndTrip
 * @brief The SouvenirAndTrip class contains all objects necessary to plan trips and view one team's souvenirs
 */
class SouvenirAndTrip : public QDialog
{
    Q_OBJECT

public:
    /// Souvenir table column count
    const int SOUVENIR_COL_COUNT = 3;
    /// Souvenir column positions
    enum SouvenirColPositions { TEAM_NAME, SOUVENIR_NAME, SOUVENIR_PRICE };
    /// Souvenir combobox labels
    QStringList souvenirComboBoxLabels;
    /// Souvenir column headers
    QStringList souvenirHeaders { "Team Name", "Souvenir Name", "Souvenir Price" };
    /// Trip table column count
    const int TRIP_TABLE_COL_COUNT = 2;
    /// Trip table column positions
    enum TripTableColPositions { T_TEAM, T_STADIUM };
    /// Trip table column headers
    QStringList tripTableHeaders { "Team Name", "Stadium Names"};
    /// Total Distance traveled
    int distanceTraveled;

    /*!
     * @brief Initializes souvenir table to blank
     * @param table; Table to initialize to blank
     * @param cols; Number of columns in table
     * @param headers; Column header names
     */
    void InitializeSouvenirTable(QTableWidget* table, const int &cols, const QStringList &headers);

    /*!
     * @brief Populates souvenir table with relevant information
     * @param team; Team information with which to populate souvenir table
     */
    void PopulateSouvenirTable(Team* team);

    /*!
     * @brief Helper method deletes table rows to initialize to blank
     * @param table; Table from which to delete all rows
     */
    void DeleteAllTableRows(QTableWidget *table);

    /*!
     * @brief Initializes trip table to blank
     * @param table; Table to initialize to blank
     * @param cols; Number of columns in table
     * @param headers; Column header names
     */
    void InitializeTripTable(QTableWidget* table, const int &cols, const QStringList &headers);

    /*!
     * @brief Populates trip table with relevant information
     * @param table; Table to populate with data
     * @param *teams; Pointer to container of team objects with which to populate the table
     */
    void PopulateTripTable(QTableWidget* table, const QVector<Team*>* teams);

    /*!
     * @brief Constructor
     * @param *parent; Pointer to parent object
     */
    explicit SouvenirAndTrip(QWidget *parent = nullptr);

    /*!
     * @brief Destructor
     */
    ~SouvenirAndTrip();

private slots:
    /*!
     * @brief Navigates back to home page
     */
    void on_Home_PushButton_clicked();

    /*!
     * @brief Finalizes custom trip information. Runs traversal
     */
    void on_Confirm_Custom_Trip_PushButton_clicked();

    /*!
     * @brief Allows user to select which team they wish to visit from Green Bay
     * @param arg; Contents of combobox on activation
     */
    void on_Souvenir_Select_Team_ComboBox_activated(const QString &arg1);

    /*!
     * @brief Finalizes Green Bay trip information. Runs traversal
     */
    void on_Green_Bay_Confirmation_PushButton_clicked();

    /*!
     * @brief Finalizes Los Angeles trip information. Runs traversal
     */
    void on_Confirm_Lo_sAngeles_Rams_Trip_PushButton_clicked();

    /*!
     * @brief Navigates from Los Angeles trip to Purchase Table
     */
    void on_losAngeles_cart_button_clicked();

    /*!
     * @brief Finalizes MST trip information. Runs traversal
     */
    void on_Confirm_MST_Trip_clicked();

    /*!
     * @brief Navigates from Green Bay trip to Purchase Table
     */
    void on_greenBay_cart_button_clicked();

    /*!
     * @brief Finalizes New England trip information. Runs traversal
     */
    void on_Confirm_New_England_Trip_PushButton_clicked();

    /*!
     * @brief Navigates from New England trip to Purchase Table
     */
    void on_newEngland_cart_button_clicked();

    /*!
     * @brief Finalizes Minnesota trip information. Runs traversal
     */
    void on_Confirm_Minnesota_Trip_PushButton_clicked();

    /*!
     * @brief Navigates from Minnesota trip to Purchase Table
     */
    void on_minnesota_cart_button_clicked();

    /*!
     * @brief Gets the items selected from the QListWidget
     */
    void on_Select_Cities_ListWidget_itemClicked(QListWidgetItem *item);

    void on_customTrip_cart_button_clicked();

private:

    /*!
     * @brief Finalizes the custom shortest trip. Runs trip.
     */
    void on_Confirm_Custom_Shortest_Trip_PushButton_clicked();

    /*!
     * @brief Navigates from custom shortest trip to Purchase Table
     */
    void on_shortestCustomTrip_cart_button_clicked();


private:
    /// Pointer to database object
    Database            *database;
    /// Pointer to querymodel used to configure table
    QSqlQueryModel      *queryModel;
    /// Pointer to ui object
    Ui::SouvenirAndTrip *ui;
    /// Pointer to list widget item used to configure table
    QListWidgetItem     *listItem;
    /// Pointer to adjacency list used for traversal algorithms
    AdjacencyList       *adjList;
    /// Pointer to list of teams to visit. Used for shopping cart construction
    QVector<Team*>      *teamList;
    /// A QStringList that holds the teams for the custom trip
    QStringList customTripList;
};

#endif // SOUVENIRANDTRIP_H
