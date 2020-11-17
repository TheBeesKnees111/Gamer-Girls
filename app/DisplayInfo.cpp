#include "mainwindow.h"
#include <QDialog>
#include "DisplayInfo.h"
#include "ui_DisplayInfo.h"
#include "Team.h"
#include "Stadium.h"
#include "Souvenir.h"
#include "Database.h"
#include <QVector>

DisplayInfo::DisplayInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayInfo)
{
    ui->setupUi(this);

    // TODO the database exists in the central mainwindow object. because this
    // creates a new connection to 'ui' which previously referenced mainwindow,
    // i created a new database connection here since it's out of scope.
    // there's probably a better way to do it, so lemme know
    db = new Database;
    TeamNameComboBoxLabels = db->GetTeamNames();

    // Initialize and populate combobox
    ui->Select_Stadium_ComboBox->clear();
    ui->Select_Stadium_ComboBox->addItems(TeamNameComboBoxLabels);
}



// Intializes viewer table to blank
void DisplayInfo::InitializeViewTable (QTableWidget* table, const int &cols, const QStringList &headers)
{
    table->clearContents();
    table->setColumnCount(cols);
    table->setHorizontalHeaderLabels(headers);
    table->setEditTriggers(QTableView::NoEditTriggers);
    table->verticalHeader()->hide();

    DeleteAllTableRows(table);
}

// Deletes contents of passed in table
void DisplayInfo::DeleteAllTableRows(QTableWidget *table)
{
    const int ROW_COUNT = table->rowCount();

    for(int index = 0; index < ROW_COUNT; index++)
    {
        table->removeRow(0);
    }
}

// Populates viewer table with information
void DisplayInfo::PopulateViewTable (QTableWidget* table, QVector<Team*> teamList)
{

}

// Populates viewer table with one team's information
void DisplayInfo::PopulateOneTeam(QTableWidget* table, Team* team)
{
    // Date opened item
    QTableWidgetItem* dateOpenedItem;
    dateOpenedItem = new QTableWidgetItem(QString::number(team->getStadium()->getDateOpened()));

    // Insert row
    table->insertRow(0);

    // Populate data
    table->setItem(0, OT_TEAM_NAME, new QTableWidgetItem(team->getTeamName()));
    table->setItem(0, OT_STADIUM_NAME, new QTableWidgetItem(team->getStadium()->getStadiumName()));
    table->setItem(0, OT_SEATING_CAP, new QTableWidgetItem(team->getStadium()->getSeatingCapacity()));
    table->setItem(0, OT_LOCATION, new QTableWidgetItem(team->getStadium()->getLocation()));
    table->setItem(0, OT_CONFERENCE, new QTableWidgetItem(team->getConference()));
    table->setItem(0, OT_DIVISION, new QTableWidgetItem(team->getDivision()));
    table->setItem(0, OT_SURFACE_TYPE, new QTableWidgetItem(team->getStadium()->getSurfaceType()));
    table->setItem(0, OT_ROOF_TYPE, new QTableWidgetItem(team->getStadium()->getRoofType()));
    table->setItem(0, OT_DATE_OPENED, dateOpenedItem);
}

void DisplayInfo::PopulateAllTeams(QTableWidget* table, QStringList teamList)
{
    for(int index = 0; index < teamList.size(); index++)
    {
        // Create Row
        table->insertRow(table->rowCount());
        // Populate Name Column
        table->setItem(table->rowCount() -1, AT_NAME, new QTableWidgetItem(teamList.at(index)));
    }
}

// Populates stadiums with teams ordered by stadium name (requirement 4)
void DisplayInfo::PopulateTeamsOrderByStadium(QVector<Team*>* teamList)
{
    for(int index = 0; index < teamList->size(); index++)
    {
        // Create Row
        ui->Datatable_TableWidget->insertRow(ui->Datatable_TableWidget->rowCount());
        // Populate Stadium Name Column
        ui->Datatable_TableWidget->setItem(ui->Datatable_TableWidget->rowCount() -1, AS_STADIUM_NAME, new QTableWidgetItem(teamList->at(index)->getStadium()->getStadiumName()));
        // Populate Team Name Column
        ui->Datatable_TableWidget->setItem(ui->Datatable_TableWidget->rowCount() -1, AS_TEAM_NAME, new QTableWidgetItem(teamList->at(index)->getTeamName()));
    }
}

// Populates teams from AFC conference ordered by team name (requirement 5)
void DisplayInfo::PopulateConferenceTeams(QVector<Team*>* teamList)
{
    for(int index = 0; index < teamList->size(); index++)
    {
        // Create Row
        ui->Datatable_TableWidget->insertRow(ui->Datatable_TableWidget->rowCount());
        // Populate Team Name Column
        ui->Datatable_TableWidget->setItem(ui->Datatable_TableWidget->rowCount() -1, AN_TEAM_NAME, new QTableWidgetItem(teamList->at(index)->getTeamName()));
        // Populate Conference/Division Name Column
        ui->Datatable_TableWidget->setItem(ui->Datatable_TableWidget->rowCount() -1, AN_CONFERENCE, new QTableWidgetItem(teamList->at(index)->getConference()));
    }
}

void DisplayInfo::PopulateStadiumsByDate(QVector<Team*>* teamList)
{
    // Date opened item
    QTableWidgetItem* dateOpenedItem;
    for(int index = 0; index < teamList->size(); index++)
    {
        // Set date opened item
        dateOpenedItem = new QTableWidgetItem(QString::number(teamList->at(index)->getStadium()->getDateOpened()));
        // Create Row
        ui->Datatable_TableWidget->insertRow(ui->Datatable_TableWidget->rowCount());
        // Populate Stadium Name Column
        ui->Datatable_TableWidget->setItem(ui->Datatable_TableWidget->rowCount() -1, SD_TEAM_NAME, new QTableWidgetItem(teamList->at(index)->getTeamName()));
        // Populate Team Name Column
        ui->Datatable_TableWidget->setItem(ui->Datatable_TableWidget->rowCount() -1, SD_STADIUM_NAME, new QTableWidgetItem(teamList->at(index)->getStadium()->getStadiumName()));
        // Populate Date Opened Column
        ui->Datatable_TableWidget->setItem(ui->Datatable_TableWidget->rowCount() -1, SD_DATE_OPENED, dateOpenedItem);
    }
}


// ------------ NAVIGATION START -------------- //


DisplayInfo::~DisplayInfo()
{
    delete ui;
}

///This function will create a pointer to the MainWindow UI. The DisplayInfo
/// page will be hidden before showing the Main Window
void DisplayInfo::on_Home_PushButton_clicked()
{
    MainWindow *mainWindow;
    mainWindow = new MainWindow(this);

    hide();

    mainWindow -> show();

}

void DisplayInfo::on_Select_Stadium_ComboBox_activated(const QString &arg1)
{
    Team* team = new Team;

    // Pass string to database to pull team information
    team = db->GetSingleTeam(arg1);

    // Initialize Table
    InitializeViewTable(ui->Datatable_TableWidget, ONE_TEAM_COL_COUNT, oneTeamTableColNames);

    // Populate table
    PopulateOneTeam(ui->Datatable_TableWidget, team);
}

void DisplayInfo::on_Print_All_Teams_PushButton_clicked()
{
    // Initialize Table
    InitializeViewTable(ui->Datatable_TableWidget, ALL_TEAMS_COL_COUNT, allTeamsTableColNames);

    // Populate Table
    PopulateAllTeams(ui->Datatable_TableWidget, TeamNameComboBoxLabels);
}

void DisplayInfo::on_Print_Stadium_PushButton_clicked()
{
    QVector<Team*>* teamList = new QVector<Team*>;
    teamList = db->GetTeamsOrderByStadium();

    // Initialize Table
    InitializeViewTable(ui->Datatable_TableWidget, ALL_STADIUMS_COL_COUNT, allStadiumsColNames);

    // Populate Table
    PopulateTeamsOrderByStadium(teamList);
}


void DisplayInfo::on_Print_AFC_Teams_PushButton_clicked()
{
    QVector<Team*>* teamList = new QVector<Team*>;
    teamList = db->GetAFCTeamsOrderByTeamName();

    // Initialize Table
    InitializeViewTable(ui->Datatable_TableWidget, AFC_COL_COUNT, AFCTeamColNames);

    // Populate Table
    PopulateConferenceTeams(teamList);
}

void DisplayInfo::on_Print_NFC_Teams_PushButton_clicked()
{
    QVector<Team*>* teamList = new QVector<Team*>;
    teamList = db->GetNFCTeamsOrderByTeamName();

    // Initialize Table
    InitializeViewTable(ui->Datatable_TableWidget, NFC_COL_COUNT, NFCTeamColNames);

    // Populate Table
    PopulateConferenceTeams(teamList);
}

void DisplayInfo::on_Print_North_NFC_Teams_PushButton_clicked()
{
    QVector<Team*>* teamList = new QVector<Team*>;
    teamList = db->GetNorthNFCTeamsOrderByTeamName();

    // Initialize Table
    InitializeViewTable(ui->Datatable_TableWidget, NORTH_NFC_COL_COUNT, NFCNorthTeamColNames);

    // Populate Table
    PopulateConferenceTeams(teamList);
}

void DisplayInfo::on_Print_Stadium_B_yDate_PushButton_clicked()
{
    QVector<Team*>* teamList = new QVector<Team*>;
    teamList = db->GetStadiumsOrderByDateOpened();

    // Initialize Table
    InitializeViewTable(ui->Datatable_TableWidget, BY_DATE_COL_COUNT, StadiumsByDateColNames);

    // Populate Table
    PopulateStadiumsByDate(teamList);
}

// ------------ NAVIGATION END -------------- //









