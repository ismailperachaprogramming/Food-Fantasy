#include "database.h"

Database::Database()
{
    //Connect to "foodfantasy.db"

    db = QSqlDatabase::addDatabase("QSQLITE");
    QDir dir = QCoreApplication::applicationDirPath();
    db.setDatabaseName("C:/Users/Michael/Desktop/CS1D_Project1-new-branch/db/FOODFANTASY.db");

    if (db.open()){
        qInfo() << "Database connection established!";
    } else {
        qInfo() << "Database connection error occured.";
    }
}

bool Database::addRestaurants(std::vector<Restaurant> restaurants){

    for (int i = 0; i < restaurants.size(); i++){
        Restaurant currRestaurant = restaurants[i];

        std::vector<double> distancesVector = currRestaurant.getDistances();
        QString name = currRestaurant.getName();
        int id = currRestaurant.getID();
        double saddleback = currRestaurant.getSaddlebackDistance();
        std::vector<MenuItem> menuVector = currRestaurant.getMenu();

        //loop through menu of restaurant to create json array of objects

        QJsonArray distances;
        //loop through distances vector to create a json array of distances
        for (int i = 0; i < distancesVector.size(); i++){
            distances.push_back(distancesVector[i]);
        }

        QJsonArray menu;

        for (int i = 0; i < menuVector.size(); i++){
            auto item = QJsonObject(
            {
            qMakePair(QString("name"), QJsonValue(menuVector[i].name)),
            qMakePair(QString("price"), QJsonValue(menuVector[i].price))
            });
            menu.push_back(QJsonValue(item));
        }

        QSqlQuery query;

        qInfo() << "Db open? " << this->db.open();
        qInfo() << "Menu 1: " << distances.at(1);

        QJsonDocument distancesDoc(distances);
        QJsonDocument menusDoc(menu);

        query.prepare("INSERT INTO restaurants (id,name,distances,saddleback_distance,menu) " "VALUES(:id,:name,:distances,:saddleback_distance,:menu)");
        query.bindValue(":id", id);
        query.bindValue(":name", name);
        query.bindValue(":distances", distancesDoc.toJson());
        query.bindValue(":saddleback_distance", saddleback);
        query.bindValue(":menu", menusDoc.toJson());

        qInfo() << query.boundValues().size();
        if (query.exec()){
            qInfo() << "Inserted";
        } else {
            qInfo() << "Error, " << query.lastError();
        }
    }
    return 1;
}

void Database::modifyMenu(Restaurant restaurant, std::vector<MenuItem> menu){
    //modify menu given restaurant
    //function will serialize menu with json and save as TEXT/STRING in 'menu' columns where restaurant is passed in restaurant
    //find proper restaurant by looking at restaurant id then query sql database based on that

    //returns true if operation is completed

    //loop through menu
    for (int i = 0; i <= menu.size(); i++){
        MenuItem currItem = menu[i];
    }
}

bool Database::getRestaurants(std::vector<Restaurant>& restaurants){
    if (restaurants.size() > 0){
        restaurants.clear();
    }
    //modified passed in restaurants vector

    //query all restaurants in restaurants table
    QSqlQuery query("select * from restaurants");
    QSqlRecord rec = query.record();
    while (query.next()){

        std::vector<double> distancesVector;
        std::vector<MenuItem> menuVector;

        //Putting column data into variables
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString distances = query.value(2).toString();
        double saddlebackDistance = query.value(3).toDouble();
        QString menu = query.value(4).toString();

        QJsonDocument json = QJsonDocument::fromJson(distances.toUtf8());
        QJsonArray jsonArray = json.array();

        for (int i = 0; i < jsonArray.size(); i++){
            distancesVector.push_back(jsonArray.at(i).toDouble());
        }

        QJsonDocument jsonDoc = QJsonDocument::fromJson(menu.toUtf8());
                QJsonArray jsonarray = jsonDoc.array();

                for (int i = 0; i < jsonarray.size(); i++)
                {
                    QJsonObject jsonObject = jsonarray.at(i).toObject();
                    if(jsonObject.isEmpty())
                    {
                        qInfo() << "Json is empty";
                    }
                    else
                    {
                        MenuItem item;
                        item.name = jsonObject.value("name").toString();
                        item.price = jsonObject.value("price").toDouble();
                        menuVector.push_back(item);

                    }
                }

        //make our new restaurant
        Restaurant newRestaurant(id, name, menuVector, distancesVector, saddlebackDistance);
        restaurants.push_back(newRestaurant);
    }
    qInfo() << "yo";
    return true;
}



