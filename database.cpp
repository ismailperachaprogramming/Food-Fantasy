#include "database.h"

#include <iostream>
#include <fstream>

using namespace std;

Database::Database()
{
    //Connect to "foodfantasy.db"

    db = QSqlDatabase::addDatabase("QSQLITE");
    QDir dir = QCoreApplication::applicationDirPath();
    db.setDatabaseName("/Users/christopherschrader/FoodFantasy/db/FOODFANTASY.db");

    if (db.open()){
        qInfo() << "Database connection established!";
    } else {
        qInfo() << "Database connection error occured.";
    }
}

std::vector<Restaurant> Database::readFile()
{
    QString filePath = "/Users/christopherschrader/FoodFantasy/CS1D_Spring_2022_New_Fast_Food_Project.txt";
    string infile = "/Users/christopherschrader/FoodFantasy/CS1D_Spring_2022_New_Fast_Food_Project.txt";

    vector<Restaurant> newRestaurants;

    QFile q_file(filePath);
    if(!q_file.exists())
    {
        qCritical() << filePath << " cannot be found.";
        exit(1);
    }

    string restaurantName;
    int restaurantID;
    MenuItem item;
    vector<MenuItem> menuItems;
    vector<double> distances;
    double saddlebackDistance = 0;
    int distanceToOtherRestaurants;
    double specificDistance = 0;
    int restaurantCount = 0;
    int numMenuItems = 0;

    ifstream file(infile);

    if(!file.is_open())
    {
        qCritical() << "File failed to open!";
    }

    while(file)
    {
        file.ignore(numeric_limits<streamsize>::max(), ':');
        getline(file, restaurantName);

        QString QRestaurantName = QString::fromStdString(restaurantName);
        file.ignore(numeric_limits<streamsize>::max(), ':');
        file >> restaurantID;
        file.ignore(10000, '\n');

        string empty = "";
        getline(file, empty);
        QString DistanceStuff = QString::fromStdString(empty);
        //qInfo() << "This will be read and skipped: " << DistanceStuff;

        for (int i = 1; i <= 12; i++)
        {
            //qInfo() << file.peek();

            string empty2 = "";
            file >> empty2;
            //file.ignore(numeric_limits<streamsize>::max(), i);
            //qInfo() << file.peek();
            //file.ignore(numeric_limits<streamsize>::max(), ' ');
            file >> specificDistance;
            distances.push_back(specificDistance);
            //qInfo() << "dist: " << i << " : " << specificDistance;
        }

        file.ignore(numeric_limits<streamsize>::max(), ':');
        file >> saddlebackDistance;
        file.ignore(numeric_limits<streamsize>::max(), ':');
        file >> numMenuItems;
        file.ignore();
        file.ignore();

        //qInfo() << "num menu items: " << numMenuItems;

        string itemName = "";
        string itemPrice = "";

        for(int j = 0; j < numMenuItems; j++)
        {

            getline(file, itemName);
            //file.ignore();
            getline(file, itemPrice);
            //item.price = std::stod(itemPrice);

            //cout << "Testing p: " << itemPrice << endl;

            QString QItemName = QString::fromStdString(itemName);
            QString QItemPrice = QString::fromStdString(itemPrice);
            //qInfo() << "test: " << QItemName;
            //qInfo() << "price test: " << QItemPrice;
            item.name = QItemName;
            item.price = std::stod(itemPrice);

            menuItems.push_back(item);
        }

        //restaurantCount++;
        //possible bug - adds multiple of the same restaurants?

        //for (int i = 0; i < restaurantCount; i++)
        //{
            Restaurant newRestaurant(restaurantID, QRestaurantName, menuItems, distances, saddlebackDistance);
            newRestaurants.push_back(newRestaurant);
        //}

        //restaurantCount--;

            file.ignore(10000, '\n');
            file.ignore(10000, '\n');

            //qInfo() << "FINISHED ONE LOOP";

            //qInfo() << "PEEK: " << file.peek();

            menuItems.clear();
            distances.clear();
            saddlebackDistance = 0;
            distanceToOtherRestaurants;
            specificDistance = 0;
            restaurantCount = 0;
            numMenuItems = 0;
    }

    file.close();
    return newRestaurants;
}

void Database::addRestaurants(std::vector<Restaurant> restaurants){

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
}

void Database::modifyMenu(Restaurant restaurant, std::vector<MenuItem> menu){
    //modify menu given restaurant
        //function will serialize menu with json and save as TEXT/STRING in 'menu' columns where restaurant is passed in restaurant
        //find proper restaurant by looking at restaurant id then query sql database based on that

        //returns true if operation is completed

        QJsonArray menuItems;

        for (int i = 0; i < menu.size(); i++)
        {
            auto item = QJsonObject(
            {
            qMakePair(QString("name"), QJsonValue(menu[i].name)),
            qMakePair(QString("price"), QJsonValue(menu[i].price))
            });

            menuItems.push_back(QJsonValue(item));

        }

        int id = restaurant.getID();
        QString idToString = QString::number(id);

        QSqlQuery query;

        QJsonDocument menuDoc(menuItems);

        query.prepare("UPDATE restaurants SET menu = :newmenu WHERE id = :idediting");
        query.bindValue(":newmenu", menuDoc.toJson());
        query.bindValue(":idediting", id);

        if (query.exec()){
            qInfo() << "Inserted";
        } else {
            qInfo() << "Error, " << query.lastError();
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



