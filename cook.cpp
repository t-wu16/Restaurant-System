#include "cook.h"
extern QVector<Table> tableVector;
extern QList<OrderCuisine> orderList;
extern QList<Bill> billList;

//构造函数
Cook::Cook(const std::string &id, const std::string &name, const std::string &password):
    People(id, name, password)
{
    for(iter=tableVector.begin(); iter!=tableVector.end();iter++)
    {
        if(iter->getState() == orderfinish)
        {
            //获取该餐桌的每一道菜
            map<Cuisine,int>::iterator cuisine_iter;
            for(cuisine_iter=iter->getFoodPlate().begin();cuisine_iter!=iter->getFoodPlate().end();
                cuisine_iter++)
            {
                if(cuisine_iter->first.getState() == "等候")
                {
                    CookMission mission(cuisine_iter->first.getName(),cuisine_iter->second,
                                        cuisine_iter->first.getRemark(),iter->getTableNumber()+1);
                    all_mission_list << mission;        //加入到所有任务的列表中
                }
            }
        }
    }

}

/*重要功能*/

//添加我的任务
void Cook::addMission(const CookMission &new_mission)
{
    my_mission_list << new_mission;
    for(int i=0;i<orderList.length();i++)
    {
        if(new_mission.getDishName() == orderList[i].getName()
           && new_mission.getTableNumber() == orderList[i].getTableNumber()+1)
        {
            orderList[i].setState("准备");
            Bill bill(new_mission.getDishName(), new_mission.getNum(),
                      orderList[i].getPrice(), my_id, my_name);
            billList << bill;
            break;
        }
    }
}

//删除一项任务
void Cook::deleteMission(const CookMission &delete_mission)
{
    for(mission_iter=all_mission_list.begin();mission_iter!=all_mission_list.end();mission_iter++)
    {
        if(mission_iter->getDishName()==delete_mission.getDishName()
           && mission_iter->getRemark()==delete_mission.getRemark())
        {
            all_mission_list.erase(mission_iter);
            break;
        }
    }
}

//获得全部任务列表
QList<CookMission>& Cook::getAllMission()
{
    return all_mission_list;
}

//获得我的任务列表
QList<CookMission>& Cook::getMyMission()
{
    return my_mission_list;
}
