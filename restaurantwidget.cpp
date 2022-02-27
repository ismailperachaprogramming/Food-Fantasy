#include "restaurantwidget.h"
#include "restaurant.h"

RestaurantWidget::RestaurantWidget(Restaurant restaurantPassed, MainWindow *parent)
    :restaurant{restaurantPassed}, parent{parent}
{

    layout = new QHBoxLayout(this);
    nameLabel = new QLabel(restaurant.getName() + " --  Saddleback Distance: " + QString::number(restaurant.getSaddlebackDistance()) + " mi");
    addButton = new QPushButton("Add Restaurant");
    menuItems = new QComboBox();

    //menuItems->addItem("--Select Option--");


    for (int i = 0; i < this->restaurant.getMenu().size(); i++)
    {
        menuItems->addItem(QString(this->restaurant.getMenu()[i].name + ": " + QString::number(this->restaurant.getMenu()[i].price)));
    }

    menuItems->connect(menuItems, SIGNAL(activated(int)), this, SLOT(on_AddMenuItemClicked(int)));
    addButton->connect(addButton, SIGNAL(clicked()), this, SLOT(on_AddRestaurantClicked()));


    layout->addWidget(nameLabel);
    layout->addWidget(addButton);
    layout->addWidget(menuItems);
}

void RestaurantWidget::on_AddRestaurantClicked() {
    QString name = this->restaurant.getName();
    qInfo() << "Restaurant clicked: " << name;
    parent->addToList(name);

}

void RestaurantWidget::on_AddMenuItemClicked(int index){
    qInfo() << "Item clicked: " << this->restaurant.getMenu()[index].name << "from restaurant: " << this->restaurant.getName();
    QString restaurantName = this->restaurant.getName();
    QString itemName = this->restaurant.getMenu()[index].name + " - $" + QString::number(this->restaurant.getMenu()[index].price);
    parent->addToMenuList(itemName, restaurantName);
}

RestaurantWidget::~RestaurantWidget(){
    delete layout;
    delete nameLabel;
    delete addButton;
    delete menuItems;
}
