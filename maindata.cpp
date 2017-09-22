#include "maindata.h"

QList<Cuisine> menuList;        //菜单列表
QVector<Table> tableVector;     //餐桌列表
QList<OrderCuisine> orderList;  //点菜列表
QList<Customer> customerList;   //顾客列表
QList<Waiter> waiterList;       //服务员列表
QList<Bill> billList;           //厨师及账单

MainData::MainData()
{
}

MainData::~MainData()
{
}

//导入数据
void MainData::dataIn()
{
    QSqlDatabase db =QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Restaurant.db");
    QSqlQuery query2(db);
    if(!db.open())
    {
        qDebug() << query2.lastError();
    }



    QSqlQuery query1;
    //菜单(编号，菜名，类型，单价, 好评数)
    query1.exec(QString("create table menu (id vchar primary key , name vchar , "
                       " price int, type vchar, praise_num int)"));

    //账户(账号， 姓名， 密码， 身份)
    query1.exec(QString("create table people(id vchar primary key , "
                       "name vchar, password vchar , identity vchar)"));

    //餐桌(顾客id，厨师id，餐桌号，餐桌状态，催菜，加水，结账，叫服务员)
    query1.exec(QString("create table tableinfo(customer_id vchar , waiter_id vchar ,"
                       "table_number int primary key , state vchar, urge_dishes int , "
                       " add_water int , check_out int , call_waiter int)"));

    //下单菜品(餐桌号，编号，菜名，类型，单价，备注，状态，数量)
    query1.exec(QString("create table food_plate(table_number int , id vchar primary key , "
                        "name vchar , type vchar , price int , remark vchar , state vchar ,"
                        "num int)"));

    //服务员
    query1.exec(QString("create table waiter(id vchar primary key, name vchar, password vchar,"
                       "comment_times int, comment_score int)"));

    //顾客
    query1.exec(QString("create table customer(id vchar primary key, name vchar, password vchar, "
                        "table_number int, credit int)"));

    //任务(菜名， 数量， 单价， 厨师账号， 厨师姓名)
    query1.exec(QString("create table bill(dish_name vchar, num int, dish_price int, cook_id vchar, "
                        "cook_name vchar)"));


    //导入菜单
    query2.exec("select * from menu");
    while(query2.next())
    {
        Cuisine food(query2.value(0).toString().toStdString(),query2.value(1).toString().toStdString(),
                     query2.value(2).toInt(),query2.value(3).toString().toStdString(),"","等候",
                     query2.value(4).toInt());
        menuList << food;
    }

    //导入餐桌
    for(int i=0;i<16;i++)       //最多16桌
    {
        Table one_table("","",i);
        tableVector.append(one_table);
    }
    query2.exec("select * from tableinfo");
    int i = 0;
    while(query2.next())
    {
        Table table(query2.value(0).toString().toStdString(),query2.value(1).toString().toStdString(),
                    query2.value(2).toInt(),State(query2.value(3).toInt()),
                    query2.value(4).toInt(),query2.value(5).toInt(),
                    query2.value(6).toInt(),query2.value(7).toInt());
        tableVector[i] = table;
        i++;
    }

    //导入每桌的食物托盘和总的点菜列表
    for(int i=0;i<16;i++)
    {
        query2.exec(QString("select * from food_plate where table_number = %1").arg(i));
        map<Cuisine,int> test;
        while(query2.next())     //导入一桌上的所有food和num
        {
            OrderCuisine orderfood(query2.value(1).toString().toStdString(),query2.value(2).toString().toStdString(),
                         query2.value(4).toInt(),query2.value(3).toString().toStdString(),
                         query2.value(5).toString().toStdString(),query2.value(6).toString().toStdString(),
                         query2.value(7).toInt(),query2.value(0).toInt());
            orderList << orderfood;

            Cuisine food(query2.value(1).toString().toStdString(),query2.value(2).toString().toStdString(),
                         query2.value(4).toInt(),query2.value(3).toString().toStdString(),
                         query2.value(5).toString().toStdString(),query2.value(6).toString().toStdString());
            int num = query2.value(7).toInt();
            test.insert(std::make_pair(food,num));
        }
        tableVector[i].setFoodPlate(test);
    }

    //导入服务员信息
    query2.exec("select * from waiter");
    while(query2.next())
    {
        Waiter waiter(query2.value(0).toString().toStdString(),query2.value(1).toString().toStdString(),
                      query2.value(2).toString().toStdString(),query2.value(3).toInt(),
                      query2.value(4).toInt());
        waiterList << waiter;
    }

    //导入顾客信息
    query2.exec("select * from customer");
    while(query2.next())
    {
        Customer customer(query2.value(0).toString().toStdString(),query2.value(1).toString().toStdString(),
                          query2.value(2).toString().toStdString(),query2.value(3).toInt(),
                          query2.value(4).toInt());
        customerList << customer;
    }

    //导入账单厨师信息
    query2.exec("select * from bill");
    while(query2.next())
    {
        Bill bill(query2.value(0).toString().toStdString(),query2.value(1).toInt(),
                  query2.value(2).toInt(),query2.value(3).toString().toStdString(),
                  query2.value(4).toString().toStdString());

        billList << bill;
    }
}


//导出数据
void MainData::dataOut()
{
    QSqlQuery query;
    //删除旧表
    query.exec("DROP table menu");
    query.exec("DROP table tableinfo");
    query.exec("DROP table mission");
    query.exec("DROP table food_plate");
    query.exec("DROP table waiter");
    query.exec("DROP table customer");

    /*建立新表,但是还没有数据*/

    //菜单(编号，菜名，类型，单价, 好评数)
    query.exec(QString("create table menu (id vchar primary key , name vchar , "
                       " price int, type vchar, praise_num int)"));

    //任务(菜名， 数量， 备注， 桌号)
    query.exec(QString("create table mission (name vchar primary key , num int , "
                       "remark vchar , table int)"));

    //餐桌(顾客id，厨师id，餐桌号，餐桌状态，催菜，加水，结账，叫服务员)
    query.exec(QString("create table tableinfo (customer_id vchar , waiter_id vchar ,"
                       "table_number int primary key , state vchar, urge_dishes int , "
                       " add_water int , check_out int , call_waiter int)"));

    //下单菜品(餐桌号，编号，菜名，类型，单价，备注，状态，好评，数量)
    query.exec(QString("create table food_plate (table_number int , id vchar, "
                       "name vchar , type vchar , price int , remark vchar , "
                       "state vchar , num int)"));

    //服务员信息(账号，姓名，密码，餐桌号，评论次数，总评分)
    query.exec(QString("create table waiter(id vchar primary key, name vchar, password vchar,"
                       "comment_times int, comment_score int)"));

    //顾客信息(账号，姓名，密码， 餐桌号， 积分)
    query.exec(QString("create table customer(id vchar primary key, name vchar, password vchar, "
                        "table_number int, credit int)"));

    /*开始存数据*/

    //导出菜单信息
    query.prepare("INSERT INTO menu VALUES(?,?,?,?,?)");
    QVariantList menu_id;
    QVariantList menu_name;
    QVariantList menu_price;
    QVariantList menu_type;
    QVariantList praise_num;
    for(int i=0;i<menuList.length();i++)
    {
        menu_id << menuList[i].getId().c_str();
        menu_name << menuList[i].getName().c_str();
        menu_price << menuList[i].getPrice();
        menu_type << menuList[i].getType().c_str();
        praise_num << menuList[i].getPraise();
     }
    query.addBindValue(menu_id);
    query.addBindValue(menu_name);
    query.addBindValue(menu_price);
    query.addBindValue(menu_type);
    query.addBindValue(praise_num);
    if(!query.execBatch())
    {
        qDebug() << query.lastError();
    }

    //导出餐桌数据
    for(int i=0;i<16;i++)
    {
        query.prepare("INSERT INTO tableinfo (customer_id, waiter_id, table_number, state, "
                      "urge_dishes, add_water, check_out, call_waiter) "
                      "VALUES (?,?,?,?,?,?,?,?)");
        QString a=tableVector[i].getCustomerId().c_str();
        QString b=tableVector[i].getWaiterId().c_str();
        int c=tableVector[i].getState();
        int d =tableVector[i].getUrgeDishes();
        int e =tableVector[i].getAddWater();
        int f =tableVector[i].getCheckOut();
        int g =tableVector[i].getCallWaiter();
        query.addBindValue(a);
        query.addBindValue(b);
        query.addBindValue(tableVector[i].getTableNumber());
        query.addBindValue(c);
        query.addBindValue(d);
        query.addBindValue(e);
        query.addBindValue(f);
        query.addBindValue(g);
        query.exec();
    }

    //导出点菜数据
    query.prepare("INSERT INTO food_plate (table_number, id, name, type, price, remark, "
                  "state, num) VALUES (?,?,?,?,?,?,?,?)");
    QVariantList table_number;
    QVariantList id;
    QVariantList name;
    QVariantList type;
    QVariantList price;
    QVariantList remark;
    QVariantList state;
    QVariantList num;
    for(int i=0;i<16;i++)
    {
        map<Cuisine,int>::iterator iter;
        for(iter=tableVector[i].getFoodPlate().begin();iter!=tableVector[i].getFoodPlate().end();iter++)
        {
            table_number << i;
            id << iter->first.getId().c_str();
            name << iter->first.getName().c_str();
            type << iter->first.getType().c_str();
            price << iter->first.getPrice();
            remark << iter->first.getRemark().c_str();
            state << iter->first.getState().c_str();
            num << iter->second;
        }
    }
    query.addBindValue(table_number);
    query.addBindValue(id);
    query.addBindValue(name);
    query.addBindValue(type);
    query.addBindValue(price);
    query.addBindValue(remark);
    query.addBindValue(state);
    query.addBindValue(num);
    if(!query.execBatch())
    {
        qDebug() << query.lastError();
    }

    //导出服务员数据
    query.prepare("INSERT INTO waiter VALUES(?,?,?,?,?)");
    QVariantList waiter_id;
    QVariantList waiter_name;
    QVariantList waiter_password;
    QVariantList comment_times;
    QVariantList comment_score;
    for(int i=0;i<waiterList.length();i++)
    {
        waiter_id << waiterList[i].getId().c_str();
        waiter_name << waiterList[i].getName().c_str();
        waiter_password << waiterList[i].getPassword().c_str();
        comment_times << waiterList[i].getCommentTimes();
        comment_score << waiterList[i].getCommentScore();
    }
    query.addBindValue(waiter_id);
    query.addBindValue(waiter_name);
    query.addBindValue(waiter_password);
    query.addBindValue(comment_times);
    query.addBindValue(comment_score);
    if(!query.execBatch())
    {
        qDebug() << query.lastError();
    }

    //导出顾客数据
    query.exec("INSERT INTO customer VALUES(?,?,?,?,?)");
    QVariantList customer_id;
    QVariantList customer_name;
    QVariantList customer_password;
    QVariantList customer_table_number;
    QVariantList customer_credit;
    for(int i=0;i<customerList.length();i++)
    {
        customer_id << customerList[i].getId().c_str();
        customer_name << customerList[i].getName().c_str();
        customer_password << customerList[i].getPassword().c_str();
        customer_table_number << customerList[i].getTableNumber();
        customer_credit << customerList[i].getCredit();
    }
    query.addBindValue(customer_id);
    query.addBindValue(customer_name);
    query.addBindValue(customer_password);
    query.addBindValue(customer_table_number);
    query.addBindValue(customer_credit);
    if(!query.execBatch())
    {
        qDebug() << query.lastError();
    }


    //检验输出
    /*
    query.exec("select * from tableinfo");
    while(query.next())
    {
        qDebug() << query.value(2).toInt();
        qDebug() << query.value(0).toString();
        qDebug() << query.value(1).toString();
    }
    */

    /*
    query.exec("select * from food_plate");
    while(query.next())
    {
        qDebug() << query.value(0).toInt();
        qDebug() << query.value(2).toString();
    }
    */

    /*
    query.exec("select * from waiter");
    while(query.next())
    {
        qDebug() << query.value(0).toString();
        qDebug() << query.value(3).toInt();
        qDebug() << query.value(4).toInt();
    }
    */
}

//导出数据2
void MainData::dataOut2()
{
    QSqlQuery query;
    query.exec("DROP table food_plate");
    query.exec("DROP table bill");

    //下单菜品(餐桌号，编号，菜名，类型，单价，备注，状态，好评，数量)
    query.exec(QString("create table food_plate (table_number int , id vchar, "
                       "name vchar , type vchar , price int , remark vchar , "
                       "state vchar, num int)"));

    query.exec(QString("create table bill(dish_name vchar, num int, dish_price int, cook_id vchar, "
                        "cook_name vchar)"));

    //导出数据
    query.prepare("INSERT INTO food_plate (table_number, id, name, type, price, remark, "
                  "state, num) VALUES (?,?,?,?,?,?,?,?)");
    QVariantList table_number;
    QVariantList id;
    QVariantList name;
    QVariantList type;
    QVariantList price;
    QVariantList remark;
    QVariantList state;
    QVariantList num;
    for(int i=0;i<orderList.length();i++)
    {
        table_number << orderList[i].getTableNumber();
        id << orderList[i].getId().c_str();
        name << orderList[i].getName().c_str();
        type << orderList[i].getType().c_str();
        price << orderList[i].getPrice();
        remark << orderList[i].getRemark().c_str();
        state << orderList[i].getState().c_str();
        num << orderList[i].getNum();

    }
    query.addBindValue(table_number);
    query.addBindValue(id);
    query.addBindValue(name);
    query.addBindValue(type);
    query.addBindValue(price);
    query.addBindValue(remark);
    query.addBindValue(state);
    query.addBindValue(num);
    if(!query.execBatch())
    {
        qDebug() << query.lastError();
    }



    query.prepare("INSERT INTO bill VALUES(?,?,?,?,?)");
    QVariantList dish_name;
    QVariantList dish_num;
    QVariantList dish_price;
    QVariantList cook_id;
    QVariantList cook_name;
    for(int i=0;i<billList.length();i++)
    {
        dish_name << billList[i].getDishName().c_str();
        dish_num << billList[i].getNum();
        dish_price << billList[i].getPrice();
        cook_id << billList[i].getCookId().c_str();
        cook_name << billList[i].getCookName().c_str();
    }
    query.addBindValue(dish_name);
    query.addBindValue(dish_num);
    query.addBindValue(dish_price);
    query.addBindValue(cook_id);
    query.addBindValue(cook_name);
    if(!query.execBatch())
    {
        qDebug() << query.lastError();
    }
}
