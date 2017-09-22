#include "waiter.h"

//构造函数
Waiter::Waiter(const std::string &id, const std::string &name, const std::string &password,
               int comment_times, int comment_score):
    People(id,name,password)
{
    for(int j=0; j<3; j++)
    {
        w_table_number[j] = -1;
    }
    serve_num = 0;
    this->comment_times = comment_times;
    this->comment_score = comment_score;
}

//基本接口
void Waiter::setTableNumber(int current_table, int table_i)
{
    w_table_number[table_i] = current_table;
    serve_num++;
}

void Waiter::setServeNum(int i)
{
    if(i==1)
    {
        serve_num++;
    }
    if(i==-1)
    {
        serve_num--;
    }
}

void Waiter::addCommentTimes()
{
    comment_times++;
}

void Waiter::addCommentScore(int score)
{
    comment_score += score;
}

int Waiter::getTableNumber(int table_i)
{
    return w_table_number[table_i];
}

int Waiter::getServeNum()
{
    return serve_num;
}

int Waiter::getCommentTimes()
{
    return comment_times;
}

int Waiter::getCommentScore()
{
    return comment_score;
}


