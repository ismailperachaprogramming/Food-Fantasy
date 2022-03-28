#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    username = "Admin";
    password = "Pass";
    admin = false;
}

Login::~Login()
{
    delete ui;
}

bool Login::getAdminStatus()
{
    return admin;
}

void Login::on_loginButton_clicked()
{
   QString usernameInput = ui->usernameEntry->text();
   QString passwordInput = ui->passwordEntry->text();

   if(usernameInput == username && passwordInput == password)
   {
        admin = true;
        QMessageBox::information(this, "Login", "Administrator login verified. Welcome!");
   }
   else
   {
        admin = false;
        QMessageBox::information(this, "Login", "Administrator login failed.");
   }
}


