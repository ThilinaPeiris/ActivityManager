#include "database.h"

bool db::connect()
{
    path = QDir::currentPath() + "//ActivityManager.sqlite";
    //qDebug() << path;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if(!m_db.open())
    {
        return false; //Database not open
    }else
    {
        return true;
    }
}

bool db::disconnect()
{
    m_db.close();
    m_db = QSqlDatabase();
    m_db.removeDatabase(QSqlDatabase::defaultConnection);

    return true;
}
