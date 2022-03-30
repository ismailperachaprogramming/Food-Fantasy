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
#include <QMessageBox>
#include <QSpinBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

/*!
 * \brief RestaurantWidget class - inherits from QWidget
 */

class RestaurantWidget : public QWidget
{
    Q_OBJECT
public:

    //! RestaurantWidget
        /*!
         * \brief Initializes all UI elements with passed in restaurant object data
         *
         */
    explicit RestaurantWidget(Restaurant restaurantPassed, MainWindow *parent = nullptr);

    ~RestaurantWidget();

private:
    QHBoxLayout *layout; /*!< QHBoxLayout object */
    QLabel *nameLabel; /*!< Restaurant name - QLabel  object */
    QPushButton *addButton; /*!< Add restaurant to trip - QPushButton  object */
    QComboBox *menuItems; /*!< QComboBox of menu items */
    QSpinBox *itemsToAdd; /*!< QSpinBox that lets user pick number of items to add */
    QPushButton *addItemButton; /*!< QPushButton to add a menu item to trip */

    //restaurant that this ui element represents
    Restaurant restaurant; /*!< Restaurant associated with widget */
    MainWindow *parent; /*!< Reference to the main application */

private slots:
    //these call methods in mainwindow.cpp
   void on_AddRestaurantClicked();
   void on_AddMenuItemClicked();


};

#endif // RESTAURANTWIDGET_H
