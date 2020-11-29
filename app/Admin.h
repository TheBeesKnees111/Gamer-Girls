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

	//Default souvenirs for new teams
	QStringList defaultSouvenirs = {"Signed Helmets",
									"Autographed Football",
									"Team Pennant",
									"Team Picture",
									"Team Jersey"};
	//Prices for default souvenirs
	QVector <double> souvenirPrices = {77.99, 99.89, 17.99, 29.99, 199.99};

    // Positions of columns by name "add souvenir" and "edit souvenir" tab in admin
    enum SouvenirTableColPositions { I_TEAM, I_NAME, I_PRICE };

    // Positions of columns by name in "edit stadium" tab of admin
    enum stadiumTableColPositions { S_NAME, S_TEAM, S_CAPACITY, S_LOCATION, S_SURFACE_TYPE, S_ROOF_TYPE, S_DATE_OPENED };


    /*
     * Methods
     */

	///Give all comboboxes values
	void PopulateComboBoxes(QString sqlQuery, QComboBox* comboBox);

	/// Populates combo boxes with team objects
	void PopulateComboBoxesItems(QString sqlQuery, QComboBox* comboBox);

	/// Initializes souvenir table to blank
    void InitializeSouvenirTable (QTableView* table);

	/// Populates souvenir table with relevant information
	void PopulateSouvenirTable ();

	/// Intializes stadium table to blank
    void InitializeStadiumTable (QTableView* table);

	/// Populates stadium table with relevant information
	void PopulateStadiumTable ();

	///Populate table of purchases
	void PopulatePurchasesTable();

	///Check if line edit is only composed of spaces
	bool IsOnlySpaces(QString& value);

	/// Constructor
    explicit Admin(QWidget *parent = nullptr);

	/// Destructor
    ~Admin();

private slots:

    ///This function will create a pointer to the MainWindow UI. The admin page will be
    /// hidden before showing the Main Window
	void on_Home_PushButton_clicked();

	///When the button is pushed the database will be queried to add the team
	///with all information entered in a file
	void on_Read_In_From_File_Button_clicked();

	///Add souvenir to database and datatable
	void on_Add_Souvenir_PushButton_clicked();

	///Update inormation of item in database
	void on_Update_Souvenir_PushButton_clicked();

	///Pull data from datatable when a cell is selected
	void on_Update_Souvenir_Datatable_clicked(const QModelIndex &index);

	///DELETE item from datatable and from database
	void on_Delete_Souvenir_PushButton_clicked();

	///Updating stadium info
	void on_Update_Stadium_PushButton_clicked();

	void on_Edit_Stadium_TableView_clicked(const QModelIndex &index);

	private:
    Ui::Admin *ui;
	int		   souvenirID;
	int        selectedTeamID = 0;
};

#endif // ADMIN_H
