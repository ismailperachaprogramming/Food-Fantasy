#include "database.h"

Database::Database()
{
    //Connect to "foodfantasy.db"

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/christopherschrader/FoodFantasy/db/FOODFANTASY.db");

    if (db.open()){
        qInfo() << "Database connection established!";
    } else {
        qInfo() << "Database connection error occured.";
    }
}

bool Database::addRestaurant(Restaurant restaurant){

    //loop through distances vector to create a json array of distances

    //loop through menu of restaurant to create json array of objects

}

bool Database::modifyMenu(Restaurant restaurant, std::vector<MenuItem> menu){
    //modify menu given restaurant
    //function will serialize menu with json and save as TEXT/STRING in 'menu' columns where restaurant is passed in restaurant
    //find proper restaurant by looking at restaurant id then query sql database based on that

    //returns true if operation is completed

    //loop through menu
    for (int i = 0; i <= menu.size(); i++){
        MenuItem currItem = menu[i];

    }
}

std::vector<Restaurant>& Database::getRestaurants(){
    //returns a vector by ref
    qInfo() << "Running.";
    std::vector<Restaurant> restaurants; //populate this in the function accordingly

    //query all restaurants in restaurants table
    QSqlQuery query("select * from restaurants");
    QSqlRecord rec = query.record();
    qInfo() << "tables: " << this->db.tables();
    qDebug() << "Number of columns: " << rec.count();

    while (query.next()){
        qInfo() << "once";
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString distances = query.value(2).toString();
        double saddlebackDistance = query.value(3).toDouble();
        QString menu = query.value(4).toString();

        qInfo() << id;
        qInfo() << name;
        qInfo() << distances;
        qInfo() << saddlebackDistance;
        qInfo() << menu;
    }
    return restaurants;
}



