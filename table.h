#ifndef TABLE_H
#define TABLE_H
#include "cuisine.h"

/*
 * Table类
 * 是各个类之间沟通的媒介。
*/
class Table :public Object
{
private:
    string customer_id;             //顾客id
    string waiter_id;               //服务员id
    int table_number;               //餐桌号
    State state;                    //餐桌状态
    map<Cuisine,int> food_plate;    //食物托盘(菜品，数量)
    bool finish_order;              //是否下单
    bool urge_dishes;               //是否催菜
    bool add_water;                 //是否加水
    bool check_out;                 //是否结账
    bool call_waiter;               //是否叫服务员
public:
    //构造函数
    Table(const string &customer_id="", const string &waiter_id="",
          int table_number=0, State state=unoccupied, bool finish_order=0,
          bool urge_dishes=0, bool add_water=0, bool check_out=0, bool call_waiter=0);

    //基本接口
    void setCustomerId(const string &customer_id);
    void setWaiterId(const string &waiter_id);
    void setTableNumber(int table_number);
    void setState(State state);
    void setFoodPlate(const map<Cuisine,int> &food_ordered);

    const string& getCustomerId() const;
    const string& getWaiterId() const;
    int getTableNumber();
    State getState();
    map<Cuisine,int>& getFoodPlate();

    bool getFinishOrder();
    bool getUrgeDishes();
    bool getAddWater();
    bool getCheckOut();
    bool getCallWaiter();


    //重要功能
    void chooseFood(const Cuisine& food, int amount);       //点菜
    void orderFinish();                                     //下单
    void urgeDishes();                                      //催菜
    void addWater();                                        //加水
    int checkOut();                                         //结账
    void callWaiter();                                      //叫服务员
};

#endif // TABLE_H
