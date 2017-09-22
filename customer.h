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
    int credit;             //顾客积分

public:
    //构造函数
    Customer(const string &id="", const string &name="", const string &password="",
             int table_number=0, int credit = 0);
    //基本功能
    void setTableNumber(int number);     //选择餐桌
    void addCredit(int money);           //设置积分
    int getTableNumber();                //获取餐桌号
    int getCredit();                     //获取积分
};

#endif // CUSTOMER_H
