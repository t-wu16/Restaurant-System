#ifndef COOKMISSION_H
#define COOKMISSION_H
#include <string>
using std::string;

/*
 * 厨师任务类
 * 用来用来记录厨师所能获得的信息
*/

class CookMission
{
private:
    string dish_name;        //菜名
    int num;                 //数量
    string remark;           //备注
    int table_number;        //桌号
public:
    CookMission(const string &dish_name="", int num=0, const string &remark="", int table_number=0);
    //基本接口
    const string& getDishName() const;
    const string& getRemark() const;
    int getNum() const;
    int getTableNumber() const;

};

#endif // COOKMISSION_H
