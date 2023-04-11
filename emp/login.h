#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QCalendarWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QTableView>
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
     bool ajouterlog();
     login(QString,QString,QString);
    ~login();

private slots:
     void on_pushButton_2_clicked();

private:
    Ui::login *ui;
     QString username,pass,mail;
     login *log;
};

#endif // LOGIN_H
