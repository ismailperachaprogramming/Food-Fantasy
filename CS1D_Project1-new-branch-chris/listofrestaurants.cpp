#include "listofrestaurants.h"
#include "ui_listofrestaurants.h"

#include <QListWidget>

listOfRestaurants::listOfRestaurants(std::vector<Restaurant> restaurants, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listOfRestaurants)
{
    ui->setupUi(this);

    QListWidget* list = ui->restaurantList;
    for (int i = 0; i < restaurants.size(); i++){
        list->addItem(restaurants[i].getName() + " -- Saddleback Distance: " + QString::number(restaurants[i].getSaddlebackDistance()) + " mi");
    }


}

listOfRestaurants::~listOfRestaurants()
{
    delete ui;
}
