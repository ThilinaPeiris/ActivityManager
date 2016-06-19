#include "addactivity.h"
#include "ui_addactivity.h"

addactivity::addactivity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addactivity)
{
    ui->setupUi(this);
}

addactivity::~addactivity()
{
    delete ui;
}

void addactivity::on_pushButton_add_clicked()
{
    db dbobj;
    QString null = "null";
    if(dbobj.connect())
    {
        //qDebug() << "Database: connection ok";
        QSqlQuery qry;
        qry.prepare("INSERT INTO activity(activityname) VALUES ('" + ui->lineEdit_actname->text() +"')");
        if(qry.exec())
        {
            dbobj.disconnect();
            QMessageBox::information(this,tr("save"),tr("<font color='black'><b>Activity details added.</b></font>"));
            this->hide();
        }else
        {
            dbobj.disconnect();
            //username and password doesn't match.
            QMessageBox::critical(this,tr("error::"),qry.lastError().text());
            //statusBar()->showMessage("Invalid Username or Password! Try Again!");
        }
    }else
    {
      return;
    }

    dbobj.disconnect();

}

void addactivity::on_pushButton_cancel_clicked()
{
    this->hide();
}
