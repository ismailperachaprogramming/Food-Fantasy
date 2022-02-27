#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QWidget>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QStandardPaths>
#include <QDir>

#include "restaurant.h"


/*!
 * \brief Database class
 * Holds several member functions that GameApp uses to properly interact with our SQLite database.
 * Aggregate member of GameApp class.
 */

class Database
{
public:

    Database();

    //Add restaurant
    //! Method to add a new restaurant to the database
    /*!
     * \brief addRestaurant
     * \param restaurant - Restaurant object to add to our database
     * \return Returns boolean of whether operation was successful
     */
    bool addRestaurant(Restaurant restaurant);

    //! Method to modify a restaurant's menu in database
    /*!
     * \brief modifyMenu
     * \param restaurant - Restaurant object that we're trying to modify.
     * \param menu - Vector of MenuItems, which represents our updated menu state.
     * \return - Returns boolean of whether operation was successful
     */

    bool modifyMenu(Restaurant restaurant, std::vector<MenuItem> menu);

    //! Method to receive all restaurants in database
    /*!
     * \brief getRestaurants
     * \return Returns a vector of Restaurant objects.
     */
    bool getRestaurants(std::vector<Restaurant>& restaurants);

private:
    QSqlDatabase db;

};

#endif // DATABASE_H
