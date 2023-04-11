#include "mainwindow.h"
#include "connexion.h"
#include <QApplication>
#include <QMessageBox>

#include "logine.h"
#include "ui_logine.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connexion c;
    bool test=c.create_cnx();

    MainWindow w;
    logine l;
    if(test)
    {

        l.show();
        //w.show();
        QMessageBox::information(nullptr,QObject::tr("database is open"),
                                 QObject::tr("connection succful .\n"),
                QMessageBox::Ok);
    }

    else
        //qDebug()<<"connexion echouer";
        QMessageBox::critical(nullptr,QObject::tr("database is not open"),
                                QObject::tr("non connecter"),
                                QMessageBox::Cancel);
         //qDebug()<<"connexion echouer";



    l.show();
    //w.show();
    return a.exec();
}
