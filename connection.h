#ifndef CONNECTION_H
#define CONNECTION_H
//连接数据库
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection()
{
    QSqlDatabase db =QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Restaurant.db");
    if(!db.open())
        return false;
    QSqlQuery query;
    query.exec(QString("create table menu (id vchar primary key, name vchar,"
                       "unit_price int, type vchar)"));
    query.exec(QString("insert into menu values ('001','米饭','2','主食')"));
    return true;
}
#endif // CONNECTION_H
