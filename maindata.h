#ifndef MAINDATA_H
#define MAINDATA_H
#include <QString>
#include <QList>
#include <QVector>
#include <map>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariantList>
#include <QSqlError>
#include <QDebug>
#include "cafeteria.h"
#include "table.h"
#include "customer.h"
#include "waiter.h"
#include "ordercuisine.h"
#include "bill.h"

class MainData
{
public:
    MainData();
    void dataIn();
    void dataOut();
    void dataOut2();
    ~MainData();

};

#endif // MAINDATA_H
