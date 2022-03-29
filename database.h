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
 * Holds several member functions that MainWindow uses to properly interact with our SQLite database.
 * Aggregate member of MainWindow class.
 */

class Database
{
public:

    //! Constructor
    //! \brief Establishes connection to .db file
    Database();

    //! readFile
    /*!
     * \brief Method to generate vector of restaurants from input file (given in project zip)
     * \return Returns vector which is populated with new restaurants from input file
     */
    std::vector<Restaurant> readFile();

    //! addRestaurants
    /*!
     * \brief Method to add a new restaurant to the database
     * \param restaurants - Vector of restaurants to add to database
     * \return Returns boolean of whether operation was successful
     */
    void addRestaurants(std::vector<Restaurant> restaurants);

    //! modifyMenu
    /*!
     * \brief Method to modify a restaurant's menu in database
     * \param restaurant - Restaurant object that we're trying to modify.
     * \param menu - Vector of MenuItems, which represents our updated menu state.
     * \return - Returns boolean of whether operation was successful
     */

    void modifyMenu(Restaurant restaurant, std::vector<MenuItem> menu);

    //! getRestaurants
    /*!
     * \brief Method to receive all restaurants in database
     * \param restaurants - Vector of restaurants by reference to modify
     * \return Returns true or false of successful/not successful operation
     */
    bool getRestaurants(std::vector<Restaurant>& restaurants);

private:
    QSqlDatabase db; /*!< QTSqlite database object */

};

#endif // DATABASE_H
