#ifndef TRIP_H
#define TRIP_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <queue>
#include <vector>

#include "restaurant.h"

/*!
 * \brief Trip class - Encapsulates the inner workings of generating a trip.
 */

class Trip
{
public:
    //! Constructor
    //! \brief Generates total milage, total spent per restaurant, and most efficient route
    Trip(bool startingFromSaddleback, bool startingFromDominos, std::vector<Restaurant> selectedRestaurants, std::multimap<int, MenuItem> selectedItems);

    //! startTrip
    /*!
     * \brief Method to start a new trip, called in constructor
     * \param startingRestaurant - Pointer to starting restaurant, nullptr if from saddleback.
     */
    void startTrip(Restaurant* startingRestaurant);

    //! createShortestRoute
    /*!
     * \brief Recursive function that finds the next closest restaurant
     * \param initialID - ID of restaurant that we want to link to the next closest available restaurant
     */
    void createShortestRoute(int initialID);

    //Getters:
    //! getTotalSpent;
    /*!
     * \brief Get total spent
     * \return Returns a double value of total spent at every restaurant combined
     */
    double getTotalSpent() const { return totalSpent; }

    //! getTotalDistance;
    /*!
     * \brief Get total distance
     * \return Returns a double value of total distance between visiting each restaurant
     */
    double getTotalDistance() const { return totalDistance; }

    //! getTotalDistance;
    /*!
     * \brief Saddleback status
     * \return Returns whether or not trip started from Saddleback.
     */
    bool isFromSaddleback() const { return startingFromSaddleback; }

    //! getMoneySpent
    /*!
     * \brief Get money spent per restaurant
     * \return Returns a map of money spent per restaurant, with the key being a restaurant ID.
     */
    std::map<int, double> getMoneySpent() const { return moneySpent; }

    //! getRoute
    /*!
     * \brief Get most efficient route
     * \return Returns a queue containing the correct order of restaurants to visit in the most efficient order.
     */
    std::queue<Restaurant>  getRoute() const { return route; }

private:
    double totalSpent; /*!< Total money spent */
    double totalDistance; /*!< Total distance travelled */
    bool startingFromSaddleback; /*!< Whether or not trip starts from Saddleback */
    bool startingFromDominos; /*!< Whether or not trip starts from Domino's */

    //Vector that we add restaurants to when they are selected in the UI
    std::vector<Restaurant> selectedRestaurants; /*!< Selected restaurants to visit */

    //Multi map that stores menu item objects to a corresponding key, where the key is the restaurant
    std::multimap<int, MenuItem> selectedItems; /*!< Selected items to visit, with key being a restaurant ID */

    std::map<int, double> moneySpent; /*!< Money spent per restaurant, with key being a restaurant ID */

    std::queue<Restaurant> route; /*!< Queue of restaurants to visit in the most efficient order */

};

#endif // TRIP_H
