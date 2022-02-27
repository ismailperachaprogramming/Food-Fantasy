#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set up ui
    QListWidget *restaurantList = ui->restaurantList;

    std::vector<Restaurant> restaurants = this->app.getRestaurants();
    for (int i = 0; i< restaurants.size(); i++)
    {
        std::cout << "ran once " << i << std::endl;
        RestaurantWidget *restaurantItem = new RestaurantWidget(restaurants[i], this);
        QListWidgetItem *item = new QListWidgetItem(restaurantList);
        restaurantList->addItem(item);
        item->setSizeHint(restaurantItem->minimumSizeHint());
        restaurantList->setItemWidget(item, restaurantItem);
    }
}

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


MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_planTrip_clicked()
{


}

