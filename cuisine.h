#ifndef CUISINE_H
#define CUISINE_H
#include "object.h"

/*
 * Cuisine类
 * 继承自Object类，抽象菜品
*/
class Cuisine:public Object
{
protected:
    int unit_price;     //菜品单价
    string food_type;   //菜品类型
    string remark;      //菜品备注
    string state;       //菜的状态（未做wait，正做doing，已上ready）
public:
    //构造函数
    Cuisine(const string &id="", const string &name="",const int price=0,
            const string &type="",const string &remark="",const string &state="wait");
    //基本接口
    void setPrice(int price);
    void setType(const string &type);
    void setRemark(const string &remark);
    void setState(const string &state);

    int getPrice() const;
    const string& getType() const;
    const string& getState() const;
    const string& getRemark() const;




};

#endif // CUISINE_H
