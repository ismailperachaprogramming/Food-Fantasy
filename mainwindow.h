#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "foodapp.h"
#include "restaurantwidget.h"
#include "restaurant.h"
#include "Database.h"
#include "listofrestaurants.h"
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void addRestaurant(Restaurant restaurant);
    void addMenuItem(Restaurant restaurant, MenuItem item);
    void addToList(QString name);
    void addToMenuList(QString name, QString restaurantName);
    std::vector<QString> getMenuList() const { return menuList; }


    ~MainWindow();

private slots:

    void on_planTrip_clicked();

    void on_openListButton_clicked();

    void on_clearButton_clicked();

    void on_customTrip_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<QString> nameList;
    std::vector<QString> menuList;

    //Database object - use this to interact with SQLite database
    Database db;
    //Stores the currentTrip. nullptr upon program opening.
    Trip* currentTrip;
    //all restaurants in db are in this vector
    std::vector<Restaurant> restaurants;

    //For keeping track of UI clicked on
    std::vector<Restaurant> selectedRestaurants;
    //Multi map that stores menu item objects to a corresponding key, where the key is the restaurant
    std::multimap<int, MenuItem> selectedItems;

    listOfRestaurants* popup;

};
#endif // MAINWINDOW_H
