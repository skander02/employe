#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QCalendarWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QTableView>
class Employe
{
    QString nom,pren,post,addr;
    int cin;
public:
    Employe();
    Employe(int cin,QString nom,QString pren,QString post,QString addr);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool modifier(int cin,QString nom, QString pren,QString post,QString addr);
    QSqlQueryModel * afficheroncombo();
    bool supprimer(int);

    void genererPDF();

    QSqlQueryModel * tri(QString,QString);

  // void recupererDatesDeLaBaseDeDonnees();

   QList<QDate> recupererDatesDeLaBaseDeDonnees(QCalendarWidget* calendarWidget);
    bool ajouterc(QCalendarWidget* calendarWidget,QString qle);
    bool supprimerc(QCalendarWidget* calendarWidget);

     bool afficherc(QCalendarWidget* calendarWidget,QLineEdit *qle);
    void rech(QComboBox *,const QString &arg1,QTableView *);


};

#endif // EMPLOYE_H
