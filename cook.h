#ifndef COOK_H
#define COOK_H

#include "table.h"
#include "people.h"
#include "cookmission.h"
#include "ordercuisine.h"
#include "maindata.h"
/*
 * Cook类
 * 继承自People类,抽象厨师
*/
class Cook : public People
{
private:
    //...姓名，账号, 密码

    QList<CookMission> all_mission_list;    //全部任务列表
    QList<CookMission> my_mission_list;     //自身任务列表
    QVector<Table>::iterator iter;
    QList<CookMission>::iterator mission_iter;

public:
    Cook(const string &id="", const string &name="", const string &password="");
    //重要功能
    void addMission(const CookMission &new_mission);      //添加任务
    void deleteMission(const CookMission &delete_mission);//删除全部任务列表中的一项
    QList<CookMission>& getMyMission();                   //返回我的任务
    QList<CookMission>& getAllMission();                  //返回全部任务
};

#endif // COOK_H
