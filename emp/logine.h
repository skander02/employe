#ifndef LOGINE_H
#define LOGINE_H

#include <QDialog>
#include <QLineEdit>
#include "logine.h"
namespace Ui {
class logine;
}

class logine : public QDialog
{
    Q_OBJECT

public:
    explicit logine(QWidget *parent = nullptr);
    ~logine();
     bool ajouter(QString username,QString pass,QString mail,int tel);
     bool verif(QString,QString);
     void sendMail(QString to);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::logine *ui;
    //logine *log;
     bool mod=true;
};


#endif // LOGINE_H
