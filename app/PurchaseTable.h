#ifndef PurchaseTable_H
#define PurchaseTable_H

#include <QDialog>
#include <QStandardItemModel>
#include <QVector>
#include <QSpinBox>
#include "Team.h"
#include "Stadium.h"
#include "Souvenir.h"
#include "Database.h"

namespace Ui {
class PurchaseTable;
}

/*!
 * @class PurchaseTable
 * @brief The PurchaseTable class contains all objects necessary to manage customer purchases
 */
class PurchaseTable : public QDialog
{
    Q_OBJECT

public:
    /// Column Count
    const int TABLE_COL_COUNT = 6;
    /// Column Positions
    enum tableColPositions { KEY, STADIUM, TEAM, S_NAME, S_PRICE, QTY };
    /// Column Header names
    QStringList tableHeaders { "KEY", "Stadium", "Team Name", "Souvenir Name", "Souvenir Price", "Quantity" };
    /// Souvenir Spinbox minimum
    const int SPIN_MIN = 0;
    /// Souvenir Spinbox maximum
    const int SPIN_MAX = 419;
    /// Vector of pointers to spinbox pointers. Needed for dynamically creating spinboxes on purchase page
    QVector<QSpinBox*>* spinBoxes;

    /*!
     * @brief Initializes Purchase Table to blank
     */
    void InitializePurchaseTable();

    /*!
     * @brief Populates Purchase Table with necessary data
     */
    void PopulatePurchaseTable();

    /*!
     * @brief Inserts dynamic spinboxes into rightmost column of purchase table
     */
    void InsertSpinBoxCol();

    /*!
     * @brief Helper function deletes all table rows to initialize table to blank
     */
    void DeleteAllTableRows();

    /*!
     * @brief Destroys shopping cart so that it can be repopulated in future purchases
     */
    void DestroyTeams();

    /*!
     * @brief Collects quantity of each souvenir that customer wishes to purchase for use in creating receipt and record
     */
    void GetSouvenirQtys();

    /*!
     * @brief Parameterized construct takes in list of visited stadium to populate shopping cart
     * @param *parent; Pointer to parent object
     * @param *teamList; Pointer to trip list used to populate shopping cart
     */
    explicit PurchaseTable(QWidget *parent, QVector<Team*>* teamList);

    ~PurchaseTable();

public slots:
    /*!
     * @brief Slot to take action when quantity of spinboxes is changed
     * @param value; New value selected by user
     */
    void qtyChanged(int value);

private slots:

    /*!
     * @brief Finalizes purchase in record and writes to database
     */
    void on_okay_pushButton_clicked();

private:
    Ui::PurchaseTable *ui; /// Pointer to ui object
    QVector<Team*>* teamCart; /// Pointer to shopping list information
    Database* db; /// Pointer to database object
};

#endif // PurchaseTable_H
