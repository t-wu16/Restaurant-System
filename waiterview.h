#ifndef WAITERVIEW_H
#define WAITERVIEW_H

#include "headfile.h"
#include "waiter.h"
#include "tableview.h"
#include "maindata.h"
namespace Ui {
class WaiterView;
}
class WaiterView : public QDialog
{
    Q_OBJECT

public:
    explicit WaiterView(QWidget *parent = 0, Waiter *waiter = NULL, Table *table1 = NULL);
    ~WaiterView();

private slots:
    void service_begin_clicked();       //开始服务
    void serve_end_clicked();           //结束服务
    void get_table_clicked();           //获取餐桌
    void btn_clicked(int i);

private:
    Ui::WaiterView *ui;
    QButtonGroup *my_button;        //按钮组
    Waiter *waiter;
    static Table *table[3];                //服务餐桌
    static int table_number;        //服务数量

};

#endif // WAITERVIEW_H
