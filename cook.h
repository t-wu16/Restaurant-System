#ifndef COOK_H
#define COOK_H

#include "people.h"
#include "table.h"
/*
 * Cook类
 * 继承自People类,抽象厨师
*/

class Cook : public People
{
private:
    string dish_name;       //要做的菜
    string cook_state;      //厨师的状态（free,busy）
    Table *table;           //餐桌(类的组合)
public:
    Cook(const string &id, const string &name, const string &password, const string &state="free");
    //基本接口
    void setDishName(const string &dish_choose);
    const string& getDishName() const ;
    void setCookState(const string &state);
    const string& getState() const;
    Table* getTable();
    //基本功能
    void initTable();       //导入实时餐桌信息
    void getMission(const string &dish_choose);
    void finishMission();
};

#endif // COOK_H
