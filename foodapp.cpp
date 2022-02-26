#include "foodapp.h"
#include <iostream>

FoodApp::FoodApp()
{
    //use our db object to populate our restaurants vector with Restaurant objects
    if(db.getRestaurants(this->restaurants)){
        printRestaurants();
        //startingAtSaddleback();
        //planningTrip();
    }
}

void FoodApp::printRestaurants() const {
    qInfo() << "size: " << restaurants.size();
    for (int i = 0; i < restaurants.size(); i++)
    {
        std::cout << std::endl << std::endl;
        std::cout << std::endl << "Name: " << restaurants[i].getName().toStdString();
        std::cout << std::endl << "Restaurant ID: " << restaurants[i].getID();
        std::cout << std::endl << "Distance to Saddleback: " << restaurants[i].getSaddlebackDistance();

        std::vector<double> distances = restaurants[i].getDistances();
        for (int i = 0; i < distances.size() - 1; i++){
            std::cout << std::endl << distances[i];
        }
        std::vector<MenuItem> menu = restaurants[i].getMenu();
        for (int i = 0; i < menu.size(); i++){
            std::cout << std::endl << menu[i].name.toStdString() << ": " << menu[i].price;
        std::cout << std::endl;
        }
    }
}

void FoodApp::startingAtSaddleback() const{
    //shortest route from saddleback college to fast-food restaurant

    double distanceFromSaddleback;
    int id;
    QString name;

    distanceFromSaddleback = restaurants[0].getSaddlebackDistance();
    id = restaurants[0].getID();
    name = restaurants[0].getName();

    for(int i = 1; i < restaurants.size(); i++)
    {
        if (distanceFromSaddleback > restaurants[i].getSaddlebackDistance())
        {
            distanceFromSaddleback = restaurants[i].getSaddlebackDistance();
            id = restaurants[i].getID();
            name = restaurants[i].getName();
        }
    }

    qInfo() << "\nID: " << id
            << "\nName: " << name
            << "\nShortest route: " << distanceFromSaddleback << " miles from Saddleback College\n";
    //************************

    //visit other closest fast-food restaurant

    entireTrip(id, true);
}

void FoodApp::planningTrip() const
{
    int option;

    qInfo() << "Choose one to start at:\n"
        << "1.  McDonald's\n"
        << "2.  Chipotle\n"
        << "3.  Domino’s Pizza\n"
        << "4.  KFC\n"
        << "5.  Subway\n"
        << "6.  In-N-Out Burger\n"
        << "7.  Wendy’s\n"
        << "8.  Jack in the Box\n"
        << "9.  El Pollo Loco\n"
        << "10. Papa John’s Pizza\n"
        << "Type a number of the option: ";
    do
    {
        std::cin >> option;
        if (option < 1 || option > 10){
            qInfo() << "\nPlease enter the option between 1 and 10: ";
        }
    } while (option < 1 || option > 10);

    entireTrip(option, false);
}

void FoodApp::entireTrip(int idR, bool fromSaddleback) const
{
    double totalDistance = 0;
    QString name = restaurants[idR - 1].getName();
    int id = idR;
    std::vector<int> idList;
    idList.push_back(id);

    if (fromSaddleback == true)
        totalDistance += restaurants[id - 1].getSaddlebackDistance();

    for (int j = 0; j < restaurants.size()-1; j++)
    {
        bool equal;
        std::vector<double> distanceNext = restaurants[id-1].getDistances();
        double distanceTo;
        int idNext;
        QString nameNext;

        if (distanceNext[0] != 0)
        {
            distanceTo = distanceNext[0];
            idNext = restaurants[0].getID();
            nameNext = restaurants[0].getName();
        }
        else
        {
            distanceTo = distanceNext[1];
            idNext = restaurants[1].getID();
            nameNext = restaurants[1].getName();
        }

        for(int i = 0; i < restaurants.size(); i++)
        {
            if (distanceTo > distanceNext[i] && id != restaurants[i].getID())
            {
                equal = true;
                for (int x = 0; x < idList.size(); x++)
                {
                    if (restaurants[i].getID() == idList[x])
                    {
                        equal = false;
                        break;
                    }
                }
                if (equal == true)
                {
                    distanceTo = distanceNext[i];
                    idNext = restaurants[i].getID();
                    nameNext = restaurants[i].getName();
                }
            }
        }

        qInfo() << "\nFrom ID:" << id << name << " to ID:" << idNext << nameNext
                << "\nThe distance between those is " << distanceTo << " miles\n";

        totalDistance += distanceTo;
        id = idNext;
        name = nameNext;
        idList.push_back(id);
    }

    qInfo() << "\n\nTotal Disance: " << totalDistance << " miles\n";
}
