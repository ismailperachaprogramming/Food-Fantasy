#ifndef RESTAURANTWIDGET_H
#define RESTAURANTWIDGET_H

class MainWindow;

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "restaurant.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class RestaurantWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RestaurantWidget(Restaurant restaurantPassed, MainWindow *parent = nullptr);

    ~RestaurantWidget();

private:
    QHBoxLayout *layout;
    QLabel *nameLabel;
    QPushButton *addButton;
    QComboBox *menuItems;

    //restaurant that this ui element represents
    Restaurant restaurant;
    MainWindow *parent;

private slots:
    //these call methods in mainwindow.cpp
   void on_AddRestaurantClicked();
   void on_AddMenuItemClicked(int index);


};

#endif // RESTAURANTWIDGET_H
