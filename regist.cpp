#include "regist.h"

Regist::Regist(QWidget *parent) :
    QDialog(parent)
{
    drawRegist();

    //connect
    connect(cancle_btn,SIGNAL(clicked()),this,SLOT(close()));
    connect(real_regist_btn,SIGNAL(clicked()),this,SLOT(real_regist_btn_clicked()));

}

Regist::~Regist()
{
    delete rLayout;
}

//绘制注册界面
void Regist::drawRegist()
{
    setMinimumSize(1000,700);
    setMaximumSize(1000,700);
    setWindowTitle(tr("顾客注册"));
    this->setStyleSheet("QDialog{border-image:url(:/img/background.jpg)}");

    font1.setBold(true);
    font1.setPointSize(15);
    font2.setPointSize(10);
    font3.setBold(true);
    font3.setPointSize(30);

    title_label = new QLabel("账号注册",this);
    title_label->setFont(font3);
    title_label->setGeometry(400,10,620,100);

    real_regist_btn = new QPushButton("确定注册",this);
    real_regist_btn->setFixedHeight(60);
    cancle_btn = new QPushButton("取消注册",this);
    cancle_btn->setFixedHeight(60);

    name_label = new QLabel("*姓名*",this);
    name_label->setFont(font1);
    name_label->setFixedSize(90,60);

    id_label = new QLabel("*账号*",this);
    id_label->setFont(font1);
    id_label->setFixedSize(90,60);

    pass_first_label = new QLabel("输入密码",this);
    pass_first_label->setFont(font1);
    pass_first_label->setFixedSize(110,60);

    pass_confirm_label = new QLabel("确认密码",this);
    pass_confirm_label->setFont(font1);
    pass_confirm_label->setFixedSize(110,60);

    name_edit = new QLineEdit(this);
    name_edit->setFont(font2);
    name_edit->setFixedSize(180,60);

    id_edit = new QLineEdit(this);
    id_edit->setPlaceholderText(tr("您的手机号"));
    id_edit->setFont(font2);
    id_edit->setFixedSize(180,60);

    pass_first_edit = new QLineEdit(this);
    pass_first_edit->setPlaceholderText(tr("6位字母或数字"));
    pass_first_edit->setEchoMode(QLineEdit::Password);
    pass_first_edit->setMaxLength(6);
    pass_first_edit->setFont(font2);
    pass_first_edit->setFixedSize(180,60);

    pass_confirm_edit = new QLineEdit(this);
    pass_confirm_edit->setEchoMode(QLineEdit::Password);
    pass_confirm_edit->setMaxLength(6);
    pass_confirm_edit->setFont(font2);
    pass_confirm_edit->setFixedSize(180,60);

    regist = new QWidget(this);
    rLayout = new QGridLayout();

    rLayout->addWidget(id_label,0,0);
    rLayout->addWidget(name_label,1,0);
    rLayout->addWidget(pass_first_label,2,0);
    rLayout->addWidget(pass_confirm_label,3,0);
    rLayout->addWidget(id_edit,0,1);
    rLayout->addWidget(name_edit,1,1);
    rLayout->addWidget(pass_first_edit,2,1);
    rLayout->addWidget(pass_confirm_edit,3,1);
    rLayout->setHorizontalSpacing(30);
    rLayout->setVerticalSpacing(30);
    rLayout->setContentsMargins(10,10,10,10);
    regist->setLayout(rLayout);
    regist->setGeometry(320,80,350,400);

    real_regist_btn->setGeometry(310,550,93,71);
    cancle_btn->setGeometry(590,550,93,71);
}

/*槽函数*/

//确定注册
void Regist::real_regist_btn_clicked()
{
    if(name_edit->text() !="" && id_edit->text().length()==11              //如果满足注册条件
       && pass_first_edit->text().length()==6 && pass_confirm_edit->text()==pass_first_edit->text())
    {
         int ok = QMessageBox::information(this,tr("注册成功"),tr("恭喜您，成功注册账号！"),
                                  QMessageBox::Yes);
         if(ok == QMessageBox::Yes)
         {
             this->hide();
         }

         //将注册信息存入数据库
         QSqlQuery query;
         query.prepare("insert into people values(?,?,?,?)");
         QVariant id,name,password,identity;
         id = QVariant(id_edit->text());
         name = name_edit->text();
         password = pass_first_edit->text();
         identity = "管理员";
         query.addBindValue(id);
         query.addBindValue(name);
         query.addBindValue(password);
         query.addBindValue(identity);
         query.exec();
         if(!query.execBatch())
         {
             qDebug() << query.lastError();
         }
    }
}
