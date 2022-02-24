#include "foodapp.h"
#include <iostream>

FoodApp::FoodApp()
{
    //use our db object to populate our restaurants vector with Restaurant objects
    if(db.getRestaurants(this->restaurants)){
        printRestaurants();
    }
}

void FoodApp::printRestaurants() const {
    qInfo() << "size: " << restaurants.size();
    for (int i = 0; i < restaurants.size(); i++){
        std::cout << std::endl << std::endl;
        //std::cout << std::endl << "Name: " << restaurants[i].getName().toStdString();
        std::cout << std::endl << "Restaurant ID: " << restaurants[i].getID();
        std::cout << std::endl << "Distance to Saddleback: " << restaurants[i].getSaddlebackDistance();

        std::vector<double> distances = restaurants[i].getDistances();
        for (int i = 0; i < distances.size(); i++){
            std::cout << std::endl << distances[i];
        }
        std::vector<MenuItem> menu = restaurants[i].getMenu();
        for (int i = 0; i < menu.size(); i++){
            std::cout << std::endl << menu[i].name.toStdString() << ": " << menu[i].price;
        }
    }
}
