#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <QObject>

struct MenuItem
{
    QString name;
    double price;
};

class Restaurant
{
public:
    Restaurant(int id, QString name, std::vector<MenuItem> menu, std::vector<double> distances, double saddlebackDistance);

    //maybe some sort of method to compare distances from a given restaurant or saddleback
    //could be operator overloading ?
    int getID() const { return restaurantID; }
    QString getName() const { return name; }
    std::vector<MenuItem> getMenu() const { return menu; }
    std::vector<double> getDistances() const { return distances; }
    double getSaddlebackDistance() const { return saddlebackDistance; }

private:
    int restaurantID;
    QString name;
    std::vector<MenuItem> menu;
    std::vector<double> distances;
    double saddlebackDistance;
};

#endif // RESTAURANT_H


