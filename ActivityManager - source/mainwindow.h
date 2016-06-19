#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "addactivity.h"
#include <QtCore>
#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Refresh();

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_addact_clicked();

    void on_pushButton_remove_clicked();

    void on_activity_listView_indexesMoved(const QModelIndexList &indexes);

    void on_activity_listView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
