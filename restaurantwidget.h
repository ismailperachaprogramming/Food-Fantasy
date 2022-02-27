#ifndef RESTAURANTWIDGET_H
#define RESTAURANTWIDGET_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "restaurant.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>

class RestaurantWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RestaurantWidget(Restaurant restaurantPassed, QWidget *parent = nullptr);

    ~RestaurantWidget();

private:
    QHBoxLayout *layout;
    QLabel *nameLabel;
    QPushButton *addButton;
    QComboBox *menuItems;

    //restaurant that this ui element represents
    Restaurant restaurant;

private slots:
    //these call methods in mainwindow.cpp
   void on_AddRestaurantClicked(QString restaurantName);
   void on_AddMenuItemClicked(int index);


};

#endif // RESTAURANTWIDGET_H
