#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include <QString>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QComboBox>

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

    /// Positions of columns by name "add souvenir" and "edit souvenir" tab in admin
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
     * @brief Will intialize souvenir table to blank
     * @param table; Table to initialize
     */
    void InitializeSouvenirTable(QTableView* table);

    /*!
     * @brief Will populate souvenir table with relevant information
     */
    void PopulateSouvenirTable();

    /*!
     * @brief Will intialize stadium table to blank
     * @param table; Table to initialize
     */
    void InitializeStadiumTable(QTableView* table);

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
    Ui::Admin *ui; /// UI pointer used to display table
    int		   souvenirID; /// SouvenirID used for interaction with database
    int        selectedTeamID = 0; /// Selected team used for interaction with database
};

#endif // ADMIN_H
