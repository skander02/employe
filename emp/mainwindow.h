#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_clicked();

    void on_mod_clicked();

    void on_supp_clicked();

    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_lineEdit_rech_textChanged(const QString &arg1);

    void on_qrcode_clicked();


    void on_pushButton_2_clicked();

    void on_ajc_clicked();

    void on_pushButton_3_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    Employe emp;
};
#endif // MAINWINDOW_H
