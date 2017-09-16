#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "people.h"

/*
 * Customer类
 * 继承自People类，抽象顾客
*/

class Customer : public People
{
private:
    int table_number;       //顾客所选餐桌号

public:
    //构造函数
    Customer(const string &id="", const string &name="", const string &password="");
    //基本功能
    void setTableNumber(int number);     //选择餐桌
    int getTableNumber();

};

#endif // CUSTOMER_H
