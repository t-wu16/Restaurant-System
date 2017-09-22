#include "customer.h"
//构造函数
Customer::Customer(const string &id, const string &name, const string &password, int table_number, int credit) :
    People(id,name,password)
{
    this->table_number = table_number;
    this->credit = credit;
}

//基本接口
void Customer::setTableNumber(int number)
{
    table_number = number;

}

void Customer::addCredit(int money)
{
    credit += money;
}

int Customer::getTableNumber()
{
    return table_number;
}

int Customer::getCredit()
{
    return credit;
}
