#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include "headfile.h"
#include "table.h"
#include "customerview.h"
#include "waiterview.h"
#include "maindata.h"
/*
 * 选桌界面
 * 包括顾客选桌和服务员选桌，外接顾客点菜界面和服务员服务界面
*/

//前向引用声明：保证顾客和服务员能够重新回到该界面进行查看。
class WaiterView;
class CustomerView;

namespace Ui {
class TableView;
}
class TableView : public QDialog
{
    Q_OBJECT

public:
    explicit TableView(QWidget *parent = 0, Customer *customer = NULL, Waiter *waiter = NULL,
                       const string &identity = "顾客");
    ~TableView();
    void initTable();                //设置一些初始数据
    Table* getTable();
    void hideEdit();
    void setTableBackground();
    QLineEdit *table_edit;           //输入餐桌号，设为公有，便于WaiterView访问。

private slots:
    void on_choose_table_clicked();
    void on_serve_table_clicked();
    void on_quit_btn_clicked();

private:
    Ui::TableView *ui;
    QFont font1;
    QFont font2;
    QPushButton *choose_table;   //开始点菜
    QPushButton *serve_table;    //开始服务
    QButtonGroup *button_group;  //按钮组

    Table *table;                //16个餐桌
    Customer *customer;
    CustomerView *customer_view;
    Waiter *waiter;
    WaiterView *waiter_view;

    string identity;             //身份字符串
};

#endif // TABLEVIEW_H
