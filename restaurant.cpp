#include "restaurant.h"

Restaurant::Restaurant(int id, QString name, std::vector<MenuItem> menu, std::vector<double> distances, double saddlebackDistance)
{
    this->restaurantID = id;
    this->name = name;
    this->menu = menu;
    this->distances = distances;
    this->saddlebackDistance = saddlebackDistance;

}
