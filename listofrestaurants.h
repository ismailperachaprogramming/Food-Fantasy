#ifndef LISTOFRESTAURANTS_H
#define LISTOFRESTAURANTS_H
#include "restaurant.h"

#include <QDialog>

namespace Ui {
class listOfRestaurants;
}

/*!
 * \brief List of restaurants class
 * Serves as a UI for the popup restaurant list, with initial distance to Saddleback
 */

class listOfRestaurants : public QDialog
{
    Q_OBJECT

public:
    explicit listOfRestaurants(std::vector<Restaurant> restaurants, QWidget *parent = nullptr);
    ~listOfRestaurants();

private:
    Ui::listOfRestaurants *ui; /*!< UI of popup window */
};

#endif // LISTOFRESTAURANTS_H
