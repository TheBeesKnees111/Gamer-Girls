#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include <QString>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QComboBox>
#include "MapADT.h"

/*!
 * @brief Souvenir struct exists to circumvent QOBJECT's inability to invoke copy constructor
 */
struct Souvenir
{
    /// Souvenir ID
	int     souvenirID;
    /// Souvenir's team ID
	int     teamID;
    /// Souvenir name
	QString itemName;
    /// Souvenir price
	float   price;

    /*!
     * @brief Friend function to overload comparison operator
     * @param souvenir; Origin souvenir
     * @param otherSouvenir; Destination souvenir
     * @return bool; Status of object equality
     */
	friend bool operator == (const Souvenir& souvenir, const Souvenir& otherSouvenir)
	{
		return (souvenir.souvenirID == otherSouvenir.souvenirID &&
				souvenir.teamID     == otherSouvenir.teamID     &&
				souvenir.itemName   == otherSouvenir.itemName   &&
				souvenir.price      == otherSouvenir.price);
	}

    /*!
     * @brief Friend function to overload ostream operator
     * @param output; Output desired
     * @param souvenir; Souvenir object to output
     * @return ostream; Ostream object to output
     */
	friend ostream& operator << (ostream& output, const Souvenir& souvenir)
	{
		output  << "SouvenirID: " << souvenir.souvenirID << endl;
		output  << "Team ID:    " << souvenir.teamID     << endl;
		output  << "Item Name:  " << souvenir.itemName.toStdString()   << endl;
		output  << "Item Price: " << souvenir.price      << endl << endl;
	}

    /*!
     * @brief Mutator to alter souvenir's ID
     * @param value; Souvenir's new ID
     */
	void SetSouvenirID(int value)
	{
		souvenirID = value;
	}

    /*!
     * @brief Mutator to alter souvenir's team's ID
     * @param value; Souvenir's team's new ID
     */
	void SetTeamID    (int value)
	{
		teamID = value;
	}

    /*!
     * @brief Mutator to alter souvenir's name
     * @param value; Souvenir's new name
     */
	void SetItemName  (const QString &value)
	{
		itemName = value;
	}

    /*!
     * @brief Mutator to alter souvenir's price
     * @param value; Souvenir's new price
     */
	void SetItemPrice (float value)
	{
		price = value;
	}
};


/*!
 * @class Admin
 * @brief The Admin class is an object that manages all administrator module functionality
 */
namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    /*!
     * @brief Enum represents ui pages of administrator section
     */
    enum AdminPages { };

    /// Number of columns in "add souvenir" and "edit souvenir" tab in admin (name, team, price)
    const int SOUVENIR_TABLE_COL_COUNT = 3;

    /// Names of column headers: e.x. { "Team Name", "" } "add souvenir" and "edit souvenir" tab in admin
    QStringList souvenirTableColNames { "Team Name", "Souvenir Name" , "Souvenir Price" };

    /// Default souvenirs for new teams
	QStringList defaultSouvenirs = {"Signed Helmets",
									"Autographed Football",
									"Team Pennant",
									"Team Picture",
									"Team Jersey"};
    /// Prices for default souvenirs
	QVector <double> souvenirPrices = {77.99, 99.89, 17.99, 29.99, 199.99};

	//Position of data in souvenir column
	enum SouvenirTableColumns
	{
		SOUVENIR_ID,
		TEAM_ID,
		ITEM_NAME,
		ITEM_PRICE
	};

    // Positions of columns by name "add souvenir" and "edit souvenir" tab in admin
    enum SouvenirTableColPositions { I_TEAM, I_NAME, I_PRICE };

    /// Positions of columns by name in "edit stadium" tab of admin
    enum stadiumTableColPositions { S_NAME, S_TEAM, S_CAPACITY, S_LOCATION, S_SURFACE_TYPE, S_ROOF_TYPE, S_DATE_OPENED };

    /*!
     * @brief Populates values in combobox
     * @param sqlQuery; Query used to populate combobox
     * @param comboBox; Combobox object to populate
     */
	void PopulateComboBoxes(QString sqlQuery, QComboBox* comboBox);

    /*!
     * @brief Populates items in combobox
     * @param sqlQuery; Query used to populate combobox
     * @param comboBox; Combobox object to populate
     */
	void PopulateComboBoxesItems(QString sqlQuery, QComboBox* comboBox);

    /*!
     * @brief Will populate souvenir table with relevant information
     */
    void PopulateSouvenirTable();

    /*!
     * @brief Will populate souvenir table with relevant information
     */
    void PopulateStadiumTable();

    /*!
     * @brief Will populate purchases table with relevant information
     */
	void PopulatePurchasesTable();

    /*!
     * @brief Will determine if user input consists only of spaces
     * @param value; Value to text
     * @return bool; True/False of whether or not input is valid
     */
	bool IsOnlySpaces(QString& value);

    /*!
     * @brief Constructor
     * @param parent; Pointer to parent object
     */
    explicit Admin(QWidget *parent = nullptr);

	///Initialize map to store all souvenir data
	void InitializeMapSouvenirData();

	/// Destructor
    /*!
     * @brief Destructor
     */
    ~Admin();

private slots:

    /*!
     * @brief This function will create a pointer to the MainWindow UI. The admin page will be hidden before showing the Main Window
     */
	void on_Home_PushButton_clicked();

    /*!
     * @brief When the button is pushed the database will be queried to add the team with all information entered in a file
     */
	void on_Read_In_From_File_Button_clicked();

    /*!
     * @brief Add souvenir to database and datatable
     */
	void on_Add_Souvenir_PushButton_clicked();

    /*!
     * @brief Update inormation of item in database
     */
	void on_Update_Souvenir_PushButton_clicked();


    /*!
     * @brief Pull data from datatable when a cell is selected
     */
	void on_Update_Souvenir_Datatable_clicked(const QModelIndex &index);

    /*!
     * @brief DELETE item from datatable and from database
     */
	void on_Delete_Souvenir_PushButton_clicked();

    /*!
     * @brief Will confirm update of stadium information
     */
	void on_Update_Stadium_PushButton_clicked();

    /*!
     * @brief Will change index to stadium editing section
     */
	void on_Edit_Stadium_TableView_clicked(const QModelIndex &index);

	private:
    /// UI pointer used to display table
    Ui::Admin *ui;
    /// SouvenirID used for interaction with database
    int		   souvenirID;
    /// Selected team used for interaction with database
    int        selectedTeamID = 0;	
    
    MapADT <int, Souvenir> souvenirs;

};

#endif // ADMIN_H
