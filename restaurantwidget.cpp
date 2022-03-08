#include "restaurantwidget.h"
#include "restaurant.h"

RestaurantWidget::RestaurantWidget(Restaurant restaurantPassed, MainWindow *parent)
    :restaurant{restaurantPassed}, parent{parent}
{

    layout = new QHBoxLayout(this);
    nameLabel = new QLabel(restaurant.getName());
    addButton = new QPushButton("Add Restaurant");
    menuItems = new QComboBox();
    itemsToAdd = new QSpinBox();
    itemsToAdd->setFixedSize(100, 20);
    itemsToAdd->setMaximum(100);
    addItemButton = new QPushButton("Add menu item(s)");

    //menuItems->addItem("--Select Option--");


    for (int i = 0; i < this->restaurant.getMenu().size(); i++)
    {
        menuItems->addItem(QString(this->restaurant.getMenu()[i].name + ": " + QString::number(this->restaurant.getMenu()[i].price)));
    }

    menuItems->connect(addItemButton, SIGNAL(clicked()), this, SLOT(on_AddMenuItemClicked()));
    addButton->connect(addButton, SIGNAL(clicked()), this, SLOT(on_AddRestaurantClicked()));


    layout->addWidget(nameLabel);
    layout->addWidget(addButton);
    layout->addWidget(menuItems);
    layout->addWidget(itemsToAdd);
    layout->addWidget(addItemButton);
}

void RestaurantWidget::on_AddRestaurantClicked() {
    QString name = this->restaurant.getName();
    qInfo() << "Restaurant clicked: " << name;

    //actual foodapp connection
    parent->addRestaurant(this->restaurant);

    //adding restaurant to GUI list
    parent->addToList(name);


}

void RestaurantWidget::on_AddMenuItemClicked(){
    /*qInfo() << "Item clicked: " << this->restaurant.getMenu()[index].name << "from restaurant: " << this->restaurant.getName();
    QString restaurantName = this->restaurant.getName();
    QString itemName = this->restaurant.getMenu()[index].name + " - $" + QString::number(this->restaurant.getMenu()[index].price);
    parent->addToMenuList(itemName, restaurantName);
    */

    int count = this->itemsToAdd->value();
    int currentIndex = this->menuItems->currentIndex();
    QString itemName = this->restaurant.getMenu()[currentIndex].name + " - $" + QString::number(this->restaurant.getMenu()[currentIndex].price);

    //change it to find which item is selected on combobox
    //and get the number of items they want to add
    //call add menu item in a for loop where the loop runs however many times they want to add the item

    int itemCount = 0;
    std::vector<QString> itemsAdded = parent->getMenuList();
    for (int i = 0; i < itemsAdded.size(); i++){
        if (itemsAdded[i] == itemName){
            itemCount++;
        }
    }

    //actual foodapp connection
    if (itemCount + count <= 100){
        for (int i = 0; i < count; i++){
            parent->addMenuItem(this->restaurant, this->restaurant.getMenu()[currentIndex]);
            parent->addToMenuList(itemName, this->restaurant.getName());
        }
    } else {
        qInfo() << "Error! Cannot add more than 100 of the same item.";
        QMessageBox popup;
        popup.critical(0, "Error", "Cannot add more than 100 of the same item at a time.");
    }
}

RestaurantWidget::~RestaurantWidget(){
    delete layout;
    delete nameLabel;
    delete addButton;
    delete menuItems;
}
