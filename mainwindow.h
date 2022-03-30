#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "foodapp.h"
#include "restaurantwidget.h"
#include "menuwidget.h"
#include "restaurant.h"
#include "Database.h"
#include "login.h"
#include "listofrestaurants.h"
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * \brief Main application page and class
 *  Has many methods for internal workings of program
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! Constructor
    //! \brief Initializes database object and loads UI with restaurants in the database.
    MainWindow(QWidget *parent = nullptr);

    //! addRestaurant
    /*!
     * \brief Adds restaurant to selected restaurants, which we need for creating a trip.
     */
    void addRestaurant(Restaurant restaurant);

    //! addMenuItem
    /*!
     * \brief Adds menu item to selected menu items, which we need for creating a trip.
     */
    void addMenuItem(Restaurant restaurant, MenuItem item);

    //! addToList
    /*!
     * \brief Adds restaurant to UI list
     */
    void addToList(QString name);

    //! addToMenuList
    /*!
     * \brief Adds item to selected items UI list
     */
    void addToMenuList(QString name, QString restaurantName);

    //! deleteItem
    /*!
     * \brief Deletes item from menu and reloads UI (updates database as well)
     */
    void deleteItem(Restaurant restaurant, std::vector<MenuItem> newMenu);

    //! editItem
    /*!
     * \brief Edits item from menu and reloads UI (updates database as well)
     */
    void editItem(Restaurant restaurant, int index);

    //! addItem
    /*!
     * \brief Adds item to menu and reloads UI (updates database as well)
     */
    void addItem(Restaurant restaurant, std::vector<MenuItem> newMenu);

    //! getMenuList
    /*!
     * \brief Accessor function that returns list of selected restaurants
     */
    std::vector<QString> getMenuList() const { return menuList; }

    ~MainWindow();

private slots:

    void on_planTrip_clicked();

    void on_openListButton_clicked();

    void on_clearButton_clicked();

    void on_customTrip_clicked();

    void on_pushButton_clicked();

    void on_startDominos_clicked();

    void on_pushButton_2_clicked();

    void on_menuAdmin_clicked();


private:
    Ui::MainWindow *ui; /*!< UI of main window */
    std::vector<QString> nameList; /*!< Selected restaurant names */
    std::vector<QString> menuList; /*!< Selected menu items */

    //Database object - use this to interact with SQLite database
    Database db; /*!< Database backend object */
    //Stores the currentTrip. nullptr upon program opening.
    Trip* currentTrip; /*!< Pointer to current trip object */
    //all restaurants in db are in this vector
    std::vector<Restaurant> restaurants; /*!< Every restaurant in the database */

    //For keeping track of UI clicked on
    std::vector<Restaurant> selectedRestaurants; /*!< Vector of selected restaurants */
    //Multi map that stores menu item objects to a corresponding key, where the key is the restaurant
    std::multimap<int, MenuItem> selectedItems; /*!< Map of selected items, with the key being a restaurant ID */

    listOfRestaurants* popup; /*!< Pointer to popup page for restaurant list */

    Login* loginpopup; /*!< Pointer to popup page for admin authentication */

};
#endif // MAINWINDOW_H
