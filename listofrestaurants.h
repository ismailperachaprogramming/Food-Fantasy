#ifndef LISTOFRESTAURANTS_H
#define LISTOFRESTAURANTS_H
#include "restaurant.h"

#include <QDialog>

namespace Ui {
class listOfRestaurants;
}

class listOfRestaurants : public QDialog
{
    Q_OBJECT

public:
    explicit listOfRestaurants(std::vector<Restaurant> restaurants, QWidget *parent = nullptr);
    ~listOfRestaurants();

private:
    Ui::listOfRestaurants *ui;
};

#endif // LISTOFRESTAURANTS_H
