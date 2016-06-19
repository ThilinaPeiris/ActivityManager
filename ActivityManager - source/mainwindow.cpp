#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include<QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->horizontalSlider->setValue(0);
    ui->progressBar->setValue(0);
    //ui->progressBar->setValue(ui->horizontalSlider->value());
    //connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),ui->progressBar,SLOT(setValue(int)));

    Refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_save_clicked()
{
    QString des = ui->textEdit->toPlainText();
    QString from = ui->dateEdit_from->date().toString();
    QString to = ui->dateEdit_to->date().toString();
    int pro = ui->progressBar->value();
    QString pro_str = QString::number(pro);

//    QModelIndexList list =ui->activity_listView->selectionModel()->selectedIndexes();

//    QStringList slist;
//    foreach(const QModelIndex &index, list){
//        slist.append( index.data(Qt::DisplayRole ).toString());
//    }
//    //qDebug() << slist.join(",");

    QString activitynme = ui->label_activityname->text();

    if(ui->label_activityname->text()!=NULL)
    {
        db dbobj;

        if(dbobj.connect())
        {
            //qDebug() << "Database: connection ok";
            QSqlQuery qry;
            //qDebug() << slist.at(0);
            //QString temp = "UPDATE activity SET description = '" + des + "', start='" + from + "', end='"+to+"', completion='"+ pro_str +"' WHERE activityname='" +slist.at(0)+ "'";
            //qDebug() << temp;
            qry.prepare("UPDATE activity SET description = '" + des + "', start='" + from + "', end='"+to+"', completion="+ pro_str +" WHERE activityname='" + activitynme + "'");
            //qry.prepare("UPDATE activity SET description = '" + des + "', start='" + from + "', end='"+to+"' WHERE activityname='" +slist.at(0)+ "'");
            if(qry.exec())
            {
                dbobj.disconnect();
                QMessageBox::information(this,tr("save"),tr("<font color='black'><b>Activity details added.</b></font>"));
            }else
            {
                //dbobj.disconnect();
                //username and password doesn't match.
                QMessageBox::critical(this,tr("error::"),qry.lastError().text());
                //statusBar()->showMessage("Invalid Username or Password! Try Again!");
            }
        }else
        {
            //database not connected
        }
        dbobj.disconnect();
    }
}

void MainWindow::on_pushButton_addact_clicked()
{
    addactivity addact;
    addact.setModal(true);
    addact.exec();
    Refresh();
}

void MainWindow::Refresh()
{
    db dbobj;
    QSqlQueryModel *modal = new QSqlQueryModel();
    if(dbobj.connect())
    {
        QSqlQuery *qry = new QSqlQuery(dbobj.m_db);

        qry->prepare("SELECT activityname FROM activity");

        if(qry->exec())
        {
            modal->setQuery(*qry);
            ui->activity_listView->setModel(modal);
            dbobj.disconnect();
        }else
        {
            //dbobj.disconnect();
            //query not exectued. error handle
        }
    }else
    {
        //database not connected
    }
    dbobj.disconnect();
}

void MainWindow::on_pushButton_remove_clicked()
{

//    QModelIndexList list =ui->activity_listView->selectionModel()->selectedIndexes();

//    QStringList slist;
//    foreach(const QModelIndex &index, list){
//        slist.append( index.data(Qt::DisplayRole ).toString());
//    }
//    //qDebug() << slist.join(",");

    QString activitynme = ui->label_activityname->text();

    if(activitynme!=NULL)
    {
        db dbobj;

        if(dbobj.connect())
        {
            //qDebug() << "Database: connection ok";
            QSqlQuery qry;
            //qDebug() << slist.at(0);
            qry.prepare("DELETE FROM activity WHERE activityname='" +activitynme+ "'");
            if(qry.exec())
            {
                dbobj.disconnect();
                QMessageBox::information(this,tr("save"),tr("<font color='black'><b>Activity details deleted.</b></font>"));

            }else
            {
                //dbobj.disconnect();
                //username and password doesn't match.
                QMessageBox::critical(this,tr("error::"),qry.lastError().text());
                //statusBar()->showMessage("Invalid Username or Password! Try Again!");
            }
        }else
        {
            //database not connected
        }
        dbobj.disconnect();

        Refresh();
    }
}

void MainWindow::on_activity_listView_indexesMoved(const QModelIndexList &indexes)
{

    QModelIndexList list =ui->activity_listView->selectionModel()->selectedIndexes();

    QStringList slist;
    foreach(const QModelIndex &index, list){
        slist.append( index.data(Qt::DisplayRole ).toString());
    }
    //qDebug() << slist.join(",");

    if(!slist.empty())
    {
        db dbobj;

        if(dbobj.connect())
        {
            //qDebug() << "Database: connection ok";
            QSqlQuery qry;
            qry.prepare("SELECT * FROM activity WHERE activityname='" +slist.at(0)+ "'");
            if(qry.exec())
            {
                while(qry.next())
                {
                    ui->textEdit->setText(qry.value(2).toString());
                   //ui->dateEdit_from->setDate(qry.value(3).toString());
                   //ui->dateEdit_to->setDate(qry.value(4).toString());
                   //ui->progressBar->setValue(qry.value(5));
                   //ui->horizontalSlider->setValue(qry.value(5));
                }

            }else
            {
                //dbobj.disconnect();
                //username and password doesn't match.
                QMessageBox::critical(this,tr("error::"),qry.lastError().text());
                //statusBar()->showMessage("Invalid Username or Password! Try Again!");
            }
        }else
        {
            //database not connected
        }
        dbobj.disconnect();

        Refresh();
    }
}

void MainWindow::on_activity_listView_clicked(const QModelIndex &index)
{

    QModelIndexList list =ui->activity_listView->selectionModel()->selectedIndexes();

    QStringList slist;
    foreach(const QModelIndex &index, list){
        slist.append( index.data(Qt::DisplayRole ).toString());
    }
    //qDebug() << slist.join(",");

    if(!slist.empty())
    {
        db dbobj;

        if(dbobj.connect())
        {
            //qDebug() << "Database: connection ok";
            QSqlQuery qry;
            qry.prepare("SELECT * FROM activity WHERE activityname='" +slist.at(0)+ "'");
            if(qry.exec())
            {
                while(qry.next())
                {
                    ui->textEdit->setText(qry.value(2).toString());
                    ui->dateEdit_from->setDate(qry.value(3).toDate());
                    ui->dateEdit_to->setDate(qry.value(4).toDate());
                    ui->progressBar->setValue(qry.value(5).toInt());
                    ui->horizontalSlider->setValue(qry.value(5).toInt());
                    ui->label_activityname->setText(slist.at(0));
                }

            }else
            {
                //dbobj.disconnect();
                //username and password doesn't match.
                QMessageBox::critical(this,tr("error::"),qry.lastError().text());
                //statusBar()->showMessage("Invalid Username or Password! Try Again!");
            }
        }else
        {
            //database not connected
        }
        dbobj.disconnect();

        Refresh();
    }
}
