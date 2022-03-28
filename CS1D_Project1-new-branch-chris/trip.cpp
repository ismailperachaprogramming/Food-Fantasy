#include "trip.h"
#include <iostream>
#include <QDebug>

Trip::Trip(bool startingFromSaddleback, bool startingFromDominos, std::vector<Restaurant> selectedRestaurants, std::multimap<int, MenuItem> selectedItems)
{
    this->selectedRestaurants = selectedRestaurants;
    this->selectedItems = selectedItems;
    this->startingFromSaddleback = startingFromSaddleback;
    this->startingFromDominos = startingFromDominos;

    this->totalDistance = 0;
    this->totalSpent = 0;

    //calculate total money spent
    //selectedItems multi map int, MenuItem
    std::multimap<int, MenuItem>::iterator it;
    for (it = selectedItems.begin(); it != selectedItems.end(); it++){
        this->totalSpent += it->second.price;
    }

    startTrip(&selectedRestaurants[0]);

    //calculate total distance travelled
    //std::map<int, int> getMoneySpent() const { return moneySpent; }
    std::map<int, double>::iterator itr;
    for (it = selectedItems.begin(); it != selectedItems.end(); it++){
        //it->first is the id key
        if (moneySpent.find(it->first) == moneySpent.end()){
            moneySpent.insert(std::pair<int, double>(it->first, it->second.price));
        } else {
            moneySpent.at(it->first) += it->second.price;
        }
    }

}

void Trip::startTrip(Restaurant* startingRestaurant){
    if (startingFromSaddleback){
        double shortestDistance = 10000;
        int id = 0;
        int index = 0;
        Restaurant* closest;
        for (int i = 0; i < selectedRestaurants.size(); i++){
            if (selectedRestaurants[i].getSaddlebackDistance() < shortestDistance){
                closest = &selectedRestaurants[i];
                shortestDistance = selectedRestaurants[i].getSaddlebackDistance();
                id = selectedRestaurants[i].getID();
                index = i;
            }
        }
        //Enqueue closest restaurant in our selected restaurants to saddleback
        this->route.push(*closest);
        this->totalDistance += shortestDistance;
        //remove closest restaurant to saddleback from our restaurants to choose from vector
        selectedRestaurants.erase(selectedRestaurants.begin() + index);
        createShortestRoute(id);
    } else {
        if (startingFromDominos){
            //3 is domino's id
            Restaurant *dominos = nullptr;
            int index = 0;
            for (int i = 0; i < selectedRestaurants.size(); i++){
                if (selectedRestaurants[i].getID() == 3){
                    dominos = &selectedRestaurants[i];
                    index = i;
                }
            }
            this->route.push(*dominos);
            selectedRestaurants.erase(selectedRestaurants.begin() + index);

            //find closest restaurant to dominos and call createShortestRoute with that id
            double shortestDistance = 10000;
            int id = 0;
            int idx = 0;
            Restaurant* closest;
            for (int i = 0; i < selectedRestaurants.size(); i++){
                if (selectedRestaurants[i].getDistances().at(2) < shortestDistance){
                    closest = &selectedRestaurants[i];
                    shortestDistance = selectedRestaurants[i].getSaddlebackDistance();
                    id = selectedRestaurants[i].getID();
                    idx = i;
                }
            }
            this->route.push(*closest);
            selectedRestaurants.erase(selectedRestaurants.begin() + idx);
            totalDistance += shortestDistance;
            qInfo() << "Name of closest to dominos: " << closest->getName();
            createShortestRoute(id);
        } else {
            this->route.push(*startingRestaurant);
            for (int i = 0; i < selectedRestaurants.size(); i++){
                if (selectedRestaurants[i].getID() == startingRestaurant->getID()){
                    selectedRestaurants.erase(selectedRestaurants.begin() + i);
                }
            }
            createShortestRoute(startingRestaurant->getID());
        }
    }

}

void Trip::createShortestRoute(int initialID){
    if (selectedRestaurants.size() == 1){
        // base case
        totalDistance += selectedRestaurants[0].getDistances().at(initialID - 1);
        this->route.push(selectedRestaurants[0]);

    } else if (selectedRestaurants.size() == 0){
        //do nothing
    } else {
        // general case
        double shortestDistance = 10000;
        int index = 0;
        int id = 0;
        Restaurant* closest = nullptr;
        Restaurant initial = this->route.front();
        for (int i = 0; i < selectedRestaurants.size(); i++){
            if (initial.getDistances().size() > 10){
                //initial is a new restaurant, so we must look at initial distance from other restaurants since they might not have the data
                if (initial.getDistances().at(selectedRestaurants[i].getID() - 1) < shortestDistance){
                    index = i;
                    id = selectedRestaurants[i].getID();
                    closest = &selectedRestaurants[i];
                    shortestDistance = initial.getDistances().at(selectedRestaurants[i].getID() - 1);
                }
            } else {
                //initial.getID() - 1 bc id starts at 1 but distances starts at index 0
                if (selectedRestaurants[i].getDistances().at(initialID - 1) < shortestDistance){
                    index = i;
                    id = selectedRestaurants[i].getID();
                    closest = &selectedRestaurants[i];
                    shortestDistance = selectedRestaurants[i].getDistances().at(initialID - 1);
                }
            }
        }
        this->totalDistance += shortestDistance;
        this->route.push(*closest);
        selectedRestaurants.erase(selectedRestaurants.begin() + index);
        //recursive function call
        createShortestRoute(id);
    }
}


