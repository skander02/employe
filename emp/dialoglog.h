#ifndef DIALOGLOG_H
#define DIALOGLOG_H

#include <QDialog>

#include "employe.h"

namespace Ui {
class Dialoglog;
}

class Dialoglog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialoglog(QWidget *parent = nullptr);
    ~Dialoglog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialoglog *ui;
};

#endif // DIALOGLOG_H
