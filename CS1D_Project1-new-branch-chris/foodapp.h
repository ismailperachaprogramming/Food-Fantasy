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

    //Delete this method
    void printRestaurants() const;

    std::vector<Restaurant> getRestaurants() const { return restaurants; };
    Trip* getCurrentTrip() const { if (currentTrip != nullptr) return currentTrip; }

    //Creates a Trip object and assigns currentTrip (Trip pointer) in this class to the newly made trip.
    void startTrip(bool startingFromSaddleback, bool startingFromDominos);

    //Adds a restaurant to selected restaurants - this is important for before they click "Plan trip" since we must keep track.
    void addRestaurant(Restaurant restaurant) { selectedRestaurants.push_back(restaurant); };
    void addMenuItem(Restaurant restaurant, MenuItem item) { selectedItems.insert(std::pair<int, MenuItem>(restaurant.getID(), item)); };

    //Set currentTrip to nullptr so the user can make a new trip
    void clearTrip() {currentTrip = nullptr; selectedRestaurants.clear(); selectedItems.clear(); };


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
