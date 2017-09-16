#ifndef REGIST_H
#define REGIST_H

#include "headfile.h"
class Regist : public QDialog
{
    Q_OBJECT

public:
    explicit Regist(QWidget *parent = 0);
    ~Regist();
    void drawRegist();

public  slots:
    void real_regist_btn_clicked();      //按下取消按钮
private:
    QFont font1;
    QFont font2;
    QFont font3;
    QPushButton *real_regist_btn;   //注册按钮
    QPushButton *cancle_btn;        //取消按钮
    QLabel *title_label;            //标题标签
    QLabel *name_label;             //姓名标签
    QLabel *id_label;               //账号标签
    QLabel *pass_first_label;       //输入密码标签
    QLabel *pass_confirm_label;     //确认密码标签
    QLineEdit *name_edit;           //姓名输入框
    QLineEdit *id_edit;             //账号输入框
    QLineEdit *pass_first_edit;     //密码输入框
    QLineEdit *pass_confirm_edit;   //确认密码输入框
    QWidget *regist;
    QGridLayout *rLayout;
};

#endif // REGIST_H
