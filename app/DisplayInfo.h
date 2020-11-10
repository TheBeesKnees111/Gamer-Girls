#ifndef DISPLAYINFO_H
#define DISPLAYINFO_H

#include "mainwindow.h"
#include <QDialog>
#include <QTableWidget>

class Team;
class Souvenir;
class Stadium;

namespace Ui {
class DisplayInfo;
}

class DisplayInfo : public QDialog
{
    Q_OBJECT

public:

                /*
                 * Attributes
                 */

    // Number of columns in "Show One Team" table
    const int ONE_TEAM_COL_COUNT = 10;

    // Column positions in "Show One Team" table
    enum OneTeamColPositions
    {
        OT_TEAM_NAME, OT_STADIUM_NAME, OT_SEATING_CAP, OT_LOCATION, OT_CONFERENCE,
        OT_DIVISION, OT_SURFACE_TYPE, OT_ROOF_TYPE, OT_DATE_OPENED
    };

    // Column header names in "Show One Team" table
    QStringList oneTeamTableColNames
    {
        "Team Name", "Stadium Name", "Seating Capacity", "Location", "Conference",
        "Division", "Surface Type", "Stadium Roof Type", "Date Opened"
    };

    // Number of columns in "All Teams by Name" table
    const int ALL_TEAMS_COL_COUNT = 1;

    // Column positions in "All Teams by Name" table
    enum AllTeamsColPositions { AT_NAME };

    // Column names in "All Teams by Name" table
    QStringList allTeamsTableColNames { "Team Name" };

    // Number of columns in "All Stadiums Sorted by Stadium Name" table
    const int ALL_STADIUMS_COL_COUNT = 2;

    // Column positions in "All Stadiums Sorted by Stadium Name" table
    enum AllStadiumsColPositions { AS_STADIUM_NAME, AS_TEAM_NAME };

    // Column names in "All Stadiums Sorted by Stadium Name" table
    QStringList allStadiumsColNames { "Stadium Name", "Team Name" };

    // Number of columns in "AFC Teams" table
    const int AFC_COL_COUNT	= 2;

    // Column positions in "Display AFC Teams" table
    enum AFCTeamColPositions { AA_TEAM_NAME, AA_CONFERENCE };

    // Column names in "Display AFC Teams" table
    QStringList AFCTeamColNames { "Team Name", "Conference" };

    // Number of columns in "NFC Teams" table
    const int NFC_COL_COUNT = 2;

    // Column positions in "Display NFC Teams" table
    enum NFCTeamColPositions { AN_TEAM_NAME, AN_CONFERENCE };

    // Column names in "Display NFC Teams" table
    QStringList NFCTeamColNames { "Team Name", "Conference" };

    // Number of columns in "North NFC Teams" table
    const int NORTH_NFC_COL_COUNT = 2;

    // Column positions in "Display NFC North Teams" table
    enum NFCNorthTeamColPositions { NN_TEAM_NAME, NN_DIVISION };

    // Column names in "Display NFC North Teams" table
    QStringList NFCNorthTeamColNames { "Team Name", "Division" };

    // Number of columns in "Sort Stadiums by Date" table
    const int BY_DATE_COL_COUNT = 3;

    // Column positions in "Sort Stadiums by Date" table
    enum StadiumsByDateColPositions { SD_STADIUM_NAME, SD_TEAM_NAME, SD_DATE_OPENED };

    // Column names in "Sort Stadiums by Date" table
    QStringList StadiumsByDateColNames { "Stadium Name", "Team Name", "Date Opened"};

    // Number of columns in "Open Stadiums" table
    const int OPEN_ROOF_COL_COUNT = 3;

    // Column positions in "Display Open Stadiums" table
    enum OpenStadiumsColPositions { OS_STADIUM_NAME, OS_TEAM_NAME, OS_ROOF_TYPE };

    // Column names in "Display Open Stadiums" table
    QStringList OpenStadiumsColNames { "Stadium Name", "Team Name", "Roof Type" };

    // Number of columns in "All NFL Stadiums by Seating Cap"
    const int STADIUMS_SEATING_CAP = 3;

    // Column positions in "All NFL Stadiums by Seating Cap"
    enum SeatingCapStadiumsColPositions { SC_STADIUM_NAME, SC_TEAM_NAME, SC_SEATING_CAP };

    // Column names in "All NFL Stadiums by Seating Cap"
    QStringList SeatingCapStadiumsColNames { "Stadium Name", "Team Name", "Seating Capacity" };

    // Number of columns in "Sort Teams by Conference" table
    const int BY_CONFERENCE_COL_COUNT = 4;

    // Column positions in "Sort Teams by Conference" table
    enum TeamsByConferenceColPositions { CT_TEAM_NAME, CT_STADIUM_NAME, CT_CONFERENCE, CT_LOCATION };

    // Column names in "Sort Teams by Conference" table
    QStringList TeamsByConferenceColNames { "Team Name", "Stadium Name", "Conference", "Location" };

    // Number of columns in "Bermuda Grass Teams" table
    const int BERMUDA_GRASS_COL_COUNT = 2;

    // Column positions in "Bermuda Grass Teams" table
    enum BermudaGrassTeamsColPositions { BG_TEAM_NAME, BG_SURFACE_TYPE };

    // Column names in "Bermuda Grass Teams" table
    QStringList BermudaGrassTeamsColNames { "Team Name", "Surface Type" };

    // Number of columns in "One Team's Souvenirs" table
    const int ONE_TEAM_SOUVENIR_COL_COUNT = 3;

    // Column positions in "One Team's Souvenirs" table
    enum OneTeamSouvenirColPositions { TS_TEAM_NAME, TS_SOUVENIR_NAME, TS_PRICE };

    // Column names in "One Team's Souvenirs" table
    QStringList OneTeamSouvenirColNames { "Team Name", "Souvenir Name", "Souvenir Price" };

    // Team name combobox to be populated by database when tab is accessed
    QStringList TeamNameComboBoxLabels;

                /*
                 * Methods
                 */

    // Intializes viewer table to blank
    void InitializeViewTable (QTableWidget* table, const int &cols, const QStringList &headers);

    // Populates viewer table with information
    void PopulateViewTable (QTableWidget* table, QVector<Team*> teamList);

    // Constructor
    explicit DisplayInfo(QWidget *parent = nullptr);

    // Destructor
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

    ///This function will create a pointer to the MainWindow UI. The DisplayInfo
    /// page will be hidden before showing the Main Window
    void on_HomePushButton_clicked();

private:
    Ui::DisplayInfo *ui;
};

#endif // DISPLAYINFO_H
