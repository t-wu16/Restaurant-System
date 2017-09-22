#ifndef SERVICEVIEW_H
#define SERVICEVIEW_H

#include "headfile.h"
#include "customerview.h"
#include "tableview.h"
#include "comment.h"
#include "maindata.h"
/*
 * 顾客服务界面
*/

namespace Ui {
class ServiceView;
}

class ServiceView : public QDialog
{
    Q_OBJECT

public:
    explicit ServiceView(QWidget *parent = 0, Customer *customer = NULL, Table *table = NULL);
    ~ServiceView();
    void drawCheck();               //绘制结算单

private slots:
    void addDishes_clicked();       //加菜
    void urgeDishes_clicked();      //催菜
    void addWater_clicked();        //加水
    void checkOut_clicked();        //结账
    void getTable_clicked();        //获取餐桌信息
    void callWaiter_clicked();      //叫服务员
    void credit_btn_clicked();      //查看积分
    void confirm_clicked();         //确认结账
    void quit_btn_clicked();        //退出登录
    void credit_hide_clicked();     //积分按钮
    void cancle_btn_clicked();      //取消结账

private:
    Ui::ServiceView *ui;
    Customer *customer;
    Table *table;

    QFont font1;
    QFont font2;
    QTableWidget *table_dishes;     //菜品进度
    QDialog *check_out_dialog;      //结账对话框
    QTableWidget *final_list;       //结账列表
    QLabel *title;                  //结账标题
    QLabel *all_price_label;        //合计标签
    QLineEdit *all_price_edit;      //合计显示
    QPushButton *check_btn;         //确认结账
    QPushButton *cancle_btn;        //取消结账
    QPushButton *credit_show;       //积分显示

};

#endif // SERVICEVIEW_H
