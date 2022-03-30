#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <QObject>

struct MenuItem
{
    QString name;
    double price;
};

/*!
 * \brief Restaurant class
 */

class Restaurant
{
public:
    //! Constructor
    //! \brief Initializes all restaurant attributes
    Restaurant(int id, QString name, std::vector<MenuItem> menu, std::vector<double> distances, double saddlebackDistance);

    //! getID
        /*!
         * \brief
         * \return Returns int which is an id for the restaurant
         */
    int getID() const { return restaurantID; }

    //! getName
        /*!
         * \brief
         * \return Returns string which is the name of the restaurant
         */
    QString getName() const { return name; }

    //! getMenu
        /*!
         * \brief
         * \return Returns vector of MenuItems, which represents the menu of the restaurant
         */
    std::vector<MenuItem> getMenu() const { return menu; }

    //! getDistances
        /*!
         * \brief
         * \return Returns vector of distances to other restaurants in the correct order
         */
    std::vector<double> getDistances() const { return distances; }

    //! getSaddlebackDistance
        /*!
         * \brief
         * \return Returns double which is a distance from restaurant to Saddleback College
         */
    double getSaddlebackDistance() const { return saddlebackDistance; }

private:
    int restaurantID; /*!< Restaurant ID - int */
    QString name; /*!< Restaurant name - QString */
    std::vector<MenuItem> menu; /*!< Restaurant menu - vector of MenuItem object */
    std::vector<double> distances; /*!< Restaurant distances - vector of double object */
    double saddlebackDistance; /*!< Distance to Saddleback - double object */
};

#endif // RESTAURANT_H


