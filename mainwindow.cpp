#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set up ui
    QListWidget *restaurantList = ui->restaurantList;

    std::vector<Restaurant> restaurants = this->app.getRestaurants();
    for (int i = 0; i< restaurants.size(); i++){
        std::cout << "ran once " << i << std::endl;
        RestaurantWidget *restaurantItem = new RestaurantWidget(restaurants[i], this);
        QListWidgetItem *item = new QListWidgetItem(restaurantList);
        restaurantList->addItem(item);
        item->setSizeHint(restaurantItem->minimumSizeHint());
        restaurantList->setItemWidget(item, restaurantItem);
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}

