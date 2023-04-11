#include "logine.h"
#include "ui_logine.h"
#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QLineEdit>
logine::logine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logine)
{
    ui->setupUi(this);
    ui->tel->setValidator(new QRegExpValidator(QRegExp("[0-9]{5,8}"),this));
        //ui->cindon->setValidator(new QIntValidator(0, 99999999, this));
       // ui->username->setValidator(new QIntValidator(0, 99999999, this));
      //  ui->pass->setValidator(new QIntValidator(0, 9999, this));


}

logine::~logine()
{
    delete ui;
}

void logine::sendMail(QString to)
{
    QSqlQuery query;
       query.prepare("SELECT pass FROM users WHERE mail = :to");
       query.bindValue(":to", to);
       if (!query.exec() || !query.next()) {
           qDebug() << "Erreur de requête SQL ou adresse e-mail non trouvée dans la base de données.";
           return;
       }
       QString password = query.value(0).toString();


       // Configuration des paramètres de l'e-mail
       QString from = "exemple@esprit.tn";
       QString smtpServer = "smtp.gmail.com";
       int smtpPort = 587;

       // Création du message de l'e-mail
       QString subject = "Mot de passe oublié";
       QString body = "Bonjour,\n\nVotre mot de passe est : " + password;

       // Ouverture d'une connexion SSL avec le serveur SMTP
       QSslSocket socket;
       socket.connectToHostEncrypted(smtpServer, smtpPort);
       if (!socket.waitForConnected()) {
           qDebug() << "Erreur de connexion au serveur SMTP.";
           return;
       }

       // Lecture de la réponse initiale du serveur
       if (!socket.waitForReadyRead()) {
           qDebug() << "Erreur de lecture de la réponse du serveur SMTP.";
           return;
       }
       QString response = QString::fromUtf8(socket.readAll());
       qDebug() << "Réponse initiale du serveur SMTP : " << response;

       // Envoi de la commande EHLO pour initialiser la connexion
       QString heloCommand = "EHLO mydomain.com\r\n";
       if (socket.write(heloCommand.toUtf8()) == -1) {
           qDebug() << "Erreur d'envoi de la commande EHLO.";
           return;
       }
       if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
           qDebug() << "Erreur lors de l'envoi de la commande EHLO.";
           return;
       }
       response = QString::fromUtf8(socket.readAll());
       qDebug() << "Réponse du serveur SMTP après la commande EHLO : " << response;

       // Envoi de la commande STARTTLS pour activer le chiffrement SSL
       QString starttlsCommand = "STARTTLS\r\n";
       if (socket.write(starttlsCommand.toUtf8()) == -1) {
           qDebug() << "Erreur d'envoi de la commande STARTTLS.";
           return;
       }
       if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
           qDebug() << "Erreur lors de l'envoi de la commande STARTTLS.";
           return;
       }
       response = QString::fromUtf8(socket.readAll());
       qDebug() << "Réponse du serveur SMTP après la commande STARTTLS : " << response;

       // Configuration des options de chiffrement SSL
      // QSsl
}

bool logine::verif(QString username, QString pass)
{
    QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM users WHERE username = :username AND pass = :pass");
       query.bindValue(":username", username);
       query.bindValue(":pass", pass);
       if (!query.exec()) {
          // qDebug() << "Erreur lors de l'exécution de la requête.";
           return false;
}
}



bool logine::ajouter(QString username,QString pass,QString mail,int tel)
{
    QSqlQuery query;
        //QString id= QString::number(ID);
        query.prepare("INSERT INTO users (username,pass,mail,tel) "
                            "VALUES (:username, :pass, :mail,:tel)");
        query.bindValue(":username",username);
        query.bindValue(":pass",pass);

        query.bindValue(":mail",mail);
        query.bindValue(":tel",tel);



        return    query.exec();
}


void logine::on_pushButton_clicked()
{
    QString username=ui->lineEdit->text();
    QString pass=ui->lineEdit_2->text();

    logine l;
    if(l.verif(username,pass))
    {

    this->hide();

 MainWindow *mainwindow= new MainWindow();
 mainwindow->show();
    }
}

void logine::on_pushButton_2_clicked()
{
    logine l;
    QString username=ui->username->text();
    QString pass=ui->pass->text();
    QString mail=ui->mail->text();
    int tel = ui->tel->text().toInt();
    l.ajouter(username,pass,mail,tel);

}

void logine::on_pushButton_3_clicked()
{
    logine l;
    QString mail=ui->mail_2->text();
    l.sendMail(mail);
}

void logine::on_pushButton_4_clicked()
{
    if(mod)
    {
   ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
   mod=false;
    }
   else
    {
       ui->lineEdit_2->setEchoMode(QLineEdit::Password);
       mod=true;
    }
}
