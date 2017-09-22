#ifndef COOKVIEW_H
#define COOKVIEW_H

#include "headfile.h"
#include "cook.h"


namespace Ui {
class CookView;
}

class CookView : public QDialog
{
    Q_OBJECT

public:
    explicit CookView(QWidget *parent = 0, Cook *cook = NULL);
    ~CookView();

private slots:
    void get_all_mission_list();        //获取全部任务内容
    void get_my_mission_list();         //获取我的任务内容
    void get_mission_btn_clicked();     //认领菜品
    void begin_mission_btn_clicked();   //开始做菜
    void finish_mission_btn_clicked();  //完成菜品
    void quit_btn_clicked();            //退出

private:
    Ui::CookView *ui;
    Cook *cook;         //厨师对象

    int my_mission_row;
    int my_mission_row_now;
    int all_mission_row;
    int all_mission_row_now;
    QString dish_name;
    int num;
    QString remark;
    int table_number;

    QString my_dish_name;
    int my_num;
    QString my_remark;
    int my_table_number;

    int i;  //用于完成菜品

};

#endif // COOKVIEW_H
