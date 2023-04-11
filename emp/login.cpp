#include "login.h"
#include "ui_login.h"
#include<QPdfWriter>
#include <QPixmap>
#include <QDate>
#include <QTextCharFormat>
#include <QPainter>
#include <QDebug>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

bool login::ajouterlog()
{
    QSqlQuery query;
        //QString id= QString::number(ID);
        query.prepare("INSERT INTO login (username,pass,mail) "
                            "VALUES (:username, :pass, :mail)");
        query.bindValue(":username",username);
        query.bindValue(":pass",pass);
        query.bindValue(":mail",mail);

        return    query.exec();

    }

login::login(QString username,QString pass,QString mail)
{
    this->username=username;
    this->pass=pass;
    this->mail=mail;
}



void login::on_pushButton_2_clicked()
{
    login lo(ui->lineEdit_4->text(),ui->lineEdit_3->text(),ui->lineEdit_5->text());
       bool test= lo.ajouterlog();

}
