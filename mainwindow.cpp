#include "mainwindow.h"

extern QVector<Table> tableVector;
extern QList<Waiter> waiterList;
extern QList<Customer> customerList;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->drawMain();
    MainData m;
    m.dataIn();
    regist_view = new Regist(this);

    //connect
    connect(login_btn,SIGNAL(clicked()),this,SLOT(login_btn_clicked()));         //按下登录按钮
    connect(regist_btn,SIGNAL(clicked()),this,SLOT(regist_btn_clicked()));       //按下注册按钮
    connect(identity_box,SIGNAL(activated(int)),this,SLOT(picture_show()));      //身份图标
    connect(forgot_btn,SIGNAL(clicked()),this,SLOT(forgot_btn_clicked()));       //按下忘记密码
}

MainWindow::~MainWindow()
{
    delete pLayout;
}


//绘制主界面
void MainWindow::drawMain()
{
    //设置界面尺寸及标题
    setMinimumSize(1000,700);
    setMaximumSize(1000,700);
    setWindowTitle(tr("餐厅服务管理系统"));
    this->setStyleSheet("QMainWindow{border-image:url(:/img/background.jpg)}");

    //设置字体
    font1.setBold(true);
    font1.setPointSize(13);
    font2.setPointSize(10);
    font3.setBold(true);
    font3.setPointSize(45);
    font4.setUnderline(true);

    //设置标签
    title_label = new QLabel("餐厅服务管理系统",this);
    title_label->setFont(font3);
    title_label->setGeometry(200,10,620,100);

    user_label = new QLabel(this);
    user_label->setText(tr("*账号*"));
    user_label->setFont(font1);
    user_label->setFixedSize(70,50);

    pass_label = new QLabel(this);
    pass_label->setText(tr("*密码*"));
    pass_label->setFont(font1);
    pass_label->setFixedSize(70,50);

    identity_label = new QLabel(this);
    identity_label->setText(tr("*身份*"));
    identity_label->setFont(font1);
    identity_label->setFixedSize(70,50);

    //设置行编辑器
    user_edit = new QLineEdit(this);
    user_edit->setPlaceholderText(tr("手机号"));
    user_edit->setFont(font2);
    user_edit->setFixedSize(180,50);

    password_edit = new QLineEdit(this);
    password_edit->setFont(font2);
    password_edit->setPlaceholderText(tr("6位数字或字母"));
    password_edit->setEchoMode(QLineEdit::Password);
    password_edit->setMaxLength(6);
    password_edit->setFixedSize(180,50);


    //设置按钮
    login_btn = new QPushButton("登录",this);
    login_btn->setFixedHeight(60);

    regist_btn = new QPushButton("注册",this);
    regist_btn->setFixedHeight(60);

    forgot_btn = new QPushButton("忘记密码",this);
    forgot_btn->setGeometry(780,260,70,40);
    forgot_btn->setFont(font4);
    forgot_btn->setFlat(false);

    QIcon help_icon(":/img/question.png");
    help_btn = new QPushButton("帮助",this);
    help_btn->setFont(font1);
    help_btn->setIcon(help_icon);
    help_btn->setIconSize(QSize(50,50));
    help_btn->setFlat(true);
    help_btn->setGeometry(860,530,140,100);

    QIcon phone_icon(":/img/phone.png");
    phone_btn = new QPushButton("800-800-8880",this);
    phone_btn->setFont(font1);
    phone_btn->setIcon(phone_icon);
    phone_btn->setIconSize(QSize(50,50));
    phone_btn->setFlat(true);
    phone_btn->setGeometry(600,530,250,100);



    //身份选择下拉框
    identity_box = new QComboBox(this);
    identity_box->setFont(font2);
    identity_box->addItem(QWidget::tr("顾客"));
    identity_box->addItem(QWidget::tr("服务员"));
    identity_box->addItem(QWidget::tr("厨师"));
    identity_box->addItem(QWidget::tr("经理"));
    identity_box->addItem(QWidget::tr("管理员"));
    identity_box->setFixedSize(90,40);

    customer_pic = new QLabel(this);
    customer_pic->setFixedSize(150,200);
    customer_pic->setStyleSheet("QWidget{border-image:url(:/img/customer.png)}");
    waiter_pic = new QLabel(this);
    waiter_pic->setFixedSize(150,200);
    waiter_pic->setStyleSheet("QWidget{border-image:url(:/img/waiter.png)}");
    waiter_pic->hide();
    cook_pic = new QLabel(this);
    cook_pic->setFixedSize(150,200);
    cook_pic->setStyleSheet("QWidget{border-image:url(:/img/cook.png)}");
    cook_pic->hide();
    manager_pic = new QLabel(this);
    manager_pic->setFixedSize(150,200);
    manager_pic->setStyleSheet("QWidget{border-image:url(:/img/manager.png)}");
    manager_pic->hide();
    administrator_pic = new QLabel(this);
    administrator_pic->setFixedSize(150,200);
    administrator_pic->setStyleSheet("QWidget{border-image:url(:/img/administrator.png)}");
    administrator_pic->hide();

    designLayout();
}


//设置布局
void MainWindow::designLayout()
{
    welcome = new QWidget(this);
    welcome->setMinimumSize(500,300);
    welcome->setMaximumSize(500,300);
    pLayout = new QGridLayout();
    pLayout->addWidget(identity_label,0,0);
    pLayout->addWidget(identity_box,0,2);
    pLayout->addWidget(waiter_pic,1,0);
    pLayout->addWidget(customer_pic,1,0);
    pLayout->addWidget(cook_pic,1,0);
    pLayout->addWidget(manager_pic,1,0);
    pLayout->addWidget(administrator_pic,1,0);
    pLayout->addWidget(user_label,0,3);
    pLayout->addWidget(pass_label,1,3);
    pLayout->addWidget(user_edit,0,4,1,2);
    pLayout->addWidget(password_edit,1,4,1,2);
    pLayout->addWidget(login_btn,3,3);
    pLayout->addWidget(regist_btn,3,5);
    pLayout->setHorizontalSpacing(20);
    pLayout->setVerticalSpacing(20);
    pLayout->setContentsMargins(10,10,10,10);
    welcome->setLayout(pLayout);
    welcome->setGeometry(250,130,350,100);
}

void MainWindow::hideAll()
{
    customer_pic->hide();
    waiter_pic->hide();
    cook_pic->hide();
    manager_pic->hide();
    administrator_pic->hide();
}

//检索账户信息
bool MainWindow::getUserInfo()
{
    bool matchFlag = false;
    //获取输入的信息
    QString id = user_edit->text();

    //利用数据库检索账号(id)
    QSqlQuery query;
    QString tempstring = "select * from people where id = ";
    tempstring += "";
    tempstring += id;
    tempstring += "";
    if(!query.exec(tempstring))
    {
        qDebug() << query.lastError();
        matchFlag = false;
    }
    else
    {
        query.next();
        user_id = query.value(0).toString();
        user_name = query.value(1).toString();
        user_pass = query.value(2).toString();
        user_identity = query.value(3).toString();
    }
    //判断是否匹配
    if(user_id == user_edit->text() && user_pass == password_edit->text()
            && user_identity == identity_box->currentText())
        matchFlag = true;
    return matchFlag;

}

/*槽函数*/

//登录按钮
void MainWindow::login_btn_clicked()
{
    //根据账号和密码在账户信息数据库中检索，如果检索成功则登录成功。
    if(getUserInfo() == true)
    {
        //利用账号从数据库中找到全部信息，分别构建对象，进入各自界面
        if(user_identity == "顾客")
        {
            Customer *customer1 = new Customer(user_id.toStdString(), user_name.toStdString(),
                                               user_pass.toStdString());
            int i=0;
            for(i=0;i<customerList.length();i++)
            {
                if(customerList[i].getId()==user_id.toStdString())
                {
                    customer1 = &customerList[i];
                    break;
                }
            }
            if(i==customerList.length())
            {
                customerList.append(*customer1);
            }
            table_view = new TableView(this, customer1);
            table_view->show();
        }

        if(user_identity == "服务员")
        {
            Waiter *waiter1 =new Waiter(user_id.toStdString(), user_name.toStdString(),
                                        user_pass.toStdString());
            int i=0;
            for(i=0;i<waiterList.length();i++)
            {
                //如果该账户已经在waiterList中
                if(waiterList[i].getId()==user_id.toStdString())
                {
                    waiter1 = &waiterList[i];
                    break;
                }
            }
            //如果不在waiterList中
            if(i==waiterList.length())
            {
                waiterList.append(*waiter1);
            }
            table_view = new TableView(this, NULL, waiter1, user_identity.toStdString());
            table_view->show();
        }

        if(user_identity == "厨师")
        {
            Cook *cook1 = new Cook(user_id.toStdString(), user_name.toStdString(),
                                   user_pass.toStdString());
            cook_view = new CookView(this,cook1);
            cook_view->show();
        }

        if(user_identity == "经理")
        {
            ManagerView *manager = new ManagerView(this);
            manager->show();
        }

        if(user_identity == "管理员")
        {
            Administrator *administrator1 = new Administrator(this);
            administrator1->show();
        }
        user_edit->clear();
        password_edit->clear();
        user_edit->setFocus();
    }
    else
    {
        QMessageBox::warning(this,tr("Warninig"),
                             tr("user name or password error!"),
                             QMessageBox::Yes);
        user_edit->clear();
        password_edit->clear();
        user_edit->setFocus();
    }
}

//注册按钮
void MainWindow::regist_btn_clicked()
{
    regist_view->show();
}

//切换图片
void MainWindow::picture_show()
{
    int k=identity_box->currentIndex();
    switch(k)
    {
    case 0:
        hideAll();
        customer_pic->show();
        break;
    case 1:
        hideAll();
        waiter_pic->show();
        break;
    case 2:
        hideAll();
        cook_pic->show();
        break;
    case 3:
        hideAll();
        manager_pic->show();
        break;
    case 4:
        hideAll();
        administrator_pic->show();
        break;
    }
}

void MainWindow::forgot_btn_clicked()
{
    forgot_view = new Forgot(this);
    forgot_view->show();
}
