#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <QObject>

struct MenuItem
{
    std::string name;
    double price;
};

class Restaurant
{
public:
    Restaurant(int id, std::string name, std::vector<MenuItem> menu, std::vector<double> distances, double saddlebackDistance);

    //maybe some sort of method to compare distances from a given restaurant or saddleback
    //could be operator overloading ?

private:
    int restaurantID;
    std::string name;
    std::vector<MenuItem> menu;
    std::vector<double> distances;
    double saddlebackDistance;
};

#endif // RESTAURANT_H
