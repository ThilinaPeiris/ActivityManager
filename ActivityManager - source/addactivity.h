#ifndef ADDACTIVITY_H
#define ADDACTIVITY_H

#include <QDialog>
#include "database.h"
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class addactivity;
}

class addactivity : public QDialog
{
    Q_OBJECT

public:
    explicit addactivity(QWidget *parent = 0);
    ~addactivity();

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::addactivity *ui;
};

#endif // ADDACTIVITY_H
