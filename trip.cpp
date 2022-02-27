#include "trip.h"
#include <iostream>

Trip::Trip(bool startingFromSaddleback, std::vector<Restaurant> selectedRestaurants, std::multimap<int, MenuItem> selectedItems)
{
    this->selectedRestaurants = selectedRestaurants;
    this->selectedItems = selectedItems;
    this->startingFromSaddleback = startingFromSaddleback;

    this->totalDistance = 0;
    this->totalSpent = 0;

    //calculate total money spent
    //selectedItems multi map int, MenuItem
    std::multimap<int, MenuItem>::iterator it;
    for (it = selectedItems.begin(); it != selectedItems.end(); it++){
        //std::cout << it->second.price;
        this->totalSpent += it->second.price;
    }

    startTrip(&selectedRestaurants[0]);

    //calculate total distance travelled
    //std::map<int, int> getMoneySpent() const { return moneySpent; }
    std::map<int, double>::iterator itr;
    for (it = selectedItems.begin(); it != selectedItems.end(); it++){
        std::cout << "ran once!" << std::endl;
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
        std::cout << "Distance: " << shortestDistance << std::endl;
        this->route.push(*closest);
        this->totalDistance += shortestDistance;
        //remove closest restaurant to saddleback from our restaurants to choose from vector
        selectedRestaurants.erase(selectedRestaurants.begin() + index);
        std::cout << std::endl << "called with id: " << id << std::endl;
        createShortestRoute(id);
    } else {
        std::cout << std::endl << "Else called with index 0" << std::endl;
        createShortestRoute(startingRestaurant->getID());
    }

}

void Trip::createShortestRoute(int initialID){
    if (selectedRestaurants.size() == 1){
        // base case
        totalDistance += selectedRestaurants[0].getDistances().at(initialID - 1);
        std::cout << "new distance added: " <<  selectedRestaurants[0].getDistances().at(initialID - 1) << std::endl;
        std::cout << "id initial: " << selectedRestaurants[0].getID() << " item initial: " << initialID;
        this->route.push(selectedRestaurants[0]);

    } else if (selectedRestaurants.size() == 0){
        //do nothing
    } else {
        // general case
        double shortestDistance = 10000;
        int index = 0;
        int id = 0;
        Restaurant* closest;
        for (int i = 0; i < selectedRestaurants.size(); i++){

            /* Uncomment once admin stuff has been featured and finish implementing
            if (initial.getDistances().size() > 10){
                //initial is a new restaurant
            }
            */

            //initial.getID() - 1 bc id starts at 1 but distances starts at index 0
            std::cout << "Closest initial id is " << initialID << std::endl;
            if (selectedRestaurants[i].getDistances().at(initialID - 1) < shortestDistance){
                index = i;
                id = selectedRestaurants[i].getID();
                closest = &selectedRestaurants[i];
                std::cout << std::endl << "Closest is at index: " << i << std::endl;
                shortestDistance = selectedRestaurants[i].getDistances().at(initialID - 1);
            }
        }
        std::cout << std::endl << "Distance 2: " << shortestDistance << std::endl;
        this->totalDistance += shortestDistance;
        this->route.push(*closest);
        selectedRestaurants.erase(selectedRestaurants.begin() + index);
        //recursive function call
        std::cout << std::endl << "called with id: " << id << std::endl;
        createShortestRoute(id);
    }
}


/* move these to food app
void Trip::addMenuItemToTrip(MenuItem item, int restaurantID){
    this->selectedItems.insert(std::pair<int, MenuItem>(restaurantID, item));
}

void Trip::addRestaurantToTrip(Restaurant restaurant){
    this->selectedRestaurants.push_back(restaurant);
}
*/
