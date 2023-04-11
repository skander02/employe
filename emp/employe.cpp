#include "employe.h"
#include<QPdfWriter>
#include <QPixmap>
#include <QDate>
#include <QTextCharFormat>
#include <QPainter>
#include <QDebug>

Employe::Employe()
{

}

Employe::Employe(int cin,QString nom,QString pren,QString post,QString addr)
{

    this->cin=cin;
    this->nom=nom;
    this->pren=pren;
    this->post=post;
    this->addr=addr;
}

bool Employe::ajouter()
{
    QSqlQuery query;
        //QString id= QString::number(ID);
        query.prepare("INSERT INTO EMPLOYES (cin,nom,pren,post,addr) "
                            "VALUES (:cin, :nom, :pren,:post ,:addr)");
        query.bindValue(":cin",cin);
        query.bindValue(":nom",nom);
        query.bindValue(":pren",pren);
        query.bindValue(":post",post);
        query.bindValue(":addr",addr);



        return    query.exec();

    }
    QSqlQueryModel * Employe ::afficher()
    {

        QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from EMPLOYES");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PREN "));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("POST "));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE "));
        ;

            return model;
    }

    bool Employe::modifier(int cin,QString nom, QString pren,QString post,QString addr)
    {

        QSqlQuery query;
    //QString idc=QString::number(id);
        query.prepare("UPDATE EMPLOYES SET nom= :nom, pren= :pren, post= :post, addr= :addr where cin= :cin ");
        query.bindValue(":cin",cin);
        query.bindValue(":nom",nom);
        query.bindValue(":pren",pren);
        query.bindValue(":post",post);
        query.bindValue(":addr",addr);


                return    query.exec();

    }
    QSqlQueryModel * Employe ::afficheroncombo()
    {

        QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from EMPLOYES");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));

            return model;
    }

    bool Employe:: supprimer(int cin)
    {
        //QString ident1= QString ::number(idd);
        QSqlQuery query;
        query.prepare("Delete from EMPLOYES where cin = :cin ");
        query.bindValue(":cin",cin);
        return    query.exec();

    }

    void  Employe::genererPDF(){
                         QPdfWriter pdf("C:\\Users\\hedia\\OneDrive\\Bureau\\emp\\pdf.pdf");
                         QPainter painter(&pdf);
                        int i = 4000;
                             painter.setPen(Qt::red);
                             painter.setFont(QFont("Arial", 50));
                             painter.drawText(900,1200,"TAB employes");
                             painter.setPen(Qt::red);
                             painter.setFont(QFont("Arial", 15));
                             painter.drawRect(100,100,7300,2600);
                             painter.drawRect(0,3000,9600,500);
                             painter.setFont(QFont("Arial", 9));
                             painter.drawText(200,3300,"cin");
                             painter.drawText(1300,3300,"nom");
                             painter.drawText(2400,3300,"pren");
                                painter.drawText(3500,3300,"post");
                                   painter.drawText(4600,3300,"addr");


                             QSqlQuery query;
                             query.prepare("select * from EMPLOYES");
                             query.exec();
                             while (query.next())
                             {
                                 painter.drawText(200,i,query.value(0).toString());
                                 painter.drawText(1300,i,query.value(1).toString());
                                 painter.drawText(2400,i,query.value(2).toString());
                                 painter.drawText(3500,i,query.value(3).toString());
                                 painter.drawText(4600,i,query.value(4).toString());


                                i = i + 500;
                             }}
    QSqlQueryModel * Employe ::tri(QString tripar,QString triordre)
    {
        QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("SELECT * FROM EMPLOYES ORDER BY " + tripar + " " + triordre);
        return model;
    }


  /* void Employe::recupererDatesDeLaBaseDeDonnees()
   {
       QSqlQuery query("SELECT datee FROM datem");

       while (query.next()) {
           QDate date = query.value(0).toDate();
           if (date.isValid()) {
               QTextCharFormat format;
               format.setBackground(Qt::red);
             }
       }
   }*/

   QList<QDate> Employe::recupererDatesDeLaBaseDeDonnees(QCalendarWidget *calendarWidget)
   {
       QList<QDate> dates;
        QSqlQuery query("SELECT datee FROM datem");
        while (query.next()) {
            QDate date = query.value(0).toDate();
            if (date.isValid()) {
                QTextCharFormat format;
                format.setBackground(Qt::red);
                calendarWidget->setDateTextFormat(date, format);
                dates.append(date);
            }
        }
        return dates;
   }


   bool Employe::ajouterc(QCalendarWidget* calendarWidget,QString titre)
   {
        QDate datee;

       datee=calendarWidget->selectedDate();
       QTextCharFormat format;
       format.setBackground(Qt::red);
        calendarWidget->setDateTextFormat(datee, format);

         //QString datees = datee.toString(Qt::ISODate);
       QSqlQuery query;
           //QString id= QString::number(ID);
           query.prepare("INSERT INTO datem (datee,titre) "
                               "VALUES (:datees,:titre)");
           query.bindValue(":datees",datee);
           query.bindValue(":titre",titre);



           return    query.exec();

       }

    bool Employe::supprimerc(QCalendarWidget* calendarWidget)
    {
        QSqlQuery query;
        QDate datee;
        datee=calendarWidget->selectedDate();
        QTextCharFormat format;
        format.setBackground(Qt::white);
         calendarWidget->setDateTextFormat(datee, format);
       datee=calendarWidget->selectedDate();
        query.prepare("Delete from datem where datee = :datee ");
        query.bindValue(":datee",datee);
        return    query.exec();
    }

    bool Employe::afficherc(QCalendarWidget* calendarWidget,QLineEdit *qle)
    {

           QDate selectedDate = calendarWidget->selectedDate();

           QString sqlQuery = "SELECT titre FROM datem WHERE datee = :selectedDate";

           QSqlQuery query;
           query.prepare(sqlQuery);
           query.bindValue(":selectedDate", selectedDate);

           if (!query.exec()) {
            } else if (!query.first()) {
              return false; } else {
               QString titre = query.value(0).toString();
               qle->setText(titre);
               return true;
           }
           return true;
    }

    void Employe::rech(QComboBox *comboBox_crit,const QString &arg1,QTableView *tabemp)
    {
        QSqlQueryModel *model= new QSqlQueryModel();
                QSqlQuery   *query= new QSqlQuery();
        if(comboBox_crit->currentText()=="cin"
                ){
            query->prepare("SELECT * FROM EMPLOYES WHERE cin LIKE'"+arg1+"%'");//
    query->exec();
        model->setQuery(*query);
    tabemp->setModel(model);


        }
        else {
            if(comboBox_crit->currentText()=="nom"){
                query->prepare("SELECT * FROM EMPLOYES WHERE nom LIKE'"+arg1+"%'");//
        query->exec();
            model->setQuery(*query);
        tabemp->setModel(model);
            }
            else{
                if(comboBox_crit->currentText()=="post")
                    query->prepare("SELECT * FROM EMPLOYES WHERE post LIKE'"+arg1+"%'");//
            query->exec();
                model->setQuery(*query);
           tabemp->setModel(model);
                }

            }
    }
