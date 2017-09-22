#include "forgot.h"
#include "ui_forgot.h"

Forgot::Forgot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Forgot)
{
    ui->setupUi(this);
    this->setStyleSheet("QDialog{border-image:url(:/img/background2.jpg)}");
    ui->label_4->hide();
    ui->captcha->hide();
    ui->get_btn_2->hide();
    ui->get_btn_3->hide();
}

Forgot::~Forgot()
{
    delete ui;
}

/*槽函数*/

//获取验证码
void Forgot::on_get_btn_clicked()
{
    QString id = ui->id_text->text();
    //利用数据库检索账号(id)
    QSqlQuery query;
    QString tempstring = "select * from people where id = ";
    tempstring += "";
    tempstring += id;
    tempstring += "";
    if(!query.exec(tempstring))
    {
        qDebug() << query.lastError();
    }
    query.next();
    password = query.value(2).toString();
    if(query.value(0).toString()=="")
    {
        QMessageBox::information(this,"注意","您的用户名不存在",QMessageBox::Yes);
    }
    else
    {
        QMessageBox::information(this,"账户验证","我们已向您的手机发送验证码",QMessageBox::Yes);
        ui->label_4->show();
        ui->captcha->show();
        ui->get_btn_2->show();
    }
}

//获取密码
void Forgot::on_get_btn_2_clicked()
{
    if(ui->captcha->text() == "456789")
    {
        ui->get_btn_3->setText(password);
        ui->get_btn_3->show();
    }
}

//隐藏界面
void Forgot::on_get_btn_3_clicked()
{
    this->hide();
}
