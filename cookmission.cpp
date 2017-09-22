#include "cookmission.h"
//构造函数
CookMission::CookMission(const string &dish_name, int num, const string &remark, int table_number) :
    dish_name(dish_name), remark(remark)
{
    this->num = num;
    this->table_number =table_number;
}

//基本接口
const string& CookMission::getDishName() const
{
    return dish_name;
}

const string& CookMission::getRemark() const
{
    return remark;
}

int CookMission::getNum() const
{
    return num;
}

int CookMission::getTableNumber() const
{
    return table_number;
}
