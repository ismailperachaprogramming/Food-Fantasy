#ifndef FOODAPP_H
#define FOODAPP_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <vector>

#include "restaurant.h"
#include "database.h"

class FoodApp
{
public:
    FoodApp();

private:
    Database db;
    std::vector<Restaurant> restaurants;
};

#endif // FOODAPP_H
