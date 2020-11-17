//#include "DPathUtils.h"

//vector<StadiumNode> createStadiumsFromDatabase()
//{
//    vector<StadiumNode> StadiumNodeList;
//    QSqlQuery query;
//    query.exec("SELECT teamName FROM teamInfo");
//    while (query.next())
//    {
//        // for the value in column 0 of the current row, turn it to a string
//        // then create a QString value because it's QtSql
//        QString team = query.value(0).toString();
//        // converts Qstring to a standard std::string then builds a city node
//        // w/ that & puts it in the vector
//        StadiumNodeList.push_back({team.toStdString()});
//    }

//    return StadiumNodeList;

//}

//vector<StadiumConnection> createConnectionsFromDatabase()
//{

//    vector<StadiumConnection> ConnectionNodeList;
//    QSqlQuery query;
//    query.exec("SELECT fromStadium, toStadium, milesBetween FROM teamDistances " );
//    while (query.next())
//    {
//        // for the value in column 0 of the current row, turn it to an int
//        int fromStadiumID = query.value(0).toInt();
//        int toStadiumID = query.value(1).toInt();
//        int milesBetween = query.value(2).toInt();

//        QSqlQuery query;
//        query.prepare("SELECT teamName FROM teamInfo "
//                  "WHERE teamID = (:ID)");
//        query.bindValue(":ID", fromStadiumID);
//        if(!query.exec())
//            qDebug() << "Failed: " << query.lastError();
//        query.next();	// Gets the first row
//        string fromStadium = query.value(0).toString().toStdString();

//        query.prepare("SELECT teamName FROM teamInfo "
//                  "WHERE teamID = (:ID)");
//        query.bindValue(":ID", toStadiumID);
//        if(!query.exec())
//            qDebug() << "Failed: " << query.lastError();
//        query.next();
//        string toStadium = query.value(0).toString().toStdString();

//        // Creating the CityConnection and adding it to the vector
//        ConnectionNodeList.push_back({{fromStadium},	// Creating StadiumNode fromStadium
//                                      {toStadium},		// crating StadiumNode toStadium
//                                      milesBetween });	// creating milesBetween
//    }

//    return ConnectionNodeList;
//}

//StadiumGraph createStadiumGraphFromDatabase()
//{
//    vector<StadiumConnection> edgeList = createConnectionsFromDatabase();
//    map<StadiumNode, vector<StadiumConnection>> adjacencyList;

//    // Adjacency list from the edge list
//    for(auto edge : edgeList)
//    {
//        string fromStadium = edge.fromStadium.name;
//        string toStadium = edge.toStadium.name;
//        int milesBetween = edge.milesBetween;

//        // Creates adjacencyList if it doesn't already exist
//        adjacencyList[{fromStadium}].push_back(edge);
//        // creating the reverse edge
//        adjacencyList[{toStadium}].push_back({
//                              {toStadium},		// crating StadiumNode toStadium
//                              {fromStadium},	// Creating StadiumNode fromStadium
//                              milesBetween });
//    }
//    return {createStadiumsFromDatabase(), adjacencyList};
//}
