#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set up ui
    //This is the list widget that holds each restaurant row
    QListWidget *restaurantList = ui->restaurantList;

    //Create a RestaurantWidget object for each restaurant and add it to the restaurantList list widget.
    std::vector<Restaurant> restaurants = this->app.getRestaurants();
    for (int i = 0; i< restaurants.size(); i++)
    {
        RestaurantWidget *restaurantItem = new RestaurantWidget(restaurants[i], this);
        QListWidgetItem *item = new QListWidgetItem(restaurantList);
        restaurantList->addItem(item);
        item->setSizeHint(restaurantItem->minimumSizeHint());
        restaurantList->setItemWidget(item, restaurantItem);
    }
}

//Purely for adding restaurant to UI list
void MainWindow::addToList(QString name)
{
    QListWidget* customList = ui->customList;

    if(std::find(nameList.begin(), nameList.end(), name) == nameList.end())
    {

       customList->addItem(name);
       nameList.push_back(name);

    }
    else
    {
        qInfo() << "Cannot add same Restaurant to the trip!";
    }


}

//Purely for adding menu item to UI list
void MainWindow::addToMenuList(QString name, QString restaurantName)
{
    QListWidget* customList = ui->menuList;


    if(std::find(nameList.begin(), nameList.end(), restaurantName) != nameList.end())
    {

        customList->addItem(name);
        menuList.push_back(name);

    }
    else
    {
        qInfo() << "Cannot add Menu Item without adding Restaurant to trip!";
    }
}

//Needed for calculating the trip information
void MainWindow::addRestaurant(Restaurant restaurant){

    qInfo() << restaurant.getName() << "Test";


    if(std::find(nameList.begin(), nameList.end(), restaurant.getName()) == nameList.end() )
    {
       //Restaurant hasn't been added already, we are good to pass it to FoodApp
       app.addRestaurant(restaurant);
    } else {
        QMessageBox popup;
        popup.critical(0, "Error", "Cannot add the same restaurant twice.");
    }
}

void MainWindow::addMenuItem(Restaurant restaurant, MenuItem item){

    if(std::find(nameList.begin(), nameList.end(), restaurant.getName()) != nameList.end())
    {
        //Restaurant this menu items belongs to has been added to trip already. Safe to add menu item.
        app.addMenuItem(restaurant, item);
    }
    else
    {
        QMessageBox popup;
        popup.critical(0, "Error", "Cannot add menu item before adding restaurant to trip.");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_planTrip_clicked()
{
    //Set this to true if we run into input validation
    bool errorExists = false;

    if(this->nameList.size() > 0 && this->menuList.size() > 0){
        if (ui->startDominos->isChecked()){
            std::cout << "Start from dominos checked and were calling";
            if(std::find(nameList.begin(), nameList.end(), "Domino's Pizza") != nameList.end())
            {
                app.startTrip(ui->startSaddleback->isChecked(), ui->startDominos->isChecked());
            } else {
                QMessageBox popup;
                errorExists = true;
                popup.critical(0, "Error", "Cannot start a trip from Domino's without adding it first.");
            }
        } else {
            app.startTrip(ui->startSaddleback->isChecked(), ui->startDominos->isChecked());
        }
    } else {
        QMessageBox popup;
        errorExists = true;
        popup.critical(0, "Error", "Cannot start a trip without adding any menu items or restaurants.");
    }

    if (!errorExists){
        //Input is properly validated, continue with displaying trip information to UI

        qInfo() << "Total money spent: " << app.getCurrentTrip()->getTotalSpent();
        ui->totalSpentLabel->setText("$" + QString::number(app.getCurrentTrip()->getTotalSpent()));


        ui->distanceLabel->setText(QString::number(app.getCurrentTrip()->getTotalDistance()) + " mi.");

        std::queue<Restaurant> route = app.getCurrentTrip()->getRoute();

        qInfo() << "Most efficient route: ";

        int count = 1;
        if (app.getCurrentTrip()->isFromSaddleback()){
            ui->routeList->addItem("1. Saddleback College");
            count++;
        }

        while (route.empty() != true){
            qInfo() << route.front().getName();
            ui->routeList->addItem(QString::number(count) + ". " + route.front().getName());
            count++;
            route.pop();
        }

        qInfo() << "Money spent per restaurant: ";

        std::map<int,double> moneySpent = app.getCurrentTrip()->getMoneySpent();
        std::map<int,double>::iterator it;
        std::vector<Restaurant> allRestaurants = app.getRestaurants();
        for (it = moneySpent.begin(); it != moneySpent.end(); it++){
            int id = it->first;
            for (int i = 0; i < allRestaurants.size(); i++){
                if (allRestaurants[i].getID() == id){
                    qInfo() << "Money spent at " << allRestaurants[i].getName() << ": " << it->second;
                    QString string = "Money spent at " + allRestaurants[i].getName() + ": $" + QString::number(it->second);
                    ui->spentList->addItem(string);
                }
            }

        }
    }

}


void MainWindow::on_openListButton_clicked()
{
    popup = new listOfRestaurants(app.getRestaurants(), this);
    popup->show();
}


void MainWindow::on_clearButton_clicked()
{
    this->nameList.clear();
    this->menuList.clear();

    this->ui->customList->clear();
    this->ui->menuList->clear();
    this->ui->routeList->clear();
    this->ui->spentList->clear();

    this->app.clearTrip();
}


void MainWindow::on_customTrip_clicked()
{
    QMessageBox popup;
    popup.information(0, "Info", "The first restaurant you add to the trip will be the starting restaurant.");
}

