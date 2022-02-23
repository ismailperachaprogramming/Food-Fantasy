#include "foodapp.h"

FoodApp::FoodApp()
{
    //use our db object to populate our restaurants vector with Restaurant objects
    //this->restaurants = db.getRestaurants();
    db.getRestaurants();
}
