#include "trip.h"

Trip::Trip(bool startingFromSaddleback, std::vector<Restaurant> selectedRestaurants, std::multimap<int, MenuItem> selectedItems)
{

}

void Trip::startTrip(Restaurant* startingRestaurant){
    if (startingFromSaddleback){
        double shortestDistance = 10000;
        int index = 0;
        Restaurant* closest;
        for (int i = 0; i < selectedRestaurants.size(); i++){
            if (selectedRestaurants[i].getSaddlebackDistance() < shortestDistance){
                closest = &selectedRestaurants[i];
                shortestDistance = selectedRestaurants[i].getSaddlebackDistance();
                index = i;
            }
        }
        //Enqueue closest restaurant in our selected restaurants to saddleback
        this->route.push(*closest);
        //remove closest restaurant to saddleback from our restaurants to choose from vector
        selectedRestaurants.erase(selectedRestaurants.begin() + index);

        createShortestRoute(*closest);
    } else {
        createShortestRoute(*startingRestaurant);
    }



}

void Trip::createShortestRoute(Restaurant initial){
    if (selectedRestaurants.size() == 0){
        // base case
    } else {
        // general case
        double shortestDistance = 10000;
        int index = 0;
        Restaurant* closest;
        for (int i = 0; i < selectedRestaurants.size(); i++){
            //initial.getID() - 1 bc id starts at 1 but distances starts at index 0
            if (selectedRestaurants[i].getDistances().at(initial.getID() - 1) < shortestDistance){
                index = i;
                closest = &selectedRestaurants[i];
                shortestDistance = selectedRestaurants[i].getDistances().at(initial.getID() - 1);
            }
        }
        this->route.push(*closest);
        selectedRestaurants.erase(selectedRestaurants.begin() + index);
        //recursive function call
        createShortestRoute(*closest);
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
