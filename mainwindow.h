#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "headfile.h"
#include "regist.h"
#include "tableview.h"
#include "customerview.h"
#include "waiterview.h"
#include "cookview.h"
#include "administrator.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initTable();
    void designLayout();          //设置布局
    void hideAll();               //隐藏所有图片
    void drawMain();              //绘制主界面


public slots:
    void login_btn_clicked();     //按下登录按钮
    void regist_btn_clicked();    //按下注册按钮
   // void forgot_btn_clicked();    //按下忘记按钮
    void picture_show();          //显示身份图片

private:
    QFont font1;                  //字体1
    QFont font2;                  //字体2
    QFont font3;                  //字体3
    QFont font4;                  //字体4
    QGridLayout *pLayout;         //格栅布局管理

    QComboBox *identity_box;       //身份下拉框

    QPushButton *login_btn;       //登录按钮
    QPushButton *regist_btn;      //注册按钮
    QPushButton *forgot_btn;      //忘记密码

    QLabel *title_label;          //标题标签
    QLabel *user_label;           //用户名标签
    QLabel *pass_label;           //密码标签
    QLabel *table_label;          //餐桌号标签
    QLabel *identity_label;       //身份标签

    QLabel *customer_pic;         //顾客图标
    QLabel *waiter_pic;           //服务员图标
    QLabel *cook_pic;             //厨师图标
    QLabel *manager_pic;          //经理图标
    QLabel *administrator_pic;    //管理员图标

    QLineEdit *user_edit;         //用户名输入框
    QLineEdit *password_edit;     //密码输入框
    QLineEdit *table_edit;        //餐桌号输入框

    QWidget *welcome;             //欢迎登录界面
    Regist *regist_view;          //注册界面
    TableView *table_view;        //餐桌界面
    CustomerView *customer_view;  //顾客界面
    WaiterView *waiter_view;      //服务员界面
    CookView *cook_view;          //初始界面

};

#endif // MAINWINDOW_H
