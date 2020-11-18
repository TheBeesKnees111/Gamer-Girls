#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include <QString>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QComboBox>

namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
// Attributes

    // TODO Page indexes
    enum AdminPages { };

    /*
     * Admin - Add/Delete/Import Section
     */

    // Number of columns in "add souvenir" and "edit souvenir" tab in admin (name, team, price)
    const int SOUVENIR_TABLE_COL_COUNT = 3;

    // Names of column headers: e.x. { "Team Name", "" } "add souvenir" and "edit souvenir" tab in admin
    QStringList souvenirTableColNames { "Team Name", "Souvenir Name" , "Souvenir Price" };

    // Positions of columns by name "add souvenir" and "edit souvenir" tab in admin
    enum SouvenirTableColPositions { I_TEAM, I_NAME, I_PRICE };

    // List of all team names
    QStringList teamNameComboBoxLabels;

    // minimum value for price of souvenir in add & edit sections
    const int SOUVENIR_PRICE_SPINBOX_MIN = 0;

    // maximum value for price of souvenir in add & edit sections
    const int SOUVENIR_PRICE_SPINBOX_MAX = 9999;


    /*
     * Admin - Edit Stadium Info
     */

    // Number of columns in "edit stadium" tab of admin
    const int STADIUM_TABLE_COL_COUNT = 7;

    // List of stadium table column names in "edit stadium" tab of admin
    QStringList stadiumTableColNames { "Stadium Name", "Team Name", "Seating Capacity", "Location", "Surface Type", "Roof Type", "Date Opened" };

    // Positions of columns by name in "edit stadium" tab of admin
    enum stadiumTableColPositions { S_NAME, S_TEAM, S_CAPACITY, S_LOCATION, S_SURFACE_TYPE, S_ROOF_TYPE, S_DATE_OPENED };

    // Combobox labels for conference type
    QStringList conferenceComboBoxLabels { "National Football Conference", "American Football Conference" };

    // Combobox labels for division type
    QStringList divisionComboBoxLabels { "NFC West", "NFC South", "NFC North", "NFC East", "AFC North", "AFC West", "AFC South", "AFC East" };

    // Combobox labels for surface type
    QStringList surfaceTypeComboBoxLabels
    {
        "Bermuda Grass", "FieldTurf Classic HD", "A-Turf Titan 50", "Kentucky Bluegrass",
        "Hellas Matrix Turf", "Desso GrassMaster", "Platinum TE Paspalum",
        "UBU Speed Series S5-M Synthetic Turf", "FieldTurf Revolution" };

    // Combobox labels for roof type
    QStringList roofTypeComboBoxLabels { "Retractable", "Fixed", "Open" };

    // Minimum for seating capacity spinbox
    const int SEATING_CAP_SPINBOX_MIN = 0;
    // maximum for seating capacity spinbox
    const int SEATING_CAP_SPINBOX_MAX = 120000;

    // Minimum for date opened spinbox
    const int DATE_OPENED_SPINBOX_MIN = 1900;

    // Maximum for date opened spinbox
    const int DATE_OPENED_SPINBOX_MAX = 2100;

    /*
     * Methods
     */

	// Populates combo boxes with relevant information
	void PopulateComboBoxes(QString sqlQuery, QComboBox* comboBox);

    // Initializes souvenir table to blank
    void InitializeSouvenirTable (QTableView* table);

    // Populates souvenir table with relevant information
	void PopulateSouvenirTable (QSqlQueryModel* model);

    // Intializes stadium table to blank
    void InitializeStadiumTable (QTableView* table);

    // Populates stadium table with relevant information
	void PopulateStadiumTable (QSqlQueryModel* model);

    // Constructor
    explicit Admin(QWidget *parent = nullptr);

    // Destructor
    ~Admin();

private slots:

    ///This function will create a pointer to the MainWindow UI. The admin page will be
    /// hidden before showing the Main Window
	void on_Home_PushButton_clicked();

	///This will check that all data for a team has been selected
	///When the button is pushed the database will be queried to add the team
	///with all information selected
	///If any field is left blank then it will display an error message
	void on_Add_Team_PushButton_clicked();

	private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
