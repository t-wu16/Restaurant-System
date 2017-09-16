#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <headfile.h>
#include "table.h"
#include "customerview.h"
#include "waiterview.h"

class WaiterView;
namespace Ui {
class TableView;
}
class CustomerView;
class TableView : public QDialog
{
    Q_OBJECT

public:
    explicit TableView(QWidget *parent = 0, Customer *customer = NULL, Waiter *waiter = NULL,
                       const string &identity = "顾客");
    ~TableView();
    void initTable();
    Table* getTable();
    void hideEdit();
    void foolmethod();
    QLineEdit *table_edit;          //输入餐桌号，设为公有，便于WaiterView访问。

public slots:
    void on_choose_table_clicked();
    void on_serve_table_clicked();

private:
    Ui::TableView *ui;
    QFont font1;
    QFont font2;
    QPushButton *choose_table;   //开始点菜
    QPushButton *serve_table;    //开始服务

    Table *table;               //16个餐桌
    Customer *customer;
    CustomerView *customer_view;
    Waiter *waiter;
    WaiterView *waiter_view;

    string identity;             //身份字符串
};

#endif // TABLEVIEW_H
