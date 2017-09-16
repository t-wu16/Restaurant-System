#ifndef SERVICEVIEW_H
#define SERVICEVIEW_H

#include <QDialog>
#include "headfile.h"
#include "customerview.h"
#include "tableview.h"


namespace Ui {
class ServiceView;
}

class ServiceView : public QDialog
{
    Q_OBJECT

public:
    explicit ServiceView(QWidget *parent = 0, Customer *customer = NULL, Table *table = NULL);
    ~ServiceView();
    void drawCheck();       //绘制结算单

public slots:
    void addDishes_clicked();
    void urgeDishes_clicked();
    void addWater_clicked();
    void checkOut_clicked();
    void getTable_clicked();
    void callWaiter_clicked();
    void confirm_clicked();

private:
    Ui::ServiceView *ui;
    Customer *customer;
    Table *table;

    QFont font1;
    QFont font2;
    QDialog *check_out_dialog;      //结账对话框
    QTableWidget *final_list;       //结账列表
    QLabel *title;                  //结账标题
    QLabel *all_price_label;        //合计标签
    QLineEdit *all_price_edit;      //合计显示
    QPushButton *check_btn;         //确认结账
    QTableWidget *table_dishes;     //菜品进度
};

#endif // SERVICEVIEW_H
