#include "restaurantwidget.h"
#include "restaurant.h"

RestaurantWidget::RestaurantWidget(Restaurant restaurantPassed, QWidget *parent)
    : QWidget{parent}, restaurant{restaurantPassed}
{

    layout = new QHBoxLayout(this);
    nameLabel = new QLabel(restaurant.getName());
    addButton = new QPushButton("Add Restaurant");
    menuItems = new QComboBox();

    for (int i = 0; i < this->restaurant.getMenu().size(); i++){
        menuItems->addItem(QString(this->restaurant.getMenu()[i].name + ": " + QString::number(this->restaurant.getMenu()[i].price)));
    }

    menuItems->connect(menuItems, SIGNAL(currentIndexChanged(int)), this, SLOT(on_AddMenuItemClicked(int)));

    layout->addWidget(nameLabel);
    layout->addWidget(addButton);
    layout->addWidget(menuItems);
}

void RestaurantWidget::on_AddRestaurantClicked(QString restaurantName) {

}

void RestaurantWidget::on_AddMenuItemClicked(int index){
    qInfo() << "Item clicked: " << this->restaurant.getMenu()[index].name << "from restaurant: " << this->restaurant.getName();
}

RestaurantWidget::~RestaurantWidget(){
    delete layout;
    delete nameLabel;
    delete addButton;
    delete menuItems;
}
