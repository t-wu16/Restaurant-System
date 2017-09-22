#include "bill.h"
//构造函数
Bill::Bill(const string& dish_name, int num, int price,
           const string& cook_id, const string& cook_name):
    dish_name(dish_name), cook_id(cook_id), cook_name(cook_name)
{
    this->num = num;
    this->price = price;
}

//基本接口
const string& Bill::getDishName() const
{
    return dish_name;
}

int Bill::getNum() const
{
    return num;
}

int Bill::getPrice() const
{
    return price;
}

const string& Bill::getCookId() const
{
    return cook_id;
}

const string& Bill::getCookName() const
{
    return cook_name;
}
