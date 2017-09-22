#include "ordercuisine.h"

//构造函数
OrderCuisine::OrderCuisine(const string &id, const string &name,const int price,const string &type,
                           const string &remark,const string &state,int num,int table_number):
    Cuisine(id,name,price,type,remark,state), num(num), table_number(table_number)
{

}

//基本接口
void OrderCuisine::setNum(int num)
{
    this->num = num;
}

void OrderCuisine::setTableNumber(int table_number)
{
    this->table_number = table_number;
}

int OrderCuisine::getNum()
{
    return num;
}

int OrderCuisine::getTableNumber()
{
    return table_number;
}
