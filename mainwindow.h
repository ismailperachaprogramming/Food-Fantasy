#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "foodapp.h"
#include "restaurantwidget.h"
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

private:
    Ui::MainWindow *ui;
    FoodApp app;
    std::vector<QString> nameList;
    std::vector<QString> menuList;

    listOfRestaurants* popup;

};
#endif // MAINWINDOW_H
