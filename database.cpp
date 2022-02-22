#include "Database.h"

Database::Database()
{

}

bool Database::addRestaurant(Restaurant restaurant){
    //returns true if operation is completed
}

bool Database::modifyMenu(Restaurant restaurant, std::vector<MenuItem> menu){
    //modify menu given restaurant
    //function will serialize menu with json and save as TEXT/STRING in 'menu' columns where restaurant is passed in restaurant
    //find proper restaurant by looking at restaurant id then query sql database based on that

    //returns true if operation is completed

    //loop through menu
    for (int i = 0;)
}

std::vector<Restaurant>& Database::getRestaurants(){
    //returns a vector by ref
}



