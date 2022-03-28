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
    Trip(bool startingFromSaddleback, bool startingFromDominos, std::vector<Restaurant> selectedRestaurants, std::multimap<int, MenuItem> selectedItems);

    void startTrip(Restaurant* startingRestaurant);

    void createShortestRoute(int initialID);

    //some sort of method to hook up to ui for adding to selectedRestaurants
    //maybe this?: loop through restaurants to find id and add to selectedRestaurants
    //this wouldnt be necessary if restaurants was a map instead of a vector

    //Getters:
    double getTotalSpent() const { return totalSpent; }
    double getTotalDistance() const { return totalDistance; }
    bool isFromSaddleback() const { return startingFromSaddleback; }
    std::map<int, double> getMoneySpent() const { return moneySpent; }
    std::queue<Restaurant>  getRoute() const { return route; }

private:
    double totalSpent;
    double totalDistance;
    bool startingFromSaddleback;
    bool startingFromDominos;

    //Vector that we add restaurants to when they are selected in the UI
    std::vector<Restaurant> selectedRestaurants;

    //Multi map that stores menu item objects to a corresponding key, where the key is the restaurant
    std::multimap<int, MenuItem> selectedItems;

    std::map<int, double> moneySpent;

    std::queue<Restaurant> route;

};

#endif // TRIP_H
