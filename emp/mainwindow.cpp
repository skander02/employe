#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QIntValidator>


#include <QChartView>
#include <QPieSeries>
#include <QtCharts>
#include <QtSql/QSqlQueryModel>
#include <QtSql>


#include <QDebug>
#include <fstream>
#include <iostream>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextEdit>
#include <QTextStream>
#include<QWidget>
#include <QtSvg/QSvgRenderer>
#include<QDirModel>
#include "qrcode.h"
#include "QPainter"
#include <QDate>
using qrcodegen::QrCode;
using qrcodegen::QrSegment;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{   QString tit;
    QLineEdit *lineEdit_cin = new QLineEdit(parent); // parent peut être un autre widget ou nullptr
    QRegExpValidator *validator = new QRegExpValidator(QRegExp("[0-9]*"), parent);


    ui->setupUi(this);
    ui->tabemp->setModel(emp.afficher());//afficher
    ui->comboBox->setModel(emp.afficheroncombo());
   //tit= emp.afficherc(ui->calendarWidget,ui->lineEdit_rech_2);

   // ui->lineEdit_rech_2->setText(tit);
    emp.afficherc(ui->calendarWidget,ui->lineEdit_rech_2);

    QList<QDate> dates = emp.recupererDatesDeLaBaseDeDonnees(ui->calendarWidget);


}

MainWindow::~MainWindow()
{
    delete ui;
}





// Appliquer le QRegExpValidator au QLineEdit
//lineEdit_cin->setValidator(validator);

void MainWindow::on_ajouter_clicked()
{


    int cin = ui->lineEdit_cin->text().toInt();
    QIntValidator *cinValidator = new QIntValidator(0, 99999999, this);



    //QIntValidator *cinValidator = new QIntValidator(0, 99999999, this);
    QString cinStr = ui->lineEdit_cin->text();
    int pos = 0;
    if (cinValidator->validate(cinStr, pos) != QValidator::Acceptable) {
        // Afficher un message d'erreur si la saisie est invalide
        QMessageBox::critical(this, "Erreur", "Le CIN doit être un nombre entier de maximum 8 chiffres.");
        return;
    }
    else
    {



    Employe e(cin,ui->lineEdit_nom->text(),ui->lineEdit_pren->text(),ui->lineEdit_post->text(),ui->lineEdit_addr->text());
       bool test= e.ajouter();
       ui->tabemp->setModel(e.afficher());
        ui->comboBox->setModel(emp.afficheroncombo());
    }
}

void MainWindow::on_mod_clicked()
{
    bool    test=emp.modifier(ui->lineEdit_cin->text().toInt(),ui->lineEdit_nom->text(),ui->lineEdit_pren->text(),ui->lineEdit_post->text(),ui->lineEdit_addr->text()) ;
          if (test)
          { ui->comboBox->setModel(emp.afficheroncombo());
                  ui->tabemp->setModel(emp.afficher());
              QMessageBox::information(nullptr,QObject::tr("OK"),
                                   QObject::tr("modification établie"),
                                   QMessageBox::Ok);}
          else{
          QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                  QObject::tr("modification non établie"),
                                  QMessageBox::Cancel);}


}

void MainWindow::on_supp_clicked()
{
    bool test=emp.supprimer(ui->comboBox->currentText().toInt());
    if(test)
    {ui->tabemp->setModel(emp.afficher());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("suppression succful .\n"),
                    QMessageBox::Cancel);
            ui->comboBox->setModel(emp.afficheroncombo());
        }

        else
            QMessageBox::critical(nullptr,QObject::tr("supprimer not open"),
                                    QObject::tr("click cancel to exist"),
                                    QMessageBox::Cancel);

}

void MainWindow::on_pushButton_clicked()
{
    if(ui->asc->isChecked())
    {
       ui->tabemp->setModel(emp.tri(ui->comboBox_crit_2->currentText(),"asc"));
    }
    if(ui->desc->isChecked())
    {
        ui->tabemp->setModel(emp.tri(ui->comboBox_crit_2->currentText(),"desc"));

    }

}

void MainWindow::on_pushButton_6_clicked()
{
    emp.genererPDF();
}

void MainWindow::on_lineEdit_rech_textChanged(const QString &arg1)
{


    emp.rech(ui->comboBox_crit,arg1,ui->tabemp);




}

void MainWindow::on_qrcode_clicked()
{
    if(ui->tabemp->currentIndex().row()==-1)
               QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                        QObject::tr("Veuillez Choisir du Tableau.\n"
                                                    "Click Ok to exit."), QMessageBox::Ok);
           else
           {


       QModelIndexList selection = ui->tabemp->selectionModel()->selectedIndexes();
        if (selection.isEmpty())
            return;

        int row = selection.at(0).row();

        // Parcours des colonnes pour récupérer tous les attributs
        QStringList attributs;
        for (int col = 0; col < ui->tabemp->model()->columnCount(); col++) {
            attributs << ui->tabemp->model()->data(ui->tabemp->model()->index(row, col)).toString();
        }

        // Génération du QR code à partir des attributs
        const QrCode qr = QrCode::encodeText(attributs.join(",").toStdString().c_str(), QrCode::Ecc::LOW);

        // Écriture du QR code dans un fichier SVG
        std::ofstream myfile;
        myfile.open("qrcode.svg");
        myfile << qr.toSvgString(0);
        myfile.close();

        // Affichage du QR code dans l'interface utilisateur
        QSvgRenderer svgRenderer(QString("qrcode.svg"));
        QPixmap pix(QSize(90, 90));
        QPainter pixPainter(&pix);
        svgRenderer.render(&pixPainter);
        ui->QRCODE_3->setPixmap(pix);


}
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_ajc_clicked()
{
    emp.ajouterc(ui->calendarWidget,ui->lineEdit_rech_3->text());
    QList<QDate> dates = emp.recupererDatesDeLaBaseDeDonnees(ui->calendarWidget);

}

void MainWindow::on_pushButton_3_clicked()
{
    emp.supprimerc(ui->calendarWidget);
    QList<QDate> dates = emp.recupererDatesDeLaBaseDeDonnees(ui->calendarWidget);

}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    if( emp.afficherc(ui->calendarWidget,ui->lineEdit_rech_2))
    {

    }
    else
        ui->lineEdit_rech_2->setText(" ");
}

void MainWindow::on_pushButton_7_clicked()
{
    QSqlQuery query;
        query.exec("SELECT post FROM EMPLOYES");

        QMap<QString, int> counts;
        int total = 0;

        while (query.next()) {
            QString type = query.value(0).toString();
            if (counts.contains(type)) {
                counts[type]++;
            } else {
                counts[type] = 1;
            }
            total++;
        }

        QPieSeries *series = new QPieSeries();
        for (auto it = counts.begin(); it != counts.end(); it++) {
            double percentage = 100 * it.value() / total;
            series->append(it.key() + QString(" (%1%)").arg(percentage, 0, 'f', 1), it.value());
        }

        QChart *chart = new QChart();

        chart->addSeries(series);
        chart->setTitle("Statistiques pour l'attribut \"POST\"");
        series->setPieSize(0.7);
        series->setLabelsVisible();

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        QDialog *dialog = new QDialog();
        dialog->resize(800, 600);
        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(chartView);
        dialog->setLayout(layout);

        chart->setParent(chartView);
        dialog->exec();
}
