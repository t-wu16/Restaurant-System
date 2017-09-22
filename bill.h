#ifndef BILL_H
#define BILL_H

#include "cafeteria.h"

class Bill
{
private:
    string dish_name;   //菜名
    int num;            //数量
    int price;          //单价
    string cook_id;     //厨师账号
    string cook_name;   //厨师姓名
public:
    Bill(const string& dish_name="", int num=0, int price=0,
         const string& cook_id="", const string& cook_name="");

    const string& getDishName() const;
    int getNum() const;
    int getPrice() const;
    const string& getCookId() const;
    const string& getCookName() const;
};

#endif // BILL_H
