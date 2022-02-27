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
    void addToList(QString name);
    void addToMenuList(QString name, QString restaurantName);


    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_planTrip_clicked();

private:
    Ui::MainWindow *ui;
    FoodApp app;
    std::vector<QString> nameList;
    std::vector<QString> menuList;

};
#endif // MAINWINDOW_H
