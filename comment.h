#ifndef COMMENT_H
#define COMMENT_H

#include <headfile.h>
#include "maindata.h"
#include "customer.h"
#include "table.h"

namespace Ui {
class Comment;
}

class Comment : public QDialog
{
    Q_OBJECT

public:
    explicit Comment(QWidget *parent = 0, Customer *customer = NULL, Table *table = NULL);
    ~Comment();

private slots:
    void praise_btn_clicked(int i);         //点击好评
    void waiter_comment_btn_clicked(int i); //评价服务员
    void finish_comment_btn_clicked();      //完成评价
private:
    Ui::Comment *ui;
    QDialog *comment_dialog;            //评价对话框
    QTableWidget *comment_list;         //评价列表
    QButtonGroup *praise_btn;           //好评按钮
    QPushButton *finish_comment_btn;    //结束服务按钮
    QButtonGroup *waiter_comment_btn;   //服务员评价按钮
    QLabel *waiter_label;               //服务员评价
    QLabel *title_label;                //标题

    Customer *customer;
    Table *table;
};

#endif // COMMENT_H
