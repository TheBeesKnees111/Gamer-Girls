#include "PurchaseTable.h"
#include "ui_PurchaseTable.h"
#include "Database.h"

PurchaseTable::PurchaseTable(QWidget *parent, QVector<Team*>* teamList):
    QDialog(parent),
    ui(new Ui::PurchaseTable)
 {
    ui->setupUi(this);

    // -------- START OLD DESIGN CODE -------- //

//    // create the row size for setup
//    int rowSize = path.size();
//    // setup row & column sizes
//    QTableWidget* tableWidget = ui->Route_List_TableWidget;
//    tableWidget->setRowCount(rowSize + 1);
//    tableWidget->setColumnCount(2);

//    int totalDistance = 0;

//    // loops thru the vector of StadiumDistances and displays the team name
//    // as well as the stadium
//    for (int row = 0; row < path.size(); row++)
//    {
//        // get & display team name
//        QString teamName = path[row]->getFromStadium()->getTeams().first()->getTeamName();
//        //    Items are created outside the table (with no parent widget) and inserted into the table with setItem():
//        QTableWidgetItem *newItem = new QTableWidgetItem(teamName);
//        tableWidget->setItem(row, 0, newItem);
//        // get & display stadium name
//        //    Items are created outside the table (with no parent widget) and inserted into the table with setItem():
//        newItem = new QTableWidgetItem(path[row]->getFromStadium()->getStadiumName());
//        tableWidget->setItem(row, 1, newItem);
//        // calculate total distance
//        totalDistance += path[row]->getDistance();
//    }

//    // calculate last team & stadium name
//    QTableWidgetItem *newItem = new QTableWidgetItem(teamName);
//    tableWidget->setItem(rowSize, 0, newItem);
//    newItem = new QTableWidgetItem(path[rowSize - 1]->getToStadium()->getStadiumName());
//    tableWidget->setItem(rowSize, 1, newItem);

//    // out put distance
//    ui->Total_Distance_Label->setText(QString("%1").arg(totalDistance));

//    // resize based on table contents
//    ui->Route_List_TableWidget->horizontalHeader()->setSectionResizeMode
//            (QHeaderView::ResizeToContents);
    // --------- END OLD DESIGN CODE ------------ //



    // --------- START NEW DESIGN CODE ------------ //

    // Instantiate database (for saving purchases)
    db = Database::getInstance();

    // Store object
    teamCart = teamList;

    // Create Spinboxes
    spinBoxes = new QVector<QSpinBox*>;

    // Initialize Purchase Table
    InitializePurchaseTable();

    // Populate Purchase Table
    PopulatePurchaseTable();

    // Insert Spinboxes
    InsertSpinBoxCol();

    // Sets horizontal header to resize for values in stadium totals table
    ui->stadium_totals_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

}

// Initialize Purchase Table
void PurchaseTable::InitializePurchaseTable()
{
    ui->purchase_tableWidget->clearContents();
    ui->purchase_tableWidget->setColumnCount(TABLE_COL_COUNT);
    ui->purchase_tableWidget->setHorizontalHeaderLabels(tableHeaders);
    ui->purchase_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->purchase_tableWidget->setEditTriggers(QTableView::NoEditTriggers);
    ui->purchase_tableWidget->hideColumn(KEY);
    ui->purchase_tableWidget->verticalHeader()->hide();

    DeleteAllTableRows();
}

// Populate Purchase Table
void PurchaseTable::PopulatePurchaseTable()
{
    QTableWidgetItem* priceItem;
    QString currentName;
    QString previousName;

    // For the length of the team list
    for(int teamIndex = 0; teamIndex < teamCart->size(); teamIndex++)
    {
        int souvListSize = teamCart->at(teamIndex)->getSouvenirList().size();

        // Iterate through each team's souvenir list
        for(int souvIndex = 0; souvIndex < souvListSize; souvIndex++)
        {
            // Generate food price tablewidgetitem
            priceItem = new QTableWidgetItem(QString::number(teamCart->at(teamIndex)->getSouvenirList().at(souvIndex)->getItemPrice(), 'f', 2));

            // If list is not empty
            if(ui->purchase_tableWidget->rowCount() != 0)
            {
                // Check to see if there's a match between this row's team name and the previous row's team name
                currentName = ui->purchase_tableWidget->item(ui->purchase_tableWidget->rowCount() -1, KEY)->data(0).toString();
                previousName = teamCart->at(teamIndex)->getTeamName();

                // Add a row to the end
                ui->purchase_tableWidget->insertRow(ui->purchase_tableWidget->rowCount());

                bool match = currentName == previousName;

                // If the row names do not match, insert the city name into the name column
                if(!match)
                {
                    // Insert stadium name into stadium name column
                    ui->purchase_tableWidget->setItem(ui->purchase_tableWidget->rowCount() - 1, TEAM, new QTableWidgetItem(teamCart->at(teamIndex)->getTeamName()));

                    // Insert stadium name into stadium column
                    ui->purchase_tableWidget->setItem(ui->purchase_tableWidget->rowCount() - 1, STADIUM, new QTableWidgetItem(teamCart->at(teamIndex)->getStadium()->getStadiumName()));
                }
                else // Else, insert blank name
                {
                    ui->purchase_tableWidget->setItem(ui->purchase_tableWidget->rowCount() - 1, TEAM, new QTableWidgetItem(""));
                }
            } // END if purchase table not empty
            else // if purchase table empty
            {
                // Add new row
                ui->purchase_tableWidget->insertRow(ui->purchase_tableWidget->rowCount());

                // Insert team name into team name column
                ui->purchase_tableWidget->setItem(ui->purchase_tableWidget->rowCount() - 1, TEAM, new QTableWidgetItem(teamCart->at(teamIndex)->getTeamName()));

                // Insert stadium name into stadium column
                ui->purchase_tableWidget->setItem(ui->purchase_tableWidget->rowCount() - 1, STADIUM, new QTableWidgetItem(teamCart->at(teamIndex)->getStadium()->getStadiumName()));
            }

            // Insert team name into key column
            ui->purchase_tableWidget->setItem(ui->purchase_tableWidget->rowCount() - 1, KEY, new QTableWidgetItem(teamCart->at(teamIndex)->getTeamName()));
            // Add souvenir name
            ui->purchase_tableWidget->setItem(ui->purchase_tableWidget->rowCount() - 1, S_NAME, new QTableWidgetItem(teamCart->at(teamIndex)->getSouvenirList().at(souvIndex)->getItemName()));
            // Add souvenir price
            ui->purchase_tableWidget->setItem(ui->purchase_tableWidget->rowCount() - 1, S_PRICE, priceItem);
        } // END for iterate through souvenir list
    } // END for iterate through team list
}

// Delete table rows
void PurchaseTable::DeleteAllTableRows()
{
    const int ROW_COUNT = ui->purchase_tableWidget->rowCount();

    for(int index = 0; index < ROW_COUNT; index++)
    {
        ui->purchase_tableWidget->removeRow(0);
    }
}

// Insert spinbox column
void PurchaseTable::InsertSpinBoxCol()
{
    QSpinBox *sBox;

    spinBoxes->clear();

    for(int row = 0; row < ui->purchase_tableWidget->rowCount(); row++)
    {
        sBox = new QSpinBox(ui->purchase_tableWidget);
        // connects the change in spinbox values to dynamic display
        connect (sBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &PurchaseTable::qtyChanged);
        sBox->setRange(SPIN_MIN, SPIN_MAX);
        ui->purchase_tableWidget->setCellWidget(row, QTY, sBox);
        spinBoxes->append(sBox);
    }
}

// Write purchase info to db
void PurchaseTable::on_okay_pushButton_clicked()
{
    // Get qtyPurchased from spinboxes
    GetSouvenirQtys();

    // Write purchase information to db
    db->SavePurchase(teamCart);

    // Delete team data for use in next trip
    DestroyTeams();

    // Disable button
    ui->okay_pushButton->setDisabled(true);
}

// Destroy cities list used in purchasing and receipt page
void PurchaseTable::DestroyTeams()
{
    int size = teamCart->size();

    for(int index = 0; index < size; index++)
    {
        teamCart->pop_front();
    }
}

// Helper function retrieves qtyPurchased from spinboxes and loads them into team cart
void PurchaseTable::GetSouvenirQtys()
{
    int tableRow = 0;

    // Outer loop to move through team objects
    for(int teamIndex = 0; teamIndex < teamCart->size(); teamIndex++)
    {
        // Inner loop to move through each team's souvenir list
        for(int souvIndex = 0; souvIndex < teamCart->at(teamIndex)->getSouvenirList().size(); souvIndex++)
        {
            // Add food to item
            teamCart->operator[](teamIndex)->getSouvenirList().at(souvIndex)->setQtyPurchased(spinBoxes->at(tableRow)->value());
            tableRow++;

//            // DEBUG: Output items
//            if(teamCart->at(teamIndex)->getSouvenirList().at(souvIndex)->getQtyPurchased() > 0)
//            {
//                qDebug() << "Item Name: " << teamCart->at(teamIndex)->getTeamName();
//                qDebug() << "Item Name: " << teamCart->at(teamIndex)->getSouvenirList().at(souvIndex)->getItemName();
//                qDebug() << "Qty Purchased: " << teamCart->at(teamIndex)->getSouvenirList().at(souvIndex)->getQtyPurchased();
//            }
        }// End inner loop
    }// End outer loop
}

// Destructor
PurchaseTable::~PurchaseTable()
{
    delete ui;
}

// When any quantities are changed, this will update the price & qty totals dynamically
void PurchaseTable::qtyChanged(int value)
{
    // initialization
    float totalPrice = 0;
    float stadiumPrice = 0;
    int   stadiumQty = 0;
    int j = 0;

    // loop through purchase table & setup for updating all tables
        for (int i = 0; i < ui->purchase_tableWidget->rowCount(); i++)
    {
        // get stadium name
        QString stadium;
        if (ui->purchase_tableWidget->item(i, 1) != nullptr)
            stadium = ui->purchase_tableWidget->item(i, 1)->text();
        // get price for specific souvenir
        QString priceText = ui->purchase_tableWidget->item(i, 4)->text();
        float price = priceText.toFloat();
        // get qty
        // cellWidget gives us a QWidget* in this cell.  typecast it to a QSpinBox* to get the value.
        QWidget *cellWidget = ui->purchase_tableWidget->cellWidget(i, 5);
        int qty = ((QSpinBox*)cellWidget)->value();

        // calculate totalPrice
        totalPrice += price * qty;

        // when the name changes, reset to update next stadium row
        if (stadium != "")
        {
            stadiumPrice = 0;
            stadiumQty = 0;
            j++;
            ui->stadium_totals_tableWidget->setRowCount(j);
            ui->stadium_totals_tableWidget->setItem(j-1, 0, new QTableWidgetItem(stadium));
        }
        // get current stadium values
        stadiumPrice += price * qty;
        stadiumQty += qty;

        // update stadium totals table
        ui->stadium_totals_tableWidget->setItem(j-1, 1, new QTableWidgetItem(tr("%1").arg(stadiumQty)));
        ui->stadium_totals_tableWidget->setItem(j-1, 2, new QTableWidgetItem(tr("$%1").arg(stadiumPrice, 0, 'f', 2)));
    }
    // update totalPurchase field
    ui->total_cost_Label->setText(tr("$%1").arg(totalPrice, 0, 'f', 2));
}
