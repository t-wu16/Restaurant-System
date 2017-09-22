#ifndef WAITER_H
#define WAITER_H

#include "people.h"
/*
 * Waiter类
 * 继承自People类，抽象服务员
*/

class Waiter : public People
{
private:
    int w_table_number[3];              //所服务的餐桌号数组
    int serve_num;                      //服务员服务的餐桌数量
    int comment_times;                  //评价次数
    int comment_score;                  //评价总分
public:
    //构造函数
    Waiter(const string &id, const string &name, const string &password,
           int comment_times=0, int comment_score=0);
    //基本接口
    void setTableNumber(int current_table, int table_i);     //认领餐桌
    void setServeNum(int i);                                 //设置服务数量
    void addCommentTimes();
    void addCommentScore(int score);
    int getTableNumber(int table_i);                         //返回服务的第i个餐桌的餐桌号
    int getServeNum();                                       //返回服务数量
    int getCommentTimes();
    int getCommentScore();

};

#endif // WAITER_H
