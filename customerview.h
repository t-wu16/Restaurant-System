#ifndef CUSTOMERVIEW_H
#define CUSTOMERVIEW_H

#include <headfile.h>
#include "customer.h"
#include "table.h"
#include "serviceview.h"

class ServiceView;
class CustomerView : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerView( QWidget *parent = 0, Customer *customer = NULL, Table *table = NULL);
    ~CustomerView();
    Customer* getCustomer();
    void drawOrder();               //绘制点菜界面
    void drawNumber();              //绘制数量选择框


public slots:
    void get_menu_item();           //获取菜单行内容
    void get_plate_item();          //获取托盘行内容
    void add_btn_clicked();         //按下添加按钮
    void delete_btn_clicked();      //按下取消按钮
    void number_btn_clicked();      //选择数量
    void finish_btn_clicked();      //下单按钮

private:
    //界面成员
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
    QTableWidget *menu_list;        //菜单列表
    QTableWidget *plate_list;       //点菜列表

    QLabel *number_label;           //选择数量
    QLineEdit *number_edit;         //选择数量
    QLabel *remark_label;
    QLineEdit *remark_edit;
    QPushButton *confirm_btn;
    QPushButton *cancle_btn;
    QWidget *number;                //数量对话框
    QGridLayout *nLayout;           //水平布局

    ServiceView *service_view;


    //逻辑成员
    Customer *customer;             //顾客指针
    Table *table;                   //顾客所选餐桌指针

    int dish_number;
    int price;
    string name;
    string id;
    string type;
    string remark;

    int menu_row;                   //用于创建界面项
    QString menu_name;
    QString menu_id;
    QString menu_type;

    int plate_row;
    int plate_row_now;
    int plate_number;
    QString plate_name;
    QString plate_id;
    QString plate_type;

};

#endif // CUSTOMERVIEW_H
