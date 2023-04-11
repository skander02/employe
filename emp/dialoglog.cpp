#include "dialoglog.h"
#include "ui_dialoglog.h"
#include "mainwindow.h"
#include "QMessageBox"
#include "ui_mainwindow.h"

Dialoglog::Dialoglog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialoglog)
{
    ui->setupUi(this);
}

Dialoglog::~Dialoglog()
{
    delete ui;
}

void Dialoglog::on_pushButton_clicked()
{

    if((ui->lineEdit->text()=="admin")&&(ui->lineEdit_2->text()=="admin"))
  {

        QMessageBox::information(this,"Sucess","Accee garantie");
        hide();
        MainWindow w;
        w.setModal(true);
        w.exec();
  }
      else
      {
          QMessageBox::information(this,"Erreur","Verifier vos informations");

      }
}
