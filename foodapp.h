#ifndef FOODAPP_H
#define FOODAPP_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <vector>
#include <map>
#include <queue>

#include "restaurant.h"
#include "database.h"
#include "trip.h"

class FoodApp
{
public:
    FoodApp();
    //test method - delete later
    void printRestaurants() const;

    std::vector<Restaurant> getRestaurants() const { return restaurants; };
    Trip* getCurrentTrip() const { if (currentTrip != nullptr) return currentTrip; }

    //send true if button to start from saddleback is true
    void startTrip(bool startingFromSaddleback);

    //we need methods to add menu items and restaurants in here to keep track of where they want to go..
    void addRestaurant(Restaurant restaurant) { selectedRestaurants.push_back(restaurant); };
    void addMenuItem(Restaurant restaurant, MenuItem item) { selectedItems.insert(std::pair<int, MenuItem>(restaurant.getID(), item)); };

    ~FoodApp();

private:
    Database db;
    Trip* currentTrip;
    //all restaurants in db are in this vector
    std::vector<Restaurant> restaurants;

    //For keeping track of UI clicked on
    std::vector<Restaurant> selectedRestaurants;
    //Multi map that stores menu item objects to a corresponding key, where the key is the restaurant
    std::multimap<int, MenuItem> selectedItems;


};

#endif // FOODAPP_H
