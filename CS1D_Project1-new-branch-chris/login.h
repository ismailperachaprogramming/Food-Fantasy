#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    bool getAdminStatus();

private slots:
    void on_loginButton_clicked();

private:
    Ui::Login *ui;
    QString username;
    QString password;
    bool admin;
};

#endif // LOGIN_H
