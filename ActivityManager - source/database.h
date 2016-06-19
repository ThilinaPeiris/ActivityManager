#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QDebug>

class db
{
public:
    bool connect();
    bool disconnect();
    QSqlDatabase m_db;
    QString path;
};

#endif // DATABASE_H
