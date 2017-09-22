#include "table.h"

//构造函数
Table::Table(const string &customer_id, const string &waiter_id, int table_number,
             State state, bool finish_order, bool urge_dishes, bool add_water, bool check_out, bool call_waiter):
    customer_id(customer_id),waiter_id(waiter_id),table_number(table_number),state(state)
{
    this->finish_order = finish_order;
    this->urge_dishes = urge_dishes;
    this->add_water = add_water;
    this->check_out = check_out;
    this->call_waiter = call_waiter;
}

//基本接口
void Table::setCustomerId(const std::string &customer_id)
{
    this->customer_id = customer_id;
}

void Table::setWaiterId(const std::string &waiter_id)
{
    this->waiter_id = waiter_id;
}

void Table::setTableNumber(int table_number)
{
    this->table_number = table_number;
}

void Table::setState(State state)
{
    this->state = state;
}

void Table::setFoodPlate(const map<Cuisine, int> &food_ordered)
{
    food_plate = food_ordered;
}

const string& Table::getCustomerId() const
{
    return customer_id;
}

const string& Table::getWaiterId() const
{
    return waiter_id;
}

int Table::getTableNumber()
{
    return table_number;
}

map<Cuisine, int> &Table::getFoodPlate()
{
    return food_plate;
}

State Table::getState()
{
    return state;
}

bool Table::getFinishOrder()
{
    state = orderfinish;
    return finish_order;
}

bool Table::getUrgeDishes()
{
    return urge_dishes;
}

bool Table::getAddWater()
{
    return add_water;
}

bool Table::getCheckOut()
{
    return check_out;
}

bool Table::getCallWaiter()
{
    return call_waiter;
}


/*重要功能*/

//点菜
void Table::chooseFood(const Cuisine &food, int amount)
{
    //首先要检验该food是否已经被添加过
    auto my_food = food_plate.find(food);   //my_food为迭代器
    if(my_food != food_plate.end())         //如果被添加过了,则进行修改
    {
        my_food->second += amount;
        if(my_food->second == 0)
        {
            food_plate.erase(my_food);
        }
    }
    else if(amount > 0)                     //如果没被添加过，且amount大于0
    {
        food_plate.insert(std::make_pair(food,amount));     //添加新的一项
    }

}

//下单
void Table::orderFinish()
{
    state = orderfinish;
    finish_order = true;
}

//催菜
void Table::urgeDishes()
{
    urge_dishes = true;
}

//加水
void Table::addWater()
{
    add_water = true;
}

//叫服务员
void Table::callWaiter()
{
    call_waiter =  true;
}

//结账
int Table::checkOut()
{
    check_out = true;
    int all_consume = 0;
    map<Cuisine,int>::iterator iter;
    for(iter=food_plate.begin(); iter!=food_plate.end(); iter++)
    {
        all_consume += iter->first.getPrice() * iter->second;

    }
    return all_consume;
}

