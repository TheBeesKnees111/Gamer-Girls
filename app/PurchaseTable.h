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

class PurchaseTable : public QDialog
{
    Q_OBJECT

public:
    // Col Count
    const int TABLE_COL_COUNT = 6;
    // Col Positions
    enum tableColPositions { KEY, STADIUM, TEAM, S_NAME, S_PRICE, QTY };
    // Header names
    QStringList tableHeaders { "KEY", "Stadium", "Team Name", "Souvenir Name", "Souvenir Price", "Quantity" };
    // Spinbox minimum
    const int SPIN_MIN = 0;
    // Spinbox maximum
    const int SPIN_MAX = 420;
    // Vector of pointers to spinbox pointers. Needed for dynamically creating spinboxes on purchase page
    QVector<QSpinBox*>* spinBoxes;

    // Initialize Purchase Table
    void InitializePurchaseTable();

    // Populate Purchase Table
    void PopulatePurchaseTable();

    // Insert dynamic spinboxes
    void InsertSpinBoxCol();

    // Clear table
    void DeleteAllTableRows();

    // Destroy team object for future use
    void DestroyTeams();

    // Collect quantity of each souvenir purchased and add to team object
    void GetSouvenirQtys();

    // Imports Team data from any trip. Populates purchase table
    explicit PurchaseTable(QWidget *parent, QVector<Team*>* teamList);

    ~PurchaseTable();

private slots:

    void on_okay_pushButton_clicked();

private:
    Ui::PurchaseTable *ui;
    QVector<Team*>* teamCart;
    Database* db;
};

#endif // PurchaseTable_H
