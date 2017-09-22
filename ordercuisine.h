#ifndef ORDERCUISINE_H
#define ORDERCUISINE_H

#include "cuisine.h"

class OrderCuisine : public Cuisine
{
private:
    int num;            //数量
    int table_number;   //餐桌号
public:
    OrderCuisine(const string &id="", const string &name="",const int price=0,
                 const string &type="",const string &remark="",const string &state="等候",
                 int num=0,int table_number=0);
    void setNum(int num);
    void setTableNumber(int table_number);
    int getNum();
    int getTableNumber();

};

#endif // ORDERCUISINE_H
