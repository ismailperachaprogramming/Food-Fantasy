#include "Database.h"

Database::Database()
{
    //Connect to "foodfantasy.db"

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("foodfantasy.db");

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
    QSqlQuery query(this->db);
    query.prepare("SELECT * from restaurants");
    qInfo() << query.isValid();

    while (query.next()){
        qInfo() << "once";
        int id = query.value(0).toInt();
        QString menu = query.value(4).toString();

        qInfo() << menu;
    }
    return restaurants;
}



