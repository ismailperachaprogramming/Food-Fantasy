#ifndef TRIP_H
#define TRIP_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <queue>
#include <vector>

#include "restaurant.h"

class Trip
{
public:
    Trip(bool startingFromSaddleback, std::vector<Restaurant> selectedRestaurants, std::multimap<int, MenuItem> selectedItems);

    void startTrip(Restaurant* startingRestaurant);

    void createShortestRoute(Restaurant initial);

    //some sort of method to hook up to ui for adding to selectedRestaurants
    //maybe this?: loop through restaurants to find id and add to selectedRestaurants
    //this wouldnt be necessary if restaurants was a map instead of a vector

private:
    double totalSpent;
    bool startingFromSaddleback;

    //Vector that we add restaurants to when they are selected in the UI
    std::vector<Restaurant> selectedRestaurants;

    //Multi map that stores menu item objects to a corresponding key, where the key is the restaurant
    std::multimap<int, MenuItem> selectedItems;

    std::queue<Restaurant> route;

};

#endif // TRIP_H
