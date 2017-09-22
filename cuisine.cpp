#include "cuisine.h"
//构造函数
Cuisine::Cuisine(const string &id, const string &name,int price, const string &type,
                 const string &remark, const string &state, int praise_num) :
    Object(id, name), unit_price(price), food_type(type), remark(remark), state(state)
{
    this->praise_num = praise_num;
}

//基本接口
void Cuisine::setPrice(int price)
{
    unit_price = price;
}

void Cuisine::setType(const string &type)
{
    food_type = type;
}

void Cuisine::setRemark(const string &remark)
{
    this->remark = remark;
}

void Cuisine::setState(const string &state)
{
    this->state = state;
}

void Cuisine::setPraise()
{
    praise_num++;
}

int Cuisine::getPrice() const
{
    return unit_price;
}

const std::string &Cuisine::getType() const
{
    return food_type;
}

const std::string &Cuisine::getRemark() const
{
    return remark;
}

const std::string &Cuisine::getState() const
{
    return state;
}

int Cuisine::getPraise() const
{
    return praise_num;
}

bool Cuisine::operator <(const Cuisine & food) const
{
    return my_id < food.my_id;
}
