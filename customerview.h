#ifndef CUSTOMERVIEW_H
#define CUSTOMERVIEW_H

#include "headfile.h"
#include "customer.h"
#include "table.h"
#include "serviceview.h"
#include "maindata.h"

/*
 * 顾客点菜界面
 * 外接顾客服务界面
*/

class ServiceView;      // 前向引用声明，作用：能够在ServiceView中回到该界面
class CustomerView : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerView(QWidget *parent = 0, Customer *customer = NULL, Table *table = NULL);
    ~CustomerView();
    Customer* getCustomer();

private:
    void drawOrder();               //绘制点菜界面
    void drawNumber();              //绘制数量选择框

private slots:
    void get_menu_item();           //获取菜单行内容
    void get_plate_item();          //获取托盘行内容
    void add_btn_clicked();         //按下添加按钮
    void delete_btn_clicked();      //按下删除按钮
    void number_btn_clicked();      //选择数量
    void cancle_btn_clicked();      //取消选择
    void finish_btn_clicked();      //下单按钮

private:
    /*界面成员*/
    QFont font1;
    QFont font2;
    QPushButton *add_btn;           //添加按钮
    QPushButton *delete_btn;        //去除按钮
    QPushButton *finish_btn;        //下单按钮
    QLabel *menu_label;             //菜单
    QLabel *plate_label;            //食物托盘
    QLabel *id_label;               //顾客账号
    QLabel *id_text;
    QLabel *name_label;             //顾客姓名
    QLabel *name_text;
    QTableView *menu_list;          //菜单视图
    QTableWidget *plate_list;       //点菜列表

    QLabel *number_label;           //数量
    QLineEdit *number_edit;
    QLabel *remark_label;           //备注
    QLineEdit *remark_edit;
    QPushButton *confirm_btn;
    QPushButton *cancle_btn;
    QDialog *number;                //数量对话框
    QGridLayout *nLayout;           //水平布局

    ServiceView *service_view;      //顾客服务界面


    /*逻辑成员*/
    Customer *customer;             //顾客指针
    Table *table;                   //顾客所选餐桌指针
    QSqlTableModel *model;          //菜单模型

    //用于获取菜单内容
    int menu_row;
    int menu_price;
    QString menu_name;
    QString menu_id;
    QString menu_type;

    //用于获取托盘内容
    int plate_row;
    int plate_row_now;
    int plate_number;
    int plate_price;
    QString plate_name;
    QString plate_id;
    QString plate_type;

    int dish_number;                //数量
    string remark;                  //备注

    MainData m;

};

#endif // CUSTOMERVIEW_H
