#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "foodapp.h"
#include "restaurantwidget.h"
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



    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FoodApp app;

};
#endif // MAINWINDOW_H
