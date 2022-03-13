#include "restaurantwidget.h"
#include "restaurant.h"

//Note that the constructor initializes a restaurant associated with the object so that we know which restaurant the user is messing with.
RestaurantWidget::RestaurantWidget(Restaurant restaurantPassed, MainWindow *parent)
    :restaurant{restaurantPassed}, parent{parent}
{

    //Creating all the UI elements dynamically for each restaurant column in the list widget.
    layout = new QHBoxLayout(this);
    nameLabel = new QLabel(restaurant.getName());
    addButton = new QPushButton("Add Restaurant");
    menuItems = new QComboBox();
    itemsToAdd = new QSpinBox();
    itemsToAdd->setFixedSize(100, 20);
    itemsToAdd->setMaximum(100);
    addItemButton = new QPushButton("Add menu item(s)");

    //Iterating over the menu to add items to the menu ComboBox
    for (int i = 0; i < this->restaurant.getMenu().size(); i++)
    {
        menuItems->addItem(QString(this->restaurant.getMenu()[i].name + ": " + QString::number(this->restaurant.getMenu()[i].price)));
    }

    //Run on_AddMenuItemClicked() method in this class when "Add Items" button has been clicked
    menuItems->connect(addItemButton, SIGNAL(clicked()), this, SLOT(on_AddMenuItemClicked()));
    //Run on_AddRestaurantClicked() method in this class when "Add Restaurant" button has been clicked
    addButton->connect(addButton, SIGNAL(clicked()), this, SLOT(on_AddRestaurantClicked()));

    //Adding all input widgets to our QHBoxLayout that groups them all together.
    layout->addWidget(nameLabel);
    layout->addWidget(addButton);
    layout->addWidget(menuItems);
    layout->addWidget(itemsToAdd);
    layout->addWidget(addItemButton);
}

void RestaurantWidget::on_AddRestaurantClicked() {
    QString name = this->restaurant.getName();
    qInfo() << "Restaurant clicked: " << name;

    //adding restaurant to FoodApp selectedRestaurants vector (to keep track of which restaurants they want in the trip)
    parent->addRestaurant(this->restaurant);

    //adding restaurant to GUI list
    parent->addToList(name);


}

void RestaurantWidget::on_AddMenuItemClicked(){
    //Gather UI data
    //Gets how many items they want to buy
    int count = this->itemsToAdd->value();
    //Index of menu ComboBox - necessary to know since we need to know which item they want.
    int currentIndex = this->menuItems->currentIndex();
    //Name of the item they're buying
    QString itemName = this->restaurant.getMenu()[currentIndex].name + " - $" + QString::number(this->restaurant.getMenu()[currentIndex].price);

    //Code below is for validating they're not adding more than 100 of the same item
    int itemCount = 0;
    std::vector<QString> itemsAdded = parent->getMenuList();

    //Loop through existing menu items added to see how many we've already added for this specific kind of item
    //Need to do this since we can only add 100 of the same item in a trip
    for (int i = 0; i < itemsAdded.size(); i++){
        if (itemsAdded[i] == itemName){
            itemCount++;
        }
    }

    //actual foodapp connection
    if (itemCount + count <= 100){
        //Loop count times where count is the number of items being added
        for (int i = 0; i < count; i++){
            //Add menu item to FoodApp selectedItems to keep track of which items have been bought for each restaurant
            parent->addMenuItem(this->restaurant, this->restaurant.getMenu()[currentIndex]);
            //Add menu item to GUI/UI list
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
